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
// Instantiates just enough AVM machinery to instantiate an avmcore and run the parser and verifier.
// Next it creates a toplevel and a couple of DomainEnvs since the parser and verifier need them.
// The builtins are parsed as a side-effect of instantiating the toplevel. Then it iterates through
// the "sdk" abcs (in practice there will be just one) parsing them. This is where the shell or
// player APIs are added above the ActionScript language primitive defintions (String, Class, Object, etc.)
// Then, it iterates over the user abcs feeding them to the parser/veifier which feeds the method bodies to
// halfmoon and then to the LLVMEmitter.
//
// Code is then emitted for the builtins+SDK ABCs and then for each user ABC.
//
// Finally, AOTInfos are generated which create the bondings between the runtime libraries and the generated code.
//
// Uses llvm's  command-line processing facility for argument parsing. Among the advantages is
// response-file support (options from a file). This is useful because AOT compiles often have
// command lines that are too long for Windows.
//
#ifdef _WIN32
#define __uncaught_exception std::uncaught_exception
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>

#include "compileabc.h"
#include "poolinfo.h"
#include "structinfo.h"
#include "BuiltinNatives.h"

#include "llvm/Support/Signals.h"
#include "llvm/Support/PrettyStackTrace.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Linker/Linker.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Support/Timer.h"
#include "llvm/IR/Verifier.h"

using namespace avmplus;

namespace compile_abc
{
#ifdef AVMPLUS_64BIT
    const unsigned int kMaxFunctionInModule = 2000;
#else
    const unsigned int kMaxFunctionInModule = 1000;
#endif
    
    const unsigned int kLargeFunctionThreshold = 30000;
    namespace options {
        using namespace llvm;
        using std::string;
        
        static cl::list<string> fileList(cl::Positional, cl::ZeroOrMore, cl::desc("<abc and bitcode files>"));
        static cl::list<string> sdkFileList("sdk", cl::ZeroOrMore, cl::desc("<sdk abc file>"));
        static cl::opt<string> fields("fields", cl::desc("Specify structure definitions"), cl::value_desc("filename"), cl::ZeroOrMore);
        static cl::opt<string> targetTriple("mtriple", cl::desc("<llvm target triple>"), cl::Required);
        static cl::opt<bool> printHMIR("print-hmir", cl::desc("Print Halfmoon IR"), cl::init(false));
        static cl::opt<bool> printGML("print-hmir-gml", cl::desc("Print Halfmoon IR as GML"), cl::init(false));
        static cl::opt<bool> verbose("verbose", cl::desc("enable verbose output"), cl::Hidden);
        static cl::opt<bool> perfLog("perf-log", cl::desc("enable logging"), cl::Hidden);
        static cl::opt<bool> emitSdk("emit-sdk", cl::desc("emit code for SDK files"), cl::init(false));
        static cl::opt<bool> emitANEFnMap("emit-ane-map", cl::desc("emit map for ANE functions"), cl::init(false));
        static cl::list<string> exportedSym("ane-symbol", cl::desc("symbol for ANE lookup"), cl::ZeroOrMore);
        static cl::opt<bool> as3Debugger("as3debugger", cl::desc("enable action script debugging"), cl::init(false));
        static cl::list<string> abcFileList("abc-file-list", cl::desc("File having abc filenames"), cl::ZeroOrMore);
        static cl::opt<bool> telemetrySampler("telemetry-sampler", cl::desc("enable telemetry advanced sampler "), cl::init(false));
        
        static void printVersion()
        {
            llvm::raw_ostream &outs = llvm::outs();
            outs << "aotcompiler " AVMPLUS_VERSION_USER " " AVMPLUS_BIN_TYPE "\n";
            if (RUNNING_ON_VALGRIND)
                outs << "  valgrind\n";
            outs << "  build " AVMPLUS_BUILD_CODE "\n";
    #ifdef AVMPLUS_DESC_STRING
            if (VMPI_strcmp(AVMPLUS_DESC_STRING, ""))
            {
                outs << "Description: " AVMPLUS_DESC_STRING "\n";
            }
    #endif
           outs << "features " << avmfeatures << "\n";
        }
    }
    
    class CodeContextCreator : public AvmCore::ICodeContextCreator
    {
    public:
        MMgc::GC* gc;
        
        explicit CodeContextCreator(MMgc::GC* _gc) : gc(_gc)
        {
        }
        
        virtual CodeContext* create(DomainEnv* domainEnv, const BugCompatibility* bugCompatibility)
        {
            return new (gc) CompilerCodeContext(domainEnv, bugCompatibility);
        }
    };
    
    class Console: public NonGCOutputStream
    {
        virtual void write(const char* utf8) { writeN(utf8, VMPI_strlen(utf8)); }
        virtual void writeN(const char* utf8, size_t charCount)
        {
            for (size_t i = 0; i < charCount; ++i)
                putc(utf8[i], stdout);
        }
    } consoleStream;
    
