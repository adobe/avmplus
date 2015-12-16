/* -*- Mode: C++; c-basic-offset: 2; indent-tabs-mode: nil; tab-width: 2 -*- */
/* vi: set ts=2 sw=2 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine.].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2010
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

//
// Per-function bitcode generation
//

#include "avmplus.h"

#ifdef VMCFG_HALFMOON

#include <queue>  // TODO: eliminate STL
#include "llvm-module.h"
#include "llvm-emitter.h"
#include "poolinfo.h"
#include "compileabc.h"

#include "llvm/Support/Casting.h"  // dyn_cast
#undef DEBUG  // "llvm/Support/Debug.h" defines DEBUG! No, seriouusly!
#include "llvm/Support/Debug.h" // llvm::dbgs()
#include "llvm/PassManager.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Timer.h"
#include "llvm/ADT/Triple.h"

#ifdef AVMPLUS_64BIT
    #include "halfmoon/generated/Stub_llvmtable_64.hh"
#else
    #include "halfmoon/generated/Stub_llvmtable.hh"
#endif

namespace options {
    using namespace llvm;
    using std::string;
    
    // TODO: revisit defaults
    static cl::opt<bool> verifyFunctions("verify-functions", cl::desc("Verify bitcode for each function"), cl::init(false));
    static cl::opt<string> dumpMatching("dump-matching", cl::desc("dump IR for functions matching the given string"));
    static cl::opt<bool> debugScopes("debug-scopes", cl::Hidden, cl::desc("display information useful for debugging scope issues"));
};

namespace compile_abc
{
using namespace avmplus;
    
#define STUBINFO(n) (isWindowsTriple ? &win_stubinfo_##n : &ios_stubinfo_##n)
#define DEFINE_STUB(name, ios_mangle, win_mangle, argDesc) \
    LLVMModule::StubInfo ios_stubinfo_##name = { #name, ios_mangle, argDesc, false, -1 }; \
    LLVMModule::StubInfo win_stubinfo_##name = { #name, win_mangle, argDesc, false, -1 };
    
DEFINE_STUB(mop_rangeCheckFailed, "_ZN7avmplus20mop_rangeCheckFailedEPNS_9MethodEnvE", "?mop_rangeCheckFailed@avmplus@@YAXPAVMethodEnv@1@@Z", "v;*'avmplus::MethodEnv'");

#ifdef AVMPLUS_64BIT
    DEFINE_STUB(coerceobj_atom, "_ZN7avmplus14coerceobj_atomEPNS_9MethodEnvExPNS_6TraitsE", "?coerceobj_atom@avmplus@@YAXPAVMethodEnv@1@HPAVTraits@1@@Z", "v;*'avmplus::MethodEnv';a;*'avmplus::Traits'");
    DEFINE_STUB(compare, "_ZN7avmplus7AvmCore7compareExx",  "?compare@AvmCore@avmplus@@SAHHH@Z", "a;a;a");
    DEFINE_STUB(atomWriteBarrier, "_ZN7avmplus7AvmCore16atomWriteBarrierEPN4MMgc2GCEPKvPxx", "?atomWriteBarrier@AvmCore@avmplus@@SAXPAVGC@MMgc@@PBXPAHH@Z", "v;*'MMgc::GC';*'avmplus::ScriptObject';*a;a");
    DEFINE_STUB(op_add_a_aa, "_ZN7avmplus11op_add_a_aaEPNS_7AvmCoreExx",  "?op_add_a_aa@avmplus@@YAHPAVAvmCore@1@HH@Z", "a;*'avmplus::AvmCore';a;a");
    DEFINE_STUB(hasnextproto, "_ZNK7avmplus9MethodEnv12hasnextprotoERxRi",  "?hasnextproto@MethodEnv@avmplus@@QBAHAAH0@Z", "i;*'avmplus::MethodEnv';*a;*i");
#else
    DEFINE_STUB(coerceobj_atom, "_ZN7avmplus14coerceobj_atomEPNS_9MethodEnvEiPNS_6TraitsE", "?coerceobj_atom@avmplus@@YAXPAVMethodEnv@1@HPAVTraits@1@@Z", "v;*'avmplus::MethodEnv';a;*'avmplus::Traits'");
    DEFINE_STUB(compare, "_ZN7avmplus7AvmCore7compareEii",  "?compare@AvmCore@avmplus@@SAHHH@Z", "a;a;a");
    DEFINE_STUB(atomWriteBarrier, "_ZN7avmplus7AvmCore16atomWriteBarrierEPN4MMgc2GCEPKvPii", "?atomWriteBarrier@AvmCore@avmplus@@SAXPAVGC@MMgc@@PBXPAHH@Z", "v;*'MMgc::GC';*'avmplus::ScriptObject';*a;a");
    DEFINE_STUB(op_add_a_aa, "_ZN7avmplus11op_add_a_aaEPNS_7AvmCoreEii",  "?op_add_a_aa@avmplus@@YAHPAVAvmCore@1@HH@Z", "a;*'avmplus::AvmCore';a;a");
    DEFINE_STUB(hasnextproto, "_ZNK7avmplus9MethodEnv12hasnextprotoERiS1_",  "?hasnextproto@MethodEnv@avmplus@@QBAHAAH0@Z", "i;*'avmplus::MethodEnv';*a;*i");
#endif
    
DEFINE_STUB(llCreateRestHelper, "llCreateRestHelper", "llCreateRestHelper", "*'avmplus::ScriptObject';*'avmplus::MethodEnv';*a;i");
DEFINE_STUB(llCreateArgumentHelper, "llCreateArgumentHelper", "llCreateArgumentHelper", "*'avmplus::ScriptObject';*'avmplus::MethodEnv';*a;i");
DEFINE_STUB(doubleToInt32, "llDoubleToInt32", "llDoubleToInt32", "i;*'avmplus::AvmCore';d");
DEFINE_STUB(privateWriteBarrierRC, "_ZN4MMgc2GC21privateWriteBarrierRCEPKvS2_S2_", "?privateWriteBarrierRC@GC@MMgc@@QAAXPBX00@Z", "v;*'MMgc::GC';*'avmplus::ScriptObject';*c;*c");
DEFINE_STUB(intToAtom, "_ZN7avmplus7AvmCore9intToAtomEi", "?intToAtom@AvmCore@avmplus@@QAAHH@Z", "a;*'avmplus::AvmCore';i");
DEFINE_STUB(uintToAtom, "_ZN7avmplus7AvmCore10uintToAtomEj", "?uintToAtom@AvmCore@avmplus@@QAAHI@Z", "a;*'avmplus::AvmCore';i");
DEFINE_STUB(beginTry, "_ZN7avmplus14ExceptionFrame8beginTryEPNS_7AvmCoreE", "?beginTry@ExceptionFrame@avmplus@@QAAXPAVAvmCore@2@@Z", "v;*'avmplus::ExceptionFrame';*'avmplus::AvmCore'");
DEFINE_STUB(endTry, "_ZN7avmplus14ExceptionFrame6endTryEv", "?endTry@ExceptionFrame@avmplus@@QAAXXZ", "v;*'avmplus::ExceptionFrame'");
DEFINE_STUB(debugEnter, "_ZN7avmplus9MethodEnv10debugEnterEPKhPNS_13CallStackNodeEPNS_9FramePtr_EPVl",  "?debugEnter@MethodEnv@avmplus@@QAAXPBEPAVCallStackNode@2@PAUFramePtr_@2@PCH@Z", "v;*'avmplus::MethodEnv';*c;*'avmplus::CallStackNode';*a;*i");
DEFINE_STUB(debugExit, "_ZN7avmplus9MethodEnv9debugExitEPNS_13CallStackNodeE",  "?debugExit@MethodEnv@avmplus@@QAAXPAVCallStackNode@2@@Z", "v;*'avmplus::MethodEnv';*'avmplus::CallStackNode'");

DEFINE_STUB(createInstanceProc, 0, 0, "*'avmplus::ScriptObject';*c");
DEFINE_STUB(resolveInterfaceProc, 0, 0, "*'avmplus::MethodEnv';*'avmplus::MethodEnv';*'avmplus::MethodInfo';*'avmplus::ScriptObject'");
DEFINE_STUB(doubleToAtom, "llDoubleToAtom",  "llDoubleToAtom", "a;*'avmplus::AvmCore';d");
DEFINE_STUB(mod, "llMod", "llMod", "d;d;d");
DEFINE_STUB(llBeginCatch, "llBeginCatch", "llBeginCatch", "i;*'avmplus::MethodEnv';*'avmplus::ExceptionFrame';i;i;*'AOTExceptionDesc';**'avmplus::Traits';*a");
DEFINE_STUB(llGetString, "llGetString", "llGetString", "*'avmplus::String';*'avmplus::PoolObject';i");
DEFINE_STUB(llGetNamespace, "llGetNamespace", "llGetNamespace", "*'avmplus::Namespace';*'avmplus::PoolObject';i");
DEFINE_STUB(llGetMethodInfo, "llGetMethodInfo", "llGetMethodInfo", "*'avmplus::MethodInfo';*'avmplus::PoolObject';i");
DEFINE_STUB(llGetClassTraits, "llGetClassTraits", "llGetClassTraits", "*'avmplus::Traits';*'avmplus::PoolObject';i");
DEFINE_STUB(llGetScriptTraits, "llGetScriptTraits", "llGetScriptTraits", "*'avmplus::Traits';*'avmplus::PoolObject';i");
DEFINE_STUB(llLoadCatchTraits, "llLoadCatchTraits", "llLoadCatchTraits", "*'avmplus::Traits';*'avmplus::MethodEnv';*'AOTExceptionDesc'");
DEFINE_STUB(activationTraits, "_ZNK7avmplus10MethodInfo16activationTraitsEv",  "?activationTraits@MethodInfo@avmplus@@QBEPAVTraits@2@XZ", "*'avmplus::Traits';*'avmplus::MethodInfo'");
DEFINE_STUB(llGetInterfaceTraitsFromPool, "llGetInterfaceTraitsFromPool", "llGetInterfaceTraitsFromPool", "*'avmplus::Traits';*'avmplus::PoolObject';i");
DEFINE_STUB(llNewClass, "llNewClass", "llNewClass",  "*'avmplus::ScriptObject';*'avmplus::MethodEnv';i;**'avmplus::Traits';*'avmplus::ScriptObject';i;i;*a");
DEFINE_STUB(llNewFunction, "llNewFunction",  "llNewFunction", "*'avmplus::ScriptObject';*'avmplus::MethodEnv';i;**'avmplus::Traits';i;i;*a");
DEFINE_STUB(llNewActivation, "llNewActivation", "llNewActivation", "*'avmplus::ScriptObject';*'avmplus::MethodEnv'");
DEFINE_STUB(llNPE, "llNPE", "llNPE", "v;*'avmplus::MethodEnv'");
DEFINE_STUB(llVerifyError, "llVerifyError", "llVerifyError", "v;*'avmplus::MethodEnv'");
DEFINE_STUB(llUPE, "llUPE",  "llUPE", "v;*'avmplus::MethodEnv';a");

DEFINE_STUB(llGetVectorTraits, "llGetVectorTraits",  "llGetVectorTraits","*'avmplus::Traits';*'avmplus::Traits';*'avmplus::Namespace'");
DEFINE_STUB(llCoreTakeSample, "llCoreTakeSample",  "llCoreTakeSample","v;*'avmplus::AvmCore'");
DEFINE_STUB(finddef_miss, "_ZN7avmplus12finddef_missEPPNS_12ScriptObjectEPNS_11MethodFrameE",  "?finddef_miss@avmplus@@YIPAVScriptObject@1@PAPAV21@PAVMethodFrame@1@@Z","*'avmplus::ScriptObject';**'avmplus::ScriptObject';*'avmplus::MethodFrame'");
DEFINE_STUB(llGetPoolSameWorker, "llGetPoolSameWorker", "llGetPoolSameWorker", "*'avmplus::PoolObject';*'avmplus::PoolObject';*'AOTInfo'");

// TODO: depending on platform, this might sometimes be _setjmp3 or setjmp.
// Figure out what the platform requires and make appropriate substitution.
// (Some of those take an additional int param, so we pass it for good measure.)
DEFINE_STUB(setjmp, "_setjmp", "_setjmp", "i;*i;i");

// Walk the IR graph top-down, generating LLVM instructions for each Instr.

LLVMEmitter::LLVMEmitter(MethodInfo* method, InstrGraph* ir)
: llvm::IRBuilder<>(method->pool()->poolInfo->modulep->getContext())
, method(method)
, pool(method->pool())
, core(static_cast<CompilerCore*>(pool->core))
, module(*pool->poolInfo->modulep)
, signature(method->getMethodSignature())
, ir(ir)
, coreAddr(0)
, gcAddr(0)
, currentFunction(0)
, entryBlock(0)
, epilogBlock(0)
, returnPhi(0)
, def_ins_(0)
, idToBlock_(0)
, env_param(0)
, argc_param(0)
, ap_param(0)
, method_frame_(0)
, params_(0)
, maxAtomParams_(0)
, maxAvmParamSize_(0)
, blocks_(0)
, num_blocks_(0)
, current_block_(0)
, max_argc_(0)
, npe_block(0)
, upe_block(0)
, upe_phi(0)
, have_catchblocks_(0)
, safepoint_space_(0)
, call_stack_node_(0)
, save_eip_(0)
, saved_eip_(0)
, exceptionFrame_(0)
, exceptionAtom_(0)
, catch_block_(0)
, enable_verbose_(true)
, isWindowsTriple(false)
, hasnextAtom_(0)
, hasnextCounter_(0)
{
    const llvm::Triple triple(module.getTargetTriple());
    if (triple.isOSWindows()) {
        isWindowsTriple = true;
        llvm_stub_table = _MSC_VERllvm_stub_table;
    }
    else if(triple.isOSDarwin()){
        llvm_stub_table = __GNUC__llvm_stub_table;
    }
    else{
        AvmAssert(false && "target OS not supported");
    }

    allocateTables();
}

LLVMEmitter::~LLVMEmitter()
{
}

llvm::Value* LLVMEmitter::createMemberGEP(llvm::Value* ptr, FieldInfo* member, const llvm::Twine &name)
{
    StructInfo* s = member->structInfo;
    llvm::Type* structPtrTy = s->type->getPointerTo();
    if (ptr->getType() == module.scriptObjectPtrTy && ptr->getType() != structPtrTy) {
        // Cast scriptObjects to actual object type
        ptr = CreateBitCast(ptr, structPtrTy);
    }
    AvmAssert(ptr->getType() == structPtrTy);
    if (s->traits) // Add a dependency on the slot layouts of the referenced object
        module.poolInfo->addDependency(s->traits);
    return CreateConstGEP2_32(ptr, 0, member->memberIx, name);
}
    
llvm::LoadInst* LLVMEmitter::loadMember(llvm::Value* ptr, FieldInfo* member, const llvm::Twine &name)
{
    llvm::Value* ep = createMemberGEP(ptr, member);
    return CreateLoad(ep, name.isTriviallyEmpty()
                                ? member->name
                                : name);
}
    
llvm::Value* LLVMEmitter::storeMember(llvm::Value* val, llvm::Value* ptr, FieldInfo* member)
{
    llvm::Value* ep = createMemberGEP(ptr, member, llvm::StringRef(member->name) + "&");
    return CreateStore(canUpcastTo(val->getType(), member->type)?upcastTo(val, member->type):val, ep);
}

llvm::Value* LLVMEmitter::ldp(llvm::Value* ptr, int32_t d)
{
    llvm::Value* typed_ptr = offsetGenericPointer(ptr, d, module.genericPtrTy);
    return CreateLoad(typed_ptr);
}

llvm::Value* LLVMEmitter::sti(llvm::Value* val, llvm::Value* ptr, int32_t d)
{
    llvm::Value* typed_ptr = offsetGenericPointer(ptr, d, getInt32Ty());
    return CreateStore(val, typed_ptr);
}

llvm::CallInst* LLVMEmitter::callIns(const LLVMModule::StubInfo *stubinfo, uint32_t argc, ...)
{
    va_list ap;
    va_start(ap, argc);
    llvm::Value** argIns = (llvm::Value**)alloca(argc*sizeof(llvm::Value*));
    for (uint32_t i=0; i < argc; i++) {
        argIns[i] = va_arg(ap, llvm::Value*);
    }
    llvm::CallInst* ins = acallIns(stubinfo, argc, argIns);

    va_end(ap);
    return ins;
}
    
bool LLVMEmitter::needsMethodFrame(const LLVMModule::StubInfo *stubinfo)
{
    // avoid chicken and egg problem here; the methodFrame will be added later.
    if (stubinfo == STUBINFO(endTry) || stubinfo == STUBINFO(beginTry) || STUBINFO(debugExit)
        || stubinfo == STUBINFO(llBeginCatch) || stubinfo == STUBINFO(setjmp))
        return false;
    
    // These don't need it either
    if (stubinfo == STUBINFO(llCreateRestHelper))
        return false;
    if (stubinfo == STUBINFO(atomWriteBarrier))
        return false;
    if (stubinfo == STUBINFO(privateWriteBarrierRC))
        return false;
    if (stubinfo == STUBINFO(hasnextproto))
        return false;
    if (stubinfo == STUBINFO(doubleToAtom))
        return false;
    if (stubinfo == STUBINFO(intToAtom))
        return false;
    if (stubinfo == STUBINFO(uintToAtom))
        return false;

    // Assume other calls will need one
    return true;
}

llvm::CallInst* LLVMEmitter::acallIns(const LLVMModule::StubInfo *stubinfo, uint32_t argc, llvm::Value** args)
{
    // Make sure we have a MethodFrame if we call anything
    if (needsMethodFrame(stubinfo))
        getMethodFrame();

    llvm::FunctionType* funcTy = module.llvmTypeForStubInfo(stubinfo);
    llvm::Value* indirectFn = 0;
    if (stubinfo->isIndirect()) {
        indirectFn = *args++;
        --argc;
        indirectFn = CreateBitCast(indirectFn, funcTy->getPointerTo());
    }
    AvmAssert(argc == stubinfo->count_args());
    for (uint32_t i = 0; i < argc; i++)
        args[i] = coerceArg(args[i], funcTy->getParamType(i));
    llvm::Value* func;
    if (indirectFn)
        func = indirectFn;
    else
        func = module.getOrInsertFunction(stubinfo->mangle, funcTy);

//    char s[1000];
//    sprintf(s, "About to call %s \n", func->getName().data());
//    InsertPrintf(s);
    
    llvm::CallInst* ins = CreateCall(func, llvm::ArrayRef<llvm::Value*>(args, argc));
    if (!funcTy->getReturnType()->isVoidTy())
        ins->setName(stubinfo->name);
    if (neverReturns(stubinfo)) {
        ins->setDoesNotReturn();
    }
    return ins;
}
    
bool LLVMEmitter::neverReturns(const LLVMModule::StubInfo* call)
{
    return call == STUBINFO(llNPE) ||
    call == STUBINFO(llUPE) ||
    call == STUBINFO(mop_rangeCheckFailed);
}

bool LLVMEmitter::canUpcastTo(llvm::Type* from, llvm::Type* to)
{
    if (from == to)
        return true;
    
    // getGenericPointerTy functions as a void* but we use char* so you can compute byte offsets in it without casting
    if (from->isPointerTy() && to == module.genericPtrTy)
        return true;
    
    // halfmoon wants to model boolean values as ints
    if (from == getInt1Ty() && to == getInt32Ty())
        return true;
#ifdef AVMPLUS_64BIT
    if (from == getInt32Ty() && to == getInt64Ty())
        return true;
#endif
    
    // try superclasses
    if (from == module.classClosurePtrTy)
        return canUpcastTo(module.scriptObjectPtrTy, to);
    if (from == module.arrayObjectPtrTy)
        return canUpcastTo(module.scriptObjectPtrTy, to);
    if (from == module.classClosurePtrTy)
        return canUpcastTo(module.scriptObjectPtrTy, to);
    if (from == module.intVectorObjectPtrTy)
        return canUpcastTo(module.scriptObjectPtrTy, to);
    if (from == module.uIntVectorObjectPtrTy)
        return canUpcastTo(module.scriptObjectPtrTy, to);
    if (from == module.doubleVectorObjectPtrTy)
        return canUpcastTo(module.scriptObjectPtrTy, to);
    
    return false;
}

llvm::Value* LLVMEmitter::upcastTo(llvm::Value* val, llvm::Type* to)
{
    llvm::Type* from = val->getType();
    if (from == to)
        return val;
    
    AvmAssert(canUpcastTo(from, to));
    
    if ((from == getInt1Ty() && to->isIntegerTy())
#ifdef AVMPLUS_64BIT
        || (from == getInt32Ty() && to == getInt64Ty())
#endif
        )
        return CreateZExt(val, to, val->getName());
    
    return CreateBitCast(val, to, val->getName());
}

bool LLVMEmitter::permissibleDowncast(llvm::Type* from, llvm::Type* to)
{
    if (from == to)
        return true;
    // TODO: Should not allow casting from generic to whatever, but "for now" it will do.
    if (from == module.genericPtrTy && to->isPointerTy())
        return true;
    // If someone tries to cast a ScriptObject to one of its subclasses, assume it's OK.
    if (from == module.scriptObjectPtrTy && canUpcastTo(to, from))
        return true;
    return false;
}

llvm::Value* LLVMEmitter::coerceArg(llvm::Value* val, llvm::Type* to)
{
    AvmAssert(canUpcastTo(val->getType(), to) || permissibleDowncast(val->getType(), to));
    const char* suffix = "_cast";
    if (val->getName().endswith("_"))
        ++suffix;
    if ((val->getType() == getInt1Ty() && to->isIntegerTy())
#ifdef AVMPLUS_64BIT
        || (val->getType() == getInt32Ty() && to == getInt64Ty())
#endif
        )        return CreateZExt(val, to, val->getName() + suffix);
    if (val->getType() != to)
        val = CreateBitCast(val, to, val->getName() + suffix);
    return val;
}

llvm::Value* LLVMEmitter::generateGetClassTraitsCall(Traits* traits)
{
     std::string name = "traits:" + module.traitsName(traits);
    // Interface traits aren't initialized via newclass instructions.
    // Instead, access them from their defining pool.
    //First search in current pool
    if (pool == traits->pool) {
        for (int j = 0, end = (int)pool->classCount(); j < end; ++j) {
            if (traits == pool->getClassTraits(j)) {
                llvm::Value* res = loadClassTraitsFromPool(poolAddr, j);
                res->setName(name);
                return res;
            }
        }
    }
    
    // Otherwise check all pools
    for (int i = 0; i < core->poolInfos.size(); i++) {
        PoolInfo* poolInfo = core->poolInfos[i];
        PoolObject* otherPool = poolInfo->pool;
        AvmAssert(otherPool != NULL);
        if (otherPool == traits->pool) {
            for (int j = 0, end = (int)otherPool->classCount(); j < end; ++j) {
                if (traits == otherPool->getClassTraits(j)) {
                    llvm::Value* res = loadClassTraitsFromPool(getPoolLLVMValue(poolInfo), j);
                    res->setName(name);
                    return res;
                }
            }
        }
    }

    std::string debugMessage = "\nClass not found " + name;
    AvmDebugMsg(false, debugMessage.c_str());
    return 0;
}
    
llvm::Value* LLVMEmitter::generateGetScriptTraitsCall(Traits* traits)
{
    std::string name = "traits:" + module.traitsName(traits);
    // Interface traits aren't initialized via newclass instructions.
    // Instead, access them from their defining pool.
    //First search in current pool
    if (pool == traits->pool) {
        for (int j = 0, end = (int)pool->scriptCount(); j < end; ++j) {
            if (traits == pool->getScriptTraits(j)) {
                llvm::Value* res = loadScriptTraitsFromPool(poolAddr, j);
                res->setName(name);
                return res;
            }
        }
    }
    
    std::string debugMessage = "\nScript Trait not found " + name;
    AvmDebugMsg(false, debugMessage.c_str());
    return 0;
}


//Generate llLoadCatchTraits For this traits
llvm::Value* LLVMEmitter::generateGetCatchTraitsCall(Traits* traits)
{
    std::string name = "traits:" + module.traitsName(traits);

    ConstStructInitializer exceptionDesc(module.aotExceptionDescStruct);
    int type_index = 0, name_index = 0;
    if(traits) {
        const uint8_t* pos = traits->getRawTraitsPos();
        type_index = AvmCore::readU32(pos);
        name_index = AvmCore::readU32(pos);
    }
    llvm::Constant* typeIndexU30 = makeU32Constant(type_index, 5);
    exceptionDesc.init(module.aotExceptionDesc_typeIndexU30_member, typeIndexU30);
    exceptionDesc.init(module.aotExceptionDesc_nameIndex_member, getInt32(name_index));
    llvm::Constant* exceptionDescs = exceptionDesc.create();
    llvm::Value* aotExceptionDescConst = CreateAlloca(module.aotExceptionDescTy, getInt32(1), "aotExceptionDescArray");
    llvm::Value* argLoc = CreateConstGEP1_32(aotExceptionDescConst, 0, "av" + llvm::Twine(0) + "&");
    CreateStore(exceptionDescs, argLoc);
    
    llvm::Value* res = callIns(STUBINFO(llLoadCatchTraits), 2, env_param, aotExceptionDescConst);
    res->setName(name);
    return res;
}
    
llvm::Value* LLVMEmitter::loadScriptTraitsFromPool(llvm::Value* pool, int index)
{
#if 0   // Slow, safe way to get the script traits. If something breaks, try this instead.
    llvm::Value* res = callIns(STUBINFO(llGetScriptTraits), 2, pool, getInt32(index));
#else
    llvm::Value* scripts = createMemberGEP(pool, module.poolobject_scripts_member);
    llvm::Value* m_list = loadMember(scripts, module.traitsList_m_list_member);
    llvm::Value* entries = createMemberGEP(m_list, module.traitsTracedList_entries_member);
    llvm::Value* scriptLoc = CreateConstGEP1_32(entries, index);
    llvm::Value* res = CreateLoad(scriptLoc);
#endif
    return res;
}
    
llvm::Value* LLVMEmitter::loadClassTraitsFromPool(llvm::Value* pool, int index)
{
#if 0   // Slow, safe way to get the class traits. If something breaks, try this instead.
    llvm::Value* res = callIns(STUBINFO(llGetClassTraits), 2, pool, getInt32(index));
#else
    llvm::Value* classes = createMemberGEP(pool, module.poolobject_classes_member);
    llvm::Value* m_list = loadMember(classes, module.traitsList_m_list_member);
    llvm::Value* entries = createMemberGEP(m_list, module.traitsTracedList_entries_member);
    llvm::Value* classLoc = CreateConstGEP1_32(entries, index);
    llvm::Value* res = CreateLoad(classLoc);
#endif
    return res;
}

//Generate llUpdateGlobalParamTraitsVar For this traits
llvm::Value* LLVMEmitter::GetVectorTraitsValue(Traits* traits)
{
    llvm::Value* res = callIns(STUBINFO(llGetVectorTraits), 2, module.getTraitsValue(this,traits->m_paramTraits), getNamespaceConstant(traits->ns()));
    return res;
}
    
// check valid pointer and unbox it (returns ScriptObject*)
llvm::Value* LLVMEmitter::downcast_obj(llvm::Value* atom, llvm::Value* env, Traits* t)
{
    callIns(STUBINFO(coerceobj_atom), 3, env, atom, module.getTraitsValue(this, t));
    return removeTagReturningPointer(atom, module.scriptObjectPtrTy);
}

llvm::Value* LLVMEmitter::nativeToAtom(llvm::Value* native, Traits* t)
{
    switch (Traits::getBuiltinType(t)) {

    case BUILTIN_number:
        return callIns(STUBINFO(doubleToAtom), 2, coreAddr, native);

    case BUILTIN_any:
    case BUILTIN_object:
    case BUILTIN_void:
        return native;  // value already represented as Atom

    case BUILTIN_int: {
        if (const llvm::ConstantInt* native_const = llvm::dyn_cast<llvm::ConstantInt>(native)) {
            int32_t val = int32_t(native_const->getSExtValue());
            if (atomIsValidIntptrValue(val)) {
                return getAtomConstant(atomFromIntptrValue(val));
            }
        }
        return callIns(STUBINFO(intToAtom), 2, coreAddr, native);
    }

    case BUILTIN_uint: {
        if (llvm::ConstantInt* native_const = llvm::dyn_cast<llvm::ConstantInt>(native)) {
            uint32_t val = uint32_t(native_const->getZExtValue());
            if (atomIsValidIntptrValue_u(val)) {
                return getAtomConstant(atomFromIntptrValue_u(val));
            }
        }
        return callIns(STUBINFO(uintToAtom), 2, coreAddr, native);
    }

    case BUILTIN_boolean:
        return applyTagToInt(native, kBooleanType);

    case BUILTIN_string:
        return applyTagToPointer(native, kStringType);

    case BUILTIN_namespace:
        return applyTagToPointer(native, kNamespaceType);

    default:
        return applyTagToPointer(native, kObjectType);
    }
}

/// Sort the IR blocks in linear order.
void LLVMEmitter::sortBlocks()
{
    Allocator scratch;
    int count = 0;
    SeqBuilder<BlockStartInstr*> list(scratch);

    // Use reverse postorder.
    for (EachBlock b(ir); !b.empty(); ++count) {
        list.add(b.popFront());
    }

    num_blocks_ = count;
    blocks_ = new (alloc) BlockStartInstr*[count];
    count = 0;
    for (SeqRange<BlockStartInstr*> i(list); !i.empty(); i.popFront()) {
        blocks_[count++] = i.front();
    }
}

/// Allocate tables we need during code generation.
///
void LLVMEmitter::allocateTables()
{
    AvmAssert(pool->codeMgr && "CodeMgr not initialized yet");
    Allocator0 alloc0(alloc);
    
    // Can be instantiated without IR to generate a VerifyError stub
    if (!ir)
        return;

    // Sort all the blocks.  Later passes will use this order.
    sortBlocks();

    // Table of defs, indexed by val_offsets[instr->id] + pos(def)
    // DEOPT: The ƒ_ array must survive to the end of assembly.
    int num_defs = ir->def_count();
    def_ins_ = new (alloc0) llvm::Value*[num_defs];
    idToBlock_ = new (alloc0) llvm::BasicBlock*[ir->size()]; // fixme: too sparse!

    int max_argc = 0;
    for (ArrayRange<BlockStartInstr*> b(blocks_, num_blocks_);
            !b.empty(); b.popFront()) {
        if (kind(b.front()) == HR_catchblock) {
            have_catchblocks_ = true;
            // Note that the block still exists in the IR.
            // If it were unreachable, there'd be no catchblock, and we don't want to create a block for it.
            CatchBlockInstr* cblock = cast<CatchBlockInstr>(b.front());
            catch_blocks_[cblock->vpc] = cblock;
        }
        for (InstrRange r(b.front()); !r.empty(); r.popFront()) {
            max_argc = max(max_argc, numUses(r.front()));
        }
    }
    
    max_argc_ = max_argc;
}

/// Set the Value* associated with a specific Def.
///
llvm::Value* LLVMEmitter::set_def_ins(Def* d, llvm::Value* ins)
{
    AvmAssert(canUpcastTo(ins->getType(), module.llvmType(d)));
    
    // To ensure debuggability, guarantee that every instruction is named.
    // (excepyt phis, which we will name later based on their edges)
    if (!ins->getType()->isVoidTy() && ins->getName().empty() && !llvm::isa<llvm::PHINode>(ins))
       ins->setName(definer(d)->info->name());
    def_ins_[defId(d)] = ins;
    
    // llvm::dbgs() << ">>> " << defId(d) << ":";
    // ins->print(llvm::dbgs());
    // llvm::dbgs() << "\n";
    
    return ins;
}

/// Get the Value* for a specific Def.
///
inline llvm::Value* LLVMEmitter::def_ins(const Def* d)
{
    llvm::Value* val = def_ins_[defId(d)];
    AvmAssert(val != 0);
    return val;
}
    
inline bool LLVMEmitter::has_def_ins(const Def* d)
{
    llvm::Value* val = def_ins_[defId(d)];
    return val != 0;;
}

inline llvm::BasicBlock* LLVMEmitter::set_block(BlockStartInstr* i, llvm::BasicBlock* block)
{
    idToBlock_[i->id] = block;
    return block;
}

inline llvm::BasicBlock* LLVMEmitter::block(BlockStartInstr* i)
{
    return idToBlock_[i->id];
}

void LLVMEmitter::emitBegin()
{
    // Be careful: this is also used to emit the prologue for VerifyError stubs
    // where there is no IR.
    AvmAssert(module.poolInfo != NULL);
    
    llvm::FunctionType* methodType = module.getFunctionTy(method);
    StUTF8String functionName(method->getMethodName());
    currentFunction = llvm::Function::Create(methodType, llvm::GlobalValue::ExternalLinkage,
        module.poolInfo->getFunctionName(method),
        &module);
    module.incrementFunctionCount();
    //Govind:Commenting this call to enable module spilitting during emit. addMethod stores llvm::Function*
    // with PoolInfo and at the end while creating AOTInfo it is used to create Array of Function pointers.
    // So intead of adding concrete function in array i am now using extern prototype, which resolves at link time.
    //module.poolInfo->addMethod(method, currentFunction);
    
    entryBlock = llvm::BasicBlock::Create(module.getContext(), "entry", currentFunction);
    SetInsertPoint(entryBlock);
    
    env_param = argc_param = ap_param = 0;
    unsigned nParams = signature->param_count()+1;  // +1 for "this"
    unsigned cParams = nParams;
    if (method->needRestOrArguments() || method->needArgsArrInMethodSig())
        cParams += 2;
    cParams += 1;  // MethodEnv*;
    llvm::Function::arg_iterator argi = currentFunction->arg_begin();
    unsigned i = 0;
    for (; i < nParams; ++i) {
        llvm::Argument* arg = argi++;
        if (i == 0)
            arg->setName("this");
        else
            arg->setName("arg["+ llvm::Twine(i) + "]");
    }
    if (method->needRestOrArguments() || method->needArgsArrInMethodSig()) {
        i += 2;
        ap_param = argi++;
        ap_param->setName("argp");
        argc_param = argi++;
        argc_param->setName("argc");
    }
    env_param = argi++;
    env_param->setName("env");
    i += 1;
    
    AvmAssert(i == cParams);  // -1 since "effect" doesn't figure here.
    AvmAssert(argi == currentFunction->arg_end());
    
    methodInfoAddr = loadMember(env_param, module.methodenv_method_member);
    poolAddr = loadMember(methodInfoAddr, module.methodinfo_pool_member);
    coreAddr = loadMember(poolAddr, module.poolobject_core_member);
    coreAddr->setName("core");
    gcAddr = loadMember(coreAddr, module.avmcore_gc_member);
    
    maxAtomParams_ = 1;
    maxAvmParamSize_ = 0;
    params_ = CreateAlloca(module.atomTy, getInt32(maxAtomParams_), "params");
    
    hasnextAtom_ = CreateAlloca(module.atomTy, getInt32(1),"hasNextAtom");
    hasnextCounter_ = CreateAlloca(getInt32Ty(), getInt32(1),"hasNextCounter");

    if (ir && ir->debugging())
        emitSafepointSetup();
    if (have_catchblocks_)
        emitExceptionHandling();
    if (ir && ir->debugging())
        emitDebugEnter();
    
    // Epilog
    {
        epilogBlock = llvm::BasicBlock::Create(module.getContext(), "epilog", currentFunction);
        PushBuilder push(this, epilogBlock);
        llvm::Type* returnType = module.llvmType(signature->returnTraits());
        returnPhi = CreatePHI(returnType, 1, "ret_val");
        if (have_catchblocks_)
            callIns(STUBINFO(endTry), 1, exceptionFrame_);
        if (ir && ir->debugging())
            callIns(STUBINFO(debugExit), 2, env_param, call_stack_node_);
        CreateRet(returnPhi);
    }
    
    // force a methodframe if there are exceptions
    if (have_catchblocks_ || core->settings.telemetry_sampler || (ir && ir->debugging()))
        getMethodFrame();
}
    
llvm::Value* LLVMEmitter::getMethodFrame()
{
    // Only create/link the methodFrame if it's used.
    // This makes field accessors much smaller!
    
    //
    // IMPORTANT!!!
    //
    // The MethodFrame must be emitted in front of the exception setup if there are catches
    // because the beginTry will cache core->methodFrame to restore it un unwind.
    // Inserting in front of params_ achieves that.
    //
    if (!method_frame_) {
        {
            // Emit the methodframe allocation and push just before the params_ temp
            // Same thing is being done @ void MethodFrame::enter(AvmCore* core, MethodEnv* e)
            //Just need to call core->takeSample(); for telemetry
            PushBuilder push(this, params_);
            method_frame_ = CreateAlloca(module.methodFrameTy, getInt32(1), "methodFrame");
            if(core->settings.telemetry_sampler)
                callIns(STUBINFO(llCoreTakeSample), 1, coreAddr);
            storeMember(env_param, method_frame_, module.methodframe_env_member);
            llvm::Value* core_mf = createMemberGEP(coreAddr, module.avmcore_methodframe_member);
            llvm::Value* old_frame = CreateLoad(core_mf, "currentMethodFrame");
            storeMember(old_frame, method_frame_, module.methodframe_next_member);
            CreateStore(method_frame_, core_mf);
        }
        {
            // Emit the methodframe pop just before the return instruction
            PushBuilder push(this, epilogBlock->getTerminator());
            
            if(core->settings.telemetry_sampler)
                callIns(STUBINFO(llCoreTakeSample), 1, coreAddr);

            llvm::Value* prevFrame = loadMember(method_frame_, module.methodframe_next_member);
            storeMember(prevFrame, coreAddr, module.avmcore_methodframe_member);
        }
    }
    return method_frame_;
}

llvm::Value* LLVMEmitter::emitConst(const Type* t)
{
    AvmAssert(isConst(t));
    switch (kind(t)) {
    default:
        AvmAssert(!"unsupported kind");
    case kTypeName: {
        const Multiname* name = nameVal(t);
        return getMultinameConstant(name);
    }
    case kTypeOrdinal: {
        llvm::Value* val = getInt32(uint32_t(ordinalVal(t)));
        val->setName("ordinal");
        return val;
    }
    case kTypeTraits: {
        Traits* traits = traitsVal(t);
        return module.getTraitsValue(this, traits);
    }
    case kTypeMethod: {
        MethodInfo* info = methodVal(t);
        return getMethodInfoValue(info);
    }
    case kTypeAny:
    case kTypeObject:
    case kTypeVoid:
    case kTypeString:
    case kTypeNamespace:
    case kTypeBoolean:
    case kTypeNumber:
    case kTypeScriptObject:
        switch (model(t)) {
        default:
            AvmAssert(!"unsupported model");
        case kModelScriptObject: {
            AvmAssert(!objectVal(t) && "can't teleport instances into the future");
            // nulls are OK
            return llvm::ConstantPointerNull::get(module.scriptObjectPtrTy);
        }
        case kModelString: {
            String* str = stringVal(t);
            return getStringConstant(str);
        }
        case kModelNamespace: {
            Namespace* ns = nsVal(t);
            return getNamespaceConstant(ns);
        }
        case kModelAtom: {
            Atom atom = atomVal(t, core);
            return getAtomConstant(atom);
        }
        case kModelDouble: {
            double dbl = doubleVal(t);
            return getDoubleConstant(dbl);
        }
        case kModelInt:
            AvmAssert(isInt(t) || isUInt(t) || isBoolean(t));
            return getInt32(isInt(t) ? uint32_t(intVal(t)) :
                                        isUInt(t) ? uint32_t(uintVal(t)) :
                                        uint32_t(boolVal(t)));
        }
    }
}
    
llvm::Value* LLVMEmitter::getAtomConstant(Atom const_atom)
{
    // Nulls are always OK
    if (!atomPtr(const_atom))
        return getPtrSizeInt(const_atom);
    switch (atomKind(const_atom)) {
        default:
            AvmAssert(!"can't teleport object to the future");
        case kNamespaceType:
            return applyTagToPointer(getNamespaceConstant(const_atom), kNamespaceType);
        case kStringType:
            return applyTagToPointer(getStringConstant(const_atom), kStringType);
        case kBooleanType:
        case kIntptrType:
            return getPtrSizeInt(const_atom);
        case kDoubleType: {
            // TODO: using a pooled constant _might_ be slightly better since it avoids repeated allocations,
            // though at the cost of added marking overhead. It depends on how often we need boxed double constants.
            llvm::Value* val = getDoubleConstant(const_atom);
            return callIns(STUBINFO(doubleToAtom), 2, coreAddr, val);
        }
    }
}
    
//
// These routines encapsulate the "pointers from the future" problem:
// Halfmoon has object references that it thinks it can just hand off to the JIT,
// but those addresses are no good in a future instantiation of the runtime.
// So we have to relate the objects we have now to the corresponding objects
// in the subsequent runtime.
//
    
llvm::Value* LLVMEmitter::getStringConstant(String* str)
{
    if (!str)
        return llvm::ConstantPointerNull::get(module.stringPtrTy);
    
    String* s2 = str;
    if (str->length() > 30) {
        s2 = s2->substr(0, 30);
        s2 = s2->appendLatin1("...");
    }
    StUTF8String strVal(s2);
    
    //
    // Find this string in the current pool
    //
    
    if (str->isEmpty()) {
        llvm::Value* res = callIns(STUBINFO(llGetString), 2, poolAddr, getInt32(0));
        res->setName("EmptyStr" + llvm::Twine(strVal.c_str()));
        return res;        
    }
        
    for (int i = 1, end = (int)pool->constantStringCount; i < end; ++i) {
        if (str->equals(pool->getString(i))) {
            llvm::Value* res = callIns(STUBINFO(llGetString), 2, poolAddr, getInt32(i));
            res->setName("str:" + llvm::Twine(strVal.c_str()));
            return res;
        }
    }
    
    // Otherwise check all pools
    for (int i = 0; i < core->poolInfos.size(); i++) {
        PoolInfo* poolInfo = core->poolInfos[i];
        PoolObject* otherPool = poolInfo->pool;
        AvmAssert(otherPool != NULL);
        for (int j = 1, end = (int)otherPool->constantStringCount; j < end; ++j) {
            if (str->equals(otherPool->getString(j))) {
                llvm::Value* res = callIns(STUBINFO(llGetString), 2, getPoolLLVMValue(poolInfo), getInt32(j));
                res->setName("str:" + llvm::Twine(strVal.c_str()));
                return res;
            }
        }
    }

    AvmAssert(!"can't find string");
    return 0;
}

llvm::Value* LLVMEmitter::getNamespaceConstant(Namespace* ns)
{
    if (!ns)
        return llvm::ConstantPointerNull::get(module.namespacePtrTy);
    //
    // Find this namespace in the current pool
    //
    llvm::Value* poolValue = poolAddr;
    int nsIndex = -1;

    StUTF8String nsName(ns->getURI());
    for (int i = 1, end = (int)pool->constantNsCount; i < end; ++i) {
        if (ns->EqualTo(pool->getNamespace(i))) {
            nsIndex = i;
            break;
        }
    }
    
    // Otherwise check all pools
    for (int i = 0; nsIndex == -1 && i < core->poolInfos.size(); i++) {
        PoolInfo* poolInfo = core->poolInfos[i];
        PoolObject* otherPool = poolInfo->pool;
        AvmAssert(otherPool != NULL);
        for (int j = 1, end = (int)otherPool->constantNsCount; j < end; ++j) {
            if (ns->EqualTo(otherPool->getNamespace(j))) {
                nsIndex = j;
                poolValue = getPoolLLVMValue(poolInfo);
                break;
            }
        }
    }

    AvmAssert(nsIndex != -1 && "can't find namespace");
    
#if 0   // Slow, safe way to get the namespace. If something breaks, try this instead.
    llvm::Value* res = callIns(STUBINFO(llGetNamespace), 2, poolValue, getInt32(nsIndex));
    res->setName("NS: " + llvm::Twine(nsName.c_str()));
#else
    llvm::Value* namespaces = createMemberGEP(poolValue, module.poolobject_namespaces_member);
    llvm::Value* m_list = loadMember(namespaces, module.namespaceRCList_m_list_member);
    llvm::Value* entries = createMemberGEP(m_list, module.namespaceList_entries_member);
    llvm::Value* nsLoc = CreateConstGEP1_32(entries, nsIndex);
    llvm::Value* res = CreateLoad(nsLoc, "NS: " + llvm::Twine(nsName.c_str()));
#endif
    return res;
}

//
// This is awfully fiddly, but doesn't seem to exist anywhere in core!
//
static bool MultinameEqual(const Multiname* mn1, const Multiname* mn2) {
    if (mn1 == mn2)
        return true;
    if (!mn1 || !mn2)
        return false;
    if (mn1->namespaceCount() != mn2->namespaceCount())
        return false;
    if (mn1->ctFlags() != mn2->ctFlags())
        return false;
    if (mn1->ctFlags() != mn2->ctFlags())
        return false;
    if (mn1->isRtns() != mn2->isRtns())
        return false;
    if (mn1->isRtname() != mn2->isRtname())
        return false;
    if (mn1->isAnyName() != mn2->isAnyName())
        return false;
    if (mn1->isAnyNamespace() != mn2->isAnyNamespace())
        return false;
    if (!mn1->isAnyName() && !mn1->isRtname() && !String::equalsWithNullChecks(mn1->getName(), mn2->getName()))
        return false;
    if (mn1->isParameterizedType() != mn2->isParameterizedType())
        return false;
    if (mn1->isParameterizedType() && mn1->getTypeParameter()!=mn2->getTypeParameter())
        return false;
    if (mn1->isAnyNamespace())
        return true;
    for (int i = 0, end = mn1->namespaceCount(); i < end; ++i)
        if (!mn1->getNamespace(i)->EqualTo(mn2->getNamespace(i)))
            return false;
    return true;
}
    
class MultinameDesc: public StUTF8String
{
public:
    MultinameDesc(AvmCore* core, const Multiname* name)
    : StUTF8String(name->isAnyName() ? core->newStringLatin1("<any>") :
                   name->isRtname() ? core->newStringLatin1("<rtname>") :
                   name->getName())
    {}
};
    
llvm::Value* LLVMEmitter::getMultinameConstant(const Multiname* mn)
{
    if (!mn)
        return llvm::ConstantPointerNull::get(module.multinamePtrTy);
    
    MultinameDesc nameStr(core, mn);
    pool->initPrecomputedMultinames();
    for (int i = 1, end = (int)pool->cpool_mn_offsets.length(); i < end; ++i) {
        if (MultinameEqual(mn, pool->precomputedMultiname(i))) {
            llvm::Value* escmn = loadMember(poolAddr, module.poolobject_escHeapMultiname_member);
            llvm::Value* elements = createMemberGEP(escmn, module.escHeapMultiname_elements_member);
            llvm::Value* res = CreateConstGEP2_32(elements, 0, i, "MN: " + llvm::Twine(nameStr.c_str()));
            return res;
        }
    }
    AvmAssert(!"can't find multiname");
    return 0;
}

int LLVMEmitter::getMultinameIndexInPool(const Multiname* mn)
{
  if (!mn)
    return -1;
  
  pool->initPrecomputedMultinames();
  for (int i = 1, end = (int)pool->cpool_mn_offsets.length(); i < end; ++i) {
    if (MultinameEqual(mn, pool->precomputedMultiname(i))) {
      return i;
    }
  }
  AvmAssert(!"can't find multiname");
  return -1;
}
  
llvm::Value* LLVMEmitter::getMethodInfoValue(MethodInfo* info)
{
    if (!info)
        return llvm::ConstantPointerNull::get(module.methodInfoPtrTy);
    
    StUTF8String methodName(info->getMethodName());
    
    // First check our own pool
    llvm::Value* poolValue = poolAddr;
    int methodIndex = -1;
    for (int i = 0, end = (int)pool->methodCount(); i < end; ++i) {
        if (info == pool->getMethodInfo(i)) {
            methodIndex = i;
            break;
        }
    }
    
    // Otherwise check all pools
    for (int i = 0; methodIndex == -1 && i < core->poolInfos.size(); i++) {
        PoolInfo* poolInfo = core->poolInfos[i];
        PoolObject* otherPool = poolInfo->pool;
        AvmAssert(otherPool != NULL);
        for (int j = 0, end = (int)otherPool->methodCount(); j < end; ++j) {
            if (info == otherPool->getMethodInfo(j)) {
                methodIndex = j;
                poolValue = getPoolLLVMValue(poolInfo);
                break;
            }
        }
    }

    AvmAssert(methodIndex != -1 && "can't find MethodInfo");
    
#if 0   // Slow, safe way to get the methodinfo. If something breaks, try this instead.
    llvm::Value* res = callIns(STUBINFO(llGetMethodInfo), 2, poolValue, getInt32(methodIndex));
    res->setName("Method: " + llvm::Twine(methodName.c_str()));
#else
    llvm::Value* methods = createMemberGEP(poolValue, module.poolobject_methods_member);
    llvm::Value* m_list = loadMember(methods, module.methodInfoGCList_m_list_member);
    llvm::Value* entries = createMemberGEP(m_list, module.methodInfoList_entries_member);
    llvm::Value* methodLoc = CreateConstGEP1_32(entries, methodIndex);
    llvm::Value* res = CreateLoad(methodLoc, "Method: " + llvm::Twine(methodName.c_str()));
#endif
    return res;
}

llvm::Value* LLVMEmitter::loadInterfaceTraitsFromPool(llvm::Value* pool, int index)
{
#if 0   // Slow, safe way to get the class traits. If something breaks, try this instead.
    llvm::Value* res = callIns(STUBINFO(llGetInterfaceTraitsFromPool), 2, pool, getInt32(index));
#else
    llvm::Value* classes = createMemberGEP(pool, module.poolobject_classes_member);
    llvm::Value* m_list = loadMember(classes, module.traitsList_m_list_member);
    llvm::Value* entries = createMemberGEP(m_list, module.traitsTracedList_entries_member);
    llvm::Value* classLoc = CreateConstGEP1_32(entries, index);
    llvm::Value* classVal = CreateLoad(classLoc);
    llvm::Value* res = loadMember(classVal, module.traits_itraits_member);
#endif
    return res;
}

llvm::Value* LLVMEmitter::toAtom(const Use& in) {
    llvm::Value* val = def_ins(in);
    // Box the value if necessary
    const Type* t = type(in);
    ModelKind modelKind = model(t);
    switch (modelKind) {
        default:
            AvmAssert(!"bad model");
        case kModelAtom:
            return val;
        case kModelScriptObject:
            return applyTagToPointer(val, kObjectType);
        case kModelString:
            return applyTagToPointer(val, kStringType);
        case kModelNamespace:
            return applyTagToPointer(val, kNamespaceType);
        case kModelInt:
            // This seems odd, but see halfmoon::toModelAtom()
            if (isBoolean(t)) {
                return applyTagToInt(val, kBooleanType);
            }
            else if (isInt(t)) {
                if (const llvm::ConstantInt* native_const = llvm::dyn_cast<llvm::ConstantInt>(val)) {
                    int32_t intval = int32_t(native_const->getSExtValue());
                    if (atomIsValidIntptrValue(intval)) {
                        return getAtomConstant(atomFromIntptrValue(intval));
                    }
                }
                return callIns(STUBINFO(intToAtom), 2, coreAddr, val);
            }
            else if (isUInt(t)) {
                if (llvm::ConstantInt* native_const = llvm::dyn_cast<llvm::ConstantInt>(val)) {
                    uint32_t uintval = uint32_t(native_const->getZExtValue());
                    if (atomIsValidIntptrValue_u(uintval)) {
                        return getAtomConstant(atomFromIntptrValue_u(uintval));
                    }
                }
                return callIns(STUBINFO(uintToAtom), 2, coreAddr, val);
            }
            AvmAssert(!"Unexpected type");
            return 0;
        case kModelDouble:
            return callIns(STUBINFO(doubleToAtom), 2, coreAddr, val);
    }
}

/// Store atoms to a stack allocated buffer.
///
void LLVMEmitter::emitAtomArgs(const Use* args_in, int argc)
{
    if (maxAtomParams_ < argc)
        maxAtomParams_ = argc;
    for (int i = 0; i < argc; ++i) {
        llvm::Value* argLoc = CreateConstGEP1_32(params_, i, "av" + llvm::Twine(i) + "&");
        llvm::Value* arg = toAtom(args_in[i]);
        CreateStore(arg, argLoc);
    }
}

llvm::Value* LLVMEmitter::emitLoadVTable(const Use& object)
{
    AvmAssert(!isNullable(type(object)));
    AvmAssert(model(type(object)) == kModelScriptObject);
    llvm::Value* obj = def_ins(object);
    if (obj->getType() == module.arrayObjectPtrTy)
        obj = CreateBitCast(obj, module.scriptObjectPtrTy);
    return loadMember(obj, module.scriptobject_vtable_member);
}

llvm::Value* LLVMEmitter::emitLoadMethodEnv(llvm::Value* vtable, int disp_id)
{
    llvm::Value* methods = createMemberGEP(vtable, module.vtable_methods_member);
    llvm::Value* methodp = CreateConstGEP1_32(methods, disp_id);
    return CreateLoad(methodp, "env");
}

llvm::Value* LLVMEmitter::emitCompareLess(llvm::Value* lhs_in, llvm::Value* rhs_in)
{
    return callIns(STUBINFO(compare), 2, lhs_in, rhs_in);
}

/// Generate a store instruction appropriate for the given type constraint.
/// This function does not do anything with write barriers.  Inlined setslots
/// or assignments to containers (Vector?) must handle write barriers.
///
llvm::Value* LLVMEmitter::emitStore(const Use& value, const Type* value_type,
                                    llvm::Value* ptr, int32_t offset, const llvm::Twine& name)
{
    llvm::Type* type = module.llvmType(value_type);
    llvm::Value* typed_ptr = offsetGenericPointer(ptr, offset, type);
    llvm::Value* val = def_ins(value);
    //This function is used to store atom sized params. boolean, int32 should be stored in Atom's space
    if((type == getInt1Ty() || type == getInt32Ty()) && type != module.atomTy) {
        type = module.atomTy;
        val = CreateZExt(val, type, val->getName());
    }
    
    llvm::Value* ret = CreateStore(upcastTo(val, type), typed_ptr);
    ret->setName(name);
    return ret;
}

/// Get LLVMIR BasicBlock associated with an HMIR block start instruction.
/// If none exists, create it now.
///
llvm::BasicBlock* LLVMEmitter::getBlock(BlockStartInstr* bsi)
{
    llvm::BasicBlock* bb = block(bsi);
    if (!bb) {
        StringBuffer name(core);
        // TODO: this should use the vpc (abc offset) but that is not (yet) tracked
        // for all BlockStartInstr types
        name << bsi->info->name() << "_" << bsi->id;
        bb = llvm::BasicBlock::Create(module.getContext(), name.c_str(), currentFunction);
        set_block(bsi, bb);
    }
    return bb;
}

// Allocate bailout block if needed.
llvm::BasicBlock* LLVMEmitter::emitBailout()
{
    AvmAssert(!"No speculation in AOT");
    return NULL;
}
    
llvm::Instruction* LLVMEmitter::getNearestInsertionInsertPointForAllUses(llvm::DominatorTree& dt, llvm::Value *def) {
    llvm::BasicBlock *nearest = 0;
    for (llvm::Value::use_iterator itUse = def->use_begin(); itUse != def->use_end(); ++itUse) {
        if (llvm::Instruction* ins = llvm::dyn_cast<llvm::Instruction>((*itUse).getUser())) {
            llvm::BasicBlock* bb = ins->getParent();
            if (nearest)
                nearest = dt.findNearestCommonDominator(nearest, bb);
            else
                nearest = bb;
        }
    }
    if (!nearest)  // not found (no uses)
        return 0;
    // If nearest block contains a use, return the instruction with the first use
    for (llvm::Value::use_iterator itUse = def->use_begin(); itUse != def->use_end(); ++itUse) {
        if (llvm::Instruction* ins = llvm::dyn_cast<llvm::Instruction>((*itUse).getUser())) {
            if (ins->getParent() == nearest) {
                for (llvm::BasicBlock::iterator itIns = nearest->begin(), end = nearest->end(); itIns != end; ++itIns) {
                    if (std::find(itIns->op_begin(), itIns->op_end(), def) != itIns->op_end()) {
                        return itIns;
                    }
                }
            }
        }
    }
    // otherwise return the terminator
    return nearest->getTerminator();
}
    
void LLVMEmitter::removeIfNotUsedOtherwiseMoveNearestToFirstUse(llvm::DominatorTree& dt, llvm::Instruction* val)
{
    llvm::Instruction* nearest = getNearestInsertionInsertPointForAllUses(dt, val);
    // If the instr is a load and has just one effective addr, then move that too
    llvm::Instruction* effectiveAddr = 0;
    if (llvm::LoadInst* load = llvm::dyn_cast<llvm::LoadInst>(val)) {
        if (llvm::Instruction* ea = llvm::dyn_cast<llvm::Instruction>(load->getPointerOperand())) {
            if (ea->hasOneUse())
                effectiveAddr = ea;
        }
    }
    val->removeFromParent();
    if (effectiveAddr)
        effectiveAddr->removeFromParent();
    if (nearest) {
        val->insertBefore(nearest);
        if (effectiveAddr)
            effectiveAddr->insertBefore(val);
    }
    else {
        delete val;
        delete effectiveAddr;
    }
}

void LLVMEmitter::finish()
{
    // If there are no returns (for instance, the method only throws)
    // remove the exit block.
    if (returnPhi->getNumIncomingValues() == 0) {
        llvm::DeleteDeadBlock(epilogBlock);
        epilogBlock = 0;
        returnPhi = 0;
    }
    // If the hasnextAtom_ object isn't used, remove it
    if (hasnextAtom_ && hasnextAtom_->hasNUses(0)) {
        hasnextAtom_->removeFromParent();
        delete hasnextAtom_;
        hasnextAtom_ = 0;
    }
    // If the hasnextCounter_ object isn't used, remove it
    if (hasnextCounter_ && hasnextCounter_->hasNUses(0)) {
        hasnextCounter_->removeFromParent();
        delete hasnextCounter_;
        hasnextCounter_ = 0;
    }

    // If the params object isn't used, remove it
    if (params_ && params_->hasNUses(0)) {
        params_->removeFromParent();
        delete params_;
        params_ = 0;
    }
    if (params_) {
        // make sure params area is big enough for any non-atom params
        int equivAtoms = (maxAvmParamSize_+3)/sizeof(Atom);
        if (maxAtomParams_ < equivAtoms)
            maxAtomParams_ = equivAtoms;
        if (maxAtomParams_ > 1) {
            // expand the params_ Alloca
            PushBuilder push(this, params_);
            llvm::AllocaInst* prevAlloc = params_;
            params_ = CreateAlloca(module.atomTy, getInt32(maxAtomParams_), "params");
            prevAlloc->replaceAllUsesWith(params_);
            prevAlloc->removeFromParent();
            delete prevAlloc;
        }
        // If params have been used for something besides atoms, make sure they're aligned
        // for doubles
        if (maxAvmParamSize_ > 0)
            params_->setAlignment(8);
    }
    
    // Remove pool, methodInfo, core and gc defs if not used, otherwise move them as near as possible
    // to their first uses to reduce the live range of the values.
    // Careful: order matters! Must be in reverse order of how they are loaded.
    llvm::DominatorTreeWrapperPass pass;
    pass.runOnFunction(*currentFunction);
    removeIfNotUsedOtherwiseMoveNearestToFirstUse(pass.getDomTree(), poolAddr);
    removeIfNotUsedOtherwiseMoveNearestToFirstUse(pass.getDomTree(), methodInfoAddr);
    removeIfNotUsedOtherwiseMoveNearestToFirstUse(pass.getDomTree(), gcAddr);
    removeIfNotUsedOtherwiseMoveNearestToFirstUse(pass.getDomTree(), coreAddr);
    
    // Dump LLVM IR
    bool matches = options::dumpMatching.length() > 0
    && currentFunction->getName().str().find(options::dumpMatching) != std::string::npos;
    if (module.printLLIR || matches)
        currentFunction->dump();

    if (options::verifyFunctions) {
        llvm::verifyFunction(*currentFunction);
    }
}

void LLVMEmitter::emit()
{
    emitBegin();

    for (int b = 0, n = num_blocks_; b < n; ++b) {
        current_block_ = b;
        for (InstrRange r(blocks_[b]); !r.empty(); r.popFront()) {
            emit(r.front());
        }
    }

    finish();
}
    
void LLVMEmitter::emitAsVerifyErrorStub()
{
    // Be careful, there is no IR in this case, only a MethodInfo and signatiure.
    emitBegin();
    callIns(STUBINFO(llVerifyError), 1, env_param);
    CreateUnreachable();
    finish();
}

bool LLVMEmitter::haveStub(InstrKind k)
{
    if (k >= llvm_stub_count)
        return false;
    const LLVMModule::StubInfo& call = llvm_stub_table[k];
    return call.name != NULL;
}

void LLVMEmitter::emit(Instr* instr)
{
    InstrKind k = kind(instr);

    if (debug_stubs && haveStub(k) && debugStub(instr)) {
        do_stub(instr, &llvm_stub_table[k]);
        return;
    }

    if (enable_mode == kModeLirStubs && haveStub(k)) {
        do_stub(instr, &llvm_stub_table[k]);
    } else {
        do_instr(this, instr);
    }
}

void LLVMEmitter::do_default(Instr* instr)
{
    InstrKind k = kind(instr);
    AvmAssert(haveStub(k));
    do_stub(instr, &llvm_stub_table[k]);
}

void LLVMEmitter::do_goto(GotoInstr* instr)
{
    llvm::BranchInst* br = CreateBr(getBlock(instr->target));
    // insert any coerces before the branch
    SetInsertPoint(br);
    addPhiEdges(instr);
}

void LLVMEmitter::do_label(LabelInstr* instr)
{
    // Wrapping up a block. It must be terminated
    AvmAssert(GetInsertBlock()->back().isTerminator());
    
    // Starting a new block. It must be empty.
    llvm::BasicBlock* bb = getBlock(instr);
    SetInsertPoint(bb);
    AvmAssert(getFirstNonPHI(bb) == 0);
    
    saved_eip_ = -1;
}
    
void LLVMEmitter::do_if(IfInstr* instr)
{
    llvm::Value* cond = def_ins(instr->cond());
    llvm::BasicBlock* true_block = getBlock(instr->true_arm());
    llvm::BasicBlock* false_block = getBlock(instr->false_arm());
    
    if(!cond->getType()->isIntegerTy(1))
        cond = CreateICmpNE(cond, getInt32(0));

    llvm::BranchInst* br = CreateCondBr(cond, true_block, false_block);
    // insert any coerces before the branch
    SetInsertPoint(br);
    addPhiEdges(instr);
}

void LLVMEmitter::do_arm(ArmInstr* arm)
{
    // Wrapping up a block. It must be terminated
    AvmAssert(GetInsertBlock()->back().isTerminator());
    
    // Starting a new block. It must be empty.
    llvm::BasicBlock* bb = getBlock(arm);
    SetInsertPoint(bb);
    AvmAssert(getFirstNonPHI(bb) == 0);
    
    saved_eip_ = -1;
}

void LLVMEmitter::do_switch(SwitchInstr* instr)
{
    unsigned num_cases = instr->num_cases();
    const Use& selector_in = instr->selector();
    llvm::Value* selector = def_ins(selector_in);
    llvm::BasicBlock* default_block = getBlock(instr->default_arm());
    llvm::SwitchInst* switch_instr = CreateSwitch(selector, default_block, num_cases);
    for (unsigned i = 0; i < num_cases; ++i) {
        llvm::BasicBlock* case_target = getBlock(instr->case_arm(i));
        switch_instr->addCase(getInt32(i), case_target);
    }
    // insert any coerces before the branch
    SetInsertPoint(switch_instr);
    addPhiEdges(instr);
}

void LLVMEmitter::do_return(StopInstr* stop)
{
    llvm::Value* retVal = def_ins(stop->value_in());
    retVal = coerceArg(retVal, module.llvmType(signature->returnTraits()));
    llvm::BranchInst* br = CreateBr(epilogBlock);
    (void)br; // unused
    returnPhi->addIncoming(retVal, GetInsertBlock());
}

/// Generate a call to a Stub function
///
void LLVMEmitter::do_stub(Instr* instr, const LLVMModule::StubInfo* call)
{
    int fixc = call->fixedArgCount;
    uint32_t limit = (fixc == -1) ? MAXARGS : fixc + 1; // +1 is for the MethodFrame* arg
    uint32_t maxArgs = limit + 3; // for argc, argv, slop
    llvm::Value** args = (llvm::Value**)alloca(maxArgs*sizeof(llvm::Value*));
    uint32_t argc = 0;
    uint32_t varargc = 0;
    args[argc++] = getMethodFrame();
    int offset = 0;
    SigRange s = inputSigRange(instr);
    for (ArrayRange<Use> u = useRange(instr); !u.empty(); s.popFront()) {
        const Use& arg = u.popFront();
        const Type* sig_type = s.front();
        AvmAssert(subtypeof(type(arg), sig_type)); // ir must be well typed!
        if (isLinear(sig_type) || isState(sig_type)) {
            continue;    // ignore stateful args
        }
        if (argc < limit) {
            AvmAssert(argc < maxArgs && "too many args");
            args[argc++] = def_ins(arg);
        } else {
            emitStore(arg, sig_type, params_, offset);
            // TODO:
            //   1 - this is naive about alignment
            // It's likely that stubs have homogeneous arguments, so alignment probably not an issue in practice.
            if(model(sig_type) == kModelDouble){
                offset += 8;
            }else { //Atom sized
                offset += sizeof(uintptr_t);
            }
                
            varargc++;
        }
        if (maxAvmParamSize_ < offset)
            maxAvmParamSize_ = offset;
    }
    if (fixc != -1) {
        AvmAssert(argc + 2 < maxArgs && "too many args");
        args[argc++] = getInt32(varargc);
        args[argc++] = params_;
    }
    llvm::Value* call_ins = acallIns(call, argc, args);
    // assume the result goes in def 0 or def 1
    switch (numDefs(instr)) {
    default:
        AvmAssert(!"too many defs");
    case 0: // do nothing
        break;
    case 1:
        if (!isEffect(outputSignature(instr)[0]))
            set_def_ins(&getDefs(instr)[0], call_ins);
        break;
    case 2:
        set_def_ins(&getDefs(instr)[1], call_ins);
        break;
    }
    if (kind(instr) == HR_throw) {
        CreateUnreachable();
    }
}
    
/// Generate code for HR_start by loading each non-dead formal parameter
/// from the argument array.
///
void LLVMEmitter::do_start(StartInstr* start)
{
    // + 3 because start has extra params not in included in param_count():
    // effect, env, and this.
    AvmAssert(numDefs(start) == signature->param_count() + 3 +
           (method->needRestOrArguments() ? 1 : 0));
    
    unsigned paramIx = 0;
    set_def_ins(start->data_param(paramIx++), env_param);

    unsigned nParams = signature->param_count()+1;  // +1 for "this"
    unsigned cParams = nParams;
    if (method->needRestOrArguments() || method->needArgsArrInMethodSig())
        cParams += 2;
    cParams += 1;  // MethodEnv*;
    llvm::Function::arg_iterator argi = currentFunction->arg_begin();
    unsigned i = 0;
    for (; i < nParams; ++i) {
        Def* arg_def = start->data_param(paramIx++);
        llvm::Argument* arg = argi++;
        set_def_ins(arg_def, arg);
    }
    if (method->needRestOrArguments() || method->needArgsArrInMethodSig()) {
        // already captured these values in the prologue
        /* ap_param = */ argi++;
        /* argc_param = */ argi++;
        i += 2;
        nParams++;
        
        if(method->needRest()) {
        set_def_ins(start->data_param(paramIx++), callIns(STUBINFO(llCreateRestHelper), 3,
                                                  env_param, ap_param, argc_param));
        }else if(method->needArguments()) {
            set_def_ins(start->data_param(paramIx++), callIns(STUBINFO(llCreateArgumentHelper), 3,
                                                              env_param, ap_param, argc_param));
        }
        // needArgsArrInMethodSig is propogated to match function signature to avoid MethodEnv* corruption.
        // actually this fuction is not using "arguments" so argc argv should be ignored.
        else if(method->needArgsArrInMethodSig()){
            paramIx++;
        }
    }
    /* env_param = */argi++;  // already loaded in the prologue
    i++;
    AvmAssert(i == cParams);
    AvmAssert(paramIx == nParams+1);  // +1 for initial methodEnv
    AvmAssert(argi == currentFunction->arg_end());
    
    // End the entry block so that it's easy to add things to it and before the main body.
    llvm::BasicBlock* startBlock = llvm::BasicBlock::Create(module.getContext(), "body", currentFunction);
    CreateBr(startBlock);
    SetInsertPoint(startBlock);
}

