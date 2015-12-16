/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "avmplus.h"
#include "MethodInfo.h"

#ifdef VMCFG_CDECL

#include "CdeclThunk.h"

#ifdef _MSC_VER
// squelch unreferenced parameter warnings
#pragma warning(disable : 4100) 
#define ALIGN_TO(NUM, DECL) __declspec(align(NUM)) DECL
#else // ndef _MSC_VER
#define ALIGN_TO(NUM, DECL) DECL __attribute__((aligned(NUM)))
#endif // ndef _MSC_VER

//#define CDECL_VERBOSE 1
namespace avmplus
{
    // stores arbitrary Avm values without allocation
    class AvmValue
    {
    private:
        enum { _tagBits = 3 };
        ALIGN_TO(16, double _d);
        Atom _a;

        double* dblPtr()
        {
            return &_d;
        }

        Atom dblAtom()
        {
            return kDoubleType | (Atom)dblPtr();
        }

    public:
        int kind()
        {
            return atomKind(_a);
        }

        Atom get(Toplevel* toplevel, Traits* t)
        {
            AvmCore* core = toplevel->core();

            BuiltinType bt = Traits::getBuiltinType(t);

            if ((bt == BUILTIN_any || bt == BUILTIN_object) && _a == dblAtom())
                _a = core->doubleToAtom(*dblPtr());

            // should not be in here if we want a void return type.
            AvmAssert(bt != BUILTIN_void);

            switch(bt)
            {
            case BUILTIN_any:
                return _a;
            case BUILTIN_int:
                return (Atom)AvmCore::integer(_a);
            case BUILTIN_uint:
                return (Atom)AvmCore::toUInt32(_a);
            case BUILTIN_boolean:
                return (Atom)AvmCore::boolean(_a);
            case BUILTIN_string:
                return (Atom)core->coerce_s(_a);
            case BUILTIN_namespace:
                if (atomKind(_a) == kNamespaceType)
                    return (Atom)core->atomToNamespace(_a);
                AvmAssert(AvmCore::isNullOrUndefined(_a));
                return nullNsAtom;
            case BUILTIN_object:
                return AvmCore::isNullOrUndefined(_a) ? nullObjectAtom : _a;
            default:
                AvmAssert(t != NUMBER_TYPE); // use getDouble
                return (Atom)AvmCore::atomToScriptObject(toplevel->coerce(_a, t));
            }
        }

        double getDouble()
        {
            return AvmCore::number(_a);
        }
        int32_t getInt32()
        {
            return AvmCore::integer(_a);
        }
        uint32_t getUInt32()
        {
            return AvmCore::toUInt32(_a);
        }
        int32_t getBoolean()
        {
            return AvmCore::boolean(_a);
        }

        void set(Atom a, Traits* t)
        {
            if (!t) {
                _a = a;
            } else {
                switch(Traits::getBuiltinType(t))
                {
                case BUILTIN_void:
                    AvmAssert(a == AtomConstants::undefinedAtom);
                    _a = AtomConstants::undefinedAtom;
                    break;
                case BUILTIN_int:
                    setInt((intptr_t)a);
                    break;
                case BUILTIN_uint:
                    setUint((uintptr_t)a);
                    break;
                case BUILTIN_boolean:
                    _a = a ? trueAtom : falseAtom;
                    break;
                case BUILTIN_string:
                    _a = a ? ((Stringp)a)->atom() : nullStringAtom;
                    break;
                case BUILTIN_namespace:
                    _a = a ? ((Namespace*)a)->atom() : nullNsAtom;
                    break;
                case BUILTIN_object:
                    if (atomKind(a) == kUnusedAtomTag)
                        _a = a ? ((ScriptObject*)a)->atom() : nullObjectAtom;
                    else
                        _a = a;
                    break;
                default:
                    AvmAssert(Traits::getBuiltinType(t) != BUILTIN_number);
                    _a = a ? ((ScriptObject*)a)->atom() : nullObjectAtom;
                }
            }
        }

        void setInt(intptr_t i)
        {
            intptr_t iwt = i << _tagBits;
            if ((iwt >> _tagBits) == i) {
                _a = (iwt | kIntptrType);
            } else {
                *dblPtr() = i;
                _a = dblAtom();
            }
        }

        void setUint(uintptr_t u)
        {
            if (u & (~(static_cast<uintptr_t>(-1) >> (_tagBits + 1)))) {
                *dblPtr() = u;
                _a = dblAtom();
            } else {
                _a = (u << 3) | kIntptrType;
            }
        }

        void setDouble(double d)
        {
            *dblPtr() = d;
            _a = dblAtom();
        }
    };

    enum // we try to stick to 4 bits here instead of the 5 in BUILTIN_xxx
    {
        kVOID = 0,
        kOBJECT,
        kCLASS,
        kFUNCTION,
        kARRAY,
        kSTRING,
        kNUMBER,
        kINT,
        kUINT,
        kBOOLEAN,
        kANY,
        kNAMESPACE,
        kVECTORINT,
        kVECTORUINT,
        kVECTORDOUBLE,
        kVECTOROBJ,
        
        
        
        kLASTENUMELEMENT/// KEEP THIS ONE THE LAST, SO THAT THE ASSERTION WORKS!
    };
    /* using MMGC_STATIC_ASSERT for lack of a better one */
    MMGC_STATIC_ASSERT(kLASTENUMELEMENT <=16); 

    static Traits* argTraitsFromType(const AvmCore* core, int32_t n)
    {
        switch(n)
        {
        case kOBJECT: return OBJECT_TYPE;
        case kCLASS: return CLASS_TYPE;
        case kFUNCTION: return FUNCTION_TYPE;
        case kARRAY: return ARRAY_TYPE;
        case kSTRING: return STRING_TYPE;
        case kNUMBER: return NUMBER_TYPE;
        case kINT: return INT_TYPE;
        case kUINT: return UINT_TYPE;
        case kBOOLEAN: return BOOLEAN_TYPE;
        case kVOID: return VOID_TYPE;
        case kANY: return NULL;
        case kNAMESPACE: return NAMESPACE_TYPE;
        case kVECTORINT: return VECTORINT_TYPE;
        case kVECTORUINT: return VECTORUINT_TYPE;
        case kVECTORDOUBLE: return VECTORDOUBLE_TYPE;
        case kVECTOROBJ: return VECTOROBJ_TYPE;
        }
        AvmAssert(false); // shouldn't happen...
        return NULL;
    }

    // iterates over callee types for a method's signature
    class MethodSigArgDescIter
    {
    protected:
        int32_t m_n;
        const MethodInfo* m_methInfo;
        const MethodSignature* m_methSig;

    public:
        MethodSigArgDescIter(MethodInfo* methInfo) : m_n(0), m_methInfo(methInfo), m_methSig(methInfo->getMethodSignature())
        {
        }

        Traits* nextType()
        {
            if (m_n <= m_methSig->param_count())
                return m_methSig->paramTraits(m_n++);
            AvmCore* core = m_methInfo->pool()->core;
            return VOID_TYPE;
        }

        bool hasRest()
        {
            return m_methInfo->needRest() ? true : false;
        }

        bool needArguments()
        {
#ifdef VMCFG_HALFMOON_AOT_RUNTIME
            //For Halfmoon, we have one more flag to accomodate in arguments. 
            return (m_methInfo->needArguments() || m_methInfo->needArgsArrInMethodSig())? true : false;
#endif
            return m_methInfo->needArguments() ? true : false;
        }

        bool needOptionalArgs()
        {
            return true;
        }

        bool isVarArg()
        {
            return false;
        }
    };

    typedef struct _APType* APType; // type doesn't matter.. just don't clash w/ va_list

    class APArgDescIter : public MethodSigArgDescIter
    {
    protected:
        int32_t m_argc;

    public:
        APArgDescIter(int argc, MethodInfo* mi) : MethodSigArgDescIter(mi), m_argc(argc)
        {
#if CDECL_VERBOSE
            if (argc >= 0 && !m_methSig->argcOk(argc))
            {
                AvmCore* core = m_methInfo->pool()->core;

                core->console << "argc bad: "; m_methInfo->print(core->console) << " : " << argc << "\n";
            }
#endif
            AvmAssert(argc < 0 || m_methSig->argcOk(argc));
        }

        Traits* nextType()
        {
            AvmCore* core = m_methInfo->pool()->core;
#if CDECL_VERBOSE
            core->console << "APArgDescIter::nextType() m_n: " << m_n << "\n";
#endif
            if (m_argc < 0 || m_n <= m_argc)
            {
                if (m_n <= m_methSig->param_count())
                    return MethodSigArgDescIter::nextType();
                else
                {
                    m_n++;
                    return NULL;
                }
            }
            return VOID_TYPE;
        }