    class CompilationJob: public ThreadPool::Job
    {
    public:
        CompilationJob(LLVMModule* llvmModule_)
        :llvmModule(llvmModule_){}
        void handler() {
            {
                llvm::NamedRegionTimer codeGenTimer("CompilationJob : LLVM IR to native"  , "Compile-abc", llvm::TimePassesIsEnabled);
                llvmModule->emit();
            }
            {
                llvm::NamedRegionTimer codeGenTimer("CompilationJob : Finalize Modules" , "Compile-abc", llvm::TimePassesIsEnabled);
                delete llvmModule;
                llvmModule = NULL;
            }
        }
    private:
        LLVMModule* llvmModule;


    };


    CompilerCore::CompilerCore(MMgc::GC* gc)
    : AvmCore(gc, kApiVersionSeries_AIR)
    , summaryModule(0)
    , firstUserPool(0)
    , builtinPoolInfo(0)
    , currentlyParsing(0)
    , fieldsChecksum(0)
    , compilerToplevel(0)
    , parseAndVerify(false)
    , bugCompatibility(0)
    , sdkCodeContext(0)
    , userCodeContext(0)
    {
        bugCompatibility = createBugCompatibility(BugCompatibility::kLatest);

        config.verifyall = true;
        config.verifyonly = true;
#ifdef AVMPLUS_VERBOSE
        config.verbose_vb = options::verbose ? avmplus::AvmCore::DEFAULT_VERBOSE_ON: 0 ;
        if (options::verbose)
            config.methodNames = true;
#endif
        settings.as3_debugger = options::as3Debugger;

        //Enable console output in debug mode. 
#ifndef DEBUG
        if (options::verbose)
#endif
            setConsoleStream(&consoleStream);
    }
    
    CompilerCore::~CompilerCore()
    {
        threadPool.stopAndWait();
    }
    
    int CompilerCore::initialize()
    {
        TRY(this, avmplus::kCatchAction_ReportAsError)
        {
            llvm::raw_ostream &errs = llvm::errs();
            
            {
                llvm::NamedRegionTimer codeGenTimer("Load Fields", "Compile-abc", llvm::TimePassesIsEnabled);

                summaryModule = new LLVMModule("aotInfo", this, settings.target_triple);
                
                // Load the field information
                {
                    std::ifstream fldStream(options::fields.c_str());
                    if (!fldStream) {
                        errs << "can't open " << options::fields << "\n";
                        return EXIT_CODE_BADFILE;
                    }
                    if (parseFieldFile(errs, fldStream, *summaryModule,
                                       &structInfos, &nativeSlotTemplates, &nativeMethods, &fieldsChecksum))
                        return EXIT_CODE_BADFILE;
                }
                
                // Have to do this after loading the field info.
                if (summaryModule->initializeDefs(llvm::errs()))
                    return EXIT_CODE_MISSINGDEFS;
            }
            {
                llvm::NamedRegionTimer codeGenTimer("Parse and verify builtins", "Compile-abc", llvm::TimePassesIsEnabled);
                poolInfos.push_back(new PoolInfo(GetGC(), "builtin.abc", "builtin"));
                PoolInfo& poolInfo = *poolInfos.back();
                builtinPoolInfo = &poolInfo;
                poolInfo.setAbcData(NativeID::builtin_abc_data, NativeID::builtin_abc_length);
                currentlyParsing = &poolInfo;
                parseAndVerify = true;
                
                int tracelevel = 0;
                initBuiltinPool(tracelevel);
                
                // Initialize a new Toplevel.  This will also create a new
                // DomainEnv based on the builtinDomain.
                // It also causes the builtins to be parsed.
                
                CodeContextCreator ccc(GetGC());
                compilerToplevel = static_cast<CompilerToplevel*>(initToplevel(ccc));
                currentlyParsing = 0;
                parseAndVerify = false;
                
                // Create a Domain/DomainEnv/CodeContext for the sdk code
                Domain* sdkDomain = avmplus::Domain::newDomain(this, builtinDomain);
                DomainEnv* sdkDomainEnv = avmplus::DomainEnv::newDomainEnv(this, sdkDomain, compilerToplevel->domainEnv());
                sdkCodeContext = new (GetGC()) CompilerCodeContext(sdkDomainEnv, bugCompatibility);
               
                // Create a Domain/DomainEnv/CodeContext for the user code
                Domain* userDomain = avmplus::Domain::newDomain(this, sdkDomain);
                DomainEnv* userDomainEnv = avmplus::DomainEnv::newDomainEnv(this, userDomain, sdkDomainEnv);
                userCodeContext = new (GetGC()) CompilerCodeContext(userDomainEnv, bugCompatibility);
            }
            
            //get the number of cores for the machine and decide the number of threads to strt dynamically.
            unsigned short numThread = std::thread::hardware_concurrency();
            threadPool.start(numThread/2);
        }
        CATCH(avmplus::Exception *exception)
        {
            llvm::raw_ostream &errs = llvm::errs();
            errs << string(exception->atom) << "\n";
            VMPI_exit(1);
        }
        END_CATCH
        END_TRY
        return EXIT_CODE_SUCCESS;
    }
    
