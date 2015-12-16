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
// Captures information that spans the compilation of a single module.
//

#ifndef __compile_abc_llvm_module__
#define __compile_abc_llvm_module__

#include "llvm/Config/llvm-config.h"
#include "llvm/Config/config.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/PassManager.h"

#include "halfmoon/hm-main.h"
#include "structinfo.h"

#include <map>
#include <vector>

namespace compile_abc
{
using namespace avmplus;
using namespace halfmoon;
    
class PoolInfo;
class LLVMEmitter;
struct StructInfo;
struct FieldInfo;
class CompilerCore;

class LLVMModuleBase: private llvm::LLVMContext, public llvm::Module
{
    public:
    std::string targetTriple;
    llvm::TargetMachine* targetMachineForLayout;
    llvm::Type* ptrSizedIntTy;
    llvm::Type *functionTy, *functionPtrTy;
        LLVMModuleBase(const llvm::StringRef name,const std::string& targetTriple,int splitIndex = 0);
        ~LLVMModuleBase();
        // emit code for module
    static void* operator new (size_t size)
    {
        typedef double AlignType;
        size_t alignSize = (size+sizeof(AlignType)-1)/sizeof(AlignType);
        void* mem = new AlignType[alignSize];
        memset(mem, 0, size);
        return mem;
    }
        bool emit();
protected:
    int splitIndex;
    bool optimizeModule;
    unsigned int functionCount;
    
};

class LLVMModule: public LLVMModuleBase
{
public:
    LLVMModule(const llvm::StringRef name, CompilerCore* core, const std::string& targetTriple,int splitIndex = 0);
    ~LLVMModule();
    
    void disableOptimizeModule();
    unsigned int getFunctionCount();
    void incrementFunctionCount();
    // Too many fields to initialize individually
    static void* operator new (size_t size)
    {
        typedef double AlignType;
        size_t alignSize = (size+sizeof(AlignType)-1)/sizeof(AlignType);
        void* mem = new AlignType[alignSize];
        memset(mem, 0, size);
        return mem;
    }
    
    // following LLVM convention, returns true if it fails
    bool initializeDefs(llvm::raw_ostream &err);
    
    CompilerCore* core;

    StructInfoMap structInfos;
    StructInfo* findStruct(const std::string& name);

    StructInfo* getStructInfo(llvm::raw_ostream &err, const std::string& name, llvm::Type** typeP, llvm::PointerType** ptrTypeP, int* errCntp);
    FieldInfo* getFieldInfo(llvm::raw_ostream &err, StructInfo* s, const std::string& name, int* errCntp);
    
    // TODO: This map assumes that Traits lifetimes exceed the lifetime of a compile (the holder is not a GCRoot).
    // If this turns out to be wrong, we'll keep a separate table of Traits in the CompilerCore just to pin them down.
    std::map<Traits*, StructInfo*> traitsToStructInfo;
    StructInfo* getSlotLayout(Traits* t);
    
    //
    // Field information. See initializeFieldInfos()
    //
    llvm::Type *atomTy;
    llvm::PointerType *atomPtrTy;
    llvm::Type *argTy, *argPtrTy;
    
    llvm::Type *avmCoreTy;
    llvm::PointerType *avmCorePtrTy;
    FieldInfo* avmcore_methodframe_member;
    FieldInfo* avmcore_exceptionAddr_member;
    FieldInfo* avmcore_gc_member;
    
    StructInfo* aotInfoStruct;
    llvm::Type *aotInfoTy;
    llvm::PointerType *aotInfoPtrTy;
    FieldInfo* aotInfo_origABCSHA1_member;
    FieldInfo* aotInfo_abcbytes_member;
    FieldInfo* aotInfo_nABCBytes_member;
    FieldInfo* aotInfo_methodDebugInfos_member;
    FieldInfo* aotInfo_abcMethods_member;
    FieldInfo* aotInfo_nABCMethods_member;
    FieldInfo* aotInfo_methodFlagsArr_member;
    FieldInfo* aotInfo_activationInfo_member;
    
    StructInfo* aotExceptionDescStruct;
    llvm::Type *aotExceptionDescTy;
    llvm::PointerType *aotExceptionDescPtrTy;
    FieldInfo* aotExceptionDesc_from_member;
    FieldInfo* aotExceptionDesc_to_member;
    FieldInfo* aotExceptionDesc_nameIndex_member;
    FieldInfo* aotExceptionDesc_typeIndexU30_member;

