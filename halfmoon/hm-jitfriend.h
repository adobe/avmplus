/* -*- Mode: C++; c-basic-offset: 2; indent-tabs-mode: nil; tab-width: 2 -*- */
/* vi: set ts=2 sw=2 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

//
// This is the main header file for the compiler implementation.
//

#ifndef HM_JITFRIEND_H
#define HM_JITFRIEND_H

#if defined(VMCFG_HALFMOON) || defined(VMCFG_HALFMOON_AOT_RUNTIME)

#include "avmplus.h"

namespace halfmoon {
  
/**
 * class JitFriend is a layer of indirection for accessing private
 * avm data structures without avm needing to refer to compiler internal
 * classes.
 */
class JitFriend {

public:
  static uintptr_t getIID(MethodInfo* info) {
    return ImtHolder::getIID(info);
  }

  static uint32_t hashIID(MethodInfo* info) {
    return ImtHolder::hashIID(info);
  }

  static GprMethodProc envImplGpr(MethodEnv* env) {
    return env->_implGPR;
  }

  static FprMethodProc envImplFpr(MethodEnv* env) {
    return env->_implFPR;
  }

  static GprImtThunkProc envImplImtGpr(MethodEnv* env) {
    return env->_implImtGPR;
  }

  static FprImtThunkProc envImplImtFpr(MethodEnv* env) {
    return (FprImtThunkProc) env->_implImtGPR;
  }

  static MethodEnv* imtEntry(VTable* vtable, MethodInfo* info) {
    return reinterpret_cast<MethodEnv*>(vtable->imt.entries[hashIID(info)]);
  }

  static MethodEnv* superInitEnv(MethodEnv* env) {
    return env->vtable()->base->init;
  }
    
  static void aotFieldLayout();

public:
  // Offsets of fields accessed directly by halfmoon JIT.
  static const size_t core_cmf_offset = offsetof(AvmCore, currentMethodFrame);
  static const size_t core_minstack_offset = offsetof(AvmCore, minstack);
  static const size_t core_interrupted_offset = offsetof(AvmCore, interrupted);
  static const size_t mf_env_offset = offsetof(MethodFrame, envOrCodeContext);
  static const size_t mf_dxns_offset = offsetof(MethodFrame, dxns);
  static const size_t env_impl_offset = offsetof(MethodEnvProcHolder, _implGPR);
  static const size_t env_scope_offset = offsetof(MethodEnv, _scope);
  static const size_t scope_vtable_offset = offsetof(ScopeChain, _vtable);
  static const size_t scope_scopes_offset = offsetof(ScopeChain, _scopes);
  static const size_t vtable_imt_offset = offsetof(VTable, imt.entries);
};

} // end namespace halfmoon
#endif // #if defined(VMCFG_HALFMOON) || defined(VMCFG_HALFMOON_AOT_RUNTIME)
#endif // HM_JITFRIEND_H
