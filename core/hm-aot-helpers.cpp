/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "avmplus.h"
#ifdef VMCFG_HALFMOON_AOT_RUNTIME

#include "AOTCompiler.h"

#ifdef DEBUGGER
#include "avmplusDebugger.h"
#endif

using namespace avmplus;

//
// Exception handling helper stubs
//

extern "C" {
    const Traits* builtin_traits_any = 0;
}

extern "C" int32_t llBeginCatch(MethodEnv* env,
                     ExceptionFrame* ef,
                     int pc,
                     int exception_count,
                     AOTExceptionDesc* exceptionDescs,
                     Traits** matchTraitspPtrs,
                     Atom* exceptionAtomp)
{
    PoolObject* pool = env->method->pool();
    AvmCore* core = pool->core;
    ef->beginCatch();
    Exception* exception = core->exceptionAddr;
    Atom atom = exception->atom;
    for (int i = 0; i < exception_count; ++i) {
        AOTExceptionDesc& desc = exceptionDescs[i];
        if (desc.from <= pc && pc < desc.to &&
            AvmCore::istype(atom, matchTraitspPtrs[i])) {
            // if traits are zero and not the special any traits, it's an uninitialized
            // type global. Don't spurtiously match it as if it were a real "any."
            // TODO: not necessary if we move traits initialization to parsing, where
            // it really belongs.
            if (!matchTraitspPtrs[i] && matchTraitspPtrs[i] != builtin_traits_any)
                continue;
            ef->beginTry(core);
            *exceptionAtomp = atom;
            return i;
        }
    }
    
    // No matching exception, so rethrow.
    core->throwException(exception);
    assert(!"not reached");
    return 0;
}

extern "C" Traits* llLoadCatchTraits(MethodEnv* env, AOTExceptionDesc* exceptionDescs)
{
    AOTExceptionDesc& desc = exceptionDescs[0];
    PoolObject* pool = env->method->pool();
    AvmCore* core = pool->core;
    Traits* scopeTraits = OBJECT_TYPE;
    
    if(desc.nameIndex) {
        Multiname qn;
        pool->parseMultiname(qn, desc.nameIndex);
        scopeTraits = Traits::newCatchTraits(env->toplevel(), pool, (TraitsPosPtr)desc.typeIndexU30, qn.getName(), qn.getNamespace());
    }
    
    return scopeTraits;
}

extern "C" Traits* llGetInterfaceTraitsFromPool(PoolObject* pool, int i)
{
    return pool->getClassTraits(i)->itraits;
}

//
// Constant-pool helper stubs
//

extern "C" String* llGetString(PoolObject* pool, int i)
{
    if (i == 0)
        return pool->core->kEmptyString;
    return pool->getString(i);
}

extern "C" Namespace* llGetNamespace(PoolObject* pool, int i)
{
    return pool->getNamespace(i);
}

// Not usually used, but here as a backstop in case someone wants to turn off inline code generation.
extern "C" MethodInfo* llGetMethodInfo(PoolObject* pool, int i)
{
    return pool->getMethodInfo(i);
}

extern "C" Traits* llGetClassTraits(PoolObject* pool, int classIndex)
{
    Traits* ctraits = pool->getClassTraits(classIndex);
    return ctraits;
}

extern "C" Traits* llGetScriptTraits(PoolObject* pool, int scriptIndex)
{
    Traits* straits = pool->getScriptTraits(scriptIndex);
    return straits;
}

extern "C" PoolObject* llGetPoolSameWorker(PoolObject* pool, AOTInfo* aotInfo)
{
#ifdef VMCFG_HALFMOON_AOT_RUNTIME // Halfmoon AOT accesses precomputed multinames directly
    PoolObject* poolSameWorker = NULL;
    std::vector<std::pair<PoolObject*, AvmCore*> > pools = aotInfo->pools;
    for(std::vector<std::pair<PoolObject*, AvmCore*> >::iterator it = pools.begin(); it != pools.end(); ++it)
    {
        //PoolObject *checkPool = (PoolObject *)(*it).first;
        if((*it).second == pool->core)
            poolSameWorker = (*it).first;
    }
    return poolSameWorker;
#else
    return NULL;
#endif

    
}
//
// Class creation.
//
// The tricky issue here is to initialize the scope type chain and the scope chain and also
// to retrieve the class and instanca traits for the class.
//
// Pointers to the locations where the class and instance traits should be saved are passed in
// as well as an array of pointers to pointers to the scope chait traits.
// The fist layer of indirection allows the table to be constructed statically; the second lavel of
// indirection is bacause the locations pointed to are (like the scope and instance traits pointers
// just mentioned) lazily filled in, as the values become known.
//
// Finally, we must do some initializations that would normally have been done by the verifier.
//

//#define DEBUG_SCOPES   // uncomment to enable scope tracing