    int CompilerCore::run(int argc, char** argv)
    {
        llvm::cl::SetVersionPrinter(options::printVersion);
        // llvm::cl::AddExtraVersionPrinter(llvm::TargetRegistry::printRegisteredTargetsForVersion);
        
        int status = EXIT_CODE_SUCCESS;
        MMgc::GCHeap::EnterLockInit();
        
        MMgc::GCHeapConfig conf;
        conf.verbose = false;
        conf.clearCheckFixedMemory();  // too slow!
        
        uint32_t secret = (uint32_t)VMPI_getPerformanceCounter();
        conf.secret = secret;
        MMgc::GCHeap::Init(conf);        

        MMGC_ENTER_RETURN(EXIT_CODE_OUT_OF_MEMORY);
        MMgc::GCConfig gcconfig;
        MMgc::GC* gc = mmfx_new(MMgc::GC(MMgc::GCHeap::GetGCHeap(), gcconfig));
        {
            MMGC_GCENTER(gc);
            
            // Calls llvm_shutdown() on exit.
            llvm::llvm_shutdown_obj auto_shutdown;
            
            // This needs to be a separate group or else the detail timings will be added to the total
            // and double-counted.  The point of this timer is to double-check that we didn't miss
            // anything big in the detail timers
            llvm::NamedRegionTimer codeGenTimer("Total Time", "AOT Compiler Command", llvm::TimePassesIsEnabled);
            {
                llvm::NamedRegionTimer LLVMInitTimer("Initialize LLVM", "Compile-abc", llvm::TimePassesIsEnabled);
                llvm::InitializeAllTargetInfos();
                llvm::InitializeAllTargets();
                llvm::InitializeAllTargetMCs();
                llvm::InitializeAllAsmPrinters();
            }

            CompilerCore* core = 0;
            {
                llvm::NamedRegionTimer LLVMInitTimer("Initialize Compiler Core", "Compile-abc", llvm::TimePassesIsEnabled);
                core = new CompilerCore(gc);
                core->settings.target_triple = llvm::Triple::normalize(options::targetTriple.c_str());
                core->settings.telemetry_sampler = options::telemetrySampler;
                halfmoon::enable_builtins = true;
                halfmoon::enable_printir = options::printHMIR | options::printGML;
                halfmoon::enable_gml = options::printGML;
                halfmoon::enable_mode = halfmoon::kModeAnalyze;
                //TODO: Revisit this option during performance testing. Because of scheduling pass ( early / middle ), halfmoon IR
                // is generated differently and llvm emit fails with error.(Instruction does not dominate all uses!) 
                halfmoon::enable_schedule = halfmoon::kScheduleNone;
            }
            
            status = core->compile();
            
            {
                llvm::NamedRegionTimer LLVMInitTimer("Finalize Compiler Core", "Compile-abc", llvm::TimePassesIsEnabled);
                delete core;
                gc->Collect();
            }
        }
        
        mmfx_delete( gc );
        MMgc::GCHeap::Destroy();
        MMgc::GCHeap::EnterLockDestroy();
        return status;
    }
    
