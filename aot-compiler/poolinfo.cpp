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
 * Portions created by the Initial Developer are Copyright (C) 2004-2006
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

#include <stdio.h>
#include "avmplus.h"
#include "poolinfo.h"
#include "compileabc.h"
#include <sstream>

using namespace avmplus;
using namespace base; // SHA1 stuff in this namespace

namespace compile_abc
{
    
void PoolInfo::setAbcData(const uint8_t* bytes, int size) {
    SHA1HashBytes(bytes, size, sha1hash);
    totalABCSize = size;
    abcBytes = new uint8_t[size];
    abcSize = copyAbcSkippingMethodBodies(bytes, abcBytes, size);
}

void PoolInfo::appendVerifierResult(AbcEnv* abc_env_param, const compile_abc::MethodVerifyInfo& verifierInfo)
{
    verifyInfos.push_back(verifierInfo);
    AvmAssert(abc_env != NULL);
    AvmAssert(abc_env == abc_env_param);
    AvmAssert(pool == abc_env_param->pool());
    AvmAssert(pool->poolInfo == this);
}

void PoolInfo::connect(LLVMModule *modulep)
{
    AvmAssert(this->modulep == 0);
    AvmAssert(modulep->poolInfo == 0);
    this->modulep = modulep;
    modulep->poolInfo = this;
    LLVMModule& module = *modulep;
    
    llvm::Type* traitsPtrArrayTy = llvm::ArrayType::get(module.traitsPtrTy, pool->methodCount());
    activationTraits = new llvm::GlobalVariable(module, traitsPtrArrayTy,
                                                /*isConst*/false,llvm::GlobalValue::ExternalLinkage, 0, infoName+"_activationTraits");
    traitsPtrArrayTy = llvm::ArrayType::get(module.traitsPtrTy, pool->scriptCount());
    scriptTraits = new llvm::GlobalVariable(module, traitsPtrArrayTy,
        /*isConst*/false,llvm::GlobalValue::ExternalLinkage, 0, infoName+"_scriptTraits");
}

void PoolInfo::disconnect()
{
    AvmAssert(modulep->poolInfo == this);
    modulep->poolInfo = 0;
    modulep = 0;
}

void PoolInfo::init(PoolObject* thePool)
{
    if (pool != 0) {
        AvmAssert(pool == thePool);
        return;
    }
    pool = thePool;
    pool->poolInfo = this;
 
}

void PoolInfo::addMethod(MethodInfo* method, llvm::Function* func)
{
    LLVMModule& module = *modulep;
    llvm::Type* int32Ty = llvm::Type::getInt32Ty(module.getContext());
    llvm::Constant* fpCasted = llvm::ConstantExpr::getBitCast(func, module.functionPtrTy);
    llvm::Constant* methodFlagsConst  = llvm::ConstantInt::get(int32Ty, method->needArgsArrInMethodSig());
    int method_id = method->method_id();
    if (method_id == -1) {
        // This is a special activation init.
        Traits* declarer = method->declaringTraits();
        AvmAssert(declarer != 0);
        for (int i = 0, end = (int)pool->methodCount(); i < end; ++i) {
            MethodInfo* mi = pool->getMethodInfo(i);
            if (mi->activationTraits() == declarer) {
                // found the method whose activation traits are the declarer of the init.
                // So this is the method for the activation whose init we're dealing with.
                int containing_method_id = mi->method_id();
                AvmAssert(containing_method_id < (int)activationInits.size());
                activationInits[containing_method_id] = fpCasted;
                activationInitsForMethod[containing_method_id] = method_id;
                return;
            }
        }
        AvmAssert(!"can't find method for activation traits");
        return;
    }
    AvmAssert(method_id < (int)functions.size());
    functions[method_id] = fpCasted;
    methodFlagsArr[method_id] = methodFlagsConst;
    
}

llvm::GlobalVariable* PoolInfo::makeVariable(llvm::Constant* init, bool isConst, const llvm::Twine& name)
{
    llvm::GlobalValue::LinkageTypes linkage = llvm::GlobalValue::ExternalLinkage;
    llvm::GlobalVariable* gvar = 0;
    if (name.isTriviallyEmpty())
        linkage = llvm::GlobalValue::InternalLinkage;
    else {
        gvar = llvm::dyn_cast_or_null<llvm::GlobalVariable>(modulep->getNamedValue(name.str()));
    }
    if (gvar) {
        gvar->setInitializer(init);
    } else {
        gvar = new llvm::GlobalVariable(*modulep,
        init->getType(), isConst, linkage, init, name);
    }
    return gvar;
}
    
llvm::Constant* PoolInfo::const_gep(llvm::Constant* in, int i, int j)
{
    llvm::Type* int32Ty = llvm::Type::getInt32Ty(in->getContext());
    llvm::Constant* indices[] = {
        llvm::ConstantInt::get(int32Ty, i),
        llvm::ConstantInt::get(int32Ty, j) };
    llvm::Constant* res = llvm::ConstantExpr::getGetElementPtr(in, indices);
    return res;
}

#ifdef DEBUGGER
void PoolInfo::populateAllMethodsDebugInfos()
{
  // walk all methods
  llvm::Constant *nullmethodDebugInfo = llvm::Constant::getNullValue(modulep->methodDebugInfoTy);
  methodDebugInfos.resize(pool->methodCount(), nullmethodDebugInfo);
  for(uint32_t i=0, n = pool->methodCount(); i<n; i++)
  {
    MethodInfo* f = pool->getMethodInfo(i);
    if (f->hasMethodBody())
    {
      // yes there is code for this method
      if (f->abc_body_pos())
      {
        // if body_pos is null we havent got the body yet or
        // this is an interface method
        methodDebugInfos[i] = collectMethodDebugInfo(f);
      }
    }
  }
}

/**
 * Scans the bytecode and collect source level information to
 * This code is taken from Debugger::scanCode
 */
llvm::Constant* PoolInfo::collectMethodDebugInfo(MethodInfo* m)
{
  LLVMModule& module = *modulep;
  llvm::Type* int32Ty = llvm::Type::getInt32Ty(module.getContext());
  bool isConst = true;
  ConstStructInitializer aotInfo(module.methodDebugInfoStruct);
  const uint8_t *abc_start = &m->pool()->code()[0];
  
  const uint8_t *pos = m->abc_body_pos();
  
  AvmCore::skipU32(pos, 1); // max_stack
  uint32_t local_count = AvmCore::readU32(pos);
  aotInfo.init(module.methodDebugInfo_local_count_member,
               llvm::ConstantInt::get(int32Ty, local_count));
  
  uint32_t init_scope_depth = AvmCore::readU32(pos);
  uint32_t max_scope_depth = AvmCore::readU32(pos);
  aotInfo.init(module.methodDebugInfo_scope_count_member,
               llvm::ConstantInt::get(int32Ty, max_scope_depth - init_scope_depth));
  
  uint32_t num_local_names = local_count + max_scope_depth;
  std::vector<uint32_t> localNamesVec(num_local_names, 0 );
  std::vector<uint32_t> linesVec;
  
  uint32_t code_len = AvmCore::readU32(pos); // checked earlier by AbcParser::parseMethodInfos()
  
  const uint8_t *start = pos;
  const uint8_t *end = pos + code_len;
  
  uintptr_t size = 0;
  int op_count;
  SourceFile* active = NULL; // current source file
  for (const uint8_t* pc=start; pc < end; pc += size)
  {
    op_count = opcodeInfo[*pc].operandCount;
    if (op_count == -1 && *pc != OP_lookupswitch)
      return NULL; // ohh very bad, verifier will catch this
    
    size = AvmCore::calculateInstructionWidth(pc);
    
    // if pc+size overflows, we're definitely hosed
    if (uintptr_t(pc) > uintptr_t(-1) - size)
      return NULL;
    
    if (pc+size > end)
      return NULL; // also bad, let the verifier will handle it
    
    switch (*pc)
    {
      case OP_lookupswitch:
      {
        // variable length instruction
        const uint8_t *pc2 = pc+4;
        // case_count is a U30, so if the high bits are set,
        // bail and let Verifier throw the error
        uint32_t const case_count = AvmCore::readU32(pc2);
        if (case_count & 0xc0000000)
          return NULL;
        // case_count*3 can't overflow a U32...
        uint32_t const case_skip = (case_count + 1) * 3;
        // ...but size could, so check to see if it will.
        if (size > uintptr_t(-1) - case_skip)
          return NULL;
        size += case_skip;
        break;
      }
        
      case OP_debug:
      {
        // form is 8bit type followed by pool entry
        // then 4Byte extra info
        int type = (uint8_t)*(pc+1);
        
        switch(type)
        {
          case DI_LOCAL:
          {
            // in this case last word contains
            // register and line number
            const uint8_t* pc2 = pc+2;
            uint32_t index = AvmCore::readU32(pc2);
            int slot = (uint8_t)*(pc2);
            //int line = readS24(pc+5);
            if (index >= pool->constantStringCount)
              break; // let the verifier handle this
            
            if(localNamesVec.size() <= slot )
              localNamesVec.resize(slot +1 , 0);
            localNamesVec[slot] = index;
          }
        }
        
        break;
      }
        
      case OP_debugline:
      {
        // this means that we have a new source line for the given offset
        const uint8_t* pc2 = pc+1;
        int line = AvmCore::readU32(pc2);
        
        linesVec.push_back(line);
    
        break;
      }
        
      case OP_debugfile:
      {
        // new or existing source file
        const uint8_t* pc2 = pc+1;
        uint32_t index = AvmCore::readU32(pc2);
        if (index >= pool->constantStringCount)
          break; // let the verifier handle this
        aotInfo.init(module.methodDebugInfo_file_name_member,
                     llvm::ConstantInt::get(int32Ty, index));

        break;
      }
    }
  }
  
  uint32_t localNamesSize = localNamesVec.size();
  uint32_t* localNamesArr = new uint32_t[localNamesSize];
  for(int i =0; i < localNamesSize; ++i)
    localNamesArr[i]=localNamesVec[i];
  llvm::Constant* local_namesConst = llvm::ConstantDataArray::get(module.getContext(), llvm::ArrayRef<uint32_t>(localNamesArr, localNamesSize));
  
  aotInfo.init(module.methodDebugInfo_local_names_member,
               const_gep(makeVariable(local_namesConst, isConst, getFunctionName(m)+"_local_names"), 0, 0));
  
  uint32_t linesSize = linesVec.size();
  aotInfo.init(module.methodDebugInfo_line_count_member,
               llvm::ConstantInt::get(int32Ty, linesSize));
  
  uint32_t* linesArr = new uint32_t[linesSize];
  for(int i =0; i < linesSize; ++i)
    linesArr[i]=linesVec[i];
  
  llvm::Constant* linesConst = llvm::ConstantDataArray::get(module.getContext(), llvm::ArrayRef<uint32_t>(linesArr, linesSize));

  aotInfo.init(module.methodDebugInfo_lines_member,
               const_gep(makeVariable(linesConst, isConst, getFunctionName(m)+"_lines"), 0, 0));
  

  return aotInfo.create();
}
#endif //DEBUGGER

void PoolInfo::populateMethodsArray()
{
    LLVMModule& module = *modulep;
    llvm::Constant *nullFn = llvm::Constant::getNullValue(module.functionPtrTy);
    int methodCount = pool->methodCount();
    functions.resize(methodCount, nullFn);
    llvm::Type* int32Ty = llvm::Type::getInt32Ty(module.getContext());
    llvm::Constant* zeroConst = llvm::ConstantInt::get(int32Ty, 0);
    methodFlagsArr.resize(methodCount, zeroConst);
    activationInits.resize(methodCount, nullFn);
    activationInitsForMethod.resize(methodCount, -1);
    
    for (unsigned i = 0; i < verifyInfos.size(); ++i) {
        MethodVerifyInfo& verifyInfo = verifyInfos[i];
        MethodInfo* method = verifyInfo.method;
        //Add all Aoted function weather they are verified or not. VM Created Methods (id == -1 ) are not aoted hence not adding in array.
        if (method->method_id() >= 0 && !method->isNative()) {
            llvm::FunctionType* methodType = module.getFunctionTy(method);
            llvm::Function* currentFunction = llvm::Function::Create(methodType, llvm::GlobalValue::ExternalLinkage,
                                                     getFunctionName(method));
            
            addMethod(method, currentFunction);
        }
    }
}

void PoolInfo::createAOTInfo()
{
    creatingAOTInfo = true;
    LLVMModule& module = *modulep;
    
    llvm::Type* int32Ty = llvm::Type::getInt32Ty(module.getContext());
    bool isConst = true, nonConst = false;
    
    llvm::Constant* sha1Const = llvm::ConstantDataArray::get(module.getContext(), llvm::ArrayRef<uint8_t>(sha1hash));
    
    llvm::Constant* abcBytesConst = llvm::ConstantDataArray::get(module.getContext(), llvm::ArrayRef<uint8_t>(abcBytes, abcSize));
    
    //Populate Function pointer array
    populateMethodsArray();
    llvm::Constant* abcMethodsConst = llvm::ConstantArray::get(llvm::ArrayType::get(module.functionPtrTy, functions.size()), functions);
    llvm::Constant* methodFlagsArrConst = llvm::ConstantArray::get(llvm::ArrayType::get(int32Ty, methodFlagsArr.size()), methodFlagsArr);
    
    std::vector<llvm::Constant*> activationInfos(pool->methodCount());
    for (int i = 0, end = activationInfos.size(); i < end; ++i) {
        ConstStructInitializer actInfo(module.aotActivationInfoStruct);
        // always -1; this could be simplified and save a lot of space
        actInfo.init(module.aotActivationInfo_initMethodId_member, llvm::ConstantInt::get(int32Ty, -1));
        actInfo.init(module.aotActivationInfo_initHandler_member, activationInits[i]);
        activationInfos[i] = actInfo.create();
    }
    llvm::Constant* activationInfoConst = llvm::ConstantArray::get(llvm::ArrayType::get(module.aotActivationInfoTy, activationInfos.size()), activationInfos);
    llvm::Constant* activationTraitsConst = llvm::Constant::getNullValue(llvm::ArrayType::get(module.traitsPtrTy, activationInfos.size()));
    llvm::Constant* scriptTraitsConst = llvm::Constant::getNullValue(llvm::ArrayType::get(module.traitsPtrTy, pool->scriptCount()));
    
    activationTraits->setInitializer(activationTraitsConst);
    scriptTraits->setInitializer(scriptTraitsConst);
    
    ConstStructInitializer aotInfo(module.aotInfoStruct);
    aotInfo.init(module.aotInfo_origABCSHA1_member,
                 sha1Const);
    aotInfo.init(module.aotInfo_abcbytes_member,
                 const_gep(makeVariable(abcBytesConst, isConst, infoName+"_abcBytes"), 0, 0));
    aotInfo.init(module.aotInfo_nABCBytes_member,
        llvm::ConstantInt::get(int32Ty, abcSize));

#ifdef DEBUGGER
    if(halfmoon::AOTIsDebugMode()) {
      populateAllMethodsDebugInfos();
      llvm::Constant* methodDebugInfosConst = llvm::ConstantArray::get(llvm::ArrayType::get(module.methodDebugInfoTy, methodDebugInfos.size()), methodDebugInfos);
      aotInfo.init(module.aotInfo_methodDebugInfos_member,
               const_gep(makeVariable(methodDebugInfosConst, isConst, infoName+"_methodDebugInfos"), 0, 0));
    }
#endif

    aotInfo.init(module.aotInfo_abcMethods_member,
        const_gep(makeVariable(abcMethodsConst, isConst, infoName+"_abcMethods"), 0, 0));
    aotInfo.init(module.aotInfo_nABCMethods_member,
        llvm::ConstantInt::get(int32Ty, pool->methodCount()));
    aotInfo.init(module.aotInfo_methodFlagsArr_member,
                 const_gep(makeVariable(methodFlagsArrConst, isConst, infoName+"_methodFlagsArr"), 0, 0));
    aotInfo.init(module.aotInfo_activationInfo_member,
        const_gep(makeVariable(activationInfoConst, isConst, infoName+"_activationInfo"), 0, 0));
    llvm::Constant* aotInfoConst = aotInfo.create();
    llvm::GlobalVariable* aotInfoVar = makeVariable(aotInfoConst, nonConst, infoName + aotInfoSuffix);
    
    generateDependencyGlobals();
    creatingAOTInfo =false;
}
    
std::string hashStr(unsigned char hash[SHA1_LENGTH])
{
    std::ostringstream buf;
    for (int i = 0; i < SHA1_LENGTH; ++i)
        buf << std::hex << hash[i];
    return buf.str();
}

void PoolInfo::generateDependencyGlobals()
{
    LLVMModule& module = *modulep;
    const llvm::GlobalValue::LinkageTypes extLinkage = llvm::GlobalValue::ExternalLinkage;
    const bool isConst = true;
    llvm::Type* int32Ty = llvm::Type::getInt32Ty(module.getContext());
    llvm::Constant* zeroConst = llvm::ConstantInt::get(int32Ty, 0);
    
    //
    // POTENTIAL PATENT MARKER
    //
    // This mechanism ensures that attempts to link incompatibly-compiled object files
    // will generate a linker error instead of difficult-to-diagnose runtime errors.
    //

    // Define a global variable whose name contains a signature of the source(s)
    // used to generate this object file.
    std::string varName = infoName + "_version_" + hashStr(sha1hash);
    llvm::GlobalVariable* myVersionGlob = new llvm::GlobalVariable(*modulep, zeroConst->getType(),
        isConst, extLinkage, zeroConst, varName.c_str());
    (void)myVersionGlob;  // unused
    
    typedef std::set<PoolInfo*> Deps;
    for (Deps::iterator i = dependsOn.begin(); i != dependsOn.end(); ++i) {
        PoolInfo* poolInfo = *i;
        // Reference a variable whose name contains a signature of the sources used
        // to create that binary if our object code depends on that file's source.
        varName = poolInfo->infoName + "_version_" + hashStr(poolInfo->sha1hash);
        llvm::GlobalValue *gRef = module.getNamedValue(varName);
        if (!gRef)
            gRef = new llvm::GlobalVariable(*modulep, zeroConst->getType(), isConst, extLinkage, 0, varName.c_str());
        std::string varRefName = infoName + "_requires_" + poolInfo->infoName + "_version";
        llvm::GlobalVariable* gRefVar = new llvm::GlobalVariable(*modulep, gRef->getType(),
            isConst, extLinkage, gRef, varRefName);
        (void)gRefVar; // unused
    }
}
    
void PoolInfo::createFieldsChecksum(uint64_t checksum, bool defineIt)
{
    LLVMModule& module = *modulep;
    const llvm::GlobalValue::LinkageTypes extLinkage = llvm::GlobalValue::ExternalLinkage;
    const bool isConst = true;
    llvm::Type* int32Ty = llvm::Type::getInt32Ty(module.getContext());
    llvm::Constant* zeroConst = llvm::ConstantInt::get(int32Ty, 0);

    std::ostringstream buf;
    buf << "fields_checksum_" << std::hex << checksum;
    std::string varName = buf.str();
    if (defineIt) {
        llvm::GlobalVariable* fieldsVar = new llvm::GlobalVariable(*modulep, zeroConst->getType(),
            isConst, extLinkage, zeroConst, varName.c_str());
        (void)fieldsVar; // unused
    }
    else {
        llvm::GlobalValue *gRef = module.getNamedValue(varName);
        if (!gRef)
            gRef = new llvm::GlobalVariable(*modulep, zeroConst->getType(), isConst, extLinkage, 0, varName.c_str());
        
        std::string varRefName = infoName + "_requires_fields_checksum";
        llvm::GlobalVariable* gRefVar = new llvm::GlobalVariable(*modulep, gRef->getType(),
            isConst, extLinkage, gRef, varRefName);
        (void)gRefVar; // unused        
    }
}

std::string PoolInfo::getFunctionName(MethodInfo* method)
{
    StUTF8String functionName(method->getMethodName());
    std::ostringstream name;
    name << infoName << ":" << method->method_id() << ":" << functionName.c_str();
    return name.str();
}


//
// Copy ABC bytes except for the bytecodes in the method bodies.
//

inline uint32_t readU32(const uint8_t*& pos)
{
    return AvmCore::readU32(pos);
}


/*
inline int32_t readS32(const uint8_t*& pos)
{
    return (int32_t)AvmCore::readU32(pos);
}

inline uint32_t readU30(const uint8_t*& pos)
{
    uint32_t val = AvmCore::readU32(pos);
    AvmAssert((val&0xc0000000) == 0);
    return val;
}

*/

// the next six functions just do the minimum needed to advance pos to just
// after the end of the section of abcfile they are designed for

static void skipCpool(const uint8_t*& pos)
{

    // int pool
    uint32_t count = readU32(pos);
    for(uint32_t i = 1; i < count; ++i)
         readU32(pos);

    // uint pool
    count = readU32(pos);
    for(uint32_t i = 1; i < count; ++i)
        readU32(pos);

    // double pool
    count = readU32(pos);
    // doubles are always 8 bytes so lets just advance pos to just past the end of the double pool
    // there are really only count-1 doubles in there
    if (count != 0)  pos+=(count-1)*8;

    // string pool
    count = readU32(pos);

    for(uint32_t i = 1; i < count; ++i)
    {
        uint32_t length = readU32(pos);
        pos+=length;
    }

    // namespace pool
    count = readU32(pos);
    for(uint32_t i = 1; i < count; ++i)
    {
        pos++;
        readU32(pos);
    }


    // namespace set pool
    count = readU32(pos);
    for(uint32_t i = 1; i < count; ++i)
    {
        uint32_t length = readU32(pos);
        for(uint32_t j = 0; j < length; ++j)
            readU32(pos);
    }

    // multiname pool
    count = readU32(pos);

    for(uint32_t i = 1; i < count; i++)
    {
        uint8_t kind = pos[0];
        pos++;
        switch(kind)
        {
        case CONSTANT_Qname:
        case CONSTANT_QnameA:
        case CONSTANT_Multiname:
        case CONSTANT_MultinameA:
        {
            readU32(pos);
            readU32(pos);
            break;
        }
        case CONSTANT_RTQname:
        case CONSTANT_RTQnameA:
        case CONSTANT_MultinameL:
        case CONSTANT_MultinameLA:
        {
            readU32(pos);
            break;
        }
        case CONSTANT_TypeName:   
        {
            readU32(pos);      //name
            uint32_t typeCount = readU32(pos);
            for(uint32_t j=0;j<typeCount;j++)
            {
                readU32(pos);
            }
        }
        default:
            break;
        } 
    }
}

static void skipMethodInfos(const uint8_t*& pos)
{
    uint32_t count = readU32(pos);
    for(uint32_t i = 0; i < count; i++)
    {
        uint32_t params = readU32(pos);             // param_count
        readU32(pos);                               // ret_type
        for(uint32_t j = 0; j < params; ++j)        // skip over param_count param_types
            readU32(pos);
        readU32(pos);                               // name_index
        uint8_t flags = pos[0];         // flags
        pos++;
        if (flags & abcMethod_HAS_OPTIONAL)
        {
            uint32_t optionals = readU32(pos);      // optional_count
            for(uint32_t j = 0; j < optionals; ++j) // skip over optional_count ValueKinds
            {
                readU32(pos);                       // value_index
                pos++;                              // value_kind
            }
        }
        if (flags & abcMethod_HAS_PARAM_NAMES)
        {
            for(uint32_t j = 0; j < params; ++j)    // skip over param_count param_names
                readU32(pos);
        }
    }
}


static void skipMetadataInfos(const uint8_t*& pos)
{
    uint32_t count = readU32(pos);
    for(uint32_t i = 0; i < count; i++)
    {
        readU32(pos);                                  // name_index
        uint32_t numValues = readU32(pos);             // values_count
        for(uint32_t j = 0; j < numValues; ++j)        // skip over values_count keys
            readU32(pos);
        for(uint32_t j = 0; j < numValues; ++j)        // skip over values_count values
            readU32(pos);
    }
}

static void skipTraits(const uint8_t*& pos)
{
    uint32_t count = readU32(pos);
    for(uint32_t i = 0; i < count; i++)
    {
        readU32(pos);                                    // name_index
        uint8_t kind = pos[0];                           // kind
        pos++;
        uint8_t needToSkipMetadata = (( kind >> 4) & 0x04); // save important bit from high half of kind
        kind = kind & 0x0F;                              // low four bits of kind
        if (kind <= 6)                                   // these seven cases all start with two U30's (with all different names)
        {
            readU32(pos);                                // first U30
            readU32(pos);                                // second U30
        }
        if (0 == kind || 6 == kind)                      // these two cases have additional data
        {
            uint32_t valueIndex = readU32(pos);          // value_index
            if (valueIndex != 0) pos++;                  // skip over value_kind if it is there
        }
        if (needToSkipMetadata)
        {
            uint32_t metadatas = readU32(pos);           // metadata_count
            for(uint32_t j = 0; j < metadatas; ++j)      // skip over metadata_count metadatas
                readU32(pos);
        }
    }
}


static void skipInstanceAndClassInfos(const uint8_t*& pos)
{
    uint32_t count = readU32(pos);
    // first we have count InstanceInfos
    for(uint32_t i = 0; i < count; i++)
    {
        readU32(pos);                                // name_index
        readU32(pos);                                // super_index
        uint8_t flags = pos[0];                      // flags
        pos++;
        if (flags & 8)                               // protected flag is set
            readU32(pos);                            // protectedNS
        uint32_t interfaces = readU32(pos);          // interfaces_count
        for(uint32_t j = 0; j < interfaces; ++j)     // skip over interfaces_count interfaces
            readU32(pos);
        readU32(pos);                                // iinit_index
        skipTraits(pos);                             // instance_traits
    }
    // next we have count ClassInfos
    for(uint32_t i = 0; i < count; i++)
    {
        readU32(pos);                                // cinit_index
        skipTraits(pos);                             // static traits
    }
}


static void skipScriptInfos(const uint8_t*& pos)
{
    uint32_t count = readU32(pos);
    for(uint32_t i = 0; i < count; i++)
    {
        readU32(pos);                                // init_index
        skipTraits(pos);                             // traits
    }
}

static void copyMethodBodies(const uint8_t*& from, uint8_t*& to)
{
    const uint8_t* pos = from;
    int n=0;
    uint32_t count = readU32(pos);                   // bodies_count
    const uint8_t* mystart = pos;


    for(uint32_t i = 0; i < count; i++)
    {
        // carefully step through a single MethodBody omitting only the bytecodes.
        readU32(pos);                                // method_info
        readU32(pos);                                // max_stack
        readU32(pos);                                // max_regs
        readU32(pos);                                // scope_depth
        readU32(pos);                                // max_scope

        // copy what we've skipped so far
        n = pos-from;
        memcpy(to, from, n);
        to = to + n;

        // how many bytecodes?
        uint32_t length = readU32(pos);                   // code_length
        from=pos;
        *to=0;                                            // rewrite code length as 0
        to++;
        from += length;
        pos=from;                                         // advance pos to past bytecodes

        // remaining data from this MethodBody
        uint32_t exceptions = readU32(pos);               // ex_count


        for(uint32_t j = 0; j < exceptions; ++j)          // skip over exceptions Exception bodies
        {
            readU32(pos);                                 // start
            readU32(pos);                                 // end
            readU32(pos);                                 // target
            readU32(pos);                                 // type_index
            readU32(pos);                                 // name_index
        }
        skipTraits(pos);

     }
    // copy last little left-over bit
    n = pos-from;
    memcpy(to, from, n);
    from = pos;
    to = to + n;

}

/*
 * Copy ABC bytes from abcBytes to copiedBytes; both buffers are nAbcBytes long.
 * Returns the size of the copied bytes (less than or equal to nAbcBytes).
 */
uint32_t copyAbcSkippingMethodBodies(const uint8_t* abcBytes, uint8_t* copiedBytes, unsigned nAbcBytes)
{

    const uint8_t* pos = abcBytes;
    uint8_t* to = copiedBytes;

    const uint8_t* from = pos;

    

    pos +=4;        // skip over minor/major version numbers

    // printf("before cpool we are at %d \n",(int) (pos-abcBytes));
    skipCpool(pos);
    // printf("after cpool we are at %d \n",(int) (pos-abcBytes));
    skipMethodInfos(pos);
    // printf("after MethodInfos we are at %d \n",(int) (pos-abcBytes));
    skipMetadataInfos(pos);
    // printf("after MetadataInfos  e are at %d \n",(int) (pos-abcBytes));
    skipInstanceAndClassInfos(pos);
    // printf("after InstanceAndClassInfos we are at %d \n",(int) (pos-abcBytes));
    skipScriptInfos(pos);
    // printf("after ScriptInfos we are at %d \n",(int) (pos-abcBytes));

    // copy what we've skipped so far
    int n = pos-from;
    memcpy(to, from, n);
    from = pos;
    to = to + n;

    copyMethodBodies(from, to);

    // Did we parse the entire buffer?

    AvmAssert(from-abcBytes == nAbcBytes);

    // Shouldn't be more bytes in the resulting buffer than in the original
    uint32_t newSize = to-copiedBytes;
    AvmAssert(newSize <= nAbcBytes);

    return newSize;
}

} // namespace compile_abc