void LLVMEmitter::do_const(ConstantExpr* instr)
{
    Def* def = instr->value();
    set_def_ins(def, emitConst(type(def)));
}

void LLVMEmitter::do_loadenv(BinaryExpr* instr)
{
    int disp_id = ordinalVal(type(instr->lhs_in()));
    const Use& object = instr->rhs_in();
    llvm::Value* callee_env = emitLoadMethodEnv(emitLoadVTable(object), disp_id);
    set_def_ins(instr->value_out(), callee_env);
}

/// TODO use resolved ENV if available
///
void LLVMEmitter::do_loadinitenv(UnaryExpr* instr)
{
    const Use& object = instr->value_in();
    llvm::Value* vtable = emitLoadVTable(object);
    llvm::Value* callee_env = loadMember(vtable, module.vtable_init_member);
    set_def_ins(instr->value_out(), callee_env);
}

/// TODO use resolved ENV if available
///
void LLVMEmitter::do_loadsuperinitenv(UnaryExpr* instr)
{
    llvm::Value* env_in = def_ins(instr->value_in());
    llvm::Value* scope = loadMember(env_in, module.methodenv_scope_member);
    llvm::Value* vtable = loadMember(scope, module.scope_vtable_member);
    llvm::Value* base = loadMember(vtable, module.vtable_base_member);
    llvm::Value* env = loadMember(base, module.vtable_init_member);
    set_def_ins(instr->value_out(), env);
}
    