    int CompilerCore::compile()
    {
        int exitCode = initialize();
        if (exitCode != EXIT_CODE_SUCCESS)
            return exitCode;
        
        //
        // Parse SDK ABCs
        //
        {
            llvm::NamedRegionTimer codeGenTimer("Parse SDK ABC", "Compile-abc", llvm::TimePassesIsEnabled);
            for (int i= 0, end = options::sdkFileList.size(); i < end; ++i) {
                std::string& fileName = options::sdkFileList[i];
                std::ostringstream aotInfoName("sdk");
                if (i > 0)  // this doesn't come up in real life
                    aotInfoName << i;
                
                poolInfos.push_back(new PoolInfo(GetGC(), fileName, aotInfoName.str()));
                exitCode = evaluateFile(fileName, *poolInfos.back(), sdkCodeContext);
                if (exitCode != EXIT_CODE_SUCCESS)
                    return exitCode;
            }
        }
        
        // We only want user aotinfos in the AOTInfos array.
        firstUserPool = poolInfos.size();
        
        
        //parse ABCFilesList.txt and add abc files to file list
        for (int i=0, end = options::abcFileList.size(); i < end; ++i)
        {
            std::string& thisAbcFileList = options::abcFileList[i];
            std::ifstream infile(thisAbcFileList.c_str());
            for (std::string abcFileName; getline( infile, abcFileName );)
            {
                AvmAssert(abcFileName.c_str() && std::strstr(abcFileName.c_str(), ".abc"));
                options::fileList.push_back(abcFileName);
            }
            
        }
        
        //
        // Parse user ABCs
        //
        {
            llvm::NamedRegionTimer codeGenTimer("Parse user ABCs", "Compile-abc", llvm::TimePassesIsEnabled);
            for (int i= 0, end = options::fileList.size(); i < end; ++i) {
                std::string& fileName = options::fileList[i];
                std::ostringstream moduleName;
                std::string::size_type pos1 = fileName.rfind("/");
				std::string::size_type pos2 = fileName.rfind("\\");
                pos1 = (pos1 == fileName.npos)? 0: pos1+1;
				pos2 = (pos2 == fileName.npos)? 0: pos2+1;
                std::string::size_type basenamePos = (pos1 > pos2) ? pos1 : pos2;
                std::string::size_type dotPos = fileName.rfind(".");
                moduleName << fileName.substr(basenamePos, dotPos-basenamePos) << "_" << i;
                
                poolInfos.push_back(new PoolInfo(GetGC(), fileName, moduleName.str()));
                exitCode = evaluateFile(fileName, *poolInfos.back(), userCodeContext);
                if (exitCode != EXIT_CODE_SUCCESS)
                    return exitCode;
            }
        }
        
        //
        // Verify everything except ActionScript builtins (including the rest of the SDK abcs)
        //
        {
            llvm::NamedRegionTimer codeGenTimer("Verify ABCs", "Compile-abc", llvm::TimePassesIsEnabled);
            AOTExecMgr *execMgr = (AOTExecMgr*)exec;
            
            //Bug 3862419: ArcGISMobile application is crashing on both 32 and 64 bit devices.
            //Bug 3863078: [HMAOT] "SimpleCase.ipa" is crashing while packaging with HMAOT on both 32 and 64 bit devices but not with GOAOT (Same behavior on  M+2  builds).
            //Reason : Known Issue #2 at http://helpx.adobe.com/air/kb/air-compiler-known-issues.html
            //    A sample case is
            //    class A {
            //        public function getFn():int {
            //            trace("A:Fn");
            //            return 10;
            //        }
            //    }
            //    class B extends A{
            //        override public function getFn():int {
            //            trace(arguments.length());
            //            trace("B:Fn");
            //            return 20;
            //        }
            //    }
            //    var obj:A = new B();
            //    obj.getFn();
            // in ll, method signature mismatch at the place of call and called function.
            //Solution : Propogate a flag to indicate that AOT function signature will have argc, argv.
            //The boundary is Builtins where we can't propogate as we ship builtin.o
            //Flag inMethodInfo is needArgsArrInMethodSig

            execMgr->setArgArrayPropogationFlag(true);
            for (int i = 1; i < poolInfos.size(); ++i) {
                PoolInfo& poolInfo = *poolInfos[i];
                currentlyParsing = &poolInfo;
                //This will propogate the flag from bottom to top ( derived to base)
                execMgr->verifyPool(compilerToplevel, poolInfo.abc_env);
                currentlyParsing = 0;
            }
            //Now propogate top to bottom (base to derived)
            execMgr->propogateArgArrFlagTopToBottom();
            execMgr->setArgArrayPropogationFlag(false);
        }
        
        //
        // Optionally emit code for builtins and sdk pools.
        //        
        if (options::emitSdk) {
            LLVMModule* llvmModule = 0;
            {
                llvm::NamedRegionTimer codeGenTimer("Initialize Modules", "Compile-abc", llvm::TimePassesIsEnabled);
                llvmModule = new LLVMModule("builtin_abc", this, settings.target_triple);
                bool failed = llvmModule->initializeDefs(llvm::errs());
                AvmAssert(!failed);  // if this was going to fail, it would have failed in the summary module
                (void)failed;
            }
            
            for (int i = 0; i < firstUserPool; ++i) {
                // timings measured in emitPoolToModule
                PoolInfo& poolInfo = *poolInfos[i];
                emitPoolToModule(poolInfo, llvmModule);
            }
            {
                llvm::NamedRegionTimer codeGenTimer("LLVM IR to native", "Compile-abc", llvm::TimePassesIsEnabled);
                llvmModule->emit();
            }
            {
                llvm::NamedRegionTimer codeGenTimer("Finalize Modules", "Compile-abc", llvm::TimePassesIsEnabled);
                delete llvmModule;
            }
        }
        
        //
        // Based on dependency information (not yet) collected during the initial verification pass,
        // determine which of the modules need to be recompiled.
        //
        {
            llvm::NamedRegionTimer codeGenTimer("Determine out-of-date modules", "Compile-abc", llvm::TimePassesIsEnabled);
            for (unsigned i = firstUserPool; i < poolInfos.size(); ++i) {
                // TODO: for now, just mark them all as out-of-date
                poolInfos[i]->outOfDate = true;
            }
        }

        //
        // Emit code for out-of-date user modules.
        //
        
        for (unsigned i = firstUserPool; i < poolInfos.size(); ++i) {
            PoolInfo& poolInfo = *poolInfos[i];
            if (poolInfo.outOfDate) {
                emitPoolToSpilttedModules(poolInfo);
            }
        }
        
        //
        // Emit the summary module that stiches everything together
        //
        {
            llvm::NamedRegionTimer codeGenTimer("Emit Summary Module", "Compile-abc", llvm::TimePassesIsEnabled);
            emitSummaryModule();
        }
        
        //Dump abc statistics
        if(options::perfLog) {
            llvm::raw_ostream &outs = llvm::outs();
            long totalABCSize = 0;
            long nFunctions = 0 ;
            for (unsigned i = firstUserPool, nPoolInfos = poolInfos.size(); i < nPoolInfos; ++i) {
                PoolInfo& poolInfo = *poolInfos[i];
                totalABCSize += poolInfo.totalABCSize;
                for (unsigned j = 0, nMethods = poolInfo.verifyInfos.size(); j < nMethods; ++j) {
                    MethodVerifyInfo& verifyInfo = poolInfo.verifyInfos[i];
                    MethodInfo* method = verifyInfo.method;
                    if (verifyInfo.verifySucceeded && !method->isNative()) {
                        nFunctions++;
                    }
                }
            }
            outs << "\n ------------------- ABC Statistics ------------------- ";
            outs << "\n#PerfLog: Number of ABC Files : " << poolInfos.size() - firstUserPool;
            outs << "\n#PerfLog: Total ABC Size : " << totalABCSize;
            outs << "\n#PerfLog: Number Of Functions : " << nFunctions << "\n\n";
        }

        return exitCode;
    }
    
