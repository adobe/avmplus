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

#ifndef __compile_abc_structinfo__
#define __compile_abc_structinfo__

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

#include <map>
#include <vector>

//
// Manages information about the layouts of data in runtime-defined structures.
//

namespace compile_abc
{
using namespace avmplus;
using namespace halfmoon;
    
struct StructInfo;
class LLVMModule;

// A field within a structure or class
struct FieldInfo {
    FieldInfo() : structInfo(0), memberIx(0), offset(0), slot(-1), type(0) {}
    std::string name;
    StructInfo* structInfo;
    unsigned memberIx;
    unsigned offset;
    int slot;
    std::string typedesc;
    llvm::Type* type;
    static bool smallerOffset(const FieldInfo &a, const FieldInfo &b) { return a.offset < b.offset; }
};

// A structure or class
struct StructInfo {
    StructInfo() : size(0), traitsIndex(-1), type(0), traits(0) {}
    StructInfo(const StructInfo& s, LLVMModule& module);
    std::string name;
    unsigned size;
    int traitsIndex;
    llvm::StructType* type;
    Traits* traits;
    std::vector<FieldInfo> fields;
    FieldInfo* findField(const std::string& name);
    std::vector<unsigned> slotToField;
    FieldInfo* getSlot(unsigned slot) { AvmAssert(slot < slotToField.size()); return &fields[slotToField[slot]]; }
};
    
// A native nmethod
struct NativeMethod {
    NativeMethod() : id(0) {}
    int id;
    std::string mangle;
    std::string typedesc;
};

// Because FieldInfos contain pointers back to StructInfos, we need to ensure
// that StructInfos don't move. So this map contains pointers to StructInfos
// and the destructor deletes them. Sadly, you can't use auto_ptrs in collections
// (no move semantics). Solutions aren't available until C++11 or in Boost,
// and I don't want to depend on either of those just for this.
class StructInfoMap: std::map<std::string,StructInfo*>
{
public:
    ~StructInfoMap()
    {
        for (iterator it = begin(); it != end(); ++it)
            delete it->second;
    }
    
    StructInfo* findStruct(const std::string& name)
    {
        iterator it = find(name);
        if (it == end())
            return 0;
        else
            return it->second;
    }
    
    void insertStruct(const std::string& name, StructInfo* s)
    {
        AvmAssert(find(name) == end());
        (*this)[name] = s;
    }
};

bool parseFieldFile(llvm::raw_ostream &err, std::istream& in, LLVMModule& module,
                    StructInfoMap* structInfos, StructInfoMap* nativeSlotTemplates, std::vector<NativeMethod>* nativeMethods, uint64_t* pChecksum);

}
#endif /* __compile_abc_structinfo__ */

