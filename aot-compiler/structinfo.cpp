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
// Manages information about the layouts of data in runtime-defined structures.
//

#include "avmplus.h"

#ifdef VMCFG_HALFMOON

#include "llvm-module.h"
#include "llvm-emitter.h"
#include "compileabc.h"

#undef DEBUG  // "llvm/Support/Debug.h" defines DEBUG! No, seriouusly!
#include "llvm/Support/Debug.h" // llvm::dbgs()
#include "llvm/Support/Timer.h"

#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>

namespace compile_abc
{
using namespace avmplus;

//
// Parse the field-definition file
//
bool parseFieldFile(llvm::raw_ostream &err, std::istream& in, LLVMModule& module,
    StructInfoMap* structInfos, StructInfoMap* nativeSlotTemplates, std::vector<NativeMethod>* nativeMethods, uint64_t* pChecksum)
{
    using namespace std;
    string linebuf;
    int lineNum = 0;
    // FNV-1a hash: http://en.wikipedia.org/wiki/Fowler_Noll_Vo_hash
    // Fast, easy and good enough for a checksum.
#define HASH(c) (fvn1aHash = FNV_prime*(fvn1aHash^(uint8_t)c))
    const uint64_t FNV_offset_basis = 14695981039346656037ULL, FNV_prime = 1099511628211ULL;
    uint64_t fvn1aHash = FNV_offset_basis;
    int errors = 0;
    StructInfo *currentStruct = 0;
    while (getline(in, linebuf)) {
        // Checksum the contents of the file
        for (unsigned i = 0; i < linebuf.size(); ++i)
            HASH(linebuf[i]);
        HASH('\n');
        
        // Strip comments
        string::size_type pos = linebuf.find('#');
        if (pos != string::npos)
            linebuf.erase(pos);
        
        // Parse the commands
        istringstream line(linebuf);
        ++lineNum;
        string command;
        line >> skipws >> command;
        
        if (command == "") {
            // empty line
        }
        else if (command == "struct") {
            // struct <size> <name> [nativeSlotTemplate] -- introduces a structure with a given size and name
            unsigned size = 0;
            string name, nativeTemplate;
            line >> size >> name >> nativeTemplate;
            if (!nativeTemplate.empty()) {
                if (nativeSlotTemplates->findStruct(nativeTemplate)) {
                    err << lineNum << ": " << name << " redefined\n";
                    ++errors;
                    continue;
                }
            }
            else if (structInfos->findStruct(name)) {
                err << lineNum << ": " << name << " redefined\n";
                ++errors;
                continue;
            }
            if (name.empty()) {
                err << lineNum << ": missing info - " << linebuf << "\n";
                ++errors;
                continue;                    
            }
            StructInfo* info = new StructInfo();
            info->name = name;
            info->size = size;
            if (!nativeTemplate.empty())
                nativeSlotTemplates->insertStruct(nativeTemplate, info);
            else
                structInfos->insertStruct(name, info);
            currentStruct = info;
        }
        else if (command == "field") {
            // field <offset> <type> <name> [slot] -- defines a field with the given offset, type and name
            FieldInfo field;
            if (!currentStruct) {
                err << lineNum << ": Field must follow a Struct\n";
                ++errors;
                continue;
            }
            field.structInfo = currentStruct;
            string type;
            int slot = 0;
            line >> field.offset >> type >> field.name >> slot;
            // Internally, slots are numbered from zero; in the ABC, they are numbered from 1.
            // We use -1 to signify that the field is not a slot.
            field.slot = slot-1;
            if (field.name.empty()) {
                err << lineNum << ": missing info - " << linebuf << "\n";
                ++errors;
                continue;                    
            }
            if (currentStruct->findField(field.name)) {
                err << lineNum << ": " << field.name << " redefined\n";
                ++errors;
                continue;
            }
            if (type == "atom")  // TODO: is this necessary?
                type = "a";
            field.typedesc = type;
            // check if type is parseable
            llvm::Type* llType = module.llvmType(type.c_str(), true);
            if (!llType) {
                err << lineNum << ": bad type " << type << "\n";
                ++errors;
                continue;
            }
            currentStruct->fields.push_back(field);
        }
        else if (command == "native") {
            // field id mangled-name llvm-type-desc
            NativeMethod info;
            line >> info.id >> info.mangle >> info.typedesc;
            nativeMethods->push_back(info);
        }
        else {
            err << lineNum << ": unrecognized command: " << linebuf << "\n";
                ++errors;
        }
        char nextchar = 0;
        line >> nextchar;
        if (nextchar) {
            line.putback(nextchar);
            err << lineNum << ": unrecognized data at end of line: " << linebuf << "\n";
            ++errors;
        }
    }
    *pChecksum = fvn1aHash;
    return errors != 0;
}
    
// Copy a structinfo from another module, updating field.structInfo
// pointers and computing LLVM types in the new module.
StructInfo::StructInfo(const StructInfo& s, LLVMModule& module)
    : name(s.name)
    , size(s.size)
    , traitsIndex(-1)
    , type(0)
    , traits(0)
    , fields(s.fields)
{
    for (unsigned i = 0; i < fields.size(); ++i) {
        FieldInfo& field = fields[i];
        field.structInfo = this;
        field.type = 0;
        field.memberIx = 0;
        field.type = module.llvmType(field.typedesc.c_str());
    }
    type = module.getTypeByName(name);
    if (!type)
        type = llvm::StructType::create(module.getContext(), name);
}

FieldInfo* StructInfo::findField(const std::string& name)
{
    using namespace std;
    for (unsigned i = 0; i < fields.size(); ++i) {
        FieldInfo& info = fields[i];
        if (info.name == name)
            return &info;
    }
    return 0;
}
    
StructInfo* LLVMModule::findStruct(const std::string& name)
{
    // Do we have the struct already?
    StructInfo *info = structInfos.findStruct(name);
    if (!info) {
        // Find the info in the core's struct table
        info = core->structInfos.findStruct(name);
        if (!info)
            return 0;
        // Copy it to this module (llvm-types are context-specific)
        info = new StructInfo(*info, *this);
        // Layout the struct
        computeStructLayout(*info, llvm::errs());
        structInfos.insertStruct(name, info);
    }
    AvmAssert(info->type != 0);
    return info;
}

StructInfo* LLVMModule::getStructInfo(llvm::raw_ostream &err, const std::string& name, llvm::Type** typeP, llvm::PointerType** ptrTypeP, int* errCntp)
{
    StructInfo* s = findStruct(name);
    if (s) {
        *typeP = s->type;
        *ptrTypeP = s->type->getPointerTo();
    }
    else {
        err << "missing definition for " << name << "\n";
        ++*errCntp;
    }
    return s;
}

FieldInfo* LLVMModule::getFieldInfo(llvm::raw_ostream &err, StructInfo* s, const std::string& name, int* errCntp)
{
    FieldInfo* f = s->findField(name);
    if (!f) {
        err << "missing definition for " << s->name << "." << name << "\n";
        ++*errCntp;
    }
    return f;
}


bool LLVMModule::initializeFieldInfos(llvm::raw_ostream &err)
{
    int errCnt = 0;
    
    if (StructInfo* s = getStructInfo(err, "avmplus::AvmCore", &avmCoreTy, &avmCorePtrTy, &errCnt)) {
        avmcore_methodframe_member = getFieldInfo(err, s, "currentMethodFrame", &errCnt);
        avmcore_exceptionAddr_member = getFieldInfo(err, s, "exceptionAddr", &errCnt);
        avmcore_gc_member = getFieldInfo(err, s, "gc", &errCnt);
    }
    
    if (StructInfo* s = getStructInfo(err, "avmplus::ExceptionFrame", &exceptionFrameTy, &exceptionFramePtrTy, &errCnt)) {
        exceptionFrameStruct = s;
        exceptionFrame_jmpbuf_member = getFieldInfo(err, s, "jmpbuf", &errCnt);
    }
    
    if (StructInfo* s = getStructInfo(err, "AOTInfo", &aotInfoTy, &aotInfoPtrTy, &errCnt)) {
        aotInfoStruct = s;
        aotInfo_origABCSHA1_member = getFieldInfo(err, s, "origABCSHA1", &errCnt);
        aotInfo_abcbytes_member = getFieldInfo(err, s, "abcBytes", &errCnt);
        aotInfo_nABCBytes_member = getFieldInfo(err, s, "nABCBytes", &errCnt);
        aotInfo_methodDebugInfos_member = getFieldInfo(err, s, "methodDebugInfos", &errCnt);
        aotInfo_abcMethods_member = getFieldInfo(err, s, "abcMethods", &errCnt);
        aotInfo_nABCMethods_member = getFieldInfo(err, s, "nABCMethods", &errCnt);
        aotInfo_methodFlagsArr_member = getFieldInfo(err, s, "methodFlagsArr", &errCnt);
        aotInfo_activationInfo_member = getFieldInfo(err, s, "activationInfo", &errCnt);
    }
    
    if (StructInfo* s = getStructInfo(err, "AOTExceptionDesc", &aotExceptionDescTy, &aotExceptionDescPtrTy, &errCnt)) {
        aotExceptionDescStruct = s;
        aotExceptionDesc_from_member = getFieldInfo(err, s, "from", &errCnt);
        aotExceptionDesc_to_member = getFieldInfo(err, s, "to", &errCnt);
        aotExceptionDesc_nameIndex_member = getFieldInfo(err, s, "nameIndex", &errCnt);
        aotExceptionDesc_typeIndexU30_member = getFieldInfo(err, s, "typeIndexU30", &errCnt);
    }

    if (StructInfo* s = getStructInfo(err, "MethodDebugInfo", &methodDebugInfoTy, &methodDebugInfoPtrTy, &errCnt)) {
      methodDebugInfoStruct = s;
      methodDebugInfo_local_count_member = getFieldInfo(err, s, "local_count", &errCnt);
      methodDebugInfo_scope_count_member = getFieldInfo(err, s, "scope_count", &errCnt);
      methodDebugInfo_file_name_member = getFieldInfo(err, s, "file_name", &errCnt);
      methodDebugInfo_local_names_member = getFieldInfo(err, s, "local_names", &errCnt);
      methodDebugInfo_line_count_member = getFieldInfo(err, s, "line_count", &errCnt);
      methodDebugInfo_lines_member = getFieldInfo(err, s, "lines", &errCnt);
    }

    if (StructInfo* s = getStructInfo(err, "AOTActivationInfo", &aotActivationInfoTy, &aotActivationInfoPtrTy, &errCnt)) {
        aotActivationInfoStruct = s;
        aotActivationInfo_initMethodId_member = getFieldInfo(err, s, "initMethodId", &errCnt);
        aotActivationInfo_initHandler_member = getFieldInfo(err, s, "initHandler", &errCnt);
    }
    
    if (StructInfo* s = getStructInfo(err, "avmplus::Exception", &exceptionTy, &exceptionPtrTy, &errCnt)) {
        exception_atom_member = getFieldInfo(err, s, "atom", &errCnt);
    }
    
    if (StructInfo* s = getStructInfo(err, "avmplus::String", &stringTy, &stringPtrTy, &errCnt)) {
        (void)s;
    }
    
    if (StructInfo* s = getStructInfo(err, "avmplus::MethodFrame", &methodFrameTy, &methodFramePtrTy, &errCnt)) {
        methodframe_next_member = getFieldInfo(err, s, "next", &errCnt);
        methodframe_env_member  = getFieldInfo(err, s, "env", &errCnt);
    }
    
    if (StructInfo* s = getStructInfo(err, "avmplus::CallStackNode", &callStackNodeTy, &callStackNodePtrTy, &errCnt)) {
        (void)s;
    }
    
    if (StructInfo* s = getStructInfo(err, "avmplus::MethodInfo::NativeInfo", &methodInfoNativeTy, &methodInfoNativePtrTy, &errCnt)) {
        methodinfonative_handler_member = getFieldInfo(err, s, "handler", &errCnt);
    }
    
    if (StructInfo* s = getStructInfo(err, "avmplus::MethodInfo", &methodInfoTy, &methodInfoPtrTy, &errCnt)) {
        methodinfo_pool_member = getFieldInfo(err, s, "pool", &errCnt);
        methodinfo_native_member = getFieldInfo(err, s, "native", &errCnt);
    }
    
    if (StructInfo* s = getStructInfo(err, "avmplus::Multiname", &multinameTy, &multinametPtrTy, &errCnt)) {
        (void)s;
    }
        
    if (StructInfo* s = getStructInfo(err, "ESC_HeapMultiname", &escHeapMultinameTy, &escHeapMultinamePtrTy, &errCnt)) {
        escHeapMultiname_elements_member = getFieldInfo(err, s, "elements", &errCnt);
    }
    
    if (StructInfo* s = getStructInfo(err, "avmplus::TracedListData<avmplus::MethodInfo*>", &methodInfoListTy, &methodInfoListPtrTy, &errCnt)) {
        methodInfoList_entries_member = getFieldInfo(err, s, "entries", &errCnt);
    }
    
    if (StructInfo* s = getStructInfo(err, "ListAccess<avmplus::MethodInfo*>", &methodInfoGCListTy, &methodInfoGCListPtrTy, &errCnt)) {
        methodInfoGCList_m_list_member = getFieldInfo(err, s, "m_list", &errCnt);
    }

    if (StructInfo* s = getStructInfo(err, "avmplus::TracedListData<avmplus::Namespace*>", &namespaceListTy, &methodInfoListPtrTy, &errCnt)) {
        namespaceList_entries_member = getFieldInfo(err, s, "entries", &errCnt);
    }
    
    if (StructInfo* s = getStructInfo(err, "ListAccess<avmplus::Namespace*>", &namespaceRCListTy, &namespaceRCListPtrTy, &errCnt)) {
        namespaceRCList_m_list_member = getFieldInfo(err, s, "m_list", &errCnt);
    }
    
    if (StructInfo* s = getStructInfo(err, "avmplus::TracedListData<avmplus::Traits*>", &traitsTracedListTy, &traitsTracedListPtrTy, &errCnt)) {
        traitsTracedList_entries_member = getFieldInfo(err, s, "entries", &errCnt);
    }
    
    if (StructInfo* s = getStructInfo(err, "ListAccess<avmplus::Traits*>", &traitsListTy, &traitsListPtrTy, &errCnt)) {
        traitsList_m_list_member = getFieldInfo(err, s, "m_list", &errCnt);
    }
    
    if (StructInfo* s = getStructInfo(err, "avmplus::PoolObject", &poolObjectTy, &poolObjectPtrTy, &errCnt)) {
        poolobject_core_member = getFieldInfo(err, s, "core", &errCnt);
        poolobject_escHeapMultiname_member = getFieldInfo(err, s, "precompNames", &errCnt);
        poolobject_classes_member = getFieldInfo(err, s, "classes", &errCnt);
        poolobject_scripts_member = getFieldInfo(err, s, "scripts", &errCnt);
        poolobject_namespaces_member = getFieldInfo(err, s, "namespaces", &errCnt);
        poolobject_methods_member = getFieldInfo(err, s, "methods", &errCnt);
    }
    
    if (StructInfo* s = getStructInfo(err, "avmplus::VTable", &vtableTy, &vtablePtrTy, &errCnt)) {
        vtable_methods_member = getFieldInfo(err, s, "methods", &errCnt);
        vtable_init_member = getFieldInfo(err, s, "init", &errCnt);
        vtable_base_member = getFieldInfo(err, s, "base", &errCnt);
        vtable_ivtable_member = getFieldInfo(err, s, "ivtable", &errCnt);
        vtable_traits_member = getFieldInfo(err, s, "traits", &errCnt);
        vtable_createinstanceproc_member = getFieldInfo(err, s, "createInstanceProc", &errCnt);
        vtable_base_member = getFieldInfo(err, s, "base", &errCnt);
    }
    
    if (StructInfo* s = getStructInfo(err, "avmplus::Traits", &traitsTy, &traitsPtrTy, &errCnt)) {
        traits_itraits_member = getFieldInfo(err, s, "itraits", &errCnt);
    }
    
    if (StructInfo* s = getStructInfo(err, "avmplus::MethodEnv", &methodEnvTy, &methodEnvPtrTy, &errCnt)) {
        methodenv_impl_member = getFieldInfo(err, s, "impl", &errCnt);
        methodenv_scope_member = getFieldInfo(err, s, "_scope", &errCnt);
        methodenv_method_member = getFieldInfo(err, s, "method", &errCnt);
    }
    
    if (StructInfo* s = getStructInfo(err, "avmplus::ScriptObject", &scriptObjectTy, &scriptObjectPtrTy, &errCnt)) {
        scriptObjectStruct = s;
        scriptobject_vtable_member = getFieldInfo(err, s, "vtable", &errCnt);
    }
    
    if (StructInfo* s = getStructInfo(err, "avmplus::ScopeChain", &scopeChainTy, &scopeChainPtrTy, &errCnt)) {
        scope_vtable_member = getFieldInfo(err, s, "_vtable", &errCnt);
        scope_scopes_member = getFieldInfo(err, s, "_scopes", &errCnt);
        scope_abcenv_member = getFieldInfo(err, s, "_abcEnv", &errCnt);
    }

    if (StructInfo* s = getStructInfo(err, "avmplus::AbcEnv", &abcEnvTy, &abcEnvTPtrTy, &errCnt)) {
        abcenv_finddeftbl_member = getFieldInfo(err, s, "m_finddef_table", &errCnt);
    }
  
    if (StructInfo* s = getStructInfo(err, "FinddefTableType", &finddefTableTy, &finddefTablePtrTy, &errCnt)) {
      finddeftbl_elements_member = getFieldInfo(err, s, "elements", &errCnt);
    }
  
    return errCnt != 0;
}
    
} // end namespace compile_abc

#endif // VMCFG_HALFMOON
