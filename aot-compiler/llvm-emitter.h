/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
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
 * Portions created by the Initial Developer are Copyright (C) 2011
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

#ifndef __compile_abc_llvm_emitter__
#define __compile_abc_llvm_emitter__

#include <stack>
#include "llvm/Config/llvm-config.h"
#include "llvm/Config/config.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/PassManager.h"

#include "halfmoon/hm-main.h"
#include "llvm-module.h"

namespace compile_abc
{
using namespace avmplus;
using namespace halfmoon;
    
class CompilerCore;

#ifdef VMCFG_FLOAT
#error "VMCFG_FLOAT not yet supported by LLVM emitter"
#endif

class LLVMEmitter: public llvm::IRBuilder<>, public KindAdapter<LLVMEmitter, void>
{
public:
    LLVMEmitter(MethodInfo* method, InstrGraph* ir);
    ~LLVMEmitter();

    /// Emit all the LLVM IR.
    ///
    void emit();
    
    /// Emit as VerifyError stub
    void emitAsVerifyErrorStub();
    
public:
    // Implement KindAdapter
    void do_default(Instr*);
    void do_start(StartInstr*);
    void do_const(ConstantExpr*);
    void do_loadenv(BinaryExpr*);
    void do_loadinitenv(UnaryExpr*);
    void do_loadsuperinitenv(UnaryExpr*);
    void do_callmethod(CallStmt2*);
    void do_return(StopInstr*);
    void do_arm(ArmInstr*);
    void do_label(LabelInstr*);
    void do_goto(GotoInstr*);
    void do_if(IfInstr*);
    void do_setslot(CallStmt2*);
    void do_addd(BinaryExpr* i);
    void do_subd(BinaryExpr* i);
    void do_muld(BinaryExpr* i);
    void do_modulo(BinaryExpr*);
    void do_divd(BinaryExpr* i);
    void do_lessthan(BinaryExpr*);
    void do_greaterthan(BinaryExpr*);
    void do_abc_add(BinaryStmt*);
    void do_addi(BinaryExpr* i);
    void do_subi(BinaryExpr* i);
    void do_muli(BinaryExpr* i);
    void do_andi(BinaryExpr* i);
    void do_ori(BinaryExpr* i);
    void do_xori(BinaryExpr* i);
    void do_lshi(BinaryExpr* i);
    void do_rshi(BinaryExpr* i);
    void do_rshui(BinaryExpr* i);
    void do_cast(BinaryStmt*);
    // TODO: optimize these
    //void do_abc_getprop(CallStmt2*);
    //void do_abc_setprop(CallStmt2*);
    //void do_abc_callprop(CallStmt2*);
    //void do_loadenv_interface(BinaryExpr*);
    void do_callinterface(CallStmt2*);
    void do_newclass(NaryStmt2* instr);
    void do_newfunction(NaryStmt1* instr);
    void do_newactivation(UnaryStmt* insr);
    void do_getslot(CallStmt2*);
    void do_negd(UnaryExpr* i);
    void do_noti(UnaryExpr* i);
    void do_not(UnaryExpr*);
    void do_cknull(UnaryStmt*);
    void do_cknullobject(UnaryStmt*);
    void do_switch(SwitchInstr*);
    void do_eqi(BinaryExpr* i);
    void do_lti(BinaryExpr* i);
    void do_lei(BinaryExpr* i);
    void do_gti(BinaryExpr* i);
    void do_gei(BinaryExpr* i);
    void do_eqd(BinaryExpr* i);
    void do_ltd(BinaryExpr* i);
    void do_led(BinaryExpr* i);
    void do_gtd(BinaryExpr* i);
    void do_ged(BinaryExpr* i);
    void do_equi(BinaryExpr* i);
    void do_ltui(BinaryExpr* i);
    void do_leui(BinaryExpr* i);
    void do_gtui(BinaryExpr* i);
    void do_geui(BinaryExpr* i);
    void do_eqb(BinaryExpr* i);
    void do_eqp(BinaryExpr* i);
    void do_i2d(UnaryExpr* i);
    void do_d2i(UnaryExpr* i);
    void do_doubletoint32(UnaryExpr*);
    void do_i2u(UnaryExpr*);
    void do_u2i(UnaryExpr*);
    void do_u2d(UnaryExpr* i);
    void do_catchblock(CatchBlockInstr* instr);
    void do_newstate(ConstantExpr*);
    void do_setlocal(SetlocalInstr*);
    void do_getlocal(GetlocalStmt* i);
    void do_safepoint(SafepointInstr*);
    void do_int2atom(UnaryExpr*);
    void do_double2atom(UnaryExpr*);
    void do_atom2scriptobject(UnaryExpr*);
    void do_scriptobject2atom(UnaryExpr* i);
    void do_string2atom(UnaryExpr* i);
    void do_ns2atom(UnaryExpr* i);
    void do_bool2atom(UnaryExpr* i);
    void do_getouterscope(BinaryExpr* i);
    void do_abc_hasnext2(Hasnext2Stmt*);
    void do_cktimeout(UnaryStmt*);
    void do_newinstance(UnaryExpr*);
    void do_abc_finddef(BinaryStmt*);