        bool hasRest()
        {
            return false;
        }

        bool needArguments()
        {
            return false;
        }

        bool needOptionalArgs()
        {
            return false;
        }

        bool isVarArg() // can just keep pushing atoms
        {
            return true;
        }
    };

    class AtomvArgDescIter
    {
    protected:
        AvmCore* m_core;
        int32_t m_argc;

    public: // TODO is this counting right?
        AtomvArgDescIter(AvmCore* core, int argc = -2) : m_core(core), m_argc(argc) {}

        Traits* nextType()
        {
            if (m_argc == -2)
                return NULL; // all atoms all the time!
            else if (m_argc >= 0)
            {
                m_argc--;
                return NULL;
            }
            AvmCore* core = m_core;
            return VOID_TYPE;
        }

        bool hasRest()
        {
            return false;
        }

        bool needArguments()
        {
            return false;
        }

        bool needOptionalArgs()
        {
            return false;
        }

        bool isVarArg()
        {
            return true;
        }
    };

    // read 4 bit types out of a uintptr_t bitwise
    // 32 bits holds 7 argument descriptions (plus ret type)
    // 64 bits can hold 15 (plus ret type)
    class ImmArgDescIter
    {
    protected:
        uintptr_t m_argDesc;
        AvmCore* m_core;

    public:
        ImmArgDescIter(uintptr_t argDesc, AvmCore* core) : m_argDesc(argDesc), m_core(core)
        {
        }

        // iterates over the types in the argument descriptor
        // VOID signals end of arguments; it is invalid to call nextType again after
        // end of arguments!
        Traits* nextType()
        {
            return argTraitsFromType(m_core, nextTypeKind());
        }

        unsigned nextTypeKind()
        {
            unsigned type = (unsigned)(m_argDesc >> (sizeof(m_argDesc) * 8 - 4));
            m_argDesc <<= 4;
            return type;
        }

        bool hasRest()
        {
            return false;
        }

        bool needArguments()
        {
            return false;
        }

        bool needOptionalArgs()
        {
            return true;
        }

        bool isVarArg()
        {
            return false;
        }
    };

    // read types out of an unsigned char*
    class PtrArgDescIter
    {
    protected:
        // pointer to next byte of arg description
        unsigned char* m_p;
        // currently loaded bits of arg description
        unsigned char m_bitBuf;
        // number of valid bits in m_bitBuf
        unsigned char m_bits;
        AvmCore* m_core;

    public:
        PtrArgDescIter(void* argDesc, AvmCore* core) : m_p((unsigned char* )argDesc), m_bitBuf(0), m_bits(0), m_core(core)
        {
        }

        // iterates over the types in the argument descriptor
        // VOID signals end of arguments; it is invalid to call nextType again after
        // end of arguments!
        Traits* nextType()
        {
            return argTraitsFromType(m_core, nextTypeKind());
        }

        unsigned nextTypeKind()
        {
            if (m_bits == 0)
            {
                m_bitBuf = *m_p++;
                m_bits = 8;
            }

            unsigned type = m_bitBuf >> 4;

            m_bitBuf <<= 4;
            m_bits -= 4;
            return type;
        }

        bool hasRest()
        {
            return false;
        }

        bool needArguments()
        {
            return false;
        }

        bool needOptionalArgs()
        {
            return true;
        }

        bool isVarArg()
        {
            return false;
        }
    };

    // lay out an argument description
    // on x86-32, an argument description is exactly a stack layout
    // on ARM, the first 4 words are r0-r3 and the rest is exactly a stack layout
    // on ARM64, first 8 double words are v0-v7 floating point, then r0 -r7, then overflow registers
    // with natural alignment.
    // on x86-64, it will no doubt be more complicated...
    class ArgDescLayout
    {
    protected:
        void* m_dst;
#if defined(AVMPLUS_ARM) || defined(AVMPLUS_AMD64)
        void* m_minDst;
#if defined(AVMPLUS_64BIT)
        void* m_dstFP;
        int   m_fpParamCount;
        int   m_paramCount;
        const int m_numIntReg;
        const int m_numFloatReg;
#endif
#endif

    public:
        // NULL dst is legal for measuring a call layout
        ArgDescLayout(void* dst) :
#if defined(AVMPLUS_ARM) && defined(AVMPLUS_64BIT)
        m_dstFP(dst)   // First 8 FP registers (v0-v7) always
        , m_dst((void*)((uintptr_t)dst + 64)) // First 8 FP registers (v0-v7) always
        , m_minDst((void*)((uintptr_t)dst + 128)) // then x0-x7(8*8) always
        , m_fpParamCount(0) // count for first 8 FP parameters
        , m_paramCount(0) // count for first 8 non FP parameters
        , m_numIntReg(8)
        , m_numFloatReg(8)
#elif defined(AVMPLUS_AMD64)
        m_dstFP(dst)   // First 8 FP registers (v0-v7) always
        , m_dst((void*)((uintptr_t)dst + 64)) // First 8 FP registers xmm0-xmm7 always
        , m_minDst((void*)((uintptr_t)dst + 112)) // then (rdi,rsi,rdx,rcx,r8,r9) always
        , m_fpParamCount(0) // count for first m_numFloatReg FP parameters
        , m_paramCount(0) // count for first m_numIntReg non FP parameters
        , m_numIntReg(6)
        , m_numFloatReg(8)       
#else
        m_dst(dst)
#ifdef AVMPLUS_ARM //32 bit ARM
        , m_minDst((void*)((uintptr_t)dst + 16)) // must make room for a1-a4(4*4) always
#endif
#endif
        {
#if defined(AVMPLUS_ARM) && !defined(AVMPLUS_64BIT)
            AvmAssert(!(7 & (uintptr_t)dst));
#else
            AvmAssert(!(15 & (uintptr_t)dst));
#endif
        }

        void* argEnd()
        {
#if defined(AVMPLUS_ARM) || defined(AVMPLUS_AMD64)
            return (m_dst > m_minDst) ? m_dst : m_minDst;
#else
            return m_dst;
#endif
        }

        // TODO really just platform int? that's what AtomMethodProc style uses
        int32_t* int32Arg()
        {
#if (defined(AVMPLUS_ARM) && defined(AVMPLUS_64BIT)) || defined(AVMPLUS_AMD64)
            //First 8 Non FP params should go to generic registers x0-x7(8 byte). memory starting from m_dst
            if(++m_paramCount <= m_numIntReg){
                int32_t* result = (int32_t*)m_dst;
                m_dst = (void*)(8 + (uintptr_t)m_dst);
                return result;
            }else { // Remaining push to m_minDst, 4 byte
                int32_t* result = (int32_t*)m_minDst;
#ifdef AVMPLUS_AMD64
                m_minDst = (void*)((7 + (uintptr_t)m_minDst)& ~7);
                m_minDst = (void*)(8 + (uintptr_t)m_minDst);
#else
                m_minDst = (void*)(4 + (uintptr_t)m_minDst);
#endif
                return result;
            }
#else
            int32_t* result = (int32_t*)m_dst;
            m_dst = (void*)(4 + (uintptr_t)m_dst);
            return result;
#endif
        }

        double* doubleArg()
        {
#if (defined(AVMPLUS_ARM) && defined(AVMPLUS_64BIT)) || defined(AVMPLUS_AMD64)
            //First 8 FP params should go to FP registers. memory starting from m_dstFP
            if(++m_fpParamCount <= m_numFloatReg){
                double* result = (double* )m_dstFP;
                m_dstFP = (void*)(8 + (uintptr_t)m_dstFP);
                return result;
            }else { // Take care of 8 byte alignment and push to m_minDst
                m_minDst = (void*)((7 + (uintptr_t)m_minDst)& ~7);
                double* result = (double* )m_minDst;
                m_minDst = (void*)(8 + (uintptr_t)m_minDst);
                return result;
            }
#else
            // TODO: doubles on ARM may need to be aligned, but because we have only
            // two arg sizes (4 and 8 bytes) it won't affect us right now
            double* result = (double* )m_dst;
            m_dst = (void*)(8 + (uintptr_t)m_dst);
            return result;
#endif
        }