extern "C" ClassClosure* llNewClass(MethodEnv* env, int classIndex, Traits** scopeTraitsPtrs,
    ClassClosure* base, int nWithScopes, int scopeCount, Atom* scopes)
{
    PoolObject* pool = env->method->pool();
    Traits* ctraits = pool->getClassTraits(classIndex);
    AvmAssert(ctraits->pool == pool);
    
#ifdef DEBUG_SCOPES
    StUTF8String className(ctraits->formatClassName());
    printf(">> newClass %s %d %p\n", className.c_str(), classIndex, pool);
#endif
    
    if (ctraits)
    {
        Traits* itraits = ctraits->itraits;
        
#ifdef DEBUG_SCOPES
        StUTF8String ctn(ctraits ? ctraits->formatClassName(): 0);
        StUTF8String itn(itraits ? itraits->formatClassName(): 0);
        printf(">>   traits %s %s\n", ctn.c_str(), itn.c_str());
#endif
        // TODO: this is to support faster interface calls
        //   (not yet implemented in compile-aot)
        // const AOTInfo* aotInfo = pool->aotInfo;
        // AvmAssert(itraits->m_interfaceBindingFunction == NULL);
        // itraits->m_interfaceBindingFunction = aotInfo->interfaceBindingFunctions[classIndex];
        
        // Do initialiations the verifier would have done
        MethodInfo* info = env->method;
        AvmCore* core = pool->core;
        
        // Create a scope type chain; we don't really have the info we need but we can
        // assume that the traits of the actual scopes are in fact the correct types.
        MMgc::GC::AllocaAutoPtr _scopeTraitsBuffer;
        Traits** scopeTraits = reinterpret_cast<Traits**> (VMPI_alloca(core, _scopeTraitsBuffer, sizeof(Traits*) * scopeCount));
        for (int i = 0; i < scopeCount; ++i) {
            scopeTraits[i] = scopeTraitsPtrs[i];
#ifdef DEBUG_SCOPES
            StUTF8String stn(scopeTraits[i] ? scopeTraits[i]->formatClassName(): 0);
            printf(">>   scope %s\n", stn.c_str());
#endif
        }
        const ScopeTypeChain* cscope = ScopeTypeChain::create(core->GetGC(), ctraits, info->declaringScope(), scopeTraits, scopeCount, nWithScopes, NULL, ctraits);
        const ScopeTypeChain* iscope = ScopeTypeChain::create(core->GetGC(), itraits, cscope, NULL, ctraits, itraits);
        
        Toplevel* toplevel = env->toplevel();
        ctraits->resolveSignatures(toplevel);
        itraits->resolveSignatures(toplevel);
        ctraits->setDeclaringScopes(cscope);
        itraits->setDeclaringScopes(iscope);
        
        ctraits->initActivationTraits();
        itraits->initActivationTraits();
    }
    ClassClosure* res = env->newclass(ctraits, base, env->scope(), scopes);
#ifdef DEBUG_SCOPES
    printf(">> newClass exit %s %d %p\n", className.c_str(), classIndex, pool);
#endif
    return res;
}

//
// Function creation.
//
// The tricky issue here is to initialize the scope type chain and the scope chain; this works the
// same as for llNewClass.
//
// Again, we must do some initializations that would normally have been done by the verifier.
//

extern "C" ClassClosure* llNewFunction(MethodEnv* env, uint32_t methodindex,
    Traits** scopeTraitsPtrs, int nWithScopes,
    int scopeCount, Atom* scopes)
{
    PoolObject* pool = env->method->pool();
    AvmAssert(methodindex < pool->methodCount());
    MethodInfo* body = pool->getMethodInfo(methodindex);
    Traits* declTraits = body->declaringTraits();
#ifdef DEBUG_SCOPES
    StUTF8String mn(env->method->getMethodName());
    StUTF8String mn2(body->getMethodName());
    StUTF8String bt(declTraits ? declTraits->formatClassName(): 0);
    printf(">> newFunction %s, %d, %s, %s\n", mn.c_str(), methodindex, mn2.c_str(), bt.c_str());
#endif
    
    if (!declTraits) {
        const AOTInfo* aotInfo = pool->aotInfo;
        // Do initialiations the verifier would have done
        Toplevel* toplevel = env->toplevel();
        AvmCore* core = pool->core;
        MMgc::GC::AllocaAutoPtr _scopeTraitsBuffer;
        Traits** scopeTraits = reinterpret_cast<Traits**> (VMPI_alloca(core, _scopeTraitsBuffer, sizeof(Traits*) * scopeCount));
        for (int i = 0; i < scopeCount; ++i) {
            scopeTraits[i] = scopeTraitsPtrs[i];
#ifdef DEBUG_SCOPES
            StUTF8String stn(scopeTraits[i] ? scopeTraits[i]->formatClassName(): 0);
            printf(">>  scope %s\n", stn.c_str());
#endif
        }
        const ScopeTypeChain* scopeTypeChain = ScopeTypeChain::create(core->GetGC(), core->traits.function_itraits, env->method->declaringScope(), scopeTraits, scopeCount, nWithScopes, NULL, NULL);
        body->makeIntoPrototypeFunction(toplevel, scopeTypeChain);
        declTraits = body->declaringTraits();
        AvmAssert(declTraits != 0);
        Traits* atraits = body->activationTraits();
        if (atraits) {
            AvmAssert(body->activationTraits()->init == NULL);
            AvmThunkNativeFunctionHandler handler = aotInfo->activationInfo[methodindex].initHandler;
            if (handler != NULL) {
                NativeMethodInfo compiledMethodInfo;
                compiledMethodInfo.thunker = aotThunker;
                AvmThunkNativeHandler nhandler;
                nhandler.function = handler;
                atraits->init = MethodInfo::create(core->GetGC(), MethodInfo::kInitMethodStub, body->activationTraits(), &compiledMethodInfo, nhandler, aotInfo->activationInfo[methodindex].initMethodId);
            }
            
            // ---------------------------------------------------------------------------
            // Copied from Verifier::write()
            const ScopeTypeChain *scope = body->activationScope();
            if (scope == NULL) {
                scope = body->declaringScope()->cloneWithNewTraits(core->GetGC(), atraits);
                atraits->setDeclaringScopes(scope);
                body->init_activationScope(scope);
            }
            // ---------------------------------------------------------------------------
        }
    }
    
    
    ClassClosure* res = env->newfunction(body, scopes);
    return res;
}