    //Function to update Parametrized traits variable
    llvm::Value* GetVectorTraitsValue(Traits* t);
    llvm::Value* generateGetClassTraitsCall(Traits* traits);
    llvm::Value* generateGetScriptTraitsCall(Traits* traits);
    llvm::Value* generateGetCatchTraitsCall(Traits* traits);
    llvm::Value* getInterfaceTraitsValue(Traits* traits);
    llvm::Value* getActivationTraitsForMethodInfo(MethodInfo* methodInfo);
private:
    /// Emit LLVM IR for one instruction.
    ///
    void emit(Instr*);
    
    /// Finish up
    void finish();
    
    llvm::Value* castPtrToInt(llvm::Value* ptr, const llvm::Twine& name = "") {
        AvmAssert(ptr->getType()->isPointerTy());
        llvm::Type* toType = module.ptrSizedIntTy;
        // TODO (stan): reenable this AvmAssert when we're really cross-compiling.
        //     currently we're still using some jit paths and the host is 64 bits.
        // AvmAssert(ptr->getType()->canLosslesslyBitCastTo(toType));
        return CreatePtrToInt(ptr, toType, name.isTriviallyEmpty() ? ptr->getName() : name);
    }
    
    llvm::Value* castIntToPtr(llvm::Value* val, const llvm::Twine& name = "") {
        AvmAssert(val->getType()->isIntegerTy());
        llvm::Type* toType = module.genericPtrTy;
        // TODO (stan): reenable this AvmAssert when we're really cross-compiling.
        //     currently we're still using some jit paths and the host is 64 bits.
        // AvmAssert(val->getType()->canLosslesslyBitCastTo(toType));
        return CreateIntToPtr(val, toType, name.isTriviallyEmpty() ? val->getName() : name);
    }
    
    llvm::Value* offsetGenericPointer(llvm::Value* ptr, uint32_t offset) {
        AvmAssert(ptr->getType()->isPointerTy());
        // TODO: we should be using typed pointers, typically
        //   (and if it happens to be one, let's smack it down to generic anyway, "temporarily")
        if (ptr->getType() != module.genericPtrTy)
            ptr = CreateBitCast(ptr, module.genericPtrTy);
        AvmAssert(ptr->getType() == module.genericPtrTy);
        return CreateConstGEP1_32(ptr, offset);
    }
    
    llvm::Value* offsetGenericPointer(llvm::Value* ptr, uint32_t offset, llvm::Type* t) {
        llvm::Value* generic_ptr = offsetGenericPointer(ptr, offset);
        llvm::Type* ptr_type = llvm::PointerType::getUnqual(t);
        return CreateBitCast(generic_ptr, ptr_type);
    }
    
