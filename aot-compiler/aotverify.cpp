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

#include "avmplus.h"
#include "aotverify.h"
#include "compileabc.h"
#include "halfmoon/hm-main.h"
#include "llvm/Support/CommandLine.h"

namespace options {
    using namespace llvm;
    using std::string;
    
    static cl::opt<bool> verifyWarnings("verify-warnings", cl::desc("print verify warnings"), cl::init(true));
};

using namespace avmplus;

namespace compile_abc
{
    class AotPass1Writer: public CodeWriter {
    public:
        AotPass1Writer(MethodInfo* method)
        {
            verifyInfo.method = method;
        }
        
        // There is an opportunity to capture lots of information here, but for now we don't
        
        void writePrologue(const FrameState*, const uint8_t*, CodegenDriver*) {}
        void write(const FrameState*, const uint8_t*, AbcOpcode, Traits*) {}
        void writeOp1(const FrameState*, const uint8_t*, AbcOpcode, uint32_t, Traits*) {}
        void writeOp2(const FrameState*, const uint8_t*, AbcOpcode, uint32_t, uint32_t, Traits*) {}
        void writeMethodCall(const FrameState*, const uint8_t*, AbcOpcode, MethodInfo*, uintptr_t, uint32_t, Traits*) {}
        void writeNip(const FrameState*, const uint8_t*, uint32_t) {}
        void writeCheckNull(const FrameState*, uint32_t) {}
        void writeCoerce(const FrameState*, uint32_t, Traits*) {}
        void writeEpilogue(const FrameState*) {}
        void writeBlockStart(const FrameState*) {}
        
        MethodVerifyInfo verifyInfo;
    };

    AOTExecMgr::AOTExecMgr(CompilerCore* core)
    : BaseExecMgr(core)
    , core(core)
    ,propogateArgArrMethodQueue(core->gc, 0)
    ,argArrayPropogationFlag(false)
    {
    }
    
    void AOTExecMgr::notifyAbcPrepared(Toplevel* toplevel, AbcEnv* abcEnv)
    {
        PoolObject* pool = abcEnv->pool();
        PoolInfo& poolInfo = *core->currentlyParsing;
        AvmAssert(poolInfo.abc_env == 0);
        AvmAssert(poolInfo.pool == 0);
        poolInfo.abc_env = abcEnv;
        poolInfo.pool = abcEnv->pool();
        pool->poolInfo = &poolInfo;
        if (core->parseAndVerify)
            verifyPool(toplevel, abcEnv);
    }
    
    void AOTExecMgr::verifyPool(Toplevel* toplevel, AbcEnv* abcEnv)
    {
        PoolObject* pool = abcEnv->pool();
        for (int i=0, n=pool->scriptCount(); i < n; i++)
            enqTraits(pool->getScriptTraits(i));
        verifyEarly(toplevel, abcEnv);
    }
    
    void AOTExecMgr::verifyMethod(MethodInfo* m, Toplevel *toplevel, AbcEnv* abc_env)
    {
        AvmAssert(m->declaringTraits()->isResolved());
        m->resolveSignature(toplevel);
        PERFM_NTPROF_BEGIN("verify-ticks");
        MethodSignaturep ms = m->getMethodSignature();
        if (m->isNative())
            verifyNative(m, ms);
        else
            verifyAot(m, ms, toplevel, abc_env, NULL);
        PERFM_NTPROF_END("verify-ticks");
    }