    void CompilerCore::emitPoolToModule(PoolInfo& poolInfo, LLVMModule* llvmModule)
    {
        {
            llvm::NamedRegionTimer codeGenTimer("Initialize Modules", "Compile-abc", llvm::TimePassesIsEnabled);
            poolInfo.connect(llvmModule);
        }
        
        for (unsigned i = 0; i < poolInfo.verifyInfos.size(); ++i) {
            MethodVerifyInfo& verifyInfo = poolInfo.verifyInfos[i];
            MethodInfo* method = verifyInfo.method;
            if (verifyInfo.verifySucceeded) {
                if (!method->isNative()) {
                    
                    //logging
                    if(options::verbose) {
                        llvm::raw_ostream &outs = llvm::outs();
                        outs << "[" << i+1 << "/" << poolInfo.verifyInfos.size() << "] - " << poolInfo.getFunctionName(method) << "\n";
                    }

                    halfmoon::JitWriter* jit = 0;
                    {
                        llvm::NamedRegionTimer codeGenTimer("ABC to HM IR", "Compile-abc", llvm::TimePassesIsEnabled);
                        jit = new JitWriter(method, compilerToplevel, poolInfo.abc_env);
                        // re-verifying, so clear exception information; it will be recomputed
                        //method->set_abc_exceptions(gc, 0);
                        AvmAssert(method->declaringTraits()->isResolved());
                        MethodSignaturep ms = method->getMethodSignature();
                        AvmAssert(ms != 0);
                        Verifier verifier(method, ms, compilerToplevel, poolInfo.abc_env);
                        verifier.verify(jit);
                    }
                    
                    {

                        llvm::NamedRegionTimer codeGenTimer("HM IR to LLVM IR", "Compile-abc", llvm::TimePassesIsEnabled);
                        LLVMEmitter emitter(method, jit->ir());
                        emitter.emit();
                        
                    }
                    
                    {
                        // Charge deleting the IR to halfmoon
                        llvm::NamedRegionTimer codeGenTimer("ABC to HM IR", "Compile-abc", llvm::TimePassesIsEnabled);
                        delete jit;
                    }
                }
            }
            else if(method->method_id() >= 0 ){ 
                // Method failed to verify
                LLVMEmitter emitter(method, /*ir*/0);
                emitter.emitAsVerifyErrorStub();
            }
        }
        {
            llvm::NamedRegionTimer codeGenTimer("Create AOTInfo", "Compile-abc", llvm::TimePassesIsEnabled);
            poolInfo.createAOTInfo();
            // builtins is the only module that doesn't depend on anything, use that fact
            // to detect the builtin pool, whose module deeds to define the fields checksum
            bool defineFieldsChecksum = poolInfo.dependsOn.size() == 0;
            poolInfo.createFieldsChecksum(fieldsChecksum, defineFieldsChecksum);
            poolInfo.disconnect();
          
          //Delete Pool's resources, speacially one attached to Halfmoon Jit
          mmfx_delete(poolInfo.pool->codeMgr);
          poolInfo.pool->codeMgr = NULL;
        }
    }
    
    //This takes a pool and emits it. If Pool has large no of functions then
    // it is broken into multiple llvm modules and then emits.
    /*Logic for breaking :- We break the function list into chunks on following conditions:
        A) A mdoule should have maximum kMaxFunctionInModule.
        B) If we encounter a very large function, we break both before and after that function.
            Thus this creates a module with only the large function. We don't perform llvm optmization for this function.
            This was done to fix a few bugs related to very large functions. Bug#3913141 Bug#3913137
     */
    