    llvm::Value* applyTag(llvm::Value* intVal, int tag, bool shift, const llvm::Twine& name) {
        if (intVal->getType() == getInt1Ty() || intVal->getType() == getInt32Ty()) // If we have a boolean, extend to an atom
            intVal = CreateZExt(intVal, module.ptrSizedIntTy);
        if (shift)
            intVal = CreateShl(intVal, getPtrSizeInt(3));
        const char* prefix = "box_";
        switch (tag) {
            case kObjectType:       prefix = "obox_"; break;
            case kStringType:       prefix = "sbox_"; break;
            case kNamespaceType:    prefix = "nbox_"; break;
            case kSpecialBibopType: prefix = "xbox_"; break;
            case kBooleanType:      prefix = "bbox_"; break;
            case kIntptrType:       prefix = "ibox_"; break;
            case kDoubleType:       prefix = "dbox_"; break;
        }
        llvm::Twine nm(name);
        nm.concat(prefix);
        return CreateAdd(intVal,getPtrSizeInt(tag),nm);
    }
    
    llvm::Value* applyTagToInt(llvm::Value* intVal, int tag, bool shift = true) {
        return applyTag(intVal, tag, shift, intVal->getName());
    }
    
    llvm::Value* applyTagToPointer(llvm::Value* ptr, int tag) {
        llvm::Value* intVal = CreatePtrToInt(ptr, module.ptrSizedIntTy);
        return applyTag(intVal, tag, false, ptr->getName());
    }
    
    llvm::Value* removeTagReturningPointer(llvm::Value* val, llvm::Type* type) {
        AvmAssert(val->getType()->isIntegerTy());
        llvm::Value* masked = CreateAnd(val, llvm::ConstantInt::get(val->getType(), kAtomPtrMask));
        llvm::Value* ret = CreateIntToPtr(masked, type);
        const char* suffix = "_unbox";
        if (val->getName().endswith("_"))
            ++suffix;
        ret->setName(val->getName() + suffix);
        return ret;
    }
    llvm::Value* getPtrSizeInt(uintptr_t val) {
#ifdef AVMPLUS_64BIT 
        return getInt64(val);
#else
        return getInt32(val);
#endif
    }
    llvm::Value* getAtomConstant(Atom val);
    llvm::Value* getStringConstant(String* val);
    llvm::Value* getStringConstant(Atom val) { return getStringConstant(AvmCore::isString(val)? AvmCore::atomToString(val): NULL); }
    llvm::Value* getNamespaceConstant(Namespace* val);
    llvm::Value* getNamespaceConstant(Atom val) { return getNamespaceConstant(AvmCore::atomToNamespace(val)); }
    llvm::Value* getMultinameConstant(const Multiname* val);
    llvm::Value* getDoubleConstant(double val) { return llvm::ConstantFP::get(Context, llvm::APFloat(val)); }
    llvm::Value* getDoubleConstant(Atom val) { return getDoubleConstant(AvmCore::atomToDouble(val)); }
                                                                        
    llvm::Value* getMethodInfoValue(MethodInfo* info);
    
    llvm::Instruction* getFirstNonPHI(llvm::BasicBlock* bb)
    {
        // Can't use BasicBlock::getFirstNonPHI() since that assumes that the BasicBlock already
        // has a terminator. And this one doesn't since it is still being constructed.
        // That's evidently a bug since the docs say it returns null in that case.
        for (llvm::BasicBlock::iterator i = bb->begin(); i != bb->end(); ++i)
            if (!llvm::isa<llvm::PHINode>(i))
                return &*i;
        return NULL;
    }    

    /// Generate simple LLVM IR for a binary instruction that maps directly
    /// to a single Halfmoon binary instruction.
    void doModuloInstr(BinaryExpr*);
    llvm::Value* atomToScriptObject(llvm::Value* object);
    void do_stub(Instr*, const LLVMModule::StubInfo*);
    void doTagPointer(UnaryExpr* instr, Atom tag);

    // helpers to emit canned hunks of LLVM IR
    llvm::Value* emitLoadVTable(const Use& object);
    llvm::Value* emitLoadMethodEnv(llvm::Value* vtable, int disp_id);
    void emitAtomArgs(const Use* args, int argc);
    llvm::Value* emitConst(const Type* t);
    llvm::Value* emitCompareLess(llvm::Value* lhs_in, llvm::Value* rhs_in);
    llvm::Value* emitJump(llvm::Value* target = 0);
    llvm::Value* emitStore(const Use& value, const Type* constraint, llvm::Value* ptr,
                           int32_t offset, const llvm::Twine& name = "");