llvm::CallInst* LLVMEmitter::emitCall(MethodInfo* callee, llvm::Value* func, llvm::Value* callee_env, CallStmt2* call)
{
    // make sure we have a MethodFrame if we call anything
    getMethodFrame();

    // Add a dependency on the method signature of the callee
    module.poolInfo->addDependency(callee);
    
    MethodSignaturep callee_sig = callee->getMethodSignature();
    unsigned nParams = callee_sig->param_count() + 1;  // +1 for "this"
    unsigned actual_argc = call->arg_count();
    unsigned cParams = nParams;
    if (callee->needRestOrArguments() || callee->needArgsArrInMethodSig())
        cParams += 2;
    cParams += 1;  // MethodEnv*;
    std::vector<llvm::Value*> params(cParams);
    unsigned required_count = nParams - callee_sig->optional_count();
    AvmAssert(actual_argc >= required_count);
    unsigned i = 0;
    for (; i < nParams; ++i) {
        if (i < actual_argc) {
            llvm::Value* val = def_ins(call->args()[i]);
            //special handling for array objects
            if (val->getType() == module.arrayObjectPtrTy)
                val = upcastTo(val, module.scriptObjectPtrTy);
            params[i] = val;
        }
        else {
            // default arg
            Atom a = callee_sig->getDefaultValue(i - required_count);
            llvm::Value* value = 0;
            BuiltinType bt = callee_sig->paramTraitsBT(i);
            
            SlotStorageType sst = valueStorageType(bt); 
            switch (sst) {
                default:
                    AvmAssert(!"bad slotStorageType");
                case SST_int32: {
                    int ival = AvmCore::integer(a);
                    value = getInt32(ival);
                    break;
                }
                case SST_uint32: {
                    unsigned uval = AvmCore::toUInt32(a);
                    value = getInt32(uval);
                    break;
                }
                case SST_bool32: {
                    unsigned uval = AvmCore::boolean(a);
                    value = getInt32(uval);
                    break;
                }
                case SST_double: {
                    double dVal = AvmCore::number(a);
                    value = getDoubleConstant(dVal);
                    break;
                }
                case SST_string: {
                    value = getStringConstant(a);
                    break;
                }
                case SST_namespace: {
                    value = getNamespaceConstant(a);
                    break;
                }
                case SST_atom: {
                    // Receiver expects a default param presented as an atom
                    // TODO: Must be able to box any of the above types
                    value = getAtomConstant(a);
                    value->setName("dflt[" + llvm::Twine(i) + "]");
                    break;
                }
                case SST_scriptobject: {
                    AvmAssert(AvmCore::isNull(a) && (atomKind(a) == kObjectType) && "Only null default values can be handled");
                    value = llvm::ConstantPointerNull::get(module.scriptObjectPtrTy);
                    break;
                }
            }
            params[i] = value;
        }
    }
    if (callee->needRest()) {
        int nVarargs = actual_argc - nParams;
        if (nVarargs < 0)  // this can happen if there are missing optional params AND rest params
            nVarargs = 0;
        emitAtomArgs(call->args()+nParams, nVarargs);
        params[i++] = params_;
        params[i++] = getInt32(nVarargs);
    }
	//Copy all arguments including this, these arguments are consumed by
    // env->createArguments in llCreateArgumentHelper. 'this' is used to setup callee in arguments
    else if (callee->needArguments() || callee->needArgsArrInMethodSig()) {
        emitAtomArgs(call->args(), actual_argc);
        params[i++] = params_;
        params[i++] = getInt32(actual_argc-1);
    }
    else if (callee_sig->allowExtraArgs()) {
        // This case also includes ignored args... Don't pass them.
        // Anything to do here?
    }
    
    params[i++] = callee_env;
    AvmAssert(i == cParams);

    Def* value_out = call->value_out();
    AvmAssert(isBottom(type(value_out)) ||
           model(type(value_out)) == defaultModelKind(callee_sig->returnTraits()));
    (void)value_out; // unused in release builds
    
    llvm::FunctionType* functionType = module.getFunctionTy(callee);
    func = CreateBitCast(func, functionType->getPointerTo());
    
    for (int i = 0; i < cParams; ++i) {
        params[i] = coerceArg(params[i], functionType->getParamType(i));
    }

//    char s[1000];
//    sprintf(s, "About to call %s \n", func->getName().data());
//    InsertPrintf(s);
    
    return CreateCall(func, params);
}

