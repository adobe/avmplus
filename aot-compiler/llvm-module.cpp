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
// Captures information that spans the compilation of a single module.
//
// Each module generates a single object file. Each module has an LLVMContext and llvm::Module
// (actually, it extends these classes--perhaps just a bit too cleverly). The Module/Context is
// then populated with class definitions supplied by the fields parameter then it captures pointers
// to the specific StructInfo, FieldInfo, and llvm Types that are frequently used.
//
// In LLVM everything in the IR ultimately hangs off of the Context and the Context is the unit of
// concurrency: everything in a contect (that is, each entire object graph) must be accessed by a
// single thread at a time. However different graphs can be accessed in different threads.
//
// Because each ABC file can depend on things in prior ABC files and since halfmoon is single-threaded,
// the ABC parsing, verifying, and LLVM IR generation must be sequential and might as well be on the
// main thread. However the optimization and code generation phases can be parallelized on separate
// threads. Experience has shown that those are likely to be the long-poles in overall compile latency
// (the regster allocator in particular is problematic.)
//
// TODO: run code generation phases in background threads!
//

#include "avmplus.h"

#ifdef VMCFG_HALFMOON

#include "llvm-module.h"
#include "compileabc.h"
#include "llvm-emitter.h"
#include "poolinfo.h"

#include "llvm/Linker/Linker.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/TargetRegistry.h"
#undef DEBUG  // "llvm/Support/Debug.h" defines DEBUG! No, seriouusly!
#include "llvm/Support/Debug.h" // llvm::dbgs()
#include "llvm/Support/Timer.h"
#include "llvm/Support/ToolOutputFile.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/IR/LegacyPassNameParser.h"
#include "llvm/Transforms/IPO.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Bitcode/ReaderWriter.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Target/TargetLibraryInfo.h"


#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>

namespace compile_abc
{
using namespace avmplus;

namespace options {
    using namespace llvm;
    using std::string;
        
    static cl::opt<char> optLevel("O", cl::Prefix, cl::init('2'),
        cl::desc("Optimization level [-O0, -O1, -O2, or -O3] (default = '-O2')"));
    static cl::opt<bool> saveRawBitcode("save-raw-bitcode", cl::desc("save bitcode files before any optimizations"), cl::init(false));
    static cl::opt<bool> saveBitcode("save-bitcode", cl::desc("save bitcode files"), cl::init(false));
    static cl::opt<bool> saveRawLL("save-raw-ll", cl::desc("save pre-optimization llvm bitcode assembly"), cl::init(false));
    static cl::opt<bool> saveLL("save-ll", cl::desc("save llvm bitcode assembly"), cl::init(false));
    static cl::opt<bool> noVerify("no-verify", cl::desc("Don't run bitcode verification"), cl::init(false));
    static cl::opt<bool> printLLIR("print-llir", cl::desc("Print LLVM IR"), cl::init(false));
    enum EmitVal { EMIT_ASM, EMIT_OBJ, EMIT_LL, EMIT_NONE };
    static cl::opt<EmitVal> codeGenType("filetype", cl::init(EMIT_OBJ),
        cl::desc("output file type:"),
        cl::values(
            clEnumValN(EMIT_ASM, "asm", "Emit assembly files"),
            clEnumValN(EMIT_OBJ, "obj", "Emit object files"),
            clEnumValN(EMIT_LL, "bitcode", "Emit bitcode files"),
            clEnumValN(EMIT_NONE, "null", "Emit nothing"),
            clEnumValEnd));
    static cl::opt<bool> globalOpt("global-opt", cl::desc("enable global optimizations"), cl::init(false));
    static cl::opt<bool> noInline("disable-inlining", cl::desc("disable inlining"), cl::init(false));
    static cl::list<const PassInfo*, bool, PassNameParser> optimizations(cl::desc("Optimizations available:"));
    static cl::opt<bool> disableCFI("disable-cfi", cl::Hidden, cl::init(true), cl::desc("Do not use .cfi_* directives"));
    static cl::opt<bool> debugSlots("debug-slots", cl::Hidden, cl::desc("display information useful for debugging slot issues"));
}

//These flags are counterpart of Traits.cpp: finishSlotsAndMethods flags. Following function ( LLVMModule::getSlotLayout )
//    represent compile time version of Traits.cpp::finishSlotsAndMethods() and should always have same logic for slot layout.
//By default setting  false fro 32 bit and true on 64 bit ( behaviour on Mac )
namespace
{
#ifdef AVMPLUS_64BIT
	static bool align8ByteSlots = true;
	static bool alignPointersTo8Bytes = true;
#else
	static bool align8ByteSlots = false;
	static bool alignPointersTo8Bytes = false;
#endif
}