    void CompilerCore::emitPoolToSpilttedModules(PoolInfo& poolInfo)
    {
        unsigned int splitIndex = 0;
        LLVMModule* llvmModule = 0;
        createModule(poolInfo, llvmModule, splitIndex);
        
        bool splitForLargeFn = false;
		for (unsigned i = 0, end = poolInfo.verifyInfos.size(); i < end; ++i) {
            MethodVerifyInfo& verifyInfo = poolInfo.verifyInfos[i];
            MethodInfo* method = verifyInfo.method;
            if (verifyInfo.verifySucceeded) {
                if (!method->isNative()) {

                    if(options::verbose) {
                        llvm::raw_ostream &outs = llvm::outs();
                        outs << "[" << i+1 << "/" << poolInfo.verifyInfos.size() << "] - " << poolInfo.getFunctionName(method) << "\n";
                    }

                    halfmoon::JitWriter* jit = 0;
                    {
                        llvm::NamedRegionTimer codeGenTimer("ABC to HM IR", "Compile-abc", llvm::TimePassesIsEnabled);
                        jit = new JitWriter(method, compilerToplevel, poolInfo.abc_env);
                        // re-verifying, so clear exception information; it will be recomputed
                        //method->set_abc_exceptions(gc, 0);
                        AvmAssert(method->declaringTraits()->isResolved());
                        MethodSignaturep ms = method->getMethodSignature();
                        AvmAssert(ms != 0);
                        Verifier verifier(method, ms, compilerToplevel, poolInfo.abc_env);
                        verifier.verify(jit);
                    }
                    
                    {
                        int size = jit->ir()->size();
                        
                        //BREAK if your current function size exceeds the threshold.
                        if(size > kLargeFunctionThreshold)
                        {
                            if(llvmModule->getFunctionCount() != 0)   //Not the first function in the current module
                            {
                                //This creates a module with whatever functions were processed before the large function.
                                //We will not create this module in case our large function is the first function in the current module.
                                poolInfo.disconnect();
                                emitModule(llvmModule);
                                createModule(poolInfo, llvmModule, ++splitIndex);
                            }
                    
                            llvmModule->disableOptimizeModule();
                            splitForLargeFn = true;
                            
                        }
                    }
                    {
                        llvm::NamedRegionTimer codeGenTimer("HM IR to LLVM IR", "Compile-abc", llvm::TimePassesIsEnabled);
                        LLVMEmitter emitter(method, jit->ir());
                        emitter.emit();
                    }
                    
                    {
                        // Charge deleting the IR to halfmoon
                        llvm::NamedRegionTimer codeGenTimer("ABC to HM IR", "Compile-abc", llvm::TimePassesIsEnabled);
                        delete jit;
                    }
                }
            }
            else if(method->method_id() >= 0 ){
                // Method failed to verify
                LLVMEmitter emitter(method, /*ir*/0);
                emitter.emitAsVerifyErrorStub();
            }
            //Dump AOTInfo in separate module ( include i == end-1 case also)
            if (i == end-1 || llvmModule->getFunctionCount() == kMaxFunctionInModule || splitForLargeFn) {
                poolInfo.disconnect();
                emitModule(llvmModule);
                createModule(poolInfo, llvmModule, ++splitIndex);
                splitForLargeFn = false;
             }
        }
        {
            llvm::NamedRegionTimer codeGenTimer("Create AOTInfo", "Compile-abc", llvm::TimePassesIsEnabled);
            poolInfo.createAOTInfo();
        }
        
        // builtins is the only module that doesn't depend on anything, use that fact
        // to detect the builtin pool, whose module deeds to define the fields checksum
        bool defineFieldsChecksum = poolInfo.dependsOn.size() == 0;
        poolInfo.createFieldsChecksum(fieldsChecksum, defineFieldsChecksum);
        poolInfo.disconnect();
        emitModule(llvmModule);
            mmfx_delete(poolInfo.pool->codeMgr);
        poolInfo.pool->codeMgr = NULL;
        gc->Collect();
        
    }
    
    void CompilerCore::createModule(PoolInfo& poolInfo, LLVMModule*& llvmModule, int splitIndex)
    {
        
        llvm::NamedRegionTimer codeGenTimer("Initialize Modules", "Compile-abc", llvm::TimePassesIsEnabled);
        llvmModule = new LLVMModule(poolInfo.infoName, this, settings.target_triple,splitIndex);
        bool failed = llvmModule->initializeDefs(llvm::errs());
        AvmAssert(!failed);  // if this was going to fail, it would have failed in the summary module
        (void)failed;
        poolInfo.connect(llvmModule);
        
    }

    void CompilerCore::emitModule(LLVMModule* llvmModule)
    {
        //Release some memory
        gc->Collect();

        {
            llvm::NamedRegionTimer codeGenTimer("LLVM IR to native", "Compile-abc", llvm::TimePassesIsEnabled);
            if(llvm::llvm_is_multithreaded())
            {
                threadPool.enqueueJob(new CompilationJob(llvmModule));
            }
            else
            {
                CompilationJob* job = new CompilationJob(llvmModule);
                job->handler();
                delete job;
            }
        }
    }
    
    void parseOptions(int argc, char** argv)
    {
        llvm::cl::SetVersionPrinter(options::printVersion);
        bool enableResponseFile = true;
        llvm::cl::ParseCommandLineOptions(argc, argv, "avm static compiler");
        llvm::cl::ParseEnvironmentOptions(argv[0], "COMPILE_AOT_OPTIONS");
    }
    
