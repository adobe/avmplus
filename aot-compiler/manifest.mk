# ***** BEGIN LICENSE BLOCK *****
# Version: MPL 1.1/GPL 2.0/LGPL 2.1
#
# The contents of this file are subject to the Mozilla Public License Version
# 1.1 (the "License"); you may not use this file except in compliance with
# the License. You may obtain a copy of the License at
# http://www.mozilla.org/MPL/
#
# Software distributed under the License is distributed on an "AS IS" basis,
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
# for the specific language governing rights and limitations under the
# License.
#
# The Original Code is [Open Source Virtual Machine.].
#
# The Initial Developer of the Original Code is
# Adobe System Incorporated.
# Portions created by the Initial Developer are Copyright (C) 2007-2008
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   Adobe AS3 Team
#
# Alternatively, the contents of this file may be used under the terms of
# either the GNU General Public License Version 2 or later (the "GPL"), or
# the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
# in which case the provisions of the GPL or the LGPL are applicable instead
# of those above. If you wish to allow use of your version of this file only
# under the terms of either the GPL or the LGPL, and not to allow others to
# use your version of this file under the terms of the MPL, indicate your
# decision by deleting the provisions above and replace them with the notice
# and other provisions required by the GPL or the LGPL. If you do not delete
# the provisions above, a recipient may use your version of this file under
# the terms of any one of the MPL, the GPL or the LGPL.
#
# ***** END LICENSE BLOCK *****

PROGRAMS += compileabc
compileabc_BUILD_ALL = 1
compileabc_INCLUDES += $(AVM_INCLUDES) $(LLVM_INCLUDES)

compileabc_BASENAME = compile-abc
compileabc_INCLUDES += -I$(srcdir) 
compileabc_DEFINES = -DAVMPLUS_COMPILE_ABC
compileabc_BUILD_ALL = 1
compileabc_INCLUDES += $(AVM_INCLUDES) 
compileabc_STATIC_LIBRARIES = lzma zlib avmplus MMgc vmbase 
compileabc_DIR := $(curdir)/

# compiling code to use llvm requires several -D and -I options and must link to many llvm libraries.
# configure.py --enable-llvm=dir calls the llvm-config tool for these and sets LLVM_CXXFLAGS and LLVM_LDFLAGS.
# Consequently this makefile does NOT check if llvm has been built.. it must be built at configure time.

compileabc_CXXFLAGS := $(LLVM_CXXFLAGS) $(CXXFLAGS) $(APP_CXXFLAGS)
compileabc_EXTRA_LDFLAGS := $(LLVM_LDFLAGS) $(LLVM_LIBS) -stdlib=libc++ -lz -lcurses
compileabc_CXXSRCS := $(compileabc_CXXSRCS) \
    $(curdir)/compileabc.cpp \
    $(curdir)/llvm-emitter.cpp \
    $(curdir)/llvm-module.cpp \
    $(curdir)/poolinfo.cpp \
    $(curdir)/structinfo.cpp \
    $(curdir)/sha1_portable.cpp \
    $(curdir)/aotverify.cpp \
    $(NULL)

compileabc_PREPROCESSED := $(compileabc_CXXSRCS:.cpp=.$(II_SUFFIX)) $(compileabc_PCH:.h=.$(II_SUFFIX))