    llvm::BasicBlock* emitNpeHandler();
    llvm::BasicBlock* emitUpeHandler();
    llvm::BasicBlock* emitBailout();
    llvm::Value* emitLabel(BlockStartInstr*);
    void emitHelperCall2(UnaryExpr*, const LLVMModule::StubInfo* call);
    void emitBegin();

    bool canUpcastTo(llvm::Type* from, llvm::Type* to);
    bool canUpcastTo(llvm::Value* val, llvm::Type* to) {
        return canUpcastTo(val->getType(), to);
    }
    llvm::Value* upcastTo(llvm::Value* val, llvm::Type* to);
    bool permissibleDowncast(llvm::Type* from, llvm::Type* to);
    llvm::Value* toAtom(const Use& in);

    // other helpers
    void allocateTables();
    void sortBlocks();
    
    llvm::Value* set_def_ins(Def* d, llvm::Value* ins);
    llvm::Value* def_ins(const Def*);
    llvm::Value* def_ins(const Use& u) { return def_ins(def(u)); }
    bool has_def_ins(const Def*);
    llvm::BasicBlock* set_block(BlockStartInstr*, llvm::BasicBlock* ins);
    llvm::BasicBlock* block(BlockStartInstr*);

    typedef HashMap<Instr*, Seq<Instr*>*> LoopLiveMap;

    MethodInfo* method;
    PoolObject* pool;
    CompilerCore *core;
    const LLVMModule::StubInfo* llvm_stub_table;
    LLVMModule& module;
    MethodSignaturep signature; // Signature of method being compiled.
    InstrGraph* ir;
    Allocator alloc;

    llvm::LoadInst* coreAddr;
    llvm::LoadInst* gcAddr;
    llvm::LoadInst* methodInfoAddr;
    llvm::LoadInst* poolAddr;

    llvm::Function* currentFunction;
    llvm::BasicBlock* entryBlock;
    llvm::BasicBlock* epilogBlock;
    llvm::PHINode* returnPhi;
    llvm::Value** def_ins_; // Array of LLVM instructions, one per def.
    llvm::BasicBlock** idToBlock_; // Array of LLVM instructions, one per instr
    llvm::Argument *env_param, *argc_param, *ap_param;
    llvm::Value *method_frame_;
    llvm::AllocaInst* params_; // Array for parameter lists
    int maxAtomParams_; // max number of atomParams
    int maxAvmParamSize_; // max size of avmParams
    BlockStartInstr** blocks_; // Array of blocks in sorted order.
    int num_blocks_;
    int current_block_; // the blocks_[] index of the current block.
    int max_argc_;
    llvm::BasicBlock* npe_block; // label to jump to for null pointer exceptions.
    llvm::BasicBlock* upe_block; // label to jump to for undefined pointer exceptions.
    llvm::PHINode* upe_phi;   // value that might be undefined or null
    bool have_catchblocks_;
    llvm::AllocaInst* safepoint_space_; // space to store safepoint data
    llvm::AllocaInst* call_stack_node_; // debugger call stack node
    llvm::AllocaInst* save_eip_; // space to store abc pc
    int saved_eip_;
    llvm::AllocaInst* exceptionFrame_;
    llvm::AllocaInst* exceptionAtom_;
    llvm::BasicBlock* catch_block_;
    std::map<int32_t, CatchBlockInstr*> catch_blocks_;   // targets to reachable catch blocks
    const bool enable_verbose_;
    std::stack<llvm::BasicBlock*> basic_blocks;
    bool isWindowsTriple;
    
    //Bug 3909398: [iOS64]: [Graphics]: [RWL]: RealWorld apps "Solitaire 3 and "Meteor Storm 2" from Graphic Suite Crashing on launch.(working fine on 32 Bit device).
    //Reason: hasnext is called too many times from flare.loaders::ColladaLoader/start, App going out of stack due to allocating temp variables that many times
    //Solution: Instead of allocating space for each hasNext call, allocating at the start of fn.It will be removed if these variables are not used.
    llvm::AllocaInst* hasnextAtom_;
    llvm::AllocaInst* hasnextCounter_;
    