        void** ptrArg()
        {
#if (defined(AVMPLUS_ARM) && defined(AVMPLUS_64BIT)) || defined(AVMPLUS_AMD64)
            //First 8 Non FP params should go to generic registers x0-x7. memory starting from m_dst
            if(++m_paramCount <= m_numIntReg){
                void** result = (void**)m_dst;
                m_dst = (void*)(8 + (uintptr_t)m_dst);
                return result;
            }else { // Take care of 8 byte alignment and push to m_minDst
                m_minDst = (void*)((7 + (uintptr_t)m_minDst)& ~7);
                void** result = (void**)m_minDst;
                m_minDst = (void*)(8 + (uintptr_t)m_minDst);
                return result;
            }
#else
            void** result = (void**)m_dst;
            m_dst = (void*)(4 + (uintptr_t)m_dst);
            return result;
#endif
        }
    };

    // calculate the size required for the given set of argument types for a cdecl call
    // including MethodEnv
    template <class ARG_TYPE_ITER> static int32_t argDescSize(ARG_TYPE_ITER calleeTypeIter, AvmCore*)
    {
        ArgDescLayout l(NULL);

        for (;;)
        {
            Traits* t = calleeTypeIter.nextType();

            BuiltinType bt = Traits::getBuiltinType(t);

            if (bt == BUILTIN_void) break;

            switch(Traits::getBuiltinType(t))
            {
            case BUILTIN_int:
            case BUILTIN_uint:
            case BUILTIN_boolean:
                l.int32Arg();
                break;
            case BUILTIN_number:
                l.doubleArg();
                break;
            default:
                l.ptrArg();
                break;
            }
        }
        if (calleeTypeIter.needArguments() || calleeTypeIter.hasRest())
        {
            l.ptrArg(); // argv
            l.int32Arg(); // argc
            
        // In halfmoon, ArrayObject is created in function prologue by calling
        // llCreateRestHelper/llCreateArgumentHelper and calling convention doesn't accept ArrayObject*
        // In GO, ArrayObject is created and send as parameter.
#ifndef VMCFG_HALFMOON_AOT_RUNTIME
            l.ptrArg(); // rest
#endif
        }
        l.ptrArg(); // MethodEnv
        return (int32_t)(uintptr_t)l.argEnd();
    }

