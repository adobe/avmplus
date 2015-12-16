/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef AOTCompiler_h
#define AOTCompiler_h

#include "avmplus.h"
#include "CdeclThunk.h"
#include <vector>
#ifdef VMCFG_BUFFER_GUARD
#include "GenericGuard.h"
#endif

#define EXPORT_OPCODE extern "C"

#ifdef _MSC_VER
#define ATTR_VISIBILITY_DEFAULT __declspec(dllexport)
#define ATTR_CONST
#else // ndef _MSC_VER
#define ATTR_VISIBILITY_DEFAULT __attribute__ ((visibility("default")))
#define ATTR_CONST __attribute__((const))
#endif // ndef _MSC_VER

#ifdef AVMPLUS_64BIT
#define ALIGN8BYTE __attribute__((__aligned__(8)))
#else
#define ALIGN8BYTE
#endif

namespace avmplus {
    class Traits;
    class AbcEnv;
    typedef int(*InterfaceBindingFunction)(int);
#ifndef VMCFG_AOT  // TEMP hack to enable building field offset files for ordinary shell
    typedef void (AvmPlusScriptableObject::*AvmThunkNativeMethodHandler)();
    typedef void (*AvmThunkNativeFunctionHandler)(AvmPlusScriptableObject* obj);
    union AvmThunkNativeHandler
    {
        AvmThunkNativeMethodHandler method;
        AvmThunkNativeFunctionHandler function;
    };
#endif
}

//------------------------------------------------------------------------------
// LLVM type hacks
//------------------------------------------------------------------------------
// Because we can't specialise templates on typedefs we hide Atoms, bool, etc. as
// pointers to these opaque structs. The pointers are never dereferenced, they
// just get cast to whatever their real type is.
//------------------------------------------------------------------------------
typedef struct LLVMAtomS* LLVMAtom;
typedef struct LLVMBoolS* LLVMBool;
typedef struct LLVMUnusedParamS* LLVMUnusedParam;
typedef struct LLVMMultinameIndexS* LLVMMultinameIndex;
typedef struct LLVMMultinameIndexMaybeIntS* LLVMMultinameIndexMaybeInt;
typedef struct LLVMMultinamePtrMaybeIntS* LLVMMultinamePtrMaybeInt;
//------------------------------------------------------------------------------

struct MethodDebugInfo {
    const int local_count;
    const int scope_count;
    const int file_name;
    const int * const local_names;
    const int line_count;
    const int * const lines;

    // unused, here only to prevent MSVC warnings
    MethodDebugInfo() : local_count(0), scope_count(0), file_name(0), 
                        local_names(NULL), line_count(0), lines(NULL) {} 
};

typedef uintptr_t (*AOTLazyEvalFunc)(avmplus::MethodEnv *env, uintptr_t clientData);

struct AOTLazyEvalInfo
{
    uint32_t methodID;
    AOTLazyEvalFunc func;
    uintptr_t funcData;
};

struct AOTActivationInfo
{
    uint32_t initMethodId;
    const avmplus::AvmThunkNativeFunctionHandler initHandler;

    // unused, here only to prevent MSVC warnings
    AOTActivationInfo() : initHandler(NULL) {} 
};

struct AOTInfo {
    unsigned char origABCSHA1[20]; // sha1 hash of the original abc

    const unsigned char* abcBytes;
    size_t nABCBytes;

    const MethodDebugInfo* methodDebugInfos; // may be NULL if not debugging but it's always in the struct
    const avmplus::AvmThunkNativeFunctionHandler* abcMethods;
    size_t nABCMethods;

    //An Array of int ( flags ) to store some more information related to method.
#ifdef VMCFG_HALFMOON_AOT_RUNTIME 
    const int32_t *methodFlagsArr;
#endif
    
    // functions to resolve IIDs->dispids
    const avmplus::InterfaceBindingFunction* interfaceBindingFunctions;
    size_t nInterfaceBindingFunctions;

    // Activation traits info, indexed by methodId up to nActivationTraits;
    const AOTActivationInfo *activationInfo;