void LLVMEmitter::InsertPrintf(const char *s)
{
    // create function
    llvm::Type* argTypes[] = { getInt8PtrTy() };
    llvm::FunctionType* funcTy = llvm::FunctionType::get( getInt32Ty() , argTypes, /* isVarArg */ false);
    llvm::Value* func = module.getOrInsertFunction("printf", funcTy);

    // create its arguments
    llvm::Constant *str = llvm::ConstantDataArray::getString(module.getContext(), s);
    llvm::GlobalVariable* gStr = new llvm::GlobalVariable(module, str->getType(), /*isConst*/ true, llvm::GlobalValue::InternalLinkage, str, ".str");
    llvm::Value* params = { CreateConstGEP2_32(gStr, 0, 0) }  ;
    //llvm::Value *params = { gStr };

    // create the call to it
    CreateCall(func, params);
}

/// TODO use resolved stuff if available
///
void LLVMEmitter::do_callmethod(CallStmt2* call)
{
    const Use& env_in = call->param_in();
    MethodInfo* callee = getMethod(type(env_in));
    StUTF8String methodName(callee->getMethodName());
    llvm::Value* callee_env = def_ins(env_in);
    llvm::Value* callee_info = loadMember(callee_env, module.methodenv_method_member);
    llvm::Value* native_info = createMemberGEP(callee_info, module.methodinfo_native_member);
    llvm::Value* func = loadMember(native_info, module.methodinfonative_handler_member);
    func->setName(methodName.c_str());
    llvm::CallInst* result = emitCall(callee, func, callee_env, call);
    set_def_ins(call->value_out(), result);
}
    