    void AOTExecMgr::verifyAot(MethodInfo* method, MethodSignaturep ms,
                                Toplevel *toplevel, AbcEnv* abc_env, OSR* /* osr_state */)
    {
        AotPass1Writer aotWriter(method);
        AvmAssert(aotWriter.verifyInfo.verifySucceeded == false);
        
        // TODO!!! There are still some incomplete things in halfmoon.
        bool canCompile = halfmoon::canCompile(method);
        if (canCompile) {
            TRY(toplevel->core(), avmplus::kCatchAction_Ignore)
            {
                verifyCommon(method, ms, toplevel, abc_env, &aotWriter);
                aotWriter.verifyInfo.verifySucceeded = true;
            }
            CATCH(avmplus::Exception *exception)
            {
                (void)exception;
            }
            END_CATCH
            END_TRY            
        }
        
        AvmAssert(core->currentlyParsing != 0);
        PoolInfo& poolInfo = *core->currentlyParsing;
        
        if (options::verifyWarnings && !aotWriter.verifyInfo.verifySucceeded) {
            if (method->method_id() >= 0) {  // don't warn about not compiling internally-generated initializers
                const char* err = "Verify error";
                if (!canCompile)
                    err = "Halfmoon can't compile";
                llvm::outs() << "warning: " << err << ": " << poolInfo.getFunctionName(method).c_str() << "\n";
            }
        }
        //Propogate needArguments, needRest from derived towards base.
        if(aotWriter.verifyInfo.verifySucceeded && !method->pool()->isBuiltin
           && getArgArrayPropogationFlag())
        {
            //Need to propogate from base to derived (TopToBottom) so add this in Queue
            propogateArgArrMethodQueue.add(method);

            //get traits, traits bindings, disp_id
            Traits* traits = method->declaringTraits();
            const TraitsBindingsp td = traits->getTraitsBindings();
            TraitsBindingsp btd = td->base;
            int disp_id = -1;
            for (uint32_t i = 0, n = td->methodCount; i < n; i++)
            {
                if(method == td->getMethod(i)){
                    disp_id = i;
                    break;
                }
            }
            //Propogate from current to base
            // Start propogate from bottom to top only for needRestOrArguments
            if(disp_id >= 0 && method->needRestOrArguments()){
                while(btd && disp_id < btd->methodCount && btd->getMethod(disp_id))
                {
                    MethodInfo* baseMethod = btd->getMethod(disp_id);
                    //Base has method as same disp_id.Propogate the flag as needArguments
                    //Propogate from derived to base
                    if(method != baseMethod && !baseMethod->needRestOrArguments() ){
                        //We can't propogate to builtin pool throw error for this case.
                        if(baseMethod->pool()->isBuiltin){
                            llvm::errs() << "Error: Method \"" << poolInfo.getFunctionName(method).c_str() << " have either rest or argument usage unlike it's base class. \nAOT can not handle this scenario. Please refer to http://helpx.adobe.com/air/kb/air-compiler-known-issues.html for more information.\n";
                            break;
                        }else {
                            baseMethod->setNeedArgsArrInMethodSig();
                        }
                    }
                    btd = btd->base;
                }
            }
        }
        poolInfo.appendVerifierResult(abc_env, aotWriter.verifyInfo);
    }
    
    void AOTExecMgr::propogateArgArrFlagTopToBottom()
    {
        while (!propogateArgArrMethodQueue.isEmpty()) {
            MethodInfo* m = propogateArgArrMethodQueue.removeFirst();
            propogateArgArrFlagInMethodHierarchy(m);
        }
    }

    void AOTExecMgr::propogateArgArrFlagInMethodHierarchy(MethodInfo* method){
        AvmAssert(getArgArrayPropogationFlag());
        //get traits, traits bindings, disp_id
        Traits* traits = method->declaringTraits();
        const TraitsBindingsp td = traits->getTraitsBindings();
        TraitsBindingsp btd = td->base;
        int disp_id = -1;
        for (uint32_t i = 0, n = td->methodCount; i < n; i++)
        {
            if(method == td->getMethod(i)){
                disp_id = i;
                break;
            }
        }
        //if needRestOrArguments in base, then propogate it to derived function (current)
        if(disp_id >= 0 && btd && disp_id < btd->methodCount && btd->getMethod(disp_id)){
            MethodInfo* baseMethod = btd->getMethod(disp_id);
            if(method != baseMethod && !method->needRestOrArguments() &&
               (baseMethod->needRestOrArguments() || baseMethod->needArgsArrInMethodSig())){
                method->setNeedArgsArrInMethodSig();
            }
        }
    }
    bool AOTExecMgr::getArgArrayPropogationFlag() const
    {
        return argArrayPropogationFlag;
    }
    void AOTExecMgr::setArgArrayPropogationFlag(bool value)
    {
        argArrayPropogationFlag = value;
    }
    
    

    
} // namespace compile_abc

namespace avmplus {
    void AOTThrowVerifyError(AvmCore* core, String* msg)
    {
        Exception* e = new (core->GetGC()) Exception(core, msg->atom());
        core->throwException(e);
    }
}