    //Function to emit just the g_com_adobe_air_fre_fmap with all the function pointers
    //output will be extensionglue.o in current dir.
    //This function is inspired from emitSummaryModule
    void emitANEMap(int argc, char** argv)
    {
        llvm::llvm_shutdown_obj auto_shutdown;
        llvm::NamedRegionTimer codeGenTimer("Total Time ANE MAP", "AOT Compiler Command", llvm::TimePassesIsEnabled);
        {
            llvm::NamedRegionTimer LLVMInitTimer("Initialize LLVM", "Compile-abc", llvm::TimePassesIsEnabled);
            llvm::InitializeAllTargetInfos();
            llvm::InitializeAllTargets();
            llvm::InitializeAllTargetMCs();
            llvm::InitializeAllAsmPrinters();
        }
        
        LLVMModuleBase *lModule = new LLVMModuleBase("extensionglue",llvm::Triple::normalize(options::targetTriple.c_str()));
        LLVMModuleBase& module = *lModule;
     
        const bool isConst = true;
        llvm::Constant* const unInitialized = 0;
        llvm::Type* int32Ty = llvm::Type::getInt32Ty(module.getContext());
        llvm::Type* int8Ty = llvm::Type::getInt8Ty(module.getContext());
        llvm::Type* elementTypes[] = { int8Ty->getPointerTo(), module.functionPtrTy };
        llvm::StructType* nameToFunctionStructTy = llvm::StructType::create(llvm::ArrayRef<llvm::Type*>(elementTypes), "NameToFunction");
        
        std::vector<llvm::Constant*> entries;
        for (unsigned i = 0; i < options::exportedSym.size(); ++i) {
            std::string& funcName = options::exportedSym[i];
            llvm::Constant* nameConst = llvm::ConstantDataArray::getString(
                                                                           module.getContext(), funcName);
            llvm::GlobalVariable* nameVar = new llvm::GlobalVariable(module,
                                                                     nameConst->getType(), isConst, llvm::GlobalValue::InternalLinkage, nameConst, funcName+"_str");
            llvm::Constant* func = module.getOrInsertFunction(funcName, llvm::cast<llvm::FunctionType>(module.functionTy));
            llvm::Constant* indices[] = {
                llvm::ConstantInt::get(int32Ty, 0),
                llvm::ConstantInt::get(int32Ty, 0) };
            llvm::Constant* nameCharPtrConst = llvm::ConstantExpr::getGetElementPtr(nameVar, indices);
            llvm::Constant* members[] = { nameCharPtrConst, func };
            llvm::Constant* element = llvm::ConstantStruct::get(
                                                                nameToFunctionStructTy, llvm::ArrayRef<llvm::Constant*>(members));
            entries.push_back(element);
        }
        entries.push_back(llvm::Constant::getNullValue(nameToFunctionStructTy));
        llvm::Constant* nameToFunctionArrayConst = llvm::ConstantArray::get(llvm::ArrayType::get(nameToFunctionStructTy, entries.size()), entries);
        llvm::GlobalVariable* aneMap = new llvm::GlobalVariable(module,
                                                                nameToFunctionArrayConst->getType(), isConst, llvm::GlobalValue::ExternalLinkage,
                                                                nameToFunctionArrayConst, "g_com_adobe_air_fre_fmap");
        (void)aneMap; // unused
        
        verifyModule(module);
        
        module.emit();
    }
    
    void CompilerCore::emitSummaryModule()
    {
        LLVMModule& module = *summaryModule;
        const bool isConst = true;
        llvm::Constant* const unInitialized = 0;
        llvm::Type* int32Ty = llvm::Type::getInt32Ty(module.getContext());
        llvm::Type* int8Ty = llvm::Type::getInt8Ty(module.getContext());
        
        // Create AOTInfos array
        std::vector<llvm::Constant*> aotInfoConstants;
        for (unsigned i = firstUserPool; i < poolInfos.size(); ++i) {
            std::string& infoName = poolInfos[i]->infoName;
            llvm::GlobalVariable* gvar = new llvm::GlobalVariable(module, module.aotInfoTy, isConst,
                llvm::GlobalVariable::ExternalLinkage, unInitialized, infoName + aotInfoSuffix);
            aotInfoConstants.push_back(gvar);
        }
            
        llvm::Constant* aotInfosConstantArray = llvm::ConstantArray::get(
            llvm::ArrayType::get(module.aotInfoPtrTy, aotInfoConstants.size()), aotInfoConstants);

        llvm::GlobalVariable* aotInfos = new llvm::GlobalVariable(module,
            aotInfosConstantArray->getType(), isConst, llvm::GlobalValue::ExternalLinkage,
            aotInfosConstantArray, "aotInfos");
        (void)aotInfos; // unused
        
        llvm::GlobalVariable* nAotInfos = new llvm::GlobalVariable(module,
            llvm::Type::getInt32Ty(module.getContext()), isConst, llvm::GlobalValue::ExternalLinkage,
                llvm::ConstantInt::get(int32Ty, aotInfoConstants.size()), "nAOTInfos");
        (void)nAotInfos; // unused
        
        llvm::GlobalVariable* g_aotSamplerEnabled = new llvm::GlobalVariable(module,
            llvm::Type::getInt32Ty(module.getContext()), isConst, llvm::GlobalValue::ExternalLinkage,
                llvm::ConstantInt::get(int32Ty, settings.telemetry_sampler? 1:0 ), "g_aotSamplerEnabled");
        (void)g_aotSamplerEnabled; // unused
        
        // Create the ANE name->function table
        llvm::Type* elementTypes[] = { int8Ty->getPointerTo(), module.functionPtrTy };
        llvm::StructType* nameToFunctionStructTy = llvm::StructType::create(llvm::ArrayRef<llvm::Type*>(elementTypes), "NameToFunction");
        
        std::vector<llvm::Constant*> entries;
        for (unsigned i = 0; i < options::exportedSym.size(); ++i) {
            std::string& funcName = options::exportedSym[i];
            llvm::Constant* nameConst = llvm::ConstantDataArray::getString(
                module.getContext(), funcName);
            llvm::GlobalVariable* nameVar = new llvm::GlobalVariable(module,
                nameConst->getType(), isConst, llvm::GlobalValue::InternalLinkage, nameConst, funcName+"_str");
            llvm::Constant* func = module.getOrInsertFunction(funcName, llvm::cast<llvm::FunctionType>(module.functionTy));
            llvm::Constant* indices[] = {
                llvm::ConstantInt::get(int32Ty, 0),
                llvm::ConstantInt::get(int32Ty, 0) };
            llvm::Constant* nameCharPtrConst = llvm::ConstantExpr::getGetElementPtr(nameVar, indices);
            llvm::Constant* members[] = { nameCharPtrConst, func };
            llvm::Constant* element = llvm::ConstantStruct::get(
                nameToFunctionStructTy, llvm::ArrayRef<llvm::Constant*>(members));
            entries.push_back(element);
        }
        entries.push_back(llvm::Constant::getNullValue(nameToFunctionStructTy));
        llvm::Constant* nameToFunctionArrayConst = llvm::ConstantArray::get(llvm::ArrayType::get(nameToFunctionStructTy, entries.size()), entries);
        llvm::GlobalVariable* aneMap = new llvm::GlobalVariable(module,
            nameToFunctionArrayConst->getType(), isConst, llvm::GlobalValue::ExternalLinkage,
            nameToFunctionArrayConst, "g_com_adobe_air_fre_fmap");
        (void)aneMap; // unused

        
        if(llvm::llvm_is_multithreaded())
        {
            threadPool.enqueueJob(new CompilationJob(summaryModule));
        }
        else
        {
            CompilationJob* job = new CompilationJob(summaryModule);
            job->handler();
            delete job;
        }
    }
    