void LLVMEmitter::do_callinterface(CallStmt2* call)
{
    //
    // This is a quick-and-dirty (and slow) implementation that boxes the arguments,
    // calls coerceEnter, then unboxes the results.
    //
    const Use& env_in = call->param_in();
    MethodInfo* callee = getMethod(type(env_in));
    StUTF8String methodName(callee->getMethodName());
    llvm::Value* callee_env = def_ins(env_in);
    llvm::Value* methodInfo = getMethodInfoValue(callee);
    
    // Create a suitable function type for invoking the _impl method
    //   retType (proc*)(MethodEnv*, int32_t, uint32_t *)
    MethodSignaturep callee_sig = callee->getMethodSignature();
    llvm::Type* returnType = module.llvmType(callee_sig->returnTraits());
    llvm::Type* argTypes[] = { module.methodEnvPtrTy, getInt32Ty(), module.atomPtrTy, methodInfo->getType() };
    llvm::FunctionType* funcTy = llvm::FunctionType::get(returnType, argTypes, /* isVarArg */ false);

    llvm::Value* func = loadMember(callee_env, module.methodenv_impl_member);
    func = CreateBitCast(func, funcTy->getPointerTo());

    // Now construct the unboxed argp
    int offset = 0;
    unsigned nParams = call->arg_count();
    AvmAssert(nParams > 0);
    for (int i = 0; i < nParams; ++i) {
        llvm::Value* val = def_ins(call->args()[i]);

        //This function is used to store atom sized params. boolean, int32 should be stored in 8 bytes
        llvm::Type* valType =val->getType();
        if((valType == getInt1Ty() || valType == getInt32Ty()) && valType != module.atomTy) {
            valType = module.atomTy;
            val = CreateZExt(val, valType, val->getName());
        }

        llvm::Value* typed_ptr = offsetGenericPointer(params_, offset, valType);
        llvm::Value* store = CreateStore(val, typed_ptr);
        (void)store;

        // TODO:
        //   1 - this is naive about alignment
        // It's likely that stubs have homogeneous arguments, so alignment probably not an issue in practice.
        if(llvm::Type::getDoubleTy(getContext()) == val->getType()){
            offset += 8;
        }else{ //Atom type
            offset += sizeof(uintptr_t);
        }
            
        if (maxAvmParamSize_ < offset)
            maxAvmParamSize_ = offset;
    }
    llvm::Value* args[] = { callee_env, getInt32(nParams-1), params_, methodInfo };
//    char s[1000];
//    sprintf(s, "About to call func %s \n", func->getName().data());
//    InsertPrintf(s);

    llvm::CallInst* ins = CreateCall(func, args);

    set_def_ins(call->value_out(), ins);
}

