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
 * Portions created by the Initial Developer are Copyright (C) 2012
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

struct AOTLayoutData {
    char name1[512];
    char name2[512];
    unsigned fieldType;
    unsigned int1;
    unsigned int2;
};
#define DEFINESTRUCT(structname) \
    { #structname, "", 'S', sizeof(structname), 0 }
#define DEFINEFIELD2(structname, fieldname, fieldalias, type) \
    { fieldalias, type, 'F', offsetof(structname, fieldname), 0 }
#define DEFINEFIELD(structname, fieldname, type) \
    DEFINEFIELD2(structname, fieldname, #fieldname, type)
#define DEFINELAYOUT(ns, name, asname) \
    { #ns "::" #name, asname, 'S', sizeof(ns::name), 0 }
#define DEFINESLOT(ns, structname, slotstructname, fieldname, fieldtype, slotNum) \
    { #fieldname, fieldtype, 'F', \
    offsetof(ns::structname, m_slots_##structname) + offsetof(avmplus::NativeID::slotstructname, m_##fieldname), slotNum }
#define DEFINENATIVE(nativeid, unmangled, mangled, typestr) \
    { #unmangled, mangled " " typestr, 'N', nativeid, 0 }
#define FIELD_DATA_BEGIN {"<<<< Field Data Begin >>>>", "", 0, 0, 0 }
#define FIELD_DATA_END   {"<<<< Field Data End >>>>", "", 0, 0, 0 }

#ifndef VMCFG_HALFMOON
// AOT runtimes don't geneally have halfmoon defined, but the layouts structure needs to
// see the private fields.
namespace halfmoon {
    class JitFriend {
        void aotFieldLayout();
    };
}
#endif

typedef avmplus::ExactStructContainer<avmplus::HeapMultiname> ESC_HeapMultiname;
typedef avmplus::ExactStructContainer<avmplus::AbcEnv::FinddefEntry> FinddefTableType;

// This is sorta cheaty: the GCList<MethodInfo> expands the member m_list as a pointer to
// TracedListData<GCObject*>, but we'll flatten that out to bypass the private fields and
// template craziness. But beware! if the implementation changes, this will need to be revisited

// njindal: Presence of vtable in GCList/RCList doesnt't map TracedListData directly to GCList. creating a
// stubbed implementation of GCList/RCList to make offsetof work as m_list is private and offset of cannot access private members.

template<class T>
class ListAccess
{
public:
    virtual ~ListAccess();
    avmplus::TracedListData<T> *m_list;
};


AOTLayoutData* saveLayoutData; // give the function something to do (thwart optimizer)

//
// The function is a member of JitFriend to have access to structure member layouts.
//
void halfmoon::JitFriend::aotFieldLayout() {
    static AOTLayoutData field_data[] = {
        FIELD_DATA_BEGIN,
        
        DEFINESTRUCT(MMgc::GC),
        DEFINESTRUCT(avmplus::String),
        DEFINESTRUCT(avmplus::Traits),
        DEFINEFIELD(avmplus::Traits, itraits, "*'avmplus::Traits'"),
        
        DEFINESTRUCT(AOTInfo),
        DEFINEFIELD(AOTInfo, origABCSHA1, "[20]c"),
        DEFINEFIELD(AOTInfo, abcBytes, "*c"),
        DEFINEFIELD(AOTInfo, nABCBytes, "i"),
        DEFINEFIELD(AOTInfo, methodDebugInfos, "*'MethodDebugInfo'"),
        DEFINEFIELD(AOTInfo, abcMethods, "*!"),
        DEFINEFIELD(AOTInfo, nABCMethods, "i"),
        DEFINEFIELD(AOTInfo, methodFlagsArr, "*i"),
        DEFINEFIELD(AOTInfo, activationInfo, "*'AOTActivationInfo'"),
        
        DEFINESTRUCT(AOTExceptionDesc),
        DEFINEFIELD(AOTExceptionDesc, from, "i"),
        DEFINEFIELD(AOTExceptionDesc, to, "i"),
        DEFINEFIELD(AOTExceptionDesc, nameIndex, "i"),
        DEFINEFIELD(AOTExceptionDesc, typeIndexU30, "[5]c"),
        
        DEFINESTRUCT(avmplus::Multiname),

        DEFINESTRUCT(avmplus::TracedListData<avmplus::MethodInfo*>),
        DEFINEFIELD(avmplus::TracedListData<avmplus::MethodInfo*>, entries, "*'avmplus::MethodInfo'"),
        
        DEFINESTRUCT(ListAccess<avmplus::MethodInfo*>),
        DEFINEFIELD2(ListAccess<avmplus::MethodInfo*>, m_list, "m_list", "*'avmplus::TracedListData<avmplus::MethodInfo*>'"),

        DEFINESTRUCT(avmplus::TracedListData<avmplus::Namespace*>),
        DEFINEFIELD(avmplus::TracedListData<avmplus::Namespace*>, entries, "*'avmplus::Namespace'"),

        DEFINESTRUCT(ListAccess<avmplus::Namespace*>),
        DEFINEFIELD2(ListAccess<avmplus::Namespace*>, m_list, "m_list", "*'avmplus::TracedListData<avmplus::Namespace*>'"),

        DEFINESTRUCT(avmplus::TracedListData<avmplus::Traits*>),
        DEFINEFIELD(avmplus::TracedListData<avmplus::Traits*>, entries, "*'avmplus::Traits'"),
        
        DEFINESTRUCT(ListAccess<avmplus::Traits*>),
        DEFINEFIELD2(ListAccess<avmplus::Traits*>, m_list, "m_list", "*'avmplus::TracedListData<avmplus::Traits*>'"),
        
        DEFINESTRUCT(avmplus::PoolObject),
        DEFINEFIELD(avmplus::PoolObject, core, "*'avmplus::AvmCore'"),
        DEFINEFIELD(avmplus::PoolObject, precompNames, "*'ESC_HeapMultiname'"),
        DEFINEFIELD2(avmplus::PoolObject, _classes, "classes", "'ListAccess<avmplus::Traits*>'"),
        DEFINEFIELD2(avmplus::PoolObject, _scripts, "scripts", "'ListAccess<avmplus::Traits*>'"),
        DEFINEFIELD2(avmplus::PoolObject, cpool_ns, "namespaces", "'ListAccess<avmplus::Namespace*>'"),
        DEFINEFIELD2(avmplus::PoolObject, _methods, "methods", "'ListAccess<avmplus::MethodInfo*>'"),
        
        DEFINESTRUCT(ESC_HeapMultiname),
        DEFINEFIELD(ESC_HeapMultiname, elements, "[1]'avmplus::Multiname'"),
        
        DEFINESTRUCT(MethodDebugInfo),
        DEFINEFIELD(MethodDebugInfo, local_count, "i"),
        DEFINEFIELD(MethodDebugInfo, scope_count, "i"),
        DEFINEFIELD(MethodDebugInfo, file_name, "i"),
        DEFINEFIELD(MethodDebugInfo, local_names, "*i"),
        DEFINEFIELD(MethodDebugInfo, line_count, "i"),
        DEFINEFIELD(MethodDebugInfo, lines, "*i"),

        DEFINESTRUCT(AOTActivationInfo),
        DEFINEFIELD(AOTActivationInfo, initMethodId, "i"),
        DEFINEFIELD(AOTActivationInfo, initHandler, "!"),
        
        DEFINESTRUCT(avmplus::AvmCore),
        DEFINEFIELD(avmplus::AvmCore, currentMethodFrame, "*'avmplus::MethodFrame'"),
        DEFINEFIELD(avmplus::AvmCore, exceptionAddr, "*'avmplus::ExceptionFrame'"),
        DEFINEFIELD(avmplus::AvmCore, gc, "*'MMgc::GC'"),

        DEFINESTRUCT(avmplus::ExceptionFrame),
        DEFINEFIELD(avmplus::ExceptionFrame, jmpbuf, "i"),  // not really this type, but &jmpbuf is OK.
        
        DEFINESTRUCT(avmplus::Exception),
        DEFINEFIELD(avmplus::Exception, atom, "*c"),
        
        DEFINESTRUCT(avmplus::MethodInfo),
        DEFINEFIELD2(avmplus::MethodInfo, _pool, "pool", "*'avmplus::PoolObject'"),
        DEFINEFIELD2(avmplus::MethodInfo, _native, "native", "'avmplus::MethodInfo::NativeInfo'"),
        
        DEFINESTRUCT(avmplus::MethodInfo::NativeInfo),
        DEFINEFIELD(avmplus::MethodInfo::NativeInfo, handler, "!"),
        
        DEFINESTRUCT(avmplus::MethodFrame),
        DEFINEFIELD(avmplus::MethodFrame, next, "*'avmplus::MethodFrame'"),
        DEFINEFIELD2(avmplus::MethodFrame, envOrCodeContext, "env", "*'avmplus::MethodEnv'"),
        
        DEFINESTRUCT(avmplus::CallStackNode),

        DEFINESTRUCT(avmplus::ScriptObject),
        DEFINEFIELD(avmplus::ScriptObject, vtable, "*'avmplus::VTable'"),

        DEFINESTRUCT(avmplus::VTable),
        DEFINEFIELD(avmplus::VTable, init, "*'avmplus::MethodEnv'"),
        DEFINEFIELD(avmplus::VTable, base, "*'avmplus::VTable'"),
        DEFINEFIELD(avmplus::VTable, ivtable, "*'avmplus::VTable'"),
        DEFINEFIELD(avmplus::VTable, traits, "*'avmplus::Traits'"),
        DEFINEFIELD(avmplus::VTable, createInstanceProc, "!"),
        DEFINEFIELD(avmplus::VTable, methods, "*'avmplus::MethodEnv'"),  // last

        DEFINESTRUCT(avmplus::MethodEnv),
        DEFINEFIELD(avmplus::MethodEnv, method,  "*'avmplus::MethodInfo'"),
        DEFINEFIELD2(avmplus::MethodEnv, _implGPR, "impl", "!"),
        DEFINEFIELD(avmplus::MethodEnv, _scope,  "*'avmplus::ScopeChain'"),

        DEFINESTRUCT(avmplus::ScopeChain),
        DEFINEFIELD(avmplus::ScopeChain, _vtable, "*'avmplus::VTable'"),
        DEFINEFIELD(avmplus::ScopeChain, _scopes, "atom"),
        DEFINEFIELD(avmplus::ScopeChain, _abcEnv, "*'avmplus::AbcEnv'"),  // last

        DEFINESTRUCT(avmplus::AbcEnv),
        DEFINEFIELD(avmplus::AbcEnv, m_finddef_table, "*'FinddefTableType'"),
      
        DEFINESTRUCT(FinddefTableType),
        DEFINEFIELD(FinddefTableType, elements, "[1]*'avmplus::ScriptObject'"),