    // Per-ABC Lazy evaluation
    const AOTLazyEvalInfo *lazyEvalInfos;
    uintptr_t **lazyEvalValPtrs;
    uintptr_t *lazyEvalVals;
    size_t nLazyEvals;

#ifndef VMCFG_HALFMOON_AOT_RUNTIME // Halfmoon AOT accesses precomputed multinames directly
    // static multinames
    avmplus::Multiname **multinames; // TODO could probably be an array of multinames
    const int32_t *multinameIndices;
#else
    //TODO_WORKER: Need to make a better fix
    std::vector<std::pair<avmplus::PoolObject*, avmplus::AvmCore*> > pools;
#endif
};

#ifdef VMCFG_HALFMOON_AOT_RUNTIME
struct AOTExceptionDesc {
    int from, to;   // start and end vpcs of the exception
    int nameIndex; // index of the multiname for the catch variable name
    uint8_t typeIndexU30[5]; // where to store the u30 for the match traits type; newCatchTraits needs this!
}ALIGN8BYTE;
#endif

#ifdef VMCFG_BUFFER_GUARD
// Note that this assumes that there is only one AbcEnv/PoolObject per AOTInfo! I.e., a given ABC is only instantiated once!
class AOTLazyEvalGuard : public avmplus::LoadRedirGuard
{
protected:
    const avmplus::AbcEnv *m_abcEnv;

public:
    AOTLazyEvalGuard(const avmplus::AbcEnv *abcEnv);
    uintptr_t *redirectLoad(uintptr_t *faultAddr);
};
#endif

#ifndef VMCFG_HALFMOON_AOT_RUNTIME // Halfmoon AOT accesses precomputed multinames directly
#define EMPTY_AOTInfo { {}, NULL, 0, NULL, NULL, 0, NULL, NULL, 0, NULL, NULL, 0, NULL, NULL, NULL, 0, NULL, NULL, NULL  }
#else
#define EMPTY_AOTInfo { {}, NULL, 0, NULL, NULL, 0, NULL, NULL, 0, NULL, NULL, 0, NULL, NULL, NULL, 0, NULL}
#endif

struct LLVMVectorInstance {
    avmplus::Traits* iTraits;
    avmplus::Traits** vectorParamTraitsId;
};

class AOTMethodFrame {
    avmplus::MethodFrame m_frame;
public:
    inline void enter(avmplus::AvmCore* core, avmplus::MethodEnv* e) {
        m_frame.enter(core, e);
    }

    inline void exit(avmplus::AvmCore* core) {
        m_frame.exit(core);
    }

    inline void set_dxns(avmplus::Namespace* dxns) {
        m_frame.setDxns(dxns);
    }
};

extern "C" {
#ifdef VMCFG_HALFMOON_AOT_RUNTIME
    extern ATTR_VISIBILITY_DEFAULT const AOTInfo* aotInfos[];
#else
    extern ATTR_VISIBILITY_DEFAULT const AOTInfo aotInfos[];
#endif
    extern ATTR_VISIBILITY_DEFAULT const size_t nAOTInfos;
    extern ATTR_VISIBILITY_DEFAULT const avmplus::AbcEnv* aotAbcEnvs[];
    extern ATTR_VISIBILITY_DEFAULT const uint32_t nAotAbcEnvs;
    extern ATTR_VISIBILITY_DEFAULT const AOTInfo builtin_aotInfo;
#ifdef VMCFG_HALFMOON_AOT_RUNTIME  // halfmoon AOT doesn't care whether it's compiling for shell or player
    extern ATTR_VISIBILITY_DEFAULT const AOTInfo sdk_aotInfo;
#else
    extern ATTR_VISIBILITY_DEFAULT const AOTInfo shell_toplevel_aotInfo;
    extern ATTR_VISIBILITY_DEFAULT const AOTInfo avmglue_aotInfo;
#endif
    extern ATTR_VISIBILITY_DEFAULT const uint32_t abcNVectorInstances;
    extern ATTR_VISIBILITY_DEFAULT LLVMVectorInstance abcVectorInstances[];
    extern ATTR_VISIBILITY_DEFAULT const uint32_t g_aotSamplerEnabled;
    extern ATTR_VISIBILITY_DEFAULT const LLVMUnusedParam g_unusedParam;
}

avmplus::PoolObject* aotGetPool(const avmplus::MethodEnv* env) ATTR_CONST; 

MMgc::GC* aotGetGC(const avmplus::MethodEnv* env) ATTR_CONST;

avmplus::String* aotGetString(const avmplus::MethodEnv* env, int32_t index) ATTR_CONST;

#endif