//
// Create new activation traits
//
extern "C" ScriptObject* llNewActivation(MethodEnv *env)
{
    ScriptObject* result = env->newUninitializedActivation();
    MethodEnv* init = result->vtable->init;
    //MethodInfo with method_id = -1 are being skipped in halfmoon compiling.
    //hence at runtime adding this check. 
    if (init && init->method && init->method->method_id() >=0 ) {
        MethodInfo* initMI = init->method;
        AvmAssert(initMI->pool() == env->method->pool());
        const AOTInfo* aotInfo = initMI->pool()->aotInfo;
        AvmAssert(env->method->method_id() >= 0);
        uint32_t activationInitMethodId = aotInfo->activationInfo[env->method->method_id()].initMethodId;
        env->abcEnv()->setMethod(activationInitMethodId, init);
        init->coerceEnter(result->atom());
    }
    return result;
}

//
// Materializes a rest args object
//
extern "C" ArrayObject* llCreateRestHelper(MethodEnv *env, Atom *ap, int argc)
{
    // Unlike MethodEnv::createRestHelper, it isn't necessary to skip over
    // non-vararg params in the ap array since they aren't present
    return env->toplevel()->arrayClass()->newarray(ap, argc);
}

//
// calling createArguments because it creates ArrayObject and sets callee in arguments
//
extern "C" ArrayObject* llCreateArgumentHelper(MethodEnv *env, Atom *ap, int argc)
{
    return env->createArguments(ap,argc);
}

//
// Throws a null pointer exception
//
extern "C" void llNPE(MethodEnv* env)
{
    env->toplevel()->throwTypeError(kConvertNullToObjectError);
}

//
// Throws either an undefined pointer exception or a null pointer exceptiom, depending on
// the value of the atom.
//
extern "C" void llUPE(MethodEnv* env, Atom atom)
{
    AvmAssert(AvmCore::isNullOrUndefined(atom));
    // Should call nullcheckfail(), but that's private.
    // Call nullcheck, which will always throw because we already know that atom is null or undefined
    env->nullcheck(atom);
    AvmAssert(!"must not return");
    
    // But just in case it returns, throw an NPE
    llNPE(env);
}

//
// Throws a verify error (generated for functions that fail to verify)
//
extern "C" void llVerifyError(MethodEnv* env)
{
    env->toplevel()->throwVerifyError(kCorruptABCError);
}

extern "C" Atom llDoubleToAtom(AvmCore* core, double n)
{
    return core->doubleToAtom(n);
}

extern "C" int32_t llDoubleToInt32(AvmCore* core, double n)
{
    return core->doubleToInt32(n);
}

extern "C" double llMod(double x, double y)
{
    return MathUtils::mod(x, y);
}


extern "C" Traits* llGetVectorTraits(Traits* param_traits, Namespace* ns)
{
    //TODO_WORKER: This could hit performance;
    assert(param_traits && "param_traits are null");
    AvmCore* core = param_traits->pool->core;
    Stringp fullName = VectorClass::makeVectorClassName(core, param_traits);
    Traits* traits = core->domainMgr()->findTraitsInPoolByNameAndNS(param_traits->pool,fullName,ns);

    return traits;
}

#ifdef VMCFG_TELEMETRY_SAMPLER
extern "C" void llCoreTakeSample(AvmCore* core )
{
    if (core->sampleTicks)
        core->takeSample();
}
#endif 

namespace avmplus {
    // hm-stubs calls these, but we shouldn't be including jit-calls.h in the aot runtime
    // so backfill them here.
    void upe(MethodEnv* env)
    {
        env->toplevel()->throwTypeError(kConvertUndefinedToObjectError);
    }
    
    void npe(MethodEnv* env)
    {
        env->toplevel()->throwTypeError(kConvertNullToObjectError);
    }
}

#endif // VMCFG_HALFMOON_AOT_RUNTIME