    StructInfo* methodDebugInfoStruct;
    llvm::Type *methodDebugInfoTy;
    llvm::PointerType *methodDebugInfoPtrTy;
    FieldInfo* methodDebugInfo_local_count_member;
    FieldInfo* methodDebugInfo_scope_count_member;
    FieldInfo* methodDebugInfo_file_name_member;
    FieldInfo* methodDebugInfo_local_names_member;
    FieldInfo* methodDebugInfo_line_count_member;
    FieldInfo* methodDebugInfo_lines_member;

    StructInfo* aotActivationInfoStruct;
    llvm::Type *aotActivationInfoTy;
    llvm::PointerType *aotActivationInfoPtrTy;
    FieldInfo* aotActivationInfo_initMethodId_member;
    FieldInfo* aotActivationInfo_initHandler_member;

    StructInfo* exceptionFrameStruct;
    llvm::Type *exceptionFrameTy;
    llvm::PointerType *exceptionFramePtrTy;
    FieldInfo* exceptionFrame_jmpbuf_member;
    
    llvm::Type *exceptionTy;
    llvm::PointerType *exceptionPtrTy;
    FieldInfo* exception_atom_member;
    
    llvm::Type *stringTy;
    llvm::PointerType *stringPtrTy;
    
    llvm::Type *methodFrameTy;
    llvm::PointerType *methodFramePtrTy;
    FieldInfo* methodframe_next_member;
    FieldInfo* methodframe_env_member;
   
    llvm::Type *callStackNodeTy;
    llvm::PointerType *callStackNodePtrTy;
    
    llvm::Type *methodInfoNativeTy;
    llvm::PointerType *methodInfoNativePtrTy;
    FieldInfo* methodinfonative_handler_member;
    
    llvm::Type *methodInfoTy;
    llvm::PointerType *methodInfoPtrTy;
    FieldInfo* methodinfo_pool_member;
    FieldInfo* methodinfo_native_member;
    
    llvm::Type *methodInfoListTy;
    llvm::PointerType *methodInfoListPtrTy;
    FieldInfo* methodInfoList_entries_member;

    llvm::Type *methodInfoGCListTy;
    llvm::PointerType *methodInfoGCListPtrTy;
    FieldInfo* methodInfoGCList_m_list_member;
    
    llvm::Type *namespaceListTy;
    llvm::PointerType *namespaceListPtrTy;
    FieldInfo* namespaceList_entries_member;
    
    llvm::Type *namespaceRCListTy;
    llvm::PointerType *namespaceRCListPtrTy;
    FieldInfo* namespaceRCList_m_list_member;
    
    llvm::Type *traitsTracedListTy;
    llvm::PointerType *traitsTracedListPtrTy;
    FieldInfo* traitsTracedList_entries_member;
    
    llvm::Type *traitsListTy;
    llvm::PointerType *traitsListPtrTy;
    FieldInfo* traitsList_m_list_member;

    llvm::Type *poolObjectTy;
    llvm::PointerType *poolObjectPtrTy;
    FieldInfo* poolobject_core_member;
    FieldInfo* poolobject_escHeapMultiname_member;
    FieldInfo* poolobject_classes_member;
    FieldInfo* poolobject_scripts_member;
    FieldInfo* poolobject_namespaces_member;
    FieldInfo* poolobject_methods_member;
    
    llvm::Type *multinameTy;
    llvm::PointerType *multinametPtrTy;
    
    llvm::Type *escHeapMultinameTy;
    llvm::PointerType *escHeapMultinamePtrTy;
    FieldInfo* escHeapMultiname_elements_member;
    
    llvm::Type *vtableTy;
    llvm::PointerType *vtablePtrTy;
    FieldInfo* vtable_methods_member;
    FieldInfo* vtable_init_member;
    FieldInfo* vtable_base_member;
    FieldInfo* vtable_ivtable_member;
    FieldInfo* vtable_traits_member;
    FieldInfo* vtable_createinstanceproc_member;
    
    llvm::Type *traitsTy;
    llvm::PointerType *traitsPtrTy;
    FieldInfo* traits_itraits_member;
    
    llvm::Type *methodEnvTy;
    llvm::PointerType *methodEnvPtrTy;
    FieldInfo* methodenv_method_member;
    FieldInfo* methodenv_impl_member;
    FieldInfo* methodenv_scope_member;
    