    Toplevel* CompilerCore::createToplevel(AbcEnv* abcEnv)
    {
        return new (gc, MMgc::kExact) CompilerToplevel(abcEnv);
    }
    
    ApiVersion CompilerCore::getDefaultAPI()
    {
        return kApiVersionLatest[kApiVersionSeries_AIR];
    }
    
    void CompilerCore::interrupt(Toplevel*, AvmCore::InterruptReason)
    {
    }
    
    void CompilerCore::stackOverflow(Toplevel*)
    {
    }

    int CompilerCore::evaluateFile(const std::string& fileName, PoolInfo& poolInfo, avmplus::CodeContext* codeContext)
    {
        llvm::raw_ostream &errs = llvm::errs();
        
        // all files depend on the builtins
        poolInfo.addDependency(builtinPoolInfo);
        
        FILE *f = fopen(fileName.c_str(), "rb");
        if (!f) {
            errs << "cannot open file: " << fileName << "\n";
            return EXIT_CODE_BADFILE;
        }
        fseek(f, 0, SEEK_END);
        int size = ftell(f);
        rewind(f);
        
        // parse new bytecode
        ScriptBuffer code = newScriptBuffer((size_t)size);
        int readLen = fread(code.getBuffer(), 1, size, f);
        if (readLen != size) {
            errs << "read error: " << fileName << "\n";
            return EXIT_CODE_BADFILE;
        }
        fclose(f);
        
        currentlyParsing = &poolInfo;
        TRY(this, kCatchAction_ReportAsError)
        {
            poolInfo.setAbcData(code.getBuffer(), code.getSize());
            handleActionBlock(code, 0, compilerToplevel, NULL, codeContext, getDefaultAPI());
        }
        CATCH(Exception *exception)
        {
            // Can get verify errors here if the file doesn't parse.
            (void)exception;
            errs << fileName << ":\n" << StUTF8String(string(exception->atom)).c_str() << "\n";
            return EXIT_CODE_BADFILE;
        }
        END_CATCH
        END_TRY
        currentlyParsing = 0;
        
        return EXIT_CODE_SUCCESS;
    }
}

namespace avmplus
{
    Isolate* Isolate::newIsolate(int32_t, int32_t, Aggregate*)
    {
        return 0;
    }
    
    /*static*/
	bool MutexClass::getMutexSupported (GCRef<avmplus::Toplevel>)
	{
		return false;
	}

}

namespace halfmoon {
    bool AOTIsDebugMode()
    {
        return compile_abc::options::as3Debugger;
    }
}

int main(int argc, char *argv[])
{
  //Since compile-abc is run through adt. In case of failure,simply quit.
  //Without showing error dialog
#ifdef AVMPLUS_WIN32
   	DWORD dwMode = SetErrorMode(SEM_NOGPFAULTERRORBOX);
	SetErrorMode(dwMode | SEM_NOGPFAULTERRORBOX);
#endif
    llvm::sys::PrintStackTraceOnErrorSignal();
    llvm::PrettyStackTraceProgram X(argc, argv);
    compile_abc::parseOptions(argc,argv);
    int code =0;
    if (compile_abc::options::emitANEFnMap) {
         compile_abc::emitANEMap(argc,argv);
    }
    else
    {
        code = compile_abc::CompilerCore::run(argc, argv);
    }
    
    return code;
}

