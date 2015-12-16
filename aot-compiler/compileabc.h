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
// Main routine and driver for the AOT compiler.
//

#ifndef __compileabc__
#define __compileabc__

#include "avmplus.h"
#include "halfmoon/hm-main.h"
#include "llvm-emitter.h"
#include "poolinfo.h"
#include "aotverify.h"
#include "ThreadPool.h"
namespace compile_abc
{
    class LLVMEmitter;
    class LLVMModule;
    struct StructInfo;
    
    // exit codes
    enum ExitCode {
        EXIT_CODE_SUCCESS = 0,
        EXIT_CODE_BADFILE = 1,
        EXIT_CODE_MISSINGDEFS = 2,
        // internal errors
        EXIT_CODE_OUT_OF_MEMORY = 128,
        EXIT_CODE_ABORT = 129,
    };
    void emitANEMap(int argc, char** argv);
    void parseOptions(int argc,char **argv);
    class CompilerSettings
    {
    public:
        CompilerSettings()
        : do_log(false)
        , do_verbose(false)
        , as3_debugger(false)
        {
        }

        bool do_log;
        std::string target_triple;
        uint32_t do_verbose;           // copy to config
        bool as3_debugger;
        bool telemetry_sampler;
    };

    /**
     * Compiler driver and command line parser.
     */
    class Compiler: public avmplus::Aggregate {
    public:
        static int run(int argc, char *argv[]);

    private:
        int compile();
        CompilerSettings settings;
    };


    class CompilerToplevel: public avmplus::Toplevel
    {
    public:
        CompilerToplevel(avmplus::AbcEnv* abcEnv) : Toplevel(abcEnv) {}
        virtual MMgc::GCAPI::GCRef<avmplus::ClassClosure> workerClass() const { return NULL; }
        virtual MMgc::GCAPI::GCRef<avmplus::ClassClosure> workerDomainClass() const { return NULL; }
    };
    
    class CompilerCodeContext: public avmplus::CodeContext
    {
    public:
        CompilerCodeContext(avmplus::DomainEnv* domainEnv, const avmplus::BugCompatibility* bugCompatibility)
        : CodeContext(domainEnv, bugCompatibility)
        {}
    };
    
    /**
     * A subclass of AcmCore for the compiler.
     * AvmCore is a GCRoot, so this doesn't need decorations or write barriers.
     */
    class CompilerCore: public avmplus::AvmCore {
    public:
        CompilerCore(MMgc::GC* gc);
        ~CompilerCore();
        
        static int run(int argc, char *argv[]);
        
        virtual avmplus::Toplevel* createToplevel(avmplus::AbcEnv*);
        virtual avmplus::ApiVersion getDefaultAPI();
        virtual void interrupt(avmplus::Toplevel*, avmplus::AvmCore::InterruptReason);
        virtual void stackOverflow(avmplus::Toplevel*);

        virtual BaseExecMgr* createExecMgr()
        {
            return new (gc) AOTExecMgr(this);
        }

        LLVMModule* summaryModule;
        ThreadPool threadPool;
        StructInfoMap structInfos;
        StructInfoMap nativeSlotTemplates;
        std::vector<NativeMethod> nativeMethods;
        struct PoolInfos: std::vector<PoolInfo*>
        {
            // Can't have a vector of AbcInfos sice we keep pointers to them so they can't be moving
            // around when realocating. There's no suitable auto_ptr for container usage until C++11
            // (or in Boost) but I don't want to depend on those, so handle deletion here.
            ~PoolInfos()
            {
                for(unsigned i = 0; i < size(); ++i)
                    delete (*this)[i];
            }
        } poolInfos;
        int firstUserPool;
        PoolInfo* builtinPoolInfo;
        PoolInfo* currentlyParsing;
        
        uint64_t fieldsChecksum;
        CompilerToplevel* compilerToplevel;
        bool parseAndVerify;
        
    private:
        int compile();
        int initialize();
        
        int evaluateFile(const std::string& fileName, PoolInfo& poolinfo, avmplus::CodeContext* codeContext);
        
        void emitPoolToModule(PoolInfo& poolInfo, LLVMModule* llvmModule);
        void emitSummaryModule();
        //This takes a pool and emits it. If Pool has large no of functions then
        // it is broken into multiple llvm modules and then emits.
        void emitPoolToSpilttedModules(PoolInfo& poolInfo);
        void emitModule(LLVMModule* llvmModule);
        void createModule(PoolInfo& poolInfo, LLVMModule*& llvmModule, int splitIndex);
        CompilerSettings settings;
        const avmplus::BugCompatibility* bugCompatibility;
        
        CompilerCodeContext* sdkCodeContext;     
        CompilerCodeContext* userCodeContext;
                
        friend class LLVMEmitter;
        friend class CompilationJob;
    };
}
namespace halfmoon {
  bool AOTIsDebugMode();
}
#endif /* __compileabc__ */