    StructInfo* scriptObjectStruct;
    llvm::Type *scriptObjectTy;
    llvm::PointerType *scriptObjectPtrTy;
    FieldInfo* scriptobject_vtable_member;
    
    llvm::Type *scopeChainTy;
    llvm::PointerType *scopeChainPtrTy;
    FieldInfo* scope_vtable_member;
    FieldInfo* scope_scopes_member;
    FieldInfo* scope_abcenv_member;

    llvm::Type *abcEnvTy;
    llvm::PointerType *abcEnvTPtrTy;
    FieldInfo* abcenv_finddeftbl_member;
  
    llvm::Type *finddefTableTy;
    llvm::PointerType *finddefTablePtrTy;
    FieldInfo* finddeftbl_elements_member;

    llvm::PointerType* genericPtrTy;
    llvm::PointerType* arrayObjectPtrTy;
    llvm::PointerType* intVectorObjectPtrTy;
    llvm::PointerType* uIntVectorObjectPtrTy;
    llvm::PointerType* doubleVectorObjectPtrTy;
    llvm::PointerType* namespacePtrTy;
    llvm::PointerType* multinamePtrTy;
    llvm::PointerType* classClosurePtrTy;
    
    llvm::Type* fn_acalli;
    llvm::Type* fn_ocalli;
    llvm::Type* fn_scalli;
    llvm::Type* fn_ncalli;
    llvm::Type* fn_icalli;
    llvm::Type* fn_dcalli;
    
    struct StubInfo
    {
        const char* name;
        const char* mangle;
        const char* argDesc;
        bool pure;
        int fixedArgCount;
        uint32_t count_args() const;
        bool isIndirect() const { return mangle == 0; }
    };
    llvm::FunctionType* llvmTypeForStubInfo(const StubInfo* ci);
        
    llvm::Type* llvmType(const char* typeDescriptor, bool noAssert = false);
    llvm::FunctionType* llvmFunctionType(const char* functionTypeDescriptor);
    llvm::FunctionType* getFunctionTy(MethodInfo* info);

    llvm::Type* llvmType(ModelKind modelKind);
    llvm::Type* llvmType(Traits* traits);
    llvm::Type* llvmType(const Type* type);
    llvm::Type* llvmType(Def* def) { return llvmType(type(def)); }
    llvm::Type* llvmType(Def& def) { return llvmType(type(def)); }
    
    std::string traitsName(Traits* t);
    llvm::Value* getTraitsValue(LLVMEmitter* emitter, Traits* t);
    
    bool printLLIR;
    PoolInfo* poolInfo;
    
private:
    int getNameSpaceIndex(PoolObject* pool, Namespace* ns);
    
    // following LLVM convention, these return true if they fail
    bool computeStructLayout(StructInfo& structInfo, llvm::raw_ostream &err);
    unsigned getTypeSize(llvm::Type* type)
    {
        // NOTE: Post 3.1 llvm docs suggest using llvm::DataLayout
        return targetMachineForLayout->getDataLayout()->getTypeAllocSize(type);
    }

    bool initializeFieldInfos(llvm::raw_ostream &err);
    llvm::Type* parseLlvmType(const char*& cursor, bool noAssert = false);

};
    
class ConstStructInitializer
{
public:
    ConstStructInitializer(StructInfo* structInfo)
    : structInfo(structInfo)
    {
        llvm::StructType* stTy = structInfo->type;
        int nElts = stTy->getNumElements();
        inits.resize(nElts);
        for (int i = 0; i < nElts; ++i)
            inits[i] = llvm::Constant::getNullValue(stTy->getTypeAtIndex(i));
    }
    
    void init(FieldInfo* fld, llvm::Constant* val)
    {
        int ix = fld->memberIx;
        AvmAssert(fld->structInfo == structInfo);
        AvmAssert(structInfo->type->getTypeAtIndex(ix) == val->getType());
        inits[ix] = val;
    }
    
    llvm::Constant* create()
    {
        llvm::Constant* val = llvm::ConstantStruct::get(structInfo->type, inits);
        return val;
    }
    
private:
    const StructInfo* structInfo;
    std::vector<llvm::Constant*> inits;
};

}
#endif /* __compile_abc_llvm_module__ */