    // calculate the size required for the given set of argument types passed "ap" style
    // just figures out the size of the ap struct... doesn't include MethodEnv
    template <class ARG_TYPE_ITER1, class ARG_TYPE_ITER2> static int32_t apArgDescSize(ARG_TYPE_ITER1 callerTypeIter, ARG_TYPE_ITER2 calleeTypeIter, AvmCore* core)
    {
        int32_t size = 0;

        // count "regular" arguments... stored as unaligned native
        for (;;)
        {
            Traits* t = calleeTypeIter.nextType();

            BuiltinType bt = Traits::getBuiltinType(t);

            // no more "regular" arguments? break out
            if (bt == BUILTIN_void) break;

            // no more caller arguments? done
            if (callerTypeIter.nextType() == VOID_TYPE)
                return size;

            switch(Traits::getBuiltinType(t))
            {
            case BUILTIN_int:
            case BUILTIN_uint:
            case BUILTIN_boolean:
                size += sizeof(int32_t);
                break;
            case BUILTIN_number:
                size += sizeof(double);
                break;
            default:
                size += sizeof(void*);
                break;
            }
        }
        // count the rest as pointers (Atoms)
        while (callerTypeIter.nextType() != VOID_TYPE)
            size += sizeof(void*);
        return size;
    }
    
#if defined (VMCFG_HALFMOON_AOT_RUNTIME) && defined (AVMPLUS_ARM)          // Fixing HMAOT bug
    typedef void* (*ArgCoercer)(void* callee, MethodEnv* env, Traits* retTraits, uintptr_t callerArgDesc, void* callerAp, void* calleeArgDescBuf);
    extern "C" Atom coerce32CdeclShim(void* callee, unsigned calleeArgDescBufSize, ArgCoercer argCoercer, MethodEnv* env, Traits* retTraits, uintptr_t callerArgDesc, void* callerAp);
    extern "C" double coerceNCdeclShim(void* callee, unsigned calleeArgDescBufSize, ArgCoercer argCoercer, MethodEnv* env, Traits* retTraits, uintptr_t callerArgDesc, void* callerAp);
    extern "C" Atom returnCoercerN(Traits* retTraits, MethodEnv* env);
    extern "C" double returnCoercerN32(Traits* retTraits, MethodEnv* env);
    extern "C" Atom returnCoercer32(Traits* retTraits, MethodEnv* env);

#else 
    
#if defined(AVMPLUS_IA32) || defined (AVMPLUS_AMD64)
    // pseudo-cross-compiler macros for inline assembly...
    // gcc/x86 in particular isn't really production grade
#ifdef _WIN32
    // msvc stuff works well inline...
#define ASM_FUNC_BEGIN(R, N, A) static R __declspec(naked) N A {
#define ASM_FUNC_END(N) }
#define ASM1(X) __asm { X }
#define ASM2(X,Y) __asm { X,Y }
#define ASM_CALL(X) __asm { call X }
#define ASM_REDIR(F) __asm { jmp F }
#else
    // gcc doesn't support naked inline functions despite the clear use for them
    // this stuff is hackery to help development -- gcc targets should have .s files for production
#ifdef AVMPLUS_AMD64
    #define ASM_FUNC_BEGIN(R, N, A) typedef R (* N##_type)A; static void*  N##_container () { \
            void* result; \
            __asm__ (" movabsq $L"#N"_astart, %[result]" : [result] "=r" (result)); \
            goto ret; asmlbl: \
            __asm__ (" .intel_syntax noprefix "); \
            __asm__ ("L"#N"_astart: ");
    #define ASM_FUNC_END(N) __asm__ (" .att_syntax noprefix "); ret: if (result == 0) goto asmlbl; return result; } N##_type N = (N##_type)N##_container();
    #define ASM_REDIR(F) __asm__ ( "pushq qword[_"#F"]\n retq");
#else
    #define ASM_FUNC_BEGIN(R, N, A) typedef R (* N##_type)A; static void*  N##_container () { \
            void* result; \
            __asm__ (" mov $L"#N"_astart, %[result]" : [result] "=r" (result)); \
            goto ret; asmlbl: \
            __asm__ (" .intel_syntax noprefix "); \
            __asm__ ("L"#N"_astart: ");
    #define ASM_FUNC_END(N) __asm__ (" .att_syntax noprefix "); ret: if (result == 0) goto asmlbl; return result; } N##_type N = (N##_type)N##_container();
    #define ASM_REDIR(F) __asm__ ( "push [_"#F"]\n ret");
#endif       
#define ASM1(X) __asm__ ( #X );
#define ASM2(X,Y) __asm__ ( #X","#Y );
#define ASM_CALL(X) __asm__ ("call _"#X"\n");
#endif
#elif defined(AVMPLUS_ARM)
    // gcc doesn't support naked inline functions despite the clear use for them
    // this stuff is hackery to help development -- gcc targets should have .s files for production
#define ASM_BP __asm__("stmdb sp!, {a1, a2, a3, a4}\n swi 0x80\n ldmia sp!, {a1, a2, a3, a4}")
#define ASM_FUNC_BEGIN(R, N, A) \
extern R N A; \
__asm__(".section __TEXT,__text,regular,pure_instructions"); \
__asm__(".align 2"); \
__asm__(".globl _"#N" "); \
__asm__("_"#N": ");
#define ASM_FUNC_END(N)
#define ASM_REDIR(F) __asm__ ( "b _"#F" ");
    
#endif
    
    // prototype for an argument coercer
    // env is MethodEnv coercing for
    // callerArgDesc is an opaque description of the arguments to be found via callerArgDesc
    // callerAp is the variadic args passed to coerce32CdeclImmArgDesc, et al
    // calleeArgDescBuf is the argument buffer into which coerced arguments are writter
    // returns a pointer to a function used for return value conversion or NULL is none is needed
    typedef void* (*ArgCoercer)(void* callee, MethodEnv* env, Traits* retTraits, uintptr_t callerArgDesc, void* callerAp, void* calleeArgDescBuf);
    
    extern "C" {
        
        // core of the thunking mechanism...
        // doesn't necessarily return an int32_t... the N/double variant is identical
        // -- callee is the cdecl method to invoke
        // -- calleeArgDescBufSize is the amount of space to allocate for the coerced args (and possibly register alloc info for, say, x86/64)
        // -- argCoercer is a callback that does the actual filling of the coerced argument buf
        // -- env is the MethodEnv we're calling (used to get argument traits -- does not make callee redundant as env may have >1 impl)
        // -- calleeArgDesc is an opaque description of the types of variadic arguments in callerAp
        // -- callerAp represents the arguments to coerce
        ASM_FUNC_BEGIN(Atom, coerce32CdeclShim,
                       (void* callee, unsigned calleeArgDescBufSize, ArgCoercer argCoercer, MethodEnv* env, Traits* retTraits, uintptr_t callerArgDesc, void* callerAp))
#ifdef AVMPLUS_ARM
        __asm__("stmdb  sp!, {v1, v2, v3, v7, lr}");
        __asm__("mov v7, sp");
        //First four arguments are passed in registersa1-a4 and other are pushed in stack in reverse order.
        //remember 5 registers are pushed in stack and after that sp is copied to v7
        // a1 = callee
        // a2 = calleeArgDescBufSize
        // a3 = argCoercer
        // a4 = env
        // [v7, #20] = retTraits
        // [v7, #24] = callerArgDesc
        // [v7, #28] = callerAp
        __asm__("sub sp, sp, a2"); // make room for args
        __asm__("bic sp, sp, #7"); // double word align
        __asm__("mov v2, a3"); // save off argCoercer
        __asm__("mov v3, a4"); // save off env

        //Prepare to call argCoercer
        //Remember:First four arguments are passed in registersa1-a4 and other are pushed in stack in reverse order.
        // a1 stays callee
        __asm__("mov a2, a4"); // pass env
        __asm__("ldr a3, [v7, #20]"); // pass retTraits
        __asm__("ldr a4, [v7, #24]"); // pass callerArgDesc
        __asm__("mov v1, sp"); // pass calleeArgDescBuf
        __asm__("stmdb sp!, {v1}");
        __asm__("ldr v1, [v7, #28]"); // pass callerAp
        __asm__("stmdb sp!, {v1}");
        __asm__("mov v1, a1"); // save off callee
        __asm__("bl _via_v2"); // call coercer!
        __asm__("add sp, sp, #8"); // restore stack
        __asm__("mov v2, a1"); // save returnCoercer
        
        //Prepare to call implementation ( actual AOTed function )
        //Remember:First four arguments are passed in registersa1-a4 and other are pushed in stack in reverse order.
        // a1 stays callee
        __asm__("ldmia  sp!, {a1, a2, a3, a4}"); // move first 4 arg words into registers
        __asm__("bl _via_v1"); // call the implementation!
        __asm__("mov sp, v7"); // restore stack
        __asm__("cmp v2, #0"); // maybe call returnCoercer -- a1 and a2 will be the double or a1 will be the 32 and a2 will be a dummy
        __asm__("ldrne a3, [v7, #20]"); // retTraits
        __asm__("movne a4, v3"); // env
        __asm__("blne _via_v2");
        __asm__("ldmia  sp!, {v1, v2, v3, v7, pc}"); // done!
        __asm__("_via_v1: bx v1");
        __asm__("_via_v2: bx v2");
#elif defined(AVMPLUS_AMD64)
        __asm__("pushq rbp"); // save base pointer
        __asm__("movq rbp, rsp"); // save stack pointer in base pointer
        //save callee saved registers
        __asm__("pushq rbx");
        __asm__("pushq r12");
        __asm__("pushq r13");
        __asm__("pushq r14");
        __asm__("pushq r15");
        __asm__("movq rbx, rsp"); // save stack pointer
        
        // [rbp] = saved rbp
        // [rbp+8] = return address
        // [rdi] = callee
        // [rsi] = calleeArgDescBufSize
        // [rdx] = argCoercer
        // [rcx] = env
        // [r8] = retTraits
        // [r9] = callerArgDesc
        // [rbp+16] = callerAp

        // Calling function register
        // r12 - r15, rbx
        // r10-r15 temporary register; used to return long double arguments
        // st1-st7 temporary registers; used to return long double arguments
        __asm__("addq rsi, 0x15"); // move stack pointer by Arg size
        __asm__("andq rsi, 0xfffffffffffffff0"); //  16 byte aligned
        __asm__("subq rsp, rsi");
        __asm__("subq rsp, 0x8");
        __asm__("movq rsi, rsp"); // save stack pointer in callerArgDescBufSize
        
        // save arguments to temporary register, which are callee maintained
        __asm__("movq r15, rdi"); // callee
        __asm__("movq r12, rdx"); // argCoercer
        __asm__("movq r13, rcx"); // env
        __asm__("movq r14, r8"); // retTraits

        // fill register for argument passing to argCoercer
        __asm__("movq rcx, r9"); //  callerArgDesc -> rcx
        __asm__("movq r9, rsi"); //  calleeArgDescBuf -> r9
        __asm__("movq r8, [rbp+16]"); //  callerAp -> r8
        __asm__("movq rdx, r14"); //  retTraits -> rdx
        __asm__("movq rsi, r13"); //env -> rsi
        __asm__("callq r12"); //  map args: argCoercer(callee, env, retTraits, callerArgDesc, callerAp, callerArgDescBuf);
        __asm__("movq r12, rax"); //  save result mapping func

        // mov all the arguments from stack to the register -- 8 float, 6 integer/pointer 
        __asm__("movsd xmm0, [rsp]");
        __asm__("movsd xmm1, [rsp+8]");
        __asm__("movsd xmm2, [rsp+16]");
        __asm__("movsd xmm3, [rsp+24]");
        __asm__("movsd xmm4, [rsp+32]");
        __asm__("movsd xmm5, [rsp+40]");
        __asm__("movsd xmm6, [rsp+48]");
        __asm__("movsd xmm7, [rsp+56]");
        __asm__("movq rdi, [rsp+64]");
        __asm__("movq rsi, [rsp+72]");
        __asm__("movq rdx, [rsp+80]");
        __asm__("movq rcx, [rsp+88]");
        __asm__("movq r8, [rsp+96]");
        __asm__("movq r9, [rsp+104]");
        __asm__("addq rsp, 0x70"); //stack pointer moved - 112

        __asm__("callq r15"); //  call method
        __asm__("movq rsp, rbx"); // restore stack
        __asm__("cmpq r12, 0");
        __asm__("je coerce32CdeclShim_done"); 
        __asm__("subq rsp, 0x8");
        __asm__("movq rdx, r13"); //  env - rdx
        __asm__("movq rsi, r14"); //  retTraits - rsi
        __asm__("movq rdi, rax"); //  return value - rdi
        __asm__("callq r12"); //  map return value: retCoercer(retTraits, env)
        __asm__("coerce32CdeclShim_done:");
        __asm__("xorq rdx, rdx");
        __asm__("movq rsp, rbx"); // restore stack
        __asm__("popq r15");
        __asm__("popq r14");
        __asm__("popq r13");
        __asm__("popq r12");
        __asm__("popq rbx");
        __asm__("movq rsp, rbp"); // restore stack
        __asm__("popq rbp");
        __asm__("retq");

#else
#ifdef _WIN32
        (void)callee;
        (void)calleeArgDescBufSize;
        (void)argCoercer;
        (void)env;
        (void)retTraits;
        (void)callerArgDesc;
        (void)callerAp;
#endif
        ASM1(       push ebp)
        ASM2(       mov ebp, esp)
        ASM1(       push esi)
        // [ebp] = saved ebp
        // [ebp+4] = return address
        // [ebp+8] = callee
        // [ebp+12] = calleeArgDescBufSize
        // [ebp+16] = argCoercer
        // [ebp+20] = env
        // [ebp+24] = retTraits
        // [ebp+28] = callerArgDesc
        // [ebp+32] = callerAp
        ASM2(       sub esp, [ebp+12] ) //  make room for args
        ASM2(       and esp, 0xfffffff0 ) //  16 byte aligned
        ASM2(       mov eax, esp)
        ASM2(       sub esp, 8 ) // 16 byte aligned for call
        ASM1(       push eax ) //  calleeArgDescBuf
        ASM1(       push [ebp+32] ) //  callerAp
        ASM1(       push [ebp+28] ) //  callerArgDesc
        ASM1(       push [ebp+24] ) //  retTraits
        ASM1(       push [ebp+20] ) //  env
        ASM1(       push [ebp+8] ) //  callee
        ASM1(       call [ebp+16] ) //  map args: argCoercer(callee, env, retTraits, callerArgDesc, callerAp, callerArgDescBuf);
        ASM2(       add esp, 32)
        ASM2(       mov esi, eax ) //  save result mapping func
        ASM1(       call [ebp+8] ) //  call method
        ASM2(       lea esp, [ebp-4]) // restore stack
        ASM2(       cmp esi, 0)
        ASM1(       je coerce32CdeclShim_done)
        ASM2(       sub esp, 8 ) // 16 byte aligned for call
        ASM1(       push [ebp+20] ) //  env
        ASM1(       push [ebp+24] ) //  retTraits
        ASM1(       call esi ) //  map return value: retCoercer(retTraits, env)
        ASM2(       add esp, 16)
        ASM1(coerce32CdeclShim_done:)
        ASM1(       pop esi)
        ASM1(       pop ebp)
        ASM1(       ret)
#endif
        ASM_FUNC_END(coerce32CdeclShim)
        
        ASM_FUNC_BEGIN(double, coerceNCdeclShim, (void* callee,
                                                  unsigned calleeArgDescBufSize, ArgCoercer argCoercer, MethodEnv* env, Traits* retTraits, uintptr_t callerArgDesc, void* callerAp))
#ifdef _WIN32
        (void)callee;
        (void)calleeArgDescBufSize;
        (void)argCoercer;
        (void)env;
        (void)retTraits;
        (void)callerArgDesc;
        (void)callerAp;
#endif
#ifdef AVMPLUS_AMD64
        __asm__("subq rsp, 0x8"); // 16 byte aligned
        __asm__("callq qword[_coerce32CdeclShim]");
        __asm__("addq rsp, 0x8");
        __asm__("retq");
#else
        ASM_REDIR(coerce32CdeclShim) // exact same impl
#endif
        ASM_FUNC_END(coerceNCdeclShim)
        
        // Number => some 32
        ASM_FUNC_BEGIN(Atom, returnCoercerN, (Traits* retTraits, MethodEnv* env))
#ifdef AVMPLUS_ARM
        __asm__("b _returnCoercerNImpl"); // straight through
#elif defined(AVMPLUS_AMD64)
        //TODO: Function for AMD64
#else
        ASM1(       push ebp) // this is necessary to keep pthreads happy!
        ASM2(       mov ebp, esp)
        ASM2(       sub esp, 12)
        ASM1(       push [ebp+12]) // env
        ASM1(       push [ebp+8]) // retTraits
        ASM2(       sub esp, 8)
        ASM1(       fstp qword ptr [esp]) // callee will have left a value on the FP stack
        ASM_CALL(returnCoercerNImpl)
        ASM2(       add esp, 28)
        ASM1(       pop ebp)
        ASM1(       ret)
#endif
        ASM_FUNC_END(returnCoercerN)
        
#ifndef AVMPLUS_ARM
        ASM_FUNC_BEGIN(Atom, returnCoercerNPop, (Traits* retTraits, MethodEnv* env))
        #ifdef AVMPLUS_AMD64
            //TODO: Function for AMD64
        #else
            ASM1(       push ebp) // this is necessary to keep pthreads happy!
            ASM2(       mov ebp, esp)
            ASM1(       fstp st(0)) // callee will have left a value on the FP stack
            ASM1(       pop ebp)
            ASM1(       ret)
        #endif
        ASM_FUNC_END(returnCoercerNPop)
#endif
        
        // some 32 => Number
        ASM_FUNC_BEGIN(double, returnCoercerN32, (Traits* retTraits, MethodEnv* env))
#ifdef AVMPLUS_ARM
        __asm__("mov a2, a3"); // a2 is a dummy
        __asm__("mov a3, a4");
        __asm__("b _returnCoercerN32Impl");
#elif defined(AVMPLUS_AMD64)
        //TODO: Function for AMD64
#else
        ASM1(       push ebp) // this is necessary to keep pthreads happy!
        ASM2(       mov ebp, esp)
        ASM1(       push [ebp+12]) // env
        ASM1(       push [ebp+8]) // retTraits
        ASM1(       push eax)
        ASM_CALL(returnCoercerN32Impl) // will push something on the FP stack
        ASM2(       add esp, 12)
        ASM1(       pop ebp)
        ASM1(       ret)
#endif
        ASM_FUNC_END(returnCoercerN32)
        
        // some 32 => some 32
        ASM_FUNC_BEGIN(Atom, returnCoercer32, (Traits* retTraits, MethodEnv* env))
#ifdef AVMPLUS_ARM
        __asm__("mov a2, a3"); // a2 is a dummy
        __asm__("mov a3, a4");
        __asm__("b _returnCoercer32Impl");
#elif defined(AVMPLUS_AMD64)
        //TODO: Function for AMD64
#else
        ASM1(       push ebp) // this is necessary to keep pthreads happy!
        ASM2(       mov ebp, esp)
        ASM1(       push [ebp+12]) // env
        ASM1(       push [ebp+8]) // retTraits
        ASM1(       push eax)
        ASM_CALL(returnCoercer32Impl)
        ASM2(       add esp, 12)
        ASM1(       pop ebp)
        ASM1(       ret)
#endif
        ASM_FUNC_END(returnCoercer32)
        
    }

    
    
#endif  //(VMCFG_HALFMOON_AOT_RUNTIME) && defined (AVMPLUS_ARM)    
    
    
    extern "C" {
    // something => something
    Atom returnCoercer32Impl(Atom a, Traits* retTraits, MethodEnv* env)
    {
        Traits* calleeRT = env->method->getMethodSignature()->returnTraits();
        AvmValue v;
        
        v.set(a, calleeRT);
        return v.get(env->toplevel(), retTraits);
    }
    
    // something => Number
    double returnCoercerN32Impl(Atom a, Traits* /*retTraits*/, MethodEnv* env)
    {
        Traits* calleeRT = env->method->getMethodSignature()->returnTraits();
        AvmValue v;
        
        v.set(a, calleeRT);
        
        return v.getDouble();
    }
    
    // Number => something
    Atom returnCoercerNImpl(double n, Traits* retTraits, MethodEnv* env)
    {
        AvmValue v;
        
        v.setDouble(n);
        return v.get(env->toplevel(), retTraits);
    }
    }

    // returns any function required to coerce the callee's return type to the
    // caller's desired return type
    static void* returnCoercer(AvmCore* core, Traits* calleeRT, Traits* callerRT)
    {
        // same or caller will discard? no conversion
        if (callerRT == calleeRT)
            return NULL;
        if (callerRT == VOID_TYPE)
        {
#if defined(AVMPLUS_ARM) || defined(AVMPLUS_AMD64)
                return NULL;
#else
            if (calleeRT == NUMBER_TYPE)
                return (void*)returnCoercerNPop;
            else
                return NULL;
#endif
        }
        // both integral types? no conversion
        if ((callerRT == INT_TYPE || callerRT == UINT_TYPE) &&
                (calleeRT == INT_TYPE || calleeRT == UINT_TYPE))
            return NULL;
        // is callee a double returner?
        if (calleeRT == NUMBER_TYPE)
#if defined(AVMPLUS_AMD64)
            return (void*)returnCoercerNImpl;
#else
            return (void*)returnCoercerN; // Number => 32 -> returnCoercerNImpl
#endif
        // how about caller?
        if (callerRT == NUMBER_TYPE)
#if defined(AVMPLUS_AMD64)
            return (void*)returnCoercerN32Impl;
#else
            return (void*)returnCoercerN32; // 32 => Number -> returnCoercerN32Impl
#endif
        // everything else
#if defined(AVMPLUS_AMD64)
        return (void*)returnCoercer32Impl;
#else
        return (void*)returnCoercer32; // 32 => 32, 64 to 64 -> returnCoercer32Impl
#endif
    }

    static int32_t arg32(va_list_wrapper& ap)
    {
        return va_arg(ap.m_list, int32_t); // x86-64?
    }

    static int32_t arg32(APType& ap)
    {
        int32_t result = *(int32_t *)ap;
        ap = (APType)((uintptr_t)ap + sizeof(Atom)); //ap is internally stored as Atom
        return result;
    }

    static void* argPtr(va_list_wrapper& ap)
    {
        return va_arg(ap.m_list, void*);
    }
    
    static void* argPtr(APType& ap)
    {
        void* result = (void*)(*(uintptr_t *)ap);
        ap = (APType)((uintptr_t)ap + sizeof(uintptr_t));
        return result;
    }

    static double argN(va_list_wrapper& ap)
    {
        return va_arg(ap.m_list, double);
    }

    static double argN(APType& ap)
    {
        double result = *(double*)ap;
        ap = (APType)((uintptr_t)ap + sizeof(double));
        return result;
    }

    template <class ARG_ITER> static Atom coerceArgToAny(Toplevel* toplevel, ARG_ITER& ap, Traits* callerT)
    {
        AvmCore* core = toplevel->core();
        AvmValue v;

        if (callerT == NUMBER_TYPE)
            v.setDouble(argN(ap));
        else
            v.set((Atom)argPtr(ap), callerT);
        return v.get(toplevel, NULL);
    }

    // coerces a single argument and writes it to an argument desc layout
    template <class ARG_ITER> static void coerceArg(Toplevel* toplevel, ArgDescLayout& l, Traits* calleeT, ARG_ITER& callerAp, Traits* callerT)
    {
        AvmCore* core = toplevel->core();

        if (calleeT == callerT && calleeT != OBJECT_TYPE) // OBJECT_TYPE might be a naked ScriptObject... let AvmValue handle it
        {
            if (calleeT == NUMBER_TYPE)
                *l.doubleArg() = argN(callerAp);
            else if (calleeT == INT_TYPE || calleeT == UINT_TYPE || calleeT == BOOLEAN_TYPE )
#if (defined(AVMPLUS_64BIT) && defined(AVMPLUS_ARM)) || defined(AVMPLUS_AMD64)
            //On ARM64 bit, only 4 bytes are overwritten,in some cases padding is required so just clear next 4 bytes.
                *(int64_t*)l.int32Arg() = arg32(callerAp);
#else
                *l.int32Arg() = arg32(callerAp);
#endif
            else
                *l.ptrArg() = argPtr(callerAp);
        }
        // Handling cases where callerT != calleeT, for default arguments, callerT is NULL
        else if(calleeT == INT_TYPE || calleeT == UINT_TYPE || calleeT == BOOLEAN_TYPE)
        {
#if (defined(AVMPLUS_64BIT) && defined(AVMPLUS_ARM)) || defined(AVMPLUS_AMD64)
            //On ARM64 bit, only 4 bytes are overwritten,in some cases padding is required so just clear next 4 bytes.
            AvmValue v;
            v.set((Atom)argPtr(callerAp), callerT);
            if(calleeT == INT_TYPE)
                *(int64_t*)l.int32Arg() = v.getInt32();
            else if(calleeT == UINT_TYPE)
                *(int64_t*)l.int32Arg() = v.getUInt32();
            else if(calleeT == BOOLEAN_TYPE)
                *(int64_t*)l.int32Arg() = v.getBoolean();
#else
            //For 32 bit, keeping same code as in else block at the last.
            AvmValue v;
            v.set((Atom)argPtr(callerAp), callerT);
            *l.ptrArg() = (void*)v.get(toplevel, calleeT);
#endif
        }
        else if (calleeT == NUMBER_TYPE)
        {
            AvmValue v;
            v.set((Atom)argPtr(callerAp), callerT);
            *l.doubleArg() = v.getDouble();
        }
        else if (callerT == NUMBER_TYPE)
        {
            AvmValue v;
            v.setDouble(argN(callerAp));
            *l.ptrArg() = (void*)v.get(toplevel, calleeT);
        }
        else
        {
            AvmValue v;
            v.set((Atom)argPtr(callerAp), callerT);
            *l.ptrArg() = (void*)v.get(toplevel, calleeT);
        }
    }

    static void coerceArgAtom(Toplevel* toplevel, ArgDescLayout& l, Traits* calleeT, Atom a)
    {
        APType ap = (APType)&a;
        coerceArg(toplevel, l, calleeT, ap, NULL);
    }

    // coerces a single argument and writes it into an AtomList
    static void coerceArg(Toplevel* toplevel, AtomList &atoms, Traits* calleeT, va_list_wrapper& callerAp, Traits* callerT)
    {
      AvmCore* core = toplevel->core();
      
      if (callerT == NUMBER_TYPE)
      {
        AvmValue v;
        v.setDouble(argN(callerAp));
        atoms.add((Atom)v.get(toplevel, calleeT));
      }
      else
      {
        AvmValue v;
        v.set((Atom)argPtr(callerAp), callerT);
        atoms.add((Atom)v.get(toplevel, calleeT));
      }
    }

    static void coerceArgAtom(Toplevel*, AtomList &atoms, Traits* /*calleeT*/, Atom a)
    {
      atoms.add(a);
    }

    // coerces a single argument and writes it to an "ap" style arg list
    static void coerceArg(Toplevel* toplevel, APType& ap, Traits* calleeT, va_list_wrapper& callerAp, Traits* callerT)
    {
        AvmCore* core = toplevel->core();

        if (calleeT == callerT && calleeT != OBJECT_TYPE) // OBJECT_TYPE might be a naked ScriptObject... let AvmValue handle it
        {
            if (calleeT == NUMBER_TYPE)
            {
                *(double* )ap = argN(callerAp);
                ap = (APType)(sizeof(double) + (uintptr_t)ap);
            }
            else
            {
                *(uintptr_t*)ap = (uintptr_t)argPtr(callerAp);
                ap = (APType)(sizeof(uintptr_t) + (uintptr_t)ap);
            }
        }
        else if (calleeT == NUMBER_TYPE)
        {
            AvmValue v;
            v.set((Atom)argPtr(callerAp), callerT);
            *(double* )ap = v.getDouble();
            ap = (APType)(sizeof(double) + (uintptr_t)ap);
        }
        else if (callerT == NUMBER_TYPE)
        {
            AvmValue v;
            v.setDouble(argN(callerAp));
            *(int32_t*)ap = v.get(toplevel, calleeT);
            ap = (APType)(sizeof(int32_t) + (uintptr_t)ap);
        }
        else
        {
            AvmValue v;
            v.set((Atom)argPtr(callerAp), callerT);
            *(uintptr_t*)ap = v.get(toplevel, calleeT);
            ap = (APType)(sizeof(uintptr_t) + (uintptr_t)ap);
        }
    }

    static void coerceArgAtomI(Toplevel* toplevel, APType& ap, Traits* calleeT, ...)
    {
        va_list_wrapper va;

        va_start(va.m_list, calleeT);
        coerceArg(toplevel, ap, calleeT, va, NULL);
        va_end(va.m_list);
    }

    static void coerceArgAtom(Toplevel* toplevel, APType& ap, Traits* calleeT, Atom a)
    {
        coerceArgAtomI(toplevel, ap, calleeT, a);
    }

    static void handleRest(Toplevel*, ArgDescLayout& l, ArrayObject *rest, bool needArguments)
    {
        uint32_t argc = rest->getDenseLength();
        Atom *argv = rest->getDenseCopy();

        *l.ptrArg() = argv; // TODO argv
#ifndef VMCFG_HALFMOON_AOT_RUNTIME
        *l.int32Arg() = argc; // TODO argc
#else
        //In halfmoon, this is added extra
#if (defined(AVMPLUS_64BIT) && defined(AVMPLUS_ARM)) || defined(AVMPLUS_AMD64)
        //On ARM64 bit, only 4 bytes are overwritten,in some cases padding is required so just clear next 4 bytes.
        *(int64_t*)l.int32Arg() = needArguments ? argc-1 : argc ;
#else
        *l.int32Arg() = needArguments ? argc-1 : argc ;
#endif
#endif
        // In halfmoon, ArrayObject is created in function prologue by calling
        // llCreateRestHelper/llCreateArgumentHelper and calling convention doesn't accept ArrayObject*
        // In GO, ArrayObject is created and send as parameter.
#ifndef VMCFG_HALFMOON_AOT_RUNTIME
        *l.ptrArg() = rest; // rest
#endif
    }

    static void handleRest(Toplevel*, APType&, ArrayObject*, bool needArguments)
    {
        AvmAssert(false); // AP doesn't handle rest in the CC
    }
    
    static void handleRest(Toplevel*, AtomList&, ArrayObject*, bool needArguments)
    {
        AvmAssert(false);
    }

    // coerces a set of arguments and writes to a given argument description
    template <class ARG_TYPE_ITER1, class ARG_ITER, class ARG_TYPE_ITER2, class ARG_WRITER>
    static int32_t argCoerceLoop(MethodEnv* env, ARG_TYPE_ITER1 callerTypeIter, ARG_ITER callerAp,
            ARG_TYPE_ITER2 calleeTypeIter, ARG_WRITER &argDescWriter)
    {
        Toplevel* toplevel = env->toplevel();
        MethodInfo* info = env->method;
        AvmCore* core = env->core();
        int32_t argc = 0;

        // map args
        ArrayObject* argsOrRest = NULL;
        ArrayObject* args = NULL; // "arguments"
        const MethodSignature* ms = env->method->getMethodSignature();

        // "arguments" captures all arguments
        if (calleeTypeIter.needArguments())
        {
            ARG_TYPE_ITER1 callerTypeIterTemp = callerTypeIter;
            ARG_ITER callerApTemp = callerAp;
            Traits* callerT = callerTypeIterTemp.nextType();

            AvmAssert(callerT != VOID_TYPE);
            Atom a = coerceArgToAny(toplevel, callerApTemp, callerT);
            
            // In halfmoon, ArrayObject is created in function prologue by calling llCreateArgumentHelper
            // and 'this' is required to call env->createArguments there.
            // In GO, env->createArguments is called here itself and ArrayObject is send as parameter.
#ifndef VMCFG_HALFMOON_AOT_RUNTIME
            args = env->createArguments(&a, 0);
#else
            args = toplevel->arrayClass()->newarray(&a, 1);
#endif        
        }

        for (;;)
        {
            Traits* callerT = callerTypeIter.nextType();

#if CDECL_VERBOSE
            if (callerT)
                core->console << " callerT: " << callerT->formatClassName() << "\n";
            else
                core->console << " callerT: *\n";
#endif
            // no more params from caller? break out
            if (callerT == VOID_TYPE)
                break;

            Traits* calleeT = calleeTypeIter.nextType();

#if CDECL_VERBOSE
            if (calleeT)
                core->console << " calleeT: " << calleeT->formatClassName() << "\n";
            else
                core->console << " calleeT: *\n";
#endif

            // no more normal params for callee
            if (calleeT == VOID_TYPE)
            {
                if (!ms->allowExtraArgs())
                {
                    toplevel->argumentErrorClass()->throwError(kWrongArgumentCountError,
                            core->toErrorString(info),
                            core->toErrorString(ms->requiredParamCount()),
                            core->toErrorString(argc));
                }
                else // fill up rest/argument/var args
                {
                    // can we just keep pushing args? (i.e., "ap" style)
                    if (calleeTypeIter.isVarArg())
                    {
#if CDECL_VERBOSE
                        core->console << " argCoerceLoop: passing extra params as vararg\n";
#endif
                        AvmAssert(!argsOrRest); // shouldn't have rest or arguments if vararg
                        do
                        {
                            // just keep writing "atom"s
                            coerceArg(toplevel, argDescWriter, NULL, callerAp, callerT);
                            callerT = callerTypeIter.nextType();
                            argc++;
                        } while (callerT != VOID_TYPE);
                    }
                    else
                    {
                        // are we actually using the args?
                        if (calleeTypeIter.needArguments() || calleeTypeIter.hasRest())
                        {
#if CDECL_VERBOSE
                            core->console << " argCoerceLoop: passing extra params as Array\n";
#endif
                            if (!argsOrRest)
                                argsOrRest = args ? args : toplevel->arrayClass()->newArray(1);
                            do
                            {
                                Atom a = coerceArgToAny(toplevel, callerAp, callerT);
                                argsOrRest->push(&a, 1);
                                callerT = callerTypeIter.nextType();
                            } while (callerT != VOID_TYPE);
                        }
#if CDECL_VERBOSE
                        else
                            core->console << " argCoerceLoop: discarding extra params\n";
#endif
                    }
                    break;
                }
            }

            // copy arg into "arguments"
            if (argsOrRest)
            {
                ARG_ITER ap = callerAp;
                Atom a = coerceArgToAny(toplevel, ap, callerT);
                argsOrRest->push(&a, 1);
            }
            else if (args) // arguments doesn't take "this" so
                argsOrRest = args;
            coerceArg(toplevel, argDescWriter, calleeT, callerAp, callerT);
            argc++;
        }

        if (calleeTypeIter.needOptionalArgs())
        {
            // deal with "optional" args
            int32_t regArgs = ms->param_count() + 1;
            int optNum = argc - regArgs + ms->optional_count();

            if (optNum < 0) // not enough non-optional arguments passed...
                toplevel->argumentErrorClass()->throwError(kWrongArgumentCountError,
                        core->toErrorString(info),
                        core->toErrorString(ms->requiredParamCount()),
                        core->toErrorString(argc));

            while (argc < regArgs) // optional...
            {
                Traits* calleeT = calleeTypeIter.nextType();
                
#if CDECL_VERBOSE
                if (calleeT)
                    core->console << " calleeT: " << calleeT->formatClassName() << "\n";
                else
                    core->console << " calleeT: *\n";
#endif
                
                coerceArgAtom(toplevel, argDescWriter, calleeT, ms->getDefaultValue(optNum++));
                argc++;
            }
        }
        // pass ArrayObject through
        if (calleeTypeIter.needArguments() || calleeTypeIter.hasRest())
        {
            if (!argsOrRest)
                argsOrRest = args ? args : toplevel->arrayClass()->newArray(0);
            handleRest(toplevel, argDescWriter, argsOrRest, calleeTypeIter.needArguments());
        }
        return argc;
    }

    static void passBaseArgs(MethodEnv* env, va_list_wrapper& callerAp, ArgDescLayout& l)
    {
        (void)callerAp;
        (void)l;
        (void)env;
    }

    static void passBaseArgs(MethodEnv* env, APType& callerAp, ArgDescLayout& l)
    {
        (void)callerAp;
        (void)l;
        (void)env;
    }

    static void passTailArgs(MethodEnv* env, va_list_wrapper& callerAp, ArgDescLayout& l)
    {
        (void)callerAp;
        (void)l;

        // pass MethodEnv at the end
        *l.ptrArg() = env;
    }

    static void passTailArgs(MethodEnv* env, APType& callerAp, ArgDescLayout& l)
    {
        (void)callerAp;
        (void)l;

        // pass MethodEnv at the end
        *l.ptrArg() = env;
    }

    // coerces a set of variadic arguments to a cdecl arg description
    template <class ARG_TYPE_ITER, class AP_TYPE> static void* argCoercer(void* /*callee*/, MethodEnv* env, Traits* callerRT, ARG_TYPE_ITER callerTypeIter, AP_TYPE callerAp, void* calleeArgDescBuf)
    {
        ArgDescLayout l(calleeArgDescBuf);

        passBaseArgs(env, callerAp, l);

        MethodInfo* info = env->method;
        MethodSigArgDescIter calleeTypeIter(info);
        Traits* calleeRT = info->getMethodSignature()->returnTraits();
        AvmCore* core = info->pool()->core;
        argCoerceLoop(env, callerTypeIter, callerAp, calleeTypeIter, l);
#if CDECL_VERBOSE
        core->console << "argCoercer: "; info->print(core->console) << " ";
        if (callerRT)
            callerRT->print(core->console);
        else
            core->console << "*";
        core->console << " -> ";
        if (calleeRT)
            calleeRT->print(core->console);
        else
            core->console << "*";
        core->console << "\n";
#endif

        passTailArgs(env, callerAp, l);
        // return any return type Coercer
        return returnCoercer(core, calleeRT, callerRT);
    }

    // callerArgDesc is the number of atoms
    static void* atomvArgDescCoercer(void* callee, MethodEnv* env, Traits* retTraits, uintptr_t callerArgDesc, void* callerAp, void* calleeArgDescBuf)
    {
        AtomvArgDescIter callerTypeIter(env->core(), (int32_t)callerArgDesc);

        AvmAssert(false); // TESTME -- AtomvArgDescIter off by one error or not
        return argCoercer(callee, env, retTraits, callerTypeIter, (APType)callerAp, calleeArgDescBuf);
    }

    // callerArgDesc is the number of args
    static void* apArgDescCoercer(void* callee, MethodEnv* env, Traits* retTraits, uintptr_t callerArgDesc, void* callerAp, void* calleeArgDescBuf)
    {
        APArgDescIter callerTypeIter((int32_t)callerArgDesc, env->method);

        return argCoercer(callee, env, retTraits, callerTypeIter, (APType)callerAp, calleeArgDescBuf);
    }

    // callerArgDesc is a pointer to a string of nybbles describing arg types
    static void* ptrArgDescCoercer(void* callee, MethodEnv* env, Traits* retTraits, uintptr_t callerArgDesc, void* callerAp, void* calleeArgDescBuf)
    {
        PtrArgDescIter callerTypeIter((void*)callerArgDesc, env->core());

        return argCoercer(callee, env, retTraits, callerTypeIter, *(va_list_wrapper*)callerAp, calleeArgDescBuf);
    }

    // callerArgDesc is a value containing nybbles describing arg types
    static void* immArgDescCoercer(void* callee, MethodEnv* env, Traits* retTraits, uintptr_t callerArgDesc, void* callerAp, void* calleeArgDescBuf)
    {
        ImmArgDescIter callerTypeIter(callerArgDesc, env->core());

        return argCoercer(callee, env, retTraits, callerTypeIter, *(va_list_wrapper*)callerAp, calleeArgDescBuf);
    }

    // amount of stack space needed to call the given method cdecl style
    static int32_t argDescSize(MethodInfo* info)
    {
        AvmCore* core = info->pool()->core;
        MethodSigArgDescIter calleeTypeIter(info);

        return argDescSize(calleeTypeIter, core);
    }

    // calls "env" with supplied variadic arguments described by the "immediate" flavor of argument
    // description in argDesc
    // returns an int32_t value
    Atom coerce32CdeclArgDescEnter(Traits* retTraits, uintptr_t argDesc, MethodEnv* env, va_list_wrapper ap)
    {
        MethodInfo* info = env->method;
        Atom result = coerce32CdeclShim(
                (void*)info->handler_function(), argDescSize(info),
                immArgDescCoercer, env, retTraits, argDesc, &ap);
        return result;
    }

    // calls "env" with supplied variadic arguments described by the "pointer" flavor of argument
    // description in argDesc
    // returns an int32_t value
    Atom coerce32CdeclArgDescEnter(Traits* retTraits, char* argDesc, MethodEnv* env, va_list_wrapper ap)
    {
        MethodInfo* info = env->method;
        Atom result = coerce32CdeclShim(
                (void*)info->handler_function(), argDescSize(info), ptrArgDescCoercer, env, retTraits, (uintptr_t)argDesc, &ap);
        return result;
    }

    Atom coerce32CdeclArgDescEnter(Traits* retTraits, MethodEnv* env, int argc, Atom* argv)
    {
        MethodInfo* info = env->method;
        Atom result = coerce32CdeclShim(
                (void*)info->handler_function(), argDescSize(info), atomvArgDescCoercer, env, retTraits, (uintptr_t)argc, (void*)argv);
        return result;
    }

    Atom coerce32CdeclArgDescEnter(Traits* retTraits, MethodEnv* env, int argc, uint32_t* ap)
    {
        MethodInfo* info = env->method;
        Atom result = coerce32CdeclShim(
                (void*)info->handler_function(), argDescSize(info), apArgDescCoercer, env, retTraits, (uintptr_t)argc, (void*)ap);
        return result;
    }

    // calls "env" with supplied variadic arguments described by the "immediate" flavor of argument
    // description in argDesc
    // returns a double value
    double coerceNCdeclArgDescEnter(uintptr_t argDesc, MethodEnv* env, va_list_wrapper ap)
    {
        MethodInfo* info = env->method;
        AvmCore* core = env->core();

        double result = coerceNCdeclShim(
                (void*)info->handler_function(), argDescSize(info),
                immArgDescCoercer, env, NUMBER_TYPE, argDesc, &ap);
        return result;
    }

    // calls "env" with supplied variadic arguments described by the "pointer" flavor of argument
    // description in argDesc
    // returns a double value
    double coerceNCdeclArgDescEnter(char* argDesc, MethodEnv* env, va_list_wrapper ap)
    {
        MethodInfo* info = env->method;
        AvmCore* core = env->core();

        double result = coerceNCdeclShim(
                (void*)info->handler_function(), argDescSize(info), ptrArgDescCoercer, env, NUMBER_TYPE, (uintptr_t)argDesc, &ap);
        return result;
    }

    double coerceNCdeclArgDescEnter(MethodEnv* env, int argc, Atom* argv)
    {
        MethodInfo* info = env->method;
        AvmCore* core = env->core();

        double result = coerceNCdeclShim(
                (void*)info->handler_function(), argDescSize(info), atomvArgDescCoercer, env, NUMBER_TYPE, (uintptr_t)argc, (void*)argv);
        return result;
    }

    double coerceNCdeclArgDescEnter(MethodEnv* env, int argc, uint32_t* ap)
    {
        MethodInfo* info = env->method;
        AvmCore* core = env->core();
        double result = coerceNCdeclShim(
                (void*)info->handler_function(), argDescSize(info), apArgDescCoercer, env, NUMBER_TYPE, (uintptr_t)argc , (void*)ap);
        return result;
    }

    // calculate size needed for ap style argument block
    int32_t argDescApSize(uintptr_t argDesc, MethodEnv* env)
    {
        APArgDescIter calleeTypeIter(-1, env->method);
        ImmArgDescIter callerTypeIter(argDesc, env->core());
        return apArgDescSize(callerTypeIter, calleeTypeIter, env->core());
    }

    int32_t argDescApSize(char* argDesc, MethodEnv* env)
    {
        APArgDescIter calleeTypeIter(-1, env->method);
        PtrArgDescIter callerTypeIter(argDesc, env->core());
        return apArgDescSize(callerTypeIter, calleeTypeIter, env->core());
    }

    // convert arguments to ap style argument block, returning "argc"
    int32_t argDescArgsToAp(void* calleeArgDescBuf, uintptr_t argDesc, MethodEnv* env, va_list_wrapper ap)
    {
        APArgDescIter calleeTypeIter(-1, env->method);
        ImmArgDescIter callerTypeIter(argDesc, env->core());
        APType dst = (APType)calleeArgDescBuf;
        return argCoerceLoop(env, callerTypeIter, ap, calleeTypeIter, dst) - 1;
    }

    int32_t argDescArgsToAp(void* calleeArgDescBuf, char* argDesc, MethodEnv* env, va_list_wrapper ap)
    {
        APArgDescIter calleeTypeIter(-1, env->method);
        PtrArgDescIter callerTypeIter(argDesc, env->core());
        APType dst = (APType)calleeArgDescBuf;
        return argCoerceLoop(env, callerTypeIter, ap, calleeTypeIter, dst) - 1;
    }

    // count arguments... no size calculations
    template <class ARG_TYPE_ITER> static int32_t argDescArgCount(ARG_TYPE_ITER iter)
    {
        int32_t result = 0;

        while (iter.nextTypeKind() != kVOID)
            result++;
        return result;
    }

    // return number of arguments in description
    int32_t argDescArgCount(uintptr_t argDesc)
    {
        ImmArgDescIter iter(argDesc, NULL);
        return argDescArgCount(iter);
    }

    int32_t argDescArgCount(char* argDesc)
    {
        PtrArgDescIter iter(argDesc, NULL);
        return argDescArgCount(iter);
    }

    // convert arguments to Atoms
    void argDescArgsToAtomv(Atom* args, uintptr_t argDesc, MethodEnv* env, va_list_wrapper ap)
    {
        AvmCore* core = env->core();
        ImmArgDescIter callerTypeIter(argDesc, core);
        AtomvArgDescIter calleeTypeIter(core);
        APType dst = (APType)args;
        argCoerceLoop(env, callerTypeIter, ap, calleeTypeIter, dst);
    }

    void argDescArgsToAtomv(Atom* args, char* argDesc, MethodEnv* env, va_list_wrapper ap)
    {
        AvmCore* core = env->core();
        PtrArgDescIter callerTypeIter(argDesc, core);
        AtomvArgDescIter calleeTypeIter(core);
        APType dst = (APType)args;
        argCoerceLoop(env, callerTypeIter, ap, calleeTypeIter, dst);
    }
    
    // convert arguments to AtomList
    void argDescArgsToAtomList(AtomList& dst, uintptr_t argDesc, MethodEnv* env, va_list_wrapper ap)
    {
        AvmCore* core = env->core();
        ImmArgDescIter callerTypeIter(argDesc, core);
        AtomvArgDescIter calleeTypeIter(core);
        argCoerceLoop(env, callerTypeIter, ap, calleeTypeIter, dst);
    }

    void argDescArgsToAtomList(AtomList& dst, char* argDesc, MethodEnv* env, va_list_wrapper ap)
    {
        AvmCore* core = env->core();
        PtrArgDescIter callerTypeIter(argDesc, core);
        AtomvArgDescIter calleeTypeIter(core);
        argCoerceLoop(env, callerTypeIter, ap, calleeTypeIter, dst);
    }

#ifdef VMCFG_AOT
    uintptr_t aotThunker(MethodEnv* env, int32_t argc, uint32_t* argv)
    {
        Traits* rt = env->method->getMethodSignature()->returnTraits();
        return coerce32CdeclArgDescEnter(rt, env, argc, (uint32_t* )argv);
    }

    double aotThunkerN(MethodEnv* env, int32_t argc, uint32_t* argv)
    {
        return coerceNCdeclArgDescEnter(env, argc, (uint32_t* )argv);
    }
#endif // VMCFG_AOT
}

#endif // VMCFG_CDECL
