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

//
// Manages per-Pool (per-ABC file) level things such as the creation of AOTInfo structures
// that bind AOT code to the runtime libries.
//
// The naming of certain things like functions is handled here since function names contain a pool
// identifier.
//
// IMPORTANT NOTE:
//
// Instances of this class persist from when a pool is loaded until the end of the compile.
// The class should not carry heavyweight data, and in particular, it should not contain
// any references to LLVM data after "disconnect()" is called. It should be possible to delete an
// LLVM Module and LLVMContext as soon as a module's code is generated. Also: continued references to
// LLVM data after "disconnect()" will put multi-threaded code generation at unnecessary risk.
//

#ifndef __abcinfo_h__
#define __abcinfo_h__

#include "avmplus.h"
#include "halfmoon/hm-main.h"
#include "aotverify.h"
#include "llvm-module.h"
#include "sha1.h"
#include <set>
#include <string>
#include <vector>

namespace compile_abc
{
    class LLVMEmitter;
    class LLVMModule;
    using namespace avmplus;
    const std::string aotInfoSuffix = "_aotInfo";
  
    class PoolInfo: public GCRoot
    {
    public:
        PoolInfo(GC* gc, const std::string& fileName, const std::string& infoName)
        : GCRoot(gc)
        , modulep(0)
        , pool(0)
        , abcBytes(0)
        , abcSize(0)
        , totalABCSize(0)
        , fileName(fileName)
        , infoName(infoName)
        , lastDependency(0)
        , outOfDate(false)
        , abc_env(0)
        , creatingAOTInfo(false)
        {
        }
                
        ~PoolInfo()
        {
            delete[] abcBytes;
        }
        
        void setAbcData(const uint8_t* bytes, int size);
        
        void addMethod(MethodInfo* method, llvm::Function* func);
        
        std::string getFunctionName(MethodInfo* method);
        
        void connect(LLVMModule *modulep);
        void disconnect();
        
        LLVMModule* modulep;
        PoolObject* pool;
        uint8_t* abcBytes;
        int abcSize;
        int totalABCSize;
        llvm::GlobalVariable* activationTraits;
        llvm::GlobalVariable* scriptTraits;
        std::string fileName, infoName;
        
        void addDependency(MethodInfo *info) { addDependency(info->pool()->poolInfo); }
        void addDependency(Traits *traits) { addDependency(traits->pool->poolInfo); }
        void addDependency(PoolObject *pool) { addDependency(pool->poolInfo); }
        
        void addDependency(PoolInfo *poolInfo)
        {
            if (poolInfo == this)
                return;
            if (poolInfo == lastDependency)
                return;
            dependsOn.insert(poolInfo);
        }
        
        std::set<PoolInfo*> dependsOn;
        PoolInfo* lastDependency;
        bool outOfDate;
        AbcEnv* abc_env;
        
        std::vector<MethodVerifyInfo> verifyInfos;
        
        void appendVerifierResult(AbcEnv* abc_env, const compile_abc::MethodVerifyInfo& verifierInfo);
        void createAOTInfo();
        void createFieldsChecksum(uint64_t checksum, bool defineIt);
        bool isCreatingAOTInfo() { return creatingAOTInfo; }
        
    private:        
        void init(PoolObject* pool);
        llvm::GlobalVariable* makeVariable(llvm::Constant* init, bool isConst, const llvm::Twine& name="");
        static llvm::Constant* const_gep(llvm::Constant* in, int i, int j);
        void generateDependencyGlobals();
#ifdef DEBUGGER
        void populateAllMethodsDebugInfos();
        llvm::Constant* collectMethodDebugInfo(MethodInfo* m);
        std::vector<llvm::Constant*> methodDebugInfos;
#endif
        void populateMethodsArray();

        unsigned char sha1hash[base::SHA1_LENGTH];
        std::vector<llvm::Constant*> functions;
        std::vector<llvm::Constant*> methodFlagsArr;
        std::vector<llvm::Constant*> activationInits;
        std::vector<int> activationInitsForMethod;
        bool creatingAOTInfo;
    };
    
    /*
     * Copy ABC bytes from abcBytes to copiedBytes; both buffers are nAbcBytes long.
     * Returns the size of the copie bytes (less than or equal to nAbcBytes).
     */
    uint32_t copyAbcSkippingMethodBodies(const uint8_t* abcBytes, uint8_t* copiedBytes, unsigned nAbcBytes);
}


#endif /* __abcinfo_h__ */