void LLVMEmitter::do_greaterthan(BinaryExpr* instr)
{
    // This is really terrible to return an atom and then compare to true,
    // but the inner meaning here is that an AS compare can return true, false, or undefined.
    // Only "true" is true.
    // So... as a result, a < b is not equivalent to !(a >= b) since the values will differ
    // when the result of tjhe compare is undefined.
    llvm::Value* compare_atom = emitCompareLess(def_ins(instr->rhs_in()),
                                            def_ins(instr->lhs_in()));
    llvm::Value* bool_out = CreateICmpEQ(compare_atom, getAtomConstant(trueAtom), "greaterthan");
    set_def_ins(instr->value_out(), bool_out);
}

void LLVMEmitter::do_lessthan(BinaryExpr* instr)
{
    llvm::Value* compare_atom = emitCompareLess(def_ins(instr->lhs_in()),
                                            def_ins(instr->rhs_in()));
    llvm::Value* bool_out = CreateICmpEQ(compare_atom, getAtomConstant(trueAtom), "lessthan");
    set_def_ins(instr->value_out(), bool_out);
}

void LLVMEmitter::do_cast(BinaryStmt* instr)
{
    Def* value_in = def(instr->rhs_in());
    llvm::Value* value_ins = def_ins(value_in);
    llvm::Value* result_ins = downcast_obj(value_ins, env_param,
                                           traitsVal(type(instr->lhs_in())));
    set_def_ins(instr->value_out(), result_ins);
}

void LLVMEmitter::do_modulo(BinaryExpr* instr)
{
    llvm::Value* value_out = callIns(STUBINFO(mod), 2, def_ins(instr->lhs_in()),
                                     def_ins(instr->rhs_in()));
    set_def_ins(instr->value_out(), value_out);
}