    // TODO: Use AddrSpaces in order to improve alias analysis

    llvm::Value* ldp(llvm::Value* ptr, int32_t d);
    llvm::Value* sti(llvm::Value* val, llvm::Value* ptr, int32_t d);
    llvm::Value* addi(llvm::Value* a, int32_t b);
    llvm::Value* createMemberGEP(llvm::Value* ptr, FieldInfo* member, const llvm::Twine &name="");
    void storeVPC(int vpc, bool force = false);

    llvm::CallInst* callIns(const LLVMModule::StubInfo *ci, uint32_t argc, ...);
    llvm::CallInst* acallIns(const LLVMModule::StubInfo *ci, uint32_t argc, llvm::Value** args);
    bool needsMethodFrame(const LLVMModule::StubInfo *stubinfo);
    
    llvm::BasicBlock* splitEdgeIfNecessary(llvm::BasicBlock* fromBlock, llvm::BasicBlock* toBlock);
    llvm::PHINode* insertPhi(llvm::BasicBlock* bb, llvm::Type *type, unsigned numReservedValues, const llvm::Twine& name = "");
    void emitExceptionHandling();
    void emitSafepointSetup();
    void emitDebugEnter();
    
    void createPhiNodes(LabelInstr* instr);
    void addPhiEdges(GotoInstr* instr);
    void addPhiEdges(CondInstr* instr);
    void createPhiNodes(ArmInstr* instr);
    bool neverReturns(const LLVMModule::StubInfo* call);
    llvm::Value* downcast_obj(llvm::Value* atom, llvm::Value* env, Traits* t);
    llvm::Value* coerceArg(llvm::Value* val, llvm::Type* to);
    llvm::Value* nativeToAtom(llvm::Value* native, Traits* t);

    llvm::BasicBlock* getBlock(BlockStartInstr* bsi);
    llvm::CallInst* emitCall(MethodInfo* callee, llvm::Value* func, llvm::Value* callee_env, CallStmt2* call);
    llvm::Value* getMethodFrame();
    llvm::Instruction* getNearestInsertionInsertPointForAllUses(llvm::DominatorTree& dt, llvm::Value* val);
    void removeIfNotUsedOtherwiseMoveNearestToFirstUse(llvm::DominatorTree& dt, llvm::Instruction* val);
    llvm::Constant* makeU32Constant(unsigned n, unsigned size = 0);
    void InsertPrintf(const char *msg);
  
    llvm::Value* loadInterfaceTraitsFromPool(llvm::Value* pool, int index);
    llvm::Value* loadClassTraitsFromPool(llvm::Value* pool, int index);
    llvm::Value* loadScriptTraitsFromPool(llvm::Value* pool, int index);
    llvm::LoadInst* loadMember(llvm::Value* ptr, FieldInfo* member, const llvm::Twine &name="");
    llvm::Value* storeMember(llvm::Value* val, llvm::Value* ptr, FieldInfo* member);
    llvm::Value* getPoolLLVMValue(PoolInfo* poolInfo);
  
    //Get Multiname's index in Pool
    int getMultinameIndexInPool(const Multiname* mn);
    llvm::Value* getFinddefTableAddress();
    
    class PushBuilder
    {
    public:
        PushBuilder(llvm::IRBuilderBase* b, llvm::BasicBlock* bb)
        : builder(b), where(b->saveIP())
        {
            builder->SetInsertPoint(bb);
        }
        PushBuilder(llvm::IRBuilderBase* b, llvm::Instruction* ip)
        : builder(b), where(b->saveIP())
        {
            builder->SetInsertPoint(ip);
        }
        ~PushBuilder()
        {
            builder->restoreIP(where);
        }
    private:
        llvm::IRBuilderBase* builder;
        llvm::IRBuilderBase::InsertPoint where;
    };

private:
    bool haveStub(InstrKind);
};
    
} // namespace compile_abc
#endif /* __compile_abc_llvm_emitter__ */