    LLVMModuleBase::LLVMModuleBase(const llvm::StringRef name,const std::string& targetTripleArg, int splitIndex)
    : llvm::Module(name, *static_cast<llvm::LLVMContext*>(this))
    , targetTriple(targetTripleArg)
    , splitIndex(splitIndex)
    , optimizeModule(true)
    , functionCount(0)
    {
        setTargetTriple(targetTripleArg);
		//Set Slot alignment based on target triple
		//TODO: don't know how to make it generic. Currently handling only for iOS. 
		llvm::Triple triple(getTargetTriple());
		if (triple.isiOS()){
			if (triple.isArch32Bit()){
				align8ByteSlots = false;
				alignPointersTo8Bytes = false;
			}
			else if (triple.isArch64Bit()){
				align8ByteSlots = true;
				alignPointersTo8Bytes = true;
			}
		}

#ifdef AVMPLUS_64BIT
        ptrSizedIntTy = llvm::Type::getInt64Ty(getContext());
#else
        ptrSizedIntTy = llvm::Type::getInt32Ty(getContext());
#endif
        functionTy = llvm::FunctionType::get(ptrSizedIntTy, /*isVarArg*/true);
        functionPtrTy = functionTy->getPointerTo();

        {
            // TODO: this is just to fetch the TargetData for computing offsets.
            // In LLVM3.2+ we should be able to use DataLayout instead.
            std::string err, cpu(""), features("");
            llvm::TargetOptions options;
            const llvm::Target* target = llvm::TargetRegistry::lookupTarget(targetTriple, err);
            targetMachineForLayout = target->createTargetMachine(targetTriple, cpu, features, options);
            //AvmAssert(targetMachineForLayout->getTargetData() != NULL);
        }
        
    }
    LLVMModuleBase::~LLVMModuleBase() {
        if(targetMachineForLayout)
            delete targetMachineForLayout;
    }
    