void LLVMEmitter::do_addd(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateFAdd(def_ins(instr->lhs_in()), def_ins(instr->rhs_in()));
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_subd(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateFSub(def_ins(instr->lhs_in()), def_ins(instr->rhs_in()));
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_muld(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateFMul(def_ins(instr->lhs_in()), def_ins(instr->rhs_in()));
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_divd(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateFDiv(def_ins(instr->lhs_in()), def_ins(instr->rhs_in()));
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_addi(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateAdd(def_ins(instr->lhs_in()), def_ins(instr->rhs_in()));
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_subi(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateSub(def_ins(instr->lhs_in()), def_ins(instr->rhs_in()));
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_muli(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateMul(def_ins(instr->lhs_in()), def_ins(instr->rhs_in()));
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_andi(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateAnd(def_ins(instr->lhs_in()), def_ins(instr->rhs_in()));
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_ori(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateOr(def_ins(instr->lhs_in()), def_ins(instr->rhs_in()));
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_xori(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateXor(def_ins(instr->lhs_in()), def_ins(instr->rhs_in()));
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_lshi(BinaryExpr* instr)
{
    llvm::Value* value_masked = CreateAnd(def_ins(instr->rhs_in()), getInt32(0x1F));
    llvm::Value* value_out = CreateShl(def_ins(instr->lhs_in()), value_masked);
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_rshi(BinaryExpr* instr)
{
    llvm::Value* value_masked = CreateAnd(def_ins(instr->rhs_in()), getInt32(0x1F));
    llvm::Value* value_out = CreateAShr(def_ins(instr->lhs_in()), value_masked);
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_rshui(BinaryExpr* instr)
{
    llvm::Value* value_masked = CreateAnd(def_ins(instr->rhs_in()), getInt32(0x1F));
    llvm::Value* value_out = CreateLShr(def_ins(instr->lhs_in()), value_masked);
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_eqi(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateZExt(CreateICmpEQ( upcastTo(def_ins(instr->lhs_in()),getInt32Ty()),
													  upcastTo(def_ins(instr->rhs_in()),getInt32Ty())), getInt32Ty());
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_lti(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateZExt(CreateICmpSLT(def_ins(instr->lhs_in()), def_ins(instr->rhs_in())), getInt32Ty());
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_lei(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateZExt(CreateICmpSLE(def_ins(instr->lhs_in()), def_ins(instr->rhs_in())), getInt32Ty());
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_gti(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateZExt(CreateICmpSGT(def_ins(instr->lhs_in()), def_ins(instr->rhs_in())), getInt32Ty());
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_gei(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateZExt(CreateICmpSGE(def_ins(instr->lhs_in()), def_ins(instr->rhs_in())), getInt32Ty());
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_eqd(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateZExt(CreateFCmpOEQ(def_ins(instr->lhs_in()), def_ins(instr->rhs_in())), getInt32Ty());
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_ltd(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateZExt(CreateFCmpOLT(def_ins(instr->lhs_in()), def_ins(instr->rhs_in())), getInt32Ty());
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_led(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateZExt(CreateFCmpOLE(def_ins(instr->lhs_in()), def_ins(instr->rhs_in())), getInt32Ty());
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_gtd(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateZExt(CreateFCmpOGT(def_ins(instr->lhs_in()), def_ins(instr->rhs_in())), getInt32Ty());
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_ged(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateZExt(CreateFCmpOGE(def_ins(instr->lhs_in()), def_ins(instr->rhs_in())), getInt32Ty());
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_equi(BinaryExpr* instr)
{
    do_eqi(instr);
}
    
void LLVMEmitter::do_ltui(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateZExt(CreateICmpULT(def_ins(instr->lhs_in()), def_ins(instr->rhs_in())), getInt32Ty());
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_leui(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateZExt(CreateICmpULE(def_ins(instr->lhs_in()), def_ins(instr->rhs_in())), getInt32Ty());
    set_def_ins(instr->value_out(), value_out);
}
void LLVMEmitter::do_gtui(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateZExt(CreateICmpUGT(def_ins(instr->lhs_in()), def_ins(instr->rhs_in())), getInt32Ty());
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_geui(BinaryExpr* instr)
{
    llvm::Value* value_out = CreateZExt(CreateICmpUGE(def_ins(instr->lhs_in()), def_ins(instr->rhs_in())), getInt32Ty());
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_eqb(BinaryExpr* instr)
{
    do_eqi(instr);
}
    
void LLVMEmitter::do_eqp(BinaryExpr* instr)
{
    llvm::Value* lhs = def_ins(instr->lhs_in()), *rhs = def_ins(instr->rhs_in());
    if (lhs->getType() != rhs->getType()) {
        if (canUpcastTo(lhs->getType(), rhs->getType()))
            lhs = upcastTo(lhs, rhs->getType());
        else if (canUpcastTo(rhs->getType(), lhs->getType()))
            rhs = upcastTo(rhs, lhs->getType());
        else
            AvmAssert(!"incompatible pointer compare");
    }
    llvm::Value* value_out = CreateZExt(CreateICmpEQ(lhs, rhs), getInt32Ty());
    set_def_ins(instr->value_out(), value_out);
}

void LLVMEmitter::do_i2d(UnaryExpr* instr)
{
    llvm::Value* value_out = CreateSIToFP(def_ins(instr->value_in()), getDoubleTy());
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_d2i(UnaryExpr* instr)
{
    llvm::Value* value_out = CreateFPToSI(def_ins(instr->value_in()), getInt32Ty());
    set_def_ins(instr->value_out(), value_out);
}
    
void LLVMEmitter::do_negd(UnaryExpr* instr)
{
    llvm::Value* value_out = CreateFNeg(def_ins(instr->value_in()));
    set_def_ins(instr->value_out(), value_out);
}

void LLVMEmitter::do_noti(UnaryExpr* instr)
{
    llvm::Value* value_out = CreateNot(def_ins(instr->value_in()));
    set_def_ins(instr->value_out(), value_out);
}

void LLVMEmitter::do_u2d(UnaryExpr* instr)
{
    llvm::Value* value_out = CreateUIToFP(def_ins(instr->value_in()), getDoubleTy());
    set_def_ins(instr->value_out(), value_out);
}
    
llvm::Value* LLVMEmitter::atomToScriptObject(llvm::Value* object)
{
    return removeTagReturningPointer(object, module.scriptObjectPtrTy);
}

void LLVMEmitter::do_setslot(CallStmt2* instr)
{
    const Use& name_in = instr->param_in();
    const Use& object_in = instr->object_in();
    const Use& value_in = instr->vararg(0);

    int slot = ordinalVal(type(name_in));
    const Type* value_type = type(value_in);
    const Type* object_type = type(object_in);
    AvmAssert(getTraits(object_type) && "slot ops require a type with slots");
    AvmAssert(subtypeof(value_type, ir->lattice.getSlotType(object_type, slot)));
    
    // IMPORTANT: ignore the lattice info about layouts since that applies to the host architecture, not the target
    // uint32_t offset = ir->lattice.getSlotOffset(object_type, slot);
    StructInfo* slotLayout = module.getSlotLayout(getTraits(object_type));
    FieldInfo* field = slotLayout->getSlot(slot);
    
    llvm::Value* object = def_ins(object_in);
    switch (model(value_type)) {
        default:
            printf("model is: %d\n", model(value_type));
            AvmAssert(!"Unsupported model");
        case kModelAtom: {
            llvm::Value* ep = createMemberGEP(object, field, llvm::StringRef(field->name) + "&");
            callIns(STUBINFO(atomWriteBarrier), 4, gcAddr, object, ep, def_ins(value_in));
            break;
        }
        case kModelScriptObject:
        case kModelString:
        case kModelNamespace: {
            llvm::Value* ep = createMemberGEP(object, field, llvm::StringRef(field->name) + "&");
            callIns(STUBINFO(privateWriteBarrierRC), 4, gcAddr, object, ep, def_ins(value_in));
            break;
        }
        case kModelInt:
        case kModelDouble:
            storeMember(def_ins(value_in), object, field);
            break;
    }
}

void LLVMEmitter::do_getslot(CallStmt2* instr)
{
    const Use& name_in = instr->param_in();
    const Use& object_in = instr->object_in();

    int slot = ordinalVal(type(name_in));
    const Type* object_type = type(object_in);
    const Type* slot_type = ir->lattice.getSlotType(object_type, slot);
    AvmAssert(subtypeof(type(instr->value_out()), slot_type));
    (void)slot_type; // unused in release builds
    
    // IMPORTANT: ignore the lattice info about layouts since that applies to the host architecture, not the target
    // uint32_t offset = ir->lattice.getSlotOffset(object_type, slot);
    StructInfo* slotLayout = module.getSlotLayout(getTraits(object_type));
    FieldInfo* field = slotLayout->getSlot(slot);

    llvm::Value* object = def_ins(object_in);
    llvm::Value* value = loadMember(object, field);
    set_def_ins(instr->value_out(), value);
}

void LLVMEmitter::do_newinstance(UnaryExpr* instr)
{
    // copied from CodegenLIR::emitCall() case OP_construct
    const Use& ctor_in = instr->value_in();
    llvm::Value* vtable = emitLoadVTable(ctor_in);
    llvm::Value* ivtable = loadMember(vtable, module.vtable_ivtable_member);
    llvm::Value* funcptr = loadMember(ivtable, module.vtable_createinstanceproc_member);
    llvm::Value* object = callIns(STUBINFO(createInstanceProc), 2, funcptr, def_ins(ctor_in));
    set_def_ins(instr->value_out(), object);
}
    
void LLVMEmitter::do_newclass(NaryStmt2* instr)
{
    Traits* ctraits = traitsVal(type(instr->traits_in()));
    llvm::Value* baseVal = def_ins(instr->base_in());
    int classIndex = -1;
    for (int i = 0, end = pool->classCount(); i < end; ++i) {
        if (pool->getClassTraits(i) == ctraits) {
            classIndex = i;
            break;
        }
    }
    AvmAssert(classIndex != -1);
    
    std::string className(module.traitsName(ctraits));
    if (options::debugScopes) {
        printf(">> newClass %s %d\n", className.c_str(), classIndex);
    }
    
    const ScopeTypeChain *stc = ctraits->declaringScope();
    int nScopes = stc->size, nWithScopes = 0;
    int extraScopeCount = instr->arg_count();
    for (int i = 0; i < nScopes; ++i)
        if (stc->getScopeIsWithAt(i))
            ++nWithScopes;
    emitAtomArgs(instr->args(), extraScopeCount);
    
    std::vector<llvm::Value*> scopeTraitsVec(extraScopeCount);
    for (int i = nScopes-extraScopeCount, j = 0; i < nScopes; ++i,++j) {
        Traits* t = stc->getScopeTraitsAt(i);
        scopeTraitsVec[j] =  module.getTraitsValue(this, t);
        if (options::debugScopes) {
            printf(">>   scope %s %s\n", module.traitsName(t).c_str(), scopeTraitsVec[j]->getName().data());
       }
    }
    llvm::Value* scopeTraitsConst = CreateAlloca(module.traitsPtrTy, getInt32(scopeTraitsVec.size()), "scopeTraitsArray");
    
    for (int i = 0; i < scopeTraitsVec.size(); ++i) {
        llvm::Value* argLoc = CreateConstGEP1_32(scopeTraitsConst, i, "av" + llvm::Twine(i) + "&");
        CreateStore(scopeTraitsVec[i], argLoc);
    }
        
    // extern "C" ClassClosure* llNewClass(MethodEnv* env, int classIndex, Traits** ctraitsp, Traits** itraitsp, Traits*** scopeTraits,
    //     ClassClosure* base, int nWithScopes, int scopeCount, Atom* scopes)
    llvm::Value* result = callIns(STUBINFO(llNewClass), 7,
        env_param, getInt32(classIndex), /*traitsVar, itraitsVar,*/ scopeTraitsConst, baseVal,
        getInt32(nWithScopes), getInt32(extraScopeCount), params_);
    set_def_ins(instr->value_out(), result);
}

void LLVMEmitter::do_newfunction(NaryStmt1* instr)
{
    MethodInfo* body = methodVal(type(instr->info_in()));
    StUTF8String containingMethodName(method->getMethodName());
    StUTF8String functionName(body->getMethodName());
    if (options::debugScopes) {
        printf(">> newFunction %s, %d, %s, %s\n", containingMethodName.c_str(), body->method_id(), functionName.c_str(), /*dclTraitsVar->getName().data(), */module.traitsName(body->declaringTraits()).c_str());
    }
    const ScopeTypeChain *stc = body->declaringScope();
    int nScopes = stc->size, nWithScopes = 0;
    int extraScopeCount = instr->arg_count();
    for (int i = nScopes-1; i >= 0 && stc->getScopeIsWithAt(i); --i)
        ++nWithScopes;
    std::vector<llvm::Value*> scopeTraitsVec(extraScopeCount);
    for (int i = nScopes- extraScopeCount, j = 0; i < nScopes; ++i, ++j) {
        Traits* t = stc->getScopeTraitsAt(i);
        scopeTraitsVec[j] =  module.getTraitsValue(this, t);
        if (options::debugScopes) {
            printf(">>   scope %s %s\n", module.traitsName(t).c_str(), scopeTraitsVec[j]->getName().data());
        }
    }
    
    llvm::Value* scopeTraitsConst = CreateAlloca(module.traitsPtrTy, getInt32(scopeTraitsVec.size()), "scopeTraitsArray");
    
    for (int i = 0; i < scopeTraitsVec.size(); ++i) {
        llvm::Value* argLoc = CreateConstGEP1_32(scopeTraitsConst, i, "av" + llvm::Twine(i) + "&");
        CreateStore(scopeTraitsVec[i], argLoc);
    }

    
    emitAtomArgs(instr->args(), extraScopeCount);
    // extern "C" ClassClosure* llNewFunction(MethodEnv* env, uint32_t methodindex, Traits** idForDeclaringTraits, Traits*** scopeTraits,
    //     int nWithScopes, int scopeCount, Atom* scopes)

    llvm::Value* result = callIns(STUBINFO(llNewFunction), 6,
        env_param, getInt32(body->method_id()), scopeTraitsConst,
        getInt32(nWithScopes), getInt32(extraScopeCount), params_);
    set_def_ins(instr->value_out(), result);
}
    
void LLVMEmitter::do_newactivation(UnaryStmt* instr)
{
    const Use& value_in = instr->value_in();
    llvm::Value* envValue = def_ins(value_in);
    llvm::Value* result = callIns(STUBINFO(llNewActivation), 1, envValue);
    set_def_ins(instr->value_out(), result);
}

// i2u is just a copy at the machine level, so point to the input LIns*.
void LLVMEmitter::do_i2u(UnaryExpr* instr)
{
    set_def_ins(instr->value_out(), def_ins(instr->value_in()));
}

// u2i is just a copy at the machine level, so point to the input LIns*.
void LLVMEmitter::do_u2i(UnaryExpr* instr)
{
    set_def_ins(instr->value_out(), def_ins(instr->value_in()));
}

/** Generate one handler for all kConvertNullToObjectError errors. */
llvm::BasicBlock* LLVMEmitter::emitNpeHandler()
{
    if (!npe_block) {
        npe_block = llvm::BasicBlock::Create(module.getContext(), "npe", currentFunction);
        PushBuilder push(this, npe_block);
        callIns(STUBINFO(llNPE), 1, env_param);
        CreateUnreachable();
    }
    return npe_block;
}

/** Generate one handler for all kConvertUndefinedToObjectError errors. */
llvm::BasicBlock* LLVMEmitter::emitUpeHandler()
{
    if (!upe_block) {
        upe_block = llvm::BasicBlock::Create(module.getContext(), "upe", currentFunction);
        PushBuilder push(this, upe_block);
        upe_phi = CreatePHI(module.atomTy, 1, "nullOrUndef");
        callIns(STUBINFO(llUPE), 2, env_param, upe_phi);
        CreateUnreachable();
    }
    return upe_block;
}

void LLVMEmitter::do_cknull(UnaryStmt* instr)
{
    const Use& value_in = instr->value_in();
    llvm::Value* atom = def_ins(value_in);
    llvm::Value* undefined_ins = getAtomConstant(undefinedAtom);
    llvm::BasicBlock* nullcheck_ok = llvm::BasicBlock::Create(module.getContext(), "", currentFunction);
    CreateCondBr(CreateICmpULE(atom, undefined_ins), emitUpeHandler(), nullcheck_ok);
    upe_phi->addIncoming(atom, GetInsertBlock());
    SetInsertPoint(nullcheck_ok);
    set_def_ins(instr->value_out(), atom);
}

void LLVMEmitter::do_cknullobject(UnaryStmt* instr)
{
    const Use& value_in = instr->value_in();
    llvm::Value* ptr = def_ins(value_in);
    llvm::BasicBlock* nullcheck_ok = llvm::BasicBlock::Create(module.getContext(), "", currentFunction);
    AvmAssert(ptr->getType()->isPointerTy());
    llvm::Value* cmp = CreateICmpEQ(ptr, llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(ptr->getType())));
    CreateCondBr(cmp, emitNpeHandler(), nullcheck_ok);
    SetInsertPoint(nullcheck_ok);
    set_def_ins(instr->value_out(), ptr);
}

// TODO (stan): AOT doesn't need to implement timeouts, except possibly at safepoints
void LLVMEmitter::do_cktimeout(UnaryStmt* instr)
{
    set_def_ins(instr->value_out(), getInt32(0)); // always return false.
}

void LLVMEmitter::do_doubletoint32(UnaryExpr* instr)
{
	//commenting CreateFPToSI and generating a call to avmplus::doubleToInt32
	//Reason - On boundary cases (overflow ) CreateFPToSI behavior is undefined as per llvm documentation.
    //TODO - This can be improved based on logic at LirEmitter::do_doubletoint32.
    emitHelperCall2(instr, STUBINFO(doubleToInt32));
//    llvm::Value* arg = def_ins(instr->value_in());
//    llvm::Value* result = CreateFPToSI(arg, getInt32Ty()); //### TODO: Verify semantics.
//    set_def_ins(instr->value_out(), result);
}

void LLVMEmitter::do_abc_add(BinaryStmt* instr)
{
    const Use& lhs = instr->lhs_in();
    const Use& rhs = instr->rhs_in();
    llvm::Value* left_operand = def_ins(lhs);
    llvm::Value* right_operand = def_ins(rhs);
    llvm::Value* result = callIns(STUBINFO(op_add_a_aa), 3,
                                  coreAddr, left_operand, right_operand);
    set_def_ins(instr->value_out(), result);
}

/// changes model int to model atom
void LLVMEmitter::do_int2atom(UnaryExpr* i)
{
    emitHelperCall2(i, STUBINFO(intToAtom));
}

/// changes model double to atom
void LLVMEmitter::do_double2atom(UnaryExpr* i)
{
    emitHelperCall2(i, STUBINFO(doubleToAtom));
}

/// tags an atom value with the given tag
void LLVMEmitter::doTagPointer(UnaryExpr* instr, Atom tag)
{
    const Use& value_in = instr->value_in();
    llvm::Value* result = applyTagToPointer(def_ins(value_in), tag);
    set_def_ins(instr->value_out(), result);
}

//###
void LLVMEmitter::do_scriptobject2atom(UnaryExpr* i)
{
    doTagPointer(i, kObjectType);
}
void LLVMEmitter::do_string2atom(UnaryExpr* i)
{
    doTagPointer(i, kStringType);
}
void LLVMEmitter::do_ns2atom(UnaryExpr* i)
{
    doTagPointer(i, kNamespaceType);
}

/// changes model atom to scriptobject
void LLVMEmitter::do_atom2scriptobject(UnaryExpr* instr)
{
    const Use& value_in = instr->value_in();
    llvm::Value* result = removeTagReturningPointer(def_ins(value_in), module.scriptObjectPtrTy);
    set_def_ins(instr->value_out(), result);
}

/// changes model bool to atom
void LLVMEmitter::do_bool2atom(UnaryExpr* instr)
{
    Def* value_in = def(instr->value_in());
    llvm::Value* result = nativeToAtom(def_ins(value_in), getTraits(type(value_in)));
    set_def_ins(instr->value_out(), result);
}

void LLVMEmitter::do_getouterscope(BinaryExpr* instr)
{
    int scope_index = ordinalVal(type(instr->lhs_in()));
    llvm::Value* env_in = def_ins(instr->rhs_in()); // env to use
    llvm::Value* scope_chain = loadMember(env_in, module.methodenv_scope_member);
    llvm::Value* scopes = createMemberGEP(scope_chain, module.scope_scopes_member);
    llvm::Value* valuep = CreateConstGEP1_32(scopes, scope_index);
    llvm::Value* value = CreateLoad(valuep, "outer_scope");
    set_def_ins(instr->value_out(), value);
}

void LLVMEmitter::do_not(UnaryExpr* instr)
{
    llvm::Value* x = def_ins(instr->value_in());
    llvm::Value* value = 0;
    if (x->getType()->isIntegerTy(1))
        value = CreateICmpEQ(x, getInt1(false));
    else
        value = CreateICmpEQ(x, getInt32(0));
    set_def_ins(instr->value_out(), value);
}

void LLVMEmitter::do_abc_finddef(BinaryStmt* instr)
{
    const Multiname* mn = nameVal(type(instr->lhs_in()));
    MultinameDesc nameStr(core, mn);
    llvm::Value* targetObjAddr = CreateConstGEP2_32(getFinddefTableAddress(), 0,
                                          getMultinameIndexInPool(mn));
    
    //Load the sciptobject
    llvm::Value* targetObj = CreateLoad(targetObjAddr, "FDCache:" + llvm::Twine(nameStr.c_str()));
    llvm::BasicBlock* oldBlock = GetInsertBlock();
  
    //check not null
    llvm::Value* cmp = CreateICmpEQ(targetObj, llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(targetObj->getType())));
    llvm::BasicBlock* ifNull = llvm::BasicBlock::Create(getContext(), "", currentFunction);
    llvm::BasicBlock* ifNonNull = llvm::BasicBlock::Create(getContext(), "", currentFunction);
    CreateCondBr(cmp, ifNull, ifNonNull);
    SetInsertPoint(ifNull);
    
    //If script object is not there then generate call to finddef_miss
    llvm::Value* newTargetObj = callIns(STUBINFO(finddef_miss), 2,targetObjAddr,getMethodFrame());
  
    CreateBr(ifNonNull);
    SetInsertPoint(ifNonNull);
  
    llvm::PHINode* finddefPhi = llvm::PHINode::Create(module.scriptObjectPtrTy, 2, "abc_finddef", ifNonNull);
    finddefPhi->addIncoming(targetObj, oldBlock);
    finddefPhi->addIncoming(newTargetObj, ifNull);
  
    set_def_ins(instr->value_out(), finddefPhi);
}
  
void LLVMEmitter::emitHelperCall2(UnaryExpr* instr, const LLVMModule::StubInfo* call)
{
    const Use& value_in = instr->value_in();
    llvm::Value* result = callIns(call, 2, coreAddr, def_ins(value_in));
    set_def_ins(instr->value_out(), result);
}
    
void LLVMEmitter::emitSafepointSetup() {
    if (safepoint_space_)
        return;
    int safepoint_size = signature->stack_base();  // space for args and acopes
    safepoint_space_ = CreateAlloca(module.atomTy, getInt32(safepoint_size),
                                    "safepoint_space_");
}

void LLVMEmitter::emitExceptionHandling() {
    if (!have_catchblocks_)
        return;
    
    //
    // Exception handling working storage
    //
    
    exceptionFrame_ = CreateAlloca(module.exceptionFrameStruct->type, getInt32(1), "exceptionFrame");
    save_eip_ = CreateAlloca(getInt32Ty(), getInt32(1), "vpc");
    exceptionAtom_ = CreateAlloca(module.ptrSizedIntTy, getInt32(1), "exceptionAtom");
    
    //
    // Need safepoints
    //
    emitSafepointSetup();
    
    //
    // Awkward place for this, but needs to be after safepoints and eip are set up
    // and should be before the rest of exception setup
    //
    if (ir && ir->debugging())
        emitDebugEnter();
    
    //
    // Additions to the function prologue
    //
    
    // Initiailize the eip
    storeVPC(-1, true /*force*/);
    
    // ef_.beginTry(core);
    callIns(STUBINFO(beginTry), 2, exceptionFrame_, coreAddr);
    
    // Exception* setjmpResult = setjmp(exceptionFrame_.jmpBuf);
    llvm::Value* jmpbuf = createMemberGEP(exceptionFrame_, module.exceptionFrame_jmpbuf_member, "jmpbuf");
    llvm::CallInst* setjmpResult = callIns(STUBINFO(setjmp), 2, jmpbuf, getInt32(0));
    setjmpResult->setCanReturnTwice();
    
    catch_block_ = llvm::BasicBlock::Create(module.getContext(), "catch_handler", currentFunction);
    llvm::BasicBlock* afterExSetup = llvm::BasicBlock::Create(module.getContext(), "after_ex_setup", currentFunction);
    llvm::Value* setjmpNZ = CreateICmpNE(setjmpResult, getInt32(0));
    CreateCondBr(setjmpNZ, catch_block_, afterExSetup);
    SetInsertPoint(afterExSetup);

    {
        //
        // Digress to emit the catch block
        //
        PushBuilder push(this, catch_block_);
        
        ExceptionHandlerTable* eht = method->abc_exceptions();
        int exception_count = eht->exception_count;
        
        // Create the exception description table
        std::vector<llvm::Constant*> exceptionDescs(exception_count);
        std::vector<llvm::Value*> matchTraitspVec(exception_count);
        for (int i = 0; i < exception_count; ++i) {
            ExceptionHandler& hdlr = eht->exceptions[i];
            ConstStructInitializer exceptionDesc(module.aotExceptionDescStruct);
            exceptionDesc.init(module.aotExceptionDesc_from_member, getInt32(hdlr.from));
            exceptionDesc.init(module.aotExceptionDesc_to_member, getInt32(hdlr.to));
            int type_index = 0, name_index = 0;
            if (hdlr.scopeTraits) {
                const uint8_t* pos = hdlr.scopeTraits->getRawTraitsPos();
                type_index = AvmCore::readU32(pos);
                name_index = AvmCore::readU32(pos);
            }
            llvm::Constant* typeIndexU30 = makeU32Constant(type_index, 5);
            exceptionDesc.init(module.aotExceptionDesc_typeIndexU30_member, typeIndexU30);
            exceptionDesc.init(module.aotExceptionDesc_nameIndex_member, getInt32(name_index));
            exceptionDescs[i] = exceptionDesc.create();
            
            //Moved matchtraitsp out of exceptionDesc because of the restriction imposed by ConstStructInitializer, that all members of the structure have to be of type llvm::Contanst. In an attempt to make this non global we are using llvm::value for matchTraitsp instead.
            matchTraitspVec[i] = module.getTraitsValue(this, hdlr.traits);
            
        }
        llvm::Constant* exceptionDescsConst = llvm::ConstantArray::get(llvm::ArrayType::get(module.aotExceptionDescTy, exceptionDescs.size()), exceptionDescs);
        llvm::GlobalVariable* exceptionDescsVar = new llvm::GlobalVariable(module,
            exceptionDescsConst->getType(), /*isConst*/ true, llvm::GlobalValue::InternalLinkage,
            exceptionDescsConst, "exceptionDesc");
        llvm::Value* exceptionDescsVal = CreateConstGEP2_32(exceptionDescsVar, 0, 0);  // [n x AOTExceptionDesc] -> *AOTExceptionDesc

        llvm::Value* saved_eip = CreateLoad(save_eip_, "vpc_");
        // exceptionFrame_.beginCatch()
        
        llvm::Value* matchTraitspConst = CreateAlloca(module.traitsPtrTy, getInt32(matchTraitspVec.size()), "matchTraitspArray");
        for (int i = 0; i < matchTraitspVec.size(); ++i) {
                        llvm::Value* argLoc = CreateConstGEP1_32(matchTraitspConst, i, "av" + llvm::Twine(i) + "&");
                        CreateStore(matchTraitspVec[i], argLoc);
                    }

        llvm::Value* handler_ordinal = callIns(STUBINFO(llBeginCatch), 7, env_param, exceptionFrame_, saved_eip, getInt32(exception_count), exceptionDescsVal, matchTraitspConst, exceptionAtom_);
        
        int handler_count = method->abc_exceptions()->exception_count;

        // Find last reachable handler, to optimize branches generated below
        int last_ordinal = -1;
        for (int i = 0; i < handler_count; ++i) {
            ExceptionHandler* h = &method->abc_exceptions()->exceptions[i];
            if (catch_blocks_.count(h->target)) {
                last_ordinal = i;
            }
        }
        
        // There should be at least one reachable handler.
        AvmAssert(last_ordinal >= 0);
                
        // Generate a switch statement to every possible target.
        // There can be unreachable ordinals but we have to do something about them.
        // Follow the JIT's lead and just route them to the last catch block.
        CatchBlockInstr* defaultCatchBlockInstr = catch_blocks_[method->abc_exceptions()->exceptions[last_ordinal].target];
        llvm::BasicBlock* defaultCatchBlock = getBlock(defaultCatchBlockInstr);
        
        // You could make this a branch if there is only one catch, but LLVM will figure that out.
        // A special case for that is just one more way to possibly be wrong.
        llvm::SwitchInst* sw = CreateSwitch(handler_ordinal, defaultCatchBlock, last_ordinal);
        // Don't generate a case for the last ordinal; the default catches it
        for (int j = 0; j < last_ordinal; j++) {
            ExceptionHandler* h = &method->abc_exceptions()->exceptions[j];
            if (catch_blocks_.count(h->target)) {
                llvm::BasicBlock* catchBlock = getBlock(catch_blocks_[h->target]);
                sw->addCase(getInt32(j), catchBlock);
            }
        }
    }
}

void LLVMEmitter::emitDebugEnter()
{
    if (call_stack_node_)
        return;

    call_stack_node_ = CreateAlloca(module.callStackNodeTy, getInt32(1), "callStackNode");
    llvm::Value* eip = save_eip_;
    if (!eip)
        eip = llvm::ConstantPointerNull::get(getInt32Ty()->getPointerTo());
    callIns(STUBINFO(debugEnter), 5,
                     env_param, llvm::ConstantPointerNull::get(module.genericPtrTy),
                     call_stack_node_, safepoint_space_, eip);
}

llvm::Value* LLVMEmitter::getActivationTraitsForMethodInfo(MethodInfo* methodInfo)
{
    llvm::Value* methodInfoVal = getMethodInfoValue(methodInfo);
    return callIns(STUBINFO(activationTraits), 1,methodInfoVal);
}

    
void LLVMEmitter::storeVPC(int vpc, bool force)
{
    if (!force && saved_eip_ == vpc)
        return;
    if (!save_eip_) // debugging, no exceptions
        return;
    saved_eip_ = vpc;
    llvm::StoreInst* storeEip = CreateStore(getInt32(vpc), save_eip_);
    storeEip->setVolatile(true);
}

void LLVMEmitter::do_catchblock(CatchBlockInstr* instr) {
    llvm::BasicBlock* bb = getBlock(instr);
    bb->setName("catch_" + llvm::Twine(instr->vpc));
    SetInsertPoint(bb);
    
    int safepoint_size = signature->stack_base();  // space for args and scopes
    
    storeVPC(instr->vpc, true /*force*/);
    
    // "params" are in fact the arguments (locals), scopes, and one "stack" location for the exception atom
    for (int i = 0, n = instr->paramc; i < n; ++i) {
        Def* param = &instr->params[i];
        if (!param->isUsed())
            continue;
        const Type* param_type = type(param);
        if (!isLinear(param_type) && !isState(param_type)) {
            if (i < safepoint_size) {
                llvm::Type* paramTy = module.llvmType(param_type);
                llvm::Value* spLoc = CreateConstGEP1_32(safepoint_space_, i, "safepoint[" + llvm::Twine(i) + "]_");
                if (spLoc->getType() != paramTy->getPointerTo())
                    spLoc = CreateBitCast(spLoc, paramTy->getPointerTo());
                llvm::LoadInst* val = CreateLoad(spLoc, "cblocal[" + llvm::Twine(i) + "]");
                val->setVolatile(true);
                set_def_ins(param, val);
            }
            else if (i == safepoint_size) {
                llvm::LoadInst* exAtom = CreateLoad(exceptionAtom_);
                exAtom->setName("caught_" + llvm::Twine(instr->vpc));
                set_def_ins(param, exAtom);
            }
            else {
                AvmAssert(!"Illegal catchblock param");
            }
        }
    }
}


/// Newstate allocates space on the stack for safepoints
/// Unneeded for static compilation.
void LLVMEmitter::do_newstate(ConstantExpr* instr)
{
    (void)instr;
}

/// Saves the ABC local var, which also represents ABC operand stack values
/// Stores the local in its native format + type tag. Hopefully
/// NanoJIT removes the tag stores
void LLVMEmitter::do_setlocal(SetlocalInstr* instr)
{
    // again, the safepointable things are the locals and scopes
    int safepoint_size = signature->stack_base();  // space for args and scopes
    int varNo = instr->index;
    
    // TODO: Halfmoon creates setlocal instructions for frame state updates that are "stack pushes."
    // and not just for setlocals. We don't need any of those for now.
    if (varNo >= safepoint_size)
        return;

    llvm::Type* paramTy = module.llvmType(def(instr->value_in()));
    llvm::Value* spLoc = CreateConstGEP1_32(safepoint_space_, varNo, "setlocal[" + llvm::Twine(varNo) + "]_");
    llvm::StoreInst* st = CreateStore(def_ins(instr->value_in()), spLoc);
    st->setVolatile(true);
}

void LLVMEmitter::do_getlocal(GetlocalStmt* instr)
{
    int safepoint_size = signature->stack_base();  // space for args and scopes
    int varNo = instr->index;
    
    AvmAssert(varNo < safepoint_size);
    
    llvm::Value* spLoc = CreateConstGEP1_32(safepoint_space_, varNo);
    llvm::LoadInst* load = CreateLoad(spLoc, "getlocal[" + llvm::Twine(varNo) + "]_");
    set_def_ins(instr->value_out(), load);
}

/// Generates LIR for a safepoint instruction
/// Any safepoint instr that gets here cannot be optimized away
/// Stores the abc pc, setlocals store the actual data prior to this safepoint
void LLVMEmitter::do_safepoint(SafepointInstr* instr)
{
    storeVPC(instr->vpc);
}

llvm::Constant* LLVMEmitter::makeU32Constant(unsigned n, unsigned size)
{
    llvm::SmallVector<uint8_t, 5> buf;
    while (n > 0x7f) {
        buf.push_back(0x80 | (n & 0x7f));
        n = n >> 7;
    }
    buf.push_back(n);
    if (size > 0) {
        AvmAssert(size >= buf.size());
        buf.append(size - buf.size(), 0);
    }
    llvm::Constant* ca = llvm::ConstantDataArray::get(module.getContext(), buf);
    return ca;
}

// has next 2 modifies the object and index in place.
void LLVMEmitter::do_abc_hasnext2(Hasnext2Stmt* instr)
{
    AvmAssert (model(type(instr->object_in())) == kModelAtom);
    AvmAssert (model(type(instr->counter_in())) == kModelInt);
    
    CreateStore(def_ins(instr->object_in()), hasnextAtom_);
    CreateStore(def_ins(instr->counter_in()), hasnextCounter_);
    llvm::Value* new_index = callIns(STUBINFO(hasnextproto), 3, env_param, hasnextAtom_, hasnextCounter_);

    set_def_ins(instr->value_out(), new_index);
    set_def_ins(instr->object_out(), CreateLoad(hasnextAtom_));
    set_def_ins(instr->counter_out(), CreateLoad(hasnextCounter_));
}
    
llvm::BasicBlock* LLVMEmitter::splitEdgeIfNecessary(llvm::BasicBlock* fromBlock, llvm::BasicBlock* toBlock)
{
    // Can't have two predecessors from the same block in a phi.
    // So if that happens create and return a new block that branches to the destination block.
    // If not, returns fromBlock.
    if (llvm::PHINode *phi = llvm::dyn_cast<llvm::PHINode>(toBlock->begin())) {
        for (unsigned i = 0, n = phi->getNumIncomingValues(); i < n; ++i) {
            if (phi->getIncomingBlock(i) == fromBlock) {
                // Create branch instruction
                llvm::BasicBlock* bb = llvm::BasicBlock::Create(module.getContext(), fromBlock->getName()+"_split", currentFunction);
                PushBuilder push(this, bb);
                CreateBr(toBlock);
                
                // patch the original terminator instruction
                llvm::TerminatorInst* ins = fromBlock->getTerminator();
                AvmAssert(ins != NULL);
                
                // reuse i and n; we're returning anyway
                int nPatched = 0;
                for (i = 0, n = ins->getNumSuccessors(); i < n; ++i) {
                    if (toBlock == ins->getSuccessor(i)) {
                        ins->setSuccessor(i, bb);
                        ++nPatched;
                    }
                }
                AvmAssert(nPatched > 0);  // must have patched something
                return bb;
            }
        }
    }
    return fromBlock;
}

llvm::PHINode* LLVMEmitter::insertPhi(llvm::BasicBlock* bb, llvm::Type *type,
                                      unsigned numReservedValues, const llvm::Twine& name)
{
    if (llvm::Instruction* ins = getFirstNonPHI(bb))
        return llvm::PHINode::Create(type, numReservedValues, name, ins);
    else  // no non-phis so add at end
        return llvm::PHINode::Create(type, numReservedValues, name, bb);
}

static int countPreds(LabelInstr* instr) {
    GotoInstr *g = instr->preds;
    if (g == 0)
        return 0;
    int i = 0;
    do {
        ++i;
        g = g->next_goto;
    } while (g != instr->preds);
    return i;
}

void LLVMEmitter::createPhiNodes(LabelInstr* instr)
{
    llvm::BasicBlock* bb = getBlock(instr);
    const int nPreds = countPreds(instr);
    for (int iArg = 0, nArg = instr->paramc; iArg < nArg; ++iArg) {
        Def* param = &instr->params[iArg];
        if (has_def_ins(param))
            return;  // been there, done that
        const Type* param_type = type(param);
        if (!isLinear(param_type) && !isState(param_type)) {
            llvm::PHINode* phi = insertPhi(bb, module.llvmType(param_type), nPreds);
            set_def_ins(param, phi);
        }
    }
}
    
void LLVMEmitter::addPhiEdges(GotoInstr* instr)
{
    LabelInstr* label = instr->target;
    createPhiNodes(label);
    llvm::BasicBlock* fromBlock = GetInsertBlock();
    // no need to worry about splitting since goto instrs have only a single target
    for (int iArg = 0, nArg = label->paramc; iArg < nArg; ++iArg) {
        Use& arg = instr->args[iArg];
        Def& param = label->params[iArg];
        if (!isLinear(type(arg)) && !isState(type(arg))) {
            llvm::PHINode* phi = llvm::dyn_cast<llvm::PHINode>(def_ins(&param));
            AvmAssert(phi != 0);
            llvm::Type* paramTy = module.llvmType(param);
            llvm::Value* argVal = coerceArg(def_ins(arg), paramTy);
            phi->addIncoming(argVal, fromBlock);
            if (phi->getName().empty() && !argVal->getName().empty()) {
                // propagate the name of the first named argument... better than nothing
                const char* suffix = "!";
                if (argVal->getName().endswith(suffix))
                    suffix = "";
                phi->setName(argVal->getName() + suffix);
            }
        }
    }
}

void LLVMEmitter::createPhiNodes(ArmInstr* instr)
{
    llvm::BasicBlock* bb = getBlock(instr);
    const int nPreds = 1;  // ARM nodes by definition have single predecessors
    for (int iArg = 0, nArg = instr->owner->argc; iArg < nArg; ++iArg) {
        Def* param = &instr->params[iArg];
        if (has_def_ins(param))
            return;  // been there, done that
        const Type* param_type = type(param);
        if (!isLinear(param_type) && !isState(param_type)) {
            llvm::PHINode* phi = insertPhi(bb, module.llvmType(param_type), nPreds);
            set_def_ins(param, phi);
        }
    }
}

void LLVMEmitter::addPhiEdges(CondInstr* instr)
{
    // each arm
    for (int iArm = 0, nArm = instr->armc; iArm < nArm; ++iArm) {
        ArmInstr* arm = instr->arms[iArm];
        createPhiNodes(arm);
        llvm::BasicBlock* toBlock = getBlock(arm);
        // splitting accounts for the possibility that one arm might be reached by
        // differnt edges of the condition and differen "parameters."
        llvm::BasicBlock* fromBlock = splitEdgeIfNecessary(GetInsertBlock(), toBlock);
        // each arg (arg 0 is the condition)
        for (int iArg = 1, nArg = instr->argc; iArg < nArg; ++iArg) {
            Use& arg = instr->args[iArg];
            Def& param = arm->params[iArg];
            if (!isLinear(type(arg)) && !isState(type(arg))) {
                llvm::PHINode* phi = llvm::dyn_cast<llvm::PHINode>(def_ins(&param));
                AvmAssert(phi != 0);
                llvm::Type* paramTy = module.llvmType(param);
                llvm::Value* argVal = coerceArg(def_ins(arg), paramTy);
                phi->addIncoming(argVal, fromBlock);
            }
        }
    }
}

  llvm::Value* LLVMEmitter::getInterfaceTraitsValue(Traits* traits)
  {
    // Interface traits aren't initialized via newclass instructions.
    // Instead, access them from their defining pool.
    //First search in current pool
    if (pool == traits->pool) {
      for (int j = 0, end = (int)pool->classCount(); j < end; ++j) {
        if (traits == pool->getClassTraits(j)->itraits) {
          llvm::Value* res = loadInterfaceTraitsFromPool(poolAddr, j);
          res->setName(module.traitsName(traits) + "_interface");
          return res;
        }
      }
    }

    // Otherwise check all pools
    for (int i = 0; i < core->poolInfos.size(); i++) {
      PoolInfo* poolInfo = core->poolInfos[i];
      PoolObject* pool = poolInfo->pool;
      AvmAssert(pool != NULL);
      if (pool == traits->pool) {
        for (int j = 0, end = (int)pool->classCount(); j < end; ++j) {
          if (traits == pool->getClassTraits(j)->itraits) {
            llvm::Value* res = loadInterfaceTraitsFromPool(getPoolLLVMValue(poolInfo), j);
            res->setName(module.traitsName(traits) + "_interface");
            return res;
          }
        }
      }
    }
    AvmAssert(!"Interface not found");
    return 0;
  }
  
  llvm::Value* LLVMEmitter::getPoolLLVMValue(PoolInfo* poolInfo)
  {
    std::string name = poolInfo->infoName + aotInfoSuffix;
    llvm::GlobalVariable *aotInfoVar = llvm::dyn_cast_or_null<llvm::GlobalVariable>(module.getNamedValue(name));
    if (!aotInfoVar) {
      aotInfoVar = new llvm::GlobalVariable(module,
                                            module.aotInfoTy, /*isConst*/ true, llvm::GlobalValue::ExternalLinkage,
                                            0, name);
    }
    llvm::Value* res = callIns(STUBINFO(llGetPoolSameWorker), 2, poolAddr, aotInfoVar);
    return res;
  }
  
  llvm::Value* LLVMEmitter::getFinddefTableAddress()
  {
      llvm::Value* scope = loadMember(env_param, module.methodenv_scope_member);
      llvm::Value* abcEnv = loadMember(scope, module.scope_abcenv_member);
      llvm::Value* finddefTbl = loadMember(abcEnv, module.abcenv_finddeftbl_member);
      return createMemberGEP(finddefTbl, module.finddeftbl_elements_member);
  }

} // end namespace compile_abc

#endif // VMCFG_HALFMOON