    bool LLVMModuleBase::emit()
    {
        
        std::string errStr;
        std::ostringstream basename;
        basename << getModuleIdentifier();
        if(splitIndex > 0)
            basename << "_" << splitIndex;
        llvm::Triple triple(getTargetTriple());
        bool winExtns = triple.getOS() == llvm::Triple::Win32;
        
        if (options::saveRawLL) {
            std::string nm = basename.str() + "-raw.ll";
            llvm::tool_output_file llOut(nm.c_str(), errStr,llvm::sys::fs::F_None);
            if (!errStr.empty()) {
                llvm::errs() << errStr << "\n";
                return 1;
            }
            print(llOut.os(), 0);
            llOut.keep();
        }
        
        if (options::saveRawBitcode) {
            // save raw bitcode (before any optimizations that may occur below)
            std::string nm = basename.str() + "-raw.bc";
            llvm::tool_output_file bcOut(nm.c_str(), errStr, llvm::sys::fs::F_None);
            if (!errStr.empty()) {
                llvm::errs() << errStr << "\n";
                return 1;
            }
            llvm::WriteBitcodeToFile(this, bcOut.os());
            bcOut.keep();
        }
        
        const llvm::Target* target = llvm::TargetRegistry::lookupTarget(targetTriple, errStr);
        AvmAssert(target != NULL);
        
        llvm::CodeGenOpt::Level optLevel = llvm::CodeGenOpt::Default;
        if(optimizeModule) {
            switch (options::optLevel) {
                case ' ': break;
                case '0': optLevel = llvm::CodeGenOpt::None; break;
                case '1': optLevel = llvm::CodeGenOpt::Less; break;
                case '2': optLevel = llvm::CodeGenOpt::Default; break;
                case '3': optLevel = llvm::CodeGenOpt::Aggressive; break;
                default:
                    llvm::errs() << "invalid optimization level\n";
                    return true;
            }
        }else {
            optLevel = llvm::CodeGenOpt::None;
        }
        
        // TODO: Audit these settings
        //   (Some may depend on the target and ABI)
        llvm::TargetOptions targetOptions;
        targetOptions.LessPreciseFPMADOption = false;
        targetOptions.PrintMachineCode = false;
        targetOptions.NoFramePointerElim = false;
        //targetOptions.NoFramePointerElimNonLeaf = true;  // TODO: revisit this
        //targetOptions.NoExcessFPPrecision = true;   // ActionScript requires IEEE FP semantics
        targetOptions.UnsafeFPMath = false;
        targetOptions.NoInfsFPMath = false;
        targetOptions.NoNaNsFPMath = false;
        targetOptions.HonorSignDependentRoundingFPMathOption = false;
        targetOptions.UseSoftFloat = false;
        targetOptions.NoZerosInBSS = false;
        targetOptions.GuaranteedTailCallOpt = false;
        targetOptions.DisableTailCalls = false;
        //targetOptions.RealignStack = true;
        //targetOptions.DisableJumpTables = false;
        targetOptions.PositionIndependentExecutable = false;
        //targetOptions.EnableSegmentedStacks = false;
        
        
        std::string cpu("");
        std::string features("");
        llvm::Reloc::Model relocModel = llvm::Reloc::Default;
        llvm::CodeModel::Model codeModel = llvm::CodeModel::Default;
       
        std::unique_ptr<llvm::TargetMachine> targetMachine(target->createTargetMachine(
                                                                                       targetTriple, cpu, features, targetOptions,
                                                                                       relocModel, codeModel, optLevel));
        AvmAssert(targetMachine.get() != NULL);
        
        // TODO_WP81 - revisit
        // Windows linker requires function level linking, fails otherwise.
        if(winExtns)
        {
            targetMachine->setFunctionSections(true);
            targetMachine->setDataSections(true);
        }
        
        llvm::PassManager passManager;
       
        if (const llvm::DataLayout *DL = targetMachine->getDataLayout())
        {
            setDataLayout(DL);
            passManager.add(new llvm::DataLayoutPass(*DL));
        }
        else
        {
            passManager.add(new llvm::DataLayoutPass(this));
        }
        
        
        targetMachine->setAsmVerbosityDefault(true);
        //if (options::disableCFI)
        //   targetMachine->setMCUseCFI(false);
        
        passManager.add(llvm::createGlobalDCEPass());
        passManager.add(llvm::createAggressiveDCEPass());
        
        if(optimizeModule && options::optLevel > '0' ) {
            llvm::PassManagerBuilder builder;
            llvm::FunctionPassManager fpm(this);
           
            if (const llvm::DataLayout *DL = targetMachine->getDataLayout()) {
                setDataLayout(DL);
                fpm.add(new llvm::DataLayoutPass(*DL));
            }
            else // Otherwise, construct from TargetData. Why? Because LLC does.
                fpm.add(new llvm::DataLayoutPass(this));
            
            if (options::noInline) {
                // No inlining pass
            } else {
                unsigned Threshold = (options::optLevel > '2')? 300: 200;
                builder.Inliner = llvm::createFunctionInliningPass(Threshold);
            }
            builder.OptLevel = 1;//for opt > 1, llvm adds more passes and shell tests starts failing.
            builder.SizeLevel = 0;
            builder.DisableUnitAtATime = false;
            builder.DisableUnrollLoops = options::optLevel == '0';
            //builder.DisableSimplifyLibCalls = true;
            builder.populateFunctionPassManager(fpm);
            builder.populateModulePassManager(passManager);
            
            fpm.doInitialization();
            for (Module::iterator F = this->begin(), E = this->end(); F != E; ++F)
                fpm.run(*F);
            fpm.doFinalization();
        }
        
        //llvm::OwningPtr<llvm::tool_output_file> toolOut;
        //llvm::OwningPtr<llvm::formatted_raw_ostream> toolOstream;
        std::unique_ptr<llvm::tool_output_file> toolOut;
        std::unique_ptr<llvm::formatted_raw_ostream> toolOstream;
        switch (options::codeGenType) {
            case options::EMIT_ASM: {
                std::string outf(basename.str() + (winExtns ? ".asm" : ".s"));
                toolOut.reset(new llvm::tool_output_file(outf.c_str(), errStr, llvm::sys::fs::F_None));
                toolOstream.reset(new llvm::formatted_raw_ostream(toolOut->os()));
                bool failed = targetMachine->addPassesToEmitFile(passManager, *toolOstream, llvm::TargetMachine::CGFT_AssemblyFile, options::noVerify);
                AvmAssert(!failed);
                (void)failed; // unused in release builds
                break;
            }
            case options::EMIT_OBJ: {
                std::string outf(basename.str() + (winExtns ? ".obj" : ".o"));
                toolOut.reset(new llvm::tool_output_file(outf.c_str(), errStr, llvm::sys::fs::F_None));
                toolOstream.reset(new llvm::formatted_raw_ostream(toolOut->os()));
                bool failed = targetMachine->addPassesToEmitFile(passManager, *toolOstream, llvm::TargetMachine:: CGFT_ObjectFile, options::noVerify);
                AvmAssert(!failed);
                (void)failed; // unused in release builds
                break;
            }
            default: {
                if (!options::noVerify)
                    passManager.add(llvm::createVerifierPass());
            }
        }
        
        {
            passManager.run(*this);
        }
        
        if (toolOut)
            toolOut->keep();
        
        if (options::saveBitcode || options::codeGenType == options::EMIT_LL) {
            std::string nm = basename.str() + ".bc";
            llvm::tool_output_file bcOut(nm.c_str(), errStr, llvm::sys::fs::F_None);
            if (!errStr.empty()) {
                llvm::errs() << errStr << "\n";
                return 1;
            }
            llvm::WriteBitcodeToFile(this, bcOut.os());
            bcOut.keep();
        }
        
        if (options::saveLL) {
            std::string nm = basename.str() + ".ll";
            llvm::tool_output_file llOut(nm.c_str(), errStr, llvm::sys::fs::F_None);
            if (!errStr.empty()) {
                llvm::errs() << errStr << "\n";
                return 1;
            }
            print(llOut.os(), 0);
            llOut.keep();
        }
        
        
        return false;
    }
    

    
LLVMModule::LLVMModule(const llvm::StringRef name, CompilerCore* core, const std::string& targetTripleArg,int splitIndex)
: LLVMModuleBase(name,targetTripleArg,splitIndex)
, core(core)
{
    printLLIR = options::printLLIR;
    
    genericPtrTy = llvm::Type::getInt8PtrTy(getContext());
    atomTy = ptrSizedIntTy;
    atomPtrTy = atomTy->getPointerTo();
    argTy = llvm::Type::getInt64Ty(getContext());
    argPtrTy = atomTy->getPointerTo();
    
    classClosurePtrTy = llvm::cast<llvm::PointerType>(llvmType("*'avmplus::ClassClosure'"));
    namespacePtrTy = llvm::cast<llvm::PointerType>(llvmType("*'avmplus::Namespace'"));
    multinamePtrTy = llvm::cast<llvm::PointerType>(llvmType("*'avmplus::Multiname'"));
    
    arrayObjectPtrTy = llvm::cast<llvm::PointerType>(llvmType("*'avmplus::ArrayObject'"));
    intVectorObjectPtrTy = llvm::cast<llvm::PointerType>(llvmType("*'avmplus::IntVectorObject'"));
    uIntVectorObjectPtrTy = llvm::cast<llvm::PointerType>(llvmType("*'avmplus::UIntVectorObject'"));
    doubleVectorObjectPtrTy = llvm::cast<llvm::PointerType>(llvmType("*'avmplus::DoubleVectorObject'"));
    
    fn_acalli = llvmFunctionType("a;*'avmplus::MethodEnv';i;*c")->getPointerTo();
    fn_ocalli = llvmFunctionType("*'avmplus::ScriptObject';*'avmplus::MethodEnv';i;*c")->getPointerTo();
    fn_ncalli = llvmFunctionType("*'avmplus::Namespace';*'avmplus::MethodEnv';i;*c")->getPointerTo();
    fn_scalli = llvmFunctionType("*'avmplus::String';*'avmplus::MethodEnv';i;*c")->getPointerTo();
    fn_icalli = llvmFunctionType("i;*'avmplus::MethodEnv';i;*c")->getPointerTo();
    fn_dcalli = llvmFunctionType("d;*'avmplus::MethodEnv';i;*c")->getPointerTo();
}
    
LLVMModule::~LLVMModule() {
}
    
bool LLVMModule::initializeDefs(llvm::raw_ostream &err)
{
    if (initializeFieldInfos(err))
        return true;
    
    // TODO: As of LLVM 3.1, this sort of TLS is not supported for mach-o:
    // 
    // ARMTargetLowering::LowerGlobalTLSAddress(SDValue Op, SelectionDAG &DAG) const {
    //    // TODO: implement the "local dynamic" model
    //    AvmAssert(Subtarget->isTargetELF() &&
    //           "TLS not implemented for non-ELF targets");
    //
    // So for now, this isn't really TLS and it's not really important until we support
    // concurreanct anyway.
    
    bool useGeneralDynamicTLSModel = false;  // TODO: should be true

    return false;
}
    
llvm::Type* LLVMModule::llvmType(ModelKind modelKind)
{
    switch (modelKind) {
    default:
        AvmAssert(false && "bad model");
    case kModelAtom:
        return ptrSizedIntTy;
    case kModelScriptObject:
        return scriptObjectPtrTy;
    case kModelString:
        return stringPtrTy;
    case kModelNamespace:
        return namespacePtrTy;
    case kModelInt:
        return llvm::Type::getInt32Ty(getContext());
    case kModelDouble:
        return llvm::Type::getDoubleTy(getContext());
    }
}

void LLVMModule::disableOptimizeModule()
{
    optimizeModule = false;
}
    
unsigned int LLVMModule::getFunctionCount()
{
    return functionCount;
}
void LLVMModule::incrementFunctionCount()
{
    functionCount++;
}

llvm::Type* LLVMModule::llvmType(Traits* traits)
{
    return llvmType(defaultModelKind(traits));
}

//
// In retrospect, this was a mistake and I should have used the llvm assembler's type parser. [stan 12/13/12]
//
// Govindag[08/11/14] Now the format is (operator)n(type) operator could be pointer(*) or Array [number]
// operator works as prefix notation. 
llvm::Type* LLVMModule::parseLlvmType(const char*& cursor, bool noAssert)
{
    llvm::Type* type = NULL;
    switch (*cursor++)
    {
        case '*': // Pointer to type ahead
            type = parseLlvmType(cursor, noAssert)->getPointerTo();
            break;
        case '\'':
        {
            const char* symStart = cursor;
            while (*cursor != 0 && *cursor != '\'')
                ++cursor;
            if (*cursor == '\'') {
                llvm::StringRef name(symStart, cursor-symStart);
                ++cursor;
                if (name.equals("BoolKind")) {   // oops, this is an enum type, represented as int32
                    type = llvm::Type::getInt32Ty(getContext());
                    break;
                }
                type = getTypeByName(name);
                if (!type) {
                    type = llvm::StructType::create(getContext(), name);
                    if (printLLIR) {
                        type->dump();
                        llvm::dbgs() << "\n";
                    }
                }
            }
        }
            break;
        case '!':
            type = functionPtrTy;
            break;
        case 'c':
            type = llvm::Type::getInt8Ty(getContext());
            break;
        case 's':
            type = llvm::Type::getInt16Ty(getContext());
            break;
        case 'i':
            type = llvm::Type::getInt32Ty(getContext());
            break;
        case 'a':  // Atom
            type = atomTy;
            break;
        case 'x':
            type = llvm::Type::getInt64Ty(getContext());
            break;
        case 'd':
            type = llvm::Type::getDoubleTy(getContext());
            break;
        case 'f':
            type = llvm::Type::getFloatTy(getContext());
            break;
        case 'v':
            type = llvm::Type::getVoidTy(getContext());
            break;
        case '[':  //Array of type ahead
        if (*cursor >= '0' && *cursor <= '9') {
          unsigned aSize = 0;
          while (*cursor >= '0' && *cursor <= '9')
            aSize = aSize*10 + (*cursor++ - '0');
          AvmAssert(noAssert || *cursor == ']');
          type = parseLlvmType(++cursor, noAssert);
          type = llvm::ArrayType::get(type, aSize);
        }else {
          AvmAssert(noAssert || "Only numbers allowed in []");
        }
        break;
    }
    AvmAssert(noAssert || *cursor == 0 || *cursor ==';');
    AvmAssert(noAssert || type != 0);
    return type;
}

llvm::Type* LLVMModule::llvmType(const char* typeDescriptor, bool noAssert)
{
    const char* cursor = typeDescriptor;
    llvm::Type* type = parseLlvmType(cursor, noAssert);
    AvmAssert(noAssert || *cursor == 0);
    return type;
}

/// Return the LLVM data type to use for the given halfmooon Type.
///
llvm::Type* LLVMModule::llvmType(const Type* t)
{
    if (isBottom(t)) {
        return llvm::Type::getVoidTy(getContext());
    }
    if (isDataType(*t)) {
        return llvmType(model(t));
    }
    switch (kind(t)) {
        case kTypeOrdinal:
            return llvm::Type::getInt32Ty(getContext());
        case kTypeEnv:
            return methodEnvPtrTy;
        case kTypeTraits:
            return traitsPtrTy;
        case kTypeName:
            return multinamePtrTy;
        case kTypeMethod:
            return methodInfoPtrTy;
        default:
            return genericPtrTy;
    }
}

llvm::FunctionType* LLVMModule::llvmFunctionType(const char* functionTypeDescriptor)
{
    const char* cursor = functionTypeDescriptor;
    llvm::Type* returnType = parseLlvmType(cursor);
    static unsigned const maxArgs = 50;
    llvm::Type* argTypes[maxArgs];
    unsigned argc = 0;
    while (*cursor == ';' && argc < maxArgs) {
        ++cursor;
        argTypes[argc++] = parseLlvmType(cursor);
    }
    AvmAssert(*cursor == 0);
    llvm::ArrayRef<llvm::Type*> argTypesRef(argTypes, argc);
    return llvm::FunctionType::get(returnType, argTypesRef, /* isVarArg */ false);
}

llvm::FunctionType* LLVMModule::llvmTypeForStubInfo(const StubInfo* stubinfo)
{
    // TODO (stan): cache the LLVM argument types and return types rather than recompouting each time.
    return llvmFunctionType(stubinfo->argDesc);
}

uint32_t LLVMModule::StubInfo::count_args() const
{
    uint32_t argc = 0;
    for (const char* p = argDesc; *p; p++)
        if (*p == ';')
            argc++;
    return argc;
}
        
bool LLVMModule::computeStructLayout(StructInfo& structInfo, llvm::raw_ostream &err)
{
    if (options::debugSlots)
        printf(">> struct %s\n", structInfo.name.c_str());
    
    // Sort the fields by offset
    sort(structInfo.fields.begin(), structInfo.fields.end(), FieldInfo::smallerOffset);
    unsigned pos = 0;
    
    // Go through the fields, creating elements with padding where necessary
    std::vector<llvm::Type*> elements;
    for (unsigned fieldIx = 0; fieldIx < structInfo.fields.size(); ++fieldIx) {
        FieldInfo& field = structInfo.fields[fieldIx];
        field.structInfo = &structInfo;
        if (pos > field.offset) {
            err << "field " << structInfo.name << "." << field.name << " does not fit\n";
            return true;
        }
        AvmAssert(pos <= field.offset);
        
        // Insert padding if necessary
        if (pos < field.offset) {
            unsigned padSize = field.offset - pos;
            llvm::Type* pad = llvm::ArrayType::get(llvm::Type::getInt8Ty(getContext()), padSize);
            elements.push_back(pad);
            pos += padSize;
        }
        
        // Field element
        unsigned size = getTypeSize(field.type);
        field.memberIx = elements.size();
        elements.push_back(field.type);
        pos += size;
        
        // If the field is a slot, index it in the slots vector
        if (field.slot != -1) {
            if (structInfo.slotToField.size() < (unsigned)field.slot+1)
                structInfo.slotToField.resize(field.slot+1, 0);
            structInfo.slotToField[field.slot] = fieldIx;
            // printf(">>> %s %s %d %d\n", structInfo.name.c_str(), field.name.c_str(), field.slot, pos-size);
        }
        if (options::debugSlots)
            printf(">>   field %s %d %d\n", field.name.c_str(), field.slot, field.offset);
    }
    
    // If the structure contains any fields or has a size, instantiate it.
    // (zero-sized structs remain named, anonymous structs)
    if (elements.size() > 0 || structInfo.size > 0) {
        if (pos < structInfo.size) {
            unsigned padSize = structInfo.size - pos;
            llvm::Type* pad = llvm::ArrayType::get(llvm::Type::getInt8Ty(getContext()), padSize);
            elements.push_back(pad);
            pos += padSize;
        }
        structInfo.type->setBody(elements);
        unsigned size = getTypeSize(structInfo.type);
        
        // If we claimed to already know the size, verify that it is correct.
        if (size != structInfo.size && structInfo.size > 0) {
            err << "struct " << structInfo.name << " size is incorrect\n";
            return true;
        }
        structInfo.size = size;
        
        if (options::debugSlots)
            printf(">>   size %d\n", structInfo.size);
    }
    
    if (printLLIR) {
        structInfo.type->dump();
        llvm::dbgs() << "\n";
    }

    return false;
}

static String* getSlotName(const TraitsBindings* tb, unsigned slot)
{
    // It's a pain to go from slot to name; it doesn't come up normally
    StTraitsBindingsIterator iter(tb);
    while (iter.next()) {
        if (!iter.key()) continue;
        Binding b = iter.value();
        if ((AvmCore::bindingKind(b) == BKIND_VAR || AvmCore::bindingKind(b) == BKIND_CONST)
            &&  AvmCore::bindingToSlotId(b) == (int)slot) {
            return iter.key();
            break;
        }
    }
    return 0;
}
    
typedef struct
{
    unsigned slot;
    uint32_t offset;
}SLOT_AND_OFFSET;

static bool slotOffsetCompareFunc (SLOT_AND_OFFSET s1, SLOT_AND_OFFSET s2)
{
    return (s1.offset < s2.offset);
}

StructInfo* LLVMModule::getSlotLayout(Traits* t)
{
    std::map<Traits*, StructInfo*>::iterator it = traitsToStructInfo.find(t);
    if (it != traitsToStructInfo.end())
        return it->second;

    // If there's a base, make sure it's initialized.
    StructInfo *baseStruct = t->base ? getSlotLayout(t->base) : 0;
    
    // Append a new StructInfo
    StructInfo& structInfo = *new StructInfo();
    traitsToStructInfo[t] = &structInfo;
    structInfo.name = traitsName(t);
    
    // This is a new type; create it and ensure that it has a unique name.
    // This comes up for script Traits such as "global".
    if (getTypeByName(structInfo.name)) {
        int i = 0;
        std::ostringstream nm;
        do {
            nm.str("");
            nm << structInfo.name << "_" << ++i;
        } while (getTypeByName(nm.str()));
        structInfo.name = nm.str();
    }
    structInfo.type = llvm::StructType::create(getContext(), structInfo.name);
    structInfos.insertStruct(structInfo.name, &structInfo);
    
    // If there's no base class, then use ScriptObject
    if (!baseStruct)
        baseStruct = scriptObjectStruct;
    
    // Copy up the base object fields
    structInfo.fields = baseStruct->fields;
    unsigned nextSlotOffset = baseStruct->size;
    const TraitsBindings* tb = t->getTraitsBindings();
    structInfo.slotToField.resize(tb->slotCount, 0);
    
    // printf(">>> Slots for %s: %s %d\n", structInfo.name.c_str(),  baseStruct->name.c_str(), nextSlotOffset);
    
    // See if this class has native info
    if (StructInfo* nativeTemplate = core->nativeSlotTemplates.findStruct(structInfo.name)) {
        // Found it. Use field definitions from native class
        for (unsigned i = 0; i < nativeTemplate->fields.size(); ++i) {
            structInfo.fields.push_back(nativeTemplate->fields[i]);
            structInfo.fields.back().type = llvmType(structInfo.fields.back().typedesc.c_str());
        }
        structInfo.size = nativeTemplate->size;
        // Now lay it out as an LLVM struct and return
        computeStructLayout(structInfo, llvm::errs());
        if (options::debugSlots)
            printf(">>   templated-by %s\n", nativeTemplate->name.c_str());
        
        // Dependency on the builtin sdk layout is done once and for all,
        // so no need to do this here:
        //     poolInfo->addDependency(core->builtinPoolInfo);
        return &structInfo;
    }
    
    unsigned firstNewSlot = 0;
    if (t->base) {
        firstNewSlot = t->base->getTraitsBindings()->slotCount;
        // Add a dependency on the base class slot layout
        poolInfo->addDependency(t->base);
    }
    
    // This code is added for bug 3837665
    // It was assumed that the layout always has slots in order of slot ids, for the same slot type. But that's not true.
    // There could be cases when slot 2 is before slot 1 for the same slot type.
    // This happens when abc has entries in that order.
    // To be able to generate the correct order of slots in layout, now ordering the slots by the order of their
    // offset, as it would have been in AVM (tb->getSlotOffset).
    std::vector<SLOT_AND_OFFSET> slots;
    for (unsigned slot = firstNewSlot; slot < tb->slotCount; ++slot)
        slots.push_back({slot,tb->getSlotOffset(slot)});
    std::sort(slots.begin(), slots.end(), slotOffsetCompareFunc);
    
    // Compute the layout of new slots for this class
    // Slots are laid out as by kind. First 32-bit objects, then pointer-sized objects, then 64-bit items
    // TODO: makes target size and alignment assumptions
    // Used alignPointersTo8Bytes,align8ByteSlots for alignment. Same as in Traits.cpp
    bool localAlignPointersTo8Bytes = alignPointersTo8Bytes;
    bool localAlign8ByteSlots = align8ByteSlots;
    
    enum { SLOT_TYPE_32, SLOT_TYPE_PTR, SLOT_TYPE_64, SLOT_TYPE_END };
    for (unsigned slotType = 0; slotType < SLOT_TYPE_END; ++slotType) {
        // for (unsigned slot = firstNewSlot; slot < tb->slotCount; ++slot) {
        for(std::vector<SLOT_AND_OFFSET>::iterator it = slots.begin(); it != slots.end(); ++it) {
            unsigned slot = it->slot;
            Traits* slotTraits = tb->getSlotTraits(slot);
            SlotStorageType sst = valueStorageType(Traits::getBuiltinType(slotTraits));
            unsigned offset = nextSlotOffset;
            switch (sst) {
                case SST_int32:
                case SST_uint32:
                case SST_bool32:
                    if (slotType == SLOT_TYPE_32)
                        nextSlotOffset = offset+4;
                    break;
                case SST_atom:
                case SST_string:
                case SST_namespace:
                case SST_scriptobject:
                    if (slotType == SLOT_TYPE_PTR){
                        if(localAlignPointersTo8Bytes){
                            offset = (offset+7) & ~7;
                            localAlignPointersTo8Bytes = false;
                        }
                        nextSlotOffset = offset+sizeof(uintptr_t);
                    }
                    break;
                    
                case SST_double:
                    if (slotType == SLOT_TYPE_64) {
                        if(localAlign8ByteSlots){
                            offset = (offset+7) & ~7;
                            localAlign8ByteSlots = false;
                        }
                        nextSlotOffset = offset+8;
                    }
                    break;
                default:
                    AvmAssert(!"unexpected slot storage type");
            }
            if (offset != nextSlotOffset) {
                StUTF8String fldName(getSlotName(tb, slot));
                FieldInfo field;
                field.name = fldName.c_str();
                field.structInfo = &structInfo;
                field.slot = slot;
                field.offset = offset;
                field.type = llvmType(slotTraits);
                structInfo.fields.push_back(field);
            }
        }
    }
    if(align8ByteSlots)
        nextSlotOffset = (nextSlotOffset+7) & ~7;
    structInfo.size = nextSlotOffset;  // ensure it's padded to the right size if necessary
    
    // Now lay it out as an LLVM struct
    computeStructLayout(structInfo, llvm::outs());
    
    if (options::debugSlots)
        printf(">>   base %s\n", baseStruct->name.c_str());
    
    return &structInfo;
}

int LLVMModule::getNameSpaceIndex(PoolObject* pool, Namespace* ns)
{
    for (int i = 1, end = (int)pool->constantNsCount; i < end; ++i) {
        if (ns->EqualTo(pool->getNamespace(i))) {
            return i;
        }
    }
    return -1;
}

//
// Similar to Traits::formatClassName, but preserves the $ for class traits and
// handles parameterized traits
//
std::string LLVMModule::traitsName(Traits* traits)
{
    if (!traits)
        return "<null>";
    Multiname qname(traits->ns(), traits->name());
    qname.setQName();
    StringBuffer buffer(traits->core);
    switch(traits->posType())
    {
        //There could be multiple private classes with name. So add module identifier with the traits name
        // Also this issue may arise for protected namespace too. 
        case TRAITSTYPE_CLASS:
        case TRAITSTYPE_INSTANCE:
        case TRAITSTYPE_INTERFACE:
            if(traits->ns()->getType() == Namespace::NS_Private) {
                    buffer << getModuleIdentifier().c_str() << ":" << getNameSpaceIndex(traits->pool,traits->ns());
            }
            else {
              Traits* searchingTraits = traits->itraits? traits->itraits :traits;
              Multiname searchQname(searchingTraits->ns(), searchingTraits->name());
              Traits* searchResult = core->domainMgr()->findTraitsInPoolByMultiname(traits->pool, searchQname);
              AvmAssert(searchResult == NULL || searchResult != (Traits*)BIND_AMBIGUOUS);
              
              // If searchResult != searchingTraits then this is a redefinition of the same class;
              //In that case, Rename the variable with module identifier,so that always the first one is picked.
              if(searchResult != NULL && searchingTraits != searchResult )
                buffer << getModuleIdentifier().c_str() << ":" ;

            }
              
            break;
            
        // Traits that are inherently local to a module.
        // (As opposed to class traits which can be referenced across modules
        // and whose names are qualified by package.)
        case TRAITSTYPE_SCRIPT:
        case TRAITSTYPE_ACTIVATION:
            buffer << getModuleIdentifier().c_str() << ":";
            break;
            
        case TRAITSTYPE_CATCH: {
            PoolObject* pool = traits->pool;
            AvmAssert(poolInfo && poolInfo->pool == pool);  // no use referencing someone else's catch traits
            // Find the method this is a catch traits for
            // TODO: this is rather laborious!
            MethodInfo* method = 0;
            int ix = 0;
            for (int i = 0, end = (int)pool->methodCount(); i < end && method == 0; ++i) {
                MethodInfo* info = pool->getMethodInfo(i);
                if (info->isNative())
                    continue;
                ExceptionHandlerTable* eht = info->abc_exceptions();
                if (!eht)
                    continue;
                for (int j = 0, jend = eht->exception_count; j < jend; ++j) {
                    if (eht->exceptions[j].scopeTraits == traits) {
                        method = info;
                        ix = j;
                        break;
                    }
                }
            }
            AvmAssert(method != 0);
            buffer << poolInfo->getFunctionName(method).c_str() << ":" << ix << ":";
        }
    }
    buffer << qname;
    if (traits->m_paramTraits) {
        buffer << "<" << traitsName(traits->m_paramTraits).c_str() << ">:" << getModuleIdentifier().c_str();
        if(splitIndex)
            buffer << "_" << splitIndex;
    }
    switch(traits->posType())
    {
    case TRAITSTYPE_ACTIVATION: buffer << ":activation"; break;
    case TRAITSTYPE_SCRIPT: buffer << ":script"; break;
    case TRAITSTYPE_CATCH: buffer << ":catch"; break;
    }
    return buffer.c_str();
}

llvm::Value* LLVMModule::getTraitsValue(LLVMEmitter* emitter, Traits* traits)
{
    if(traits)
    {
        std::string name = "traits:" + traitsName(traits);
        if(traits->posType() == TRAITSTYPE_INSTANCE)
            return emitter->getInterfaceTraitsValue(traits);

        if (traits->isInterface())
            return emitter->getInterfaceTraitsValue(traits);

        if(traits->m_paramTraits) // Vector traits
        {
            //Generate call to update global trait varaibale for vectors
            return emitter->GetVectorTraitsValue(traits);
        }

        llvm::Constant* var;
        PoolObject* pool = traits->pool;
        llvm::Type* int32Ty = llvm::Type::getInt32Ty(getContext());
        switch (traits->posType()) {
            case TRAITSTYPE_ACTIVATION: {
                                            AvmAssert(poolInfo && poolInfo->pool == pool);  // no use referencing someone else's activation traits
                                            for (int i = 0, end = (int)pool->methodCount(); i < end; ++i) {
                                                MethodInfo* info = pool->getMethodInfo(i);
                                                if (info->activationTraits() == traits) {
                                                    llvm::Value* res = emitter->getActivationTraitsForMethodInfo(info);
                                                    return res;
                                                }
                                            }
                                        }
            case TRAITSTYPE_SCRIPT: {
                                        AvmAssert(poolInfo && poolInfo->pool == pool);  // no use referencing someone else's activation traits
                                        llvm::Value* res = emitter->generateGetScriptTraitsCall(traits);
                                        return res;
                                    }
            case TRAITSTYPE_CLASS:  {
                                      llvm::Value* res = emitter->generateGetClassTraitsCall(traits);
                                      return res;
                                    }
            case TRAITSTYPE_CATCH:  {
                                      llvm::Value* res = emitter->generateGetCatchTraitsCall(traits);
                                      return res;
                                    }
        }
    }
    else
    {
        // "any" type ("*")
        const char* name = "builtin_traits_any";
        llvm::GlobalVariable *var = llvm::dyn_cast_or_null<llvm::GlobalVariable>(getNamedValue(name));
        if (!var) {
            var = new llvm::GlobalVariable(*this,
                    traitsPtrTy, /*isConst*/ true, llvm::GlobalValue::ExternalLinkage,
                    0, name);
        }
        // underscore at end of name helps distinguish global traits var from the loaded value
        llvm::Value* val = emitter->CreateLoad(var, traitsName(traits) + "_");
        AvmAssert(val->getType() == traitsPtrTy);
        return val;
    }
}

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
llvm::FunctionType* LLVMModule::getFunctionTy(MethodInfo* info)
{
    MethodSignaturep sig = info->getMethodSignature();
    llvm::Type* resultTy = llvmType(sig->returnTraits());
    unsigned nParams = sig->param_count()+1;  // add 1 for "this"
    unsigned cParams = nParams;
    if (info->needRestOrArguments() || info->needArgsArrInMethodSig())
        cParams += 2;
    cParams += 1;  // MethodEnv*;
    std::vector<llvm::Type*> params(cParams);
    unsigned i = 0;
    for (; i < nParams; ++i) {
        params[i] = llvmType(sig->paramTraits(i));
    }
    if (info->needRestOrArguments() || info->needArgsArrInMethodSig()) {
        params[i++] = atomPtrTy;
        params[i++] = llvm::Type::getInt32Ty(getContext());
    }
    params[i++] = methodEnvPtrTy;
    AvmAssert(i == cParams);
    llvm::FunctionType* methodType = llvm::FunctionType::get(resultTy, params, false);
    return methodType;
}


} // end namespace compile_abc

#endif // VMCFG_HALFMOON
