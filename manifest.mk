# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

CPPFLAGS += -DGTEST_HAS_RTTI=0 -D_HAS_EXCEPTIONS=0

GTEST_INCLUDES = \
  -I$(topsrcdir)/gtest/gtest-1.6.0/include \
  $(NULL)
INCLUDES := $(GTEST_INCLUDES)

VMBASE_INCLUDES = \
  -I$(topsrcdir)/platform \
  -I$(topsrcdir)/VMPI \
  -I$(topsrcdir)/vmbase \
  $(NULL)

# shell must be included here because that's where avmshell-features.h lives,
# and in shell builds it is included from platform/AVMPI.h.  That's how it
# is supposed to be.
AVM_INCLUDES = \
  $(VMBASE_INCLUDES) \
  -I$(topsrcdir) \
  -I$(topsrcdir)/MMgc \
  -I$(topsrcdir)/core \
  -I$(topsrcdir)/pcre \
  -I$(topsrcdir)/eval \
  -I$(topsrcdir)/platform \
  -I$(topsrcdir)/other-licenses/zlib \
  -I$(topsrcdir)/other-licenses/lzma \
  -I$(topsrcdir)/shell \
  -I$(topsrcdir)/AVMPI \
  -I$(topsrcdir)/generated \
  -I$(topsrcdir)/aot \
  $(NULL)

# This line could just as easily go into core/manifest.mk, but putting it here
# emphasizes that we should not simply include everything everywhere.
avmplus_INCLUDES += $(AVM_INCLUDES)

$(call RECURSE_DIRS,other-licenses/zlib)
$(call RECURSE_DIRS,other-licenses/lzma)

# Bug 668442: WinPortUtils.cpp VMPI_getDaylightSavingsTA issue
# Revision buggy, original breaks gtest; disabling gtest until revision fixed.
# $(call RECURSE_DIRS,gtest)
# MTRIPLE_arch
MTRIPLE_arch = i386

$(call RECURSE_DIRS,VMPI)
$(call RECURSE_DIRS,vmbase)
$(call RECURSE_DIRS,AVMPI)
$(call RECURSE_DIRS,MMgc)
$(call RECURSE_DIRS,halfmoon)

ifeq (1,$(ENABLE_HALFMOON_AOT_COMPILER))
$(call RECURSE_DIRS,aot-compiler)
endif

ifdef ENABLE_TAMARIN
$(call RECURSE_DIRS,core pcre vprof)
ifeq (1,$(ENABLE_AOT))
$(call RECURSE_DIRS,aot)
endif
ifeq (sparc,$(TARGET_CPU))
$(call RECURSE_DIRS,nanojit)
endif
ifeq (i686,$(TARGET_CPU))
$(call RECURSE_DIRS,nanojit)
endif
ifeq (x86_64,$(TARGET_CPU))
$(call RECURSE_DIRS,nanojit)
MTRIPLE_arch = x86_64
endif
ifeq (thumb2,$(TARGET_CPU))
$(call RECURSE_DIRS,nanojit)
endif
ifeq (arm,$(TARGET_CPU))
$(call RECURSE_DIRS,nanojit)
endif
ifeq (powerpc,$(TARGET_CPU))
$(call RECURSE_DIRS,nanojit)
endif
ifeq (ppc64,$(TARGET_CPU))
$(call RECURSE_DIRS,nanojit)
endif
ifeq (mips,$(TARGET_CPU))
$(call RECURSE_DIRS,nanojit)
endif
ifeq (sh4,$(TARGET_CPU))
$(call RECURSE_DIRS,nanojit)
endif
ifeq (darwin,$(TARGET_OS))
$(call RECURSE_DIRS,platform/mac)
endif
ifeq (windows,$(TARGET_OS))
$(call RECURSE_DIRS,platform/win32)
endif
ifeq (linux,$(TARGET_OS))
$(call RECURSE_DIRS,platform/unix)
endif
ifeq (android,$(TARGET_OS))
$(call RECURSE_DIRS,platform/unix)
endif
ifeq (sunos,$(TARGET_OS))
$(call RECURSE_DIRS,platform/unix)
endif
endif

$(call RECURSE_DIRS,eval)

ifeq (1,$(ENABLE_SHELL))
$(call RECURSE_DIRS,shell)
endif

# Bug 632086: These definitions must come *after* the foo_CXXSRCS
# variables have been completely populated.
MMgc_PREPROCESSED := $(MMgc_CXXSRCS:.cpp=.$(II_SUFFIX)) $(MMgc_PCH:.h=.$(II_SUFFIX))
avmplus_PREPROCESSED := $(avmplus_CXXSRCS:.cpp=.$(II_SUFFIX)) $(avmplus_PCH:.h=.$(II_SUFFIX))
vmbase_PREPROCESSED := $(vmbase_CXXSRCS:.cpp=.$(II_SUFFIX)) $(vmbase_PCH:.h=.$(II_SUFFIX))
shell_PREPROCESSED := $(shell_CXXSRCS:.cpp=.$(II_SUFFIX))

# Bug 632086: Tie generated code for .h and .cpp together, so that
# requiring the regeneration of the .cpp file will force the
# regeneration of both to happen before the .h file is read.
GENERATED_BUILTIN_CODE := \
 $(topsrcdir)/generated/builtin.h \
 $(topsrcdir)/generated/builtin.cpp \
 $(topsrcdir)/generated/builtin.abc
GENERATED_SHELL_CODE := \
 $(topsrcdir)/generated/shell_toplevel.h \
 $(topsrcdir)/generated/shell_toplevel.cpp \
 $(topsrcdir)/generated/shell_toplevel.abc

$(MMgc_PREPROCESSED): | core-tracers
$(avmplus_PREPROCESSED): $(GENERATED_BUILTIN_CODE) | core-tracers
$(vmbase_PREPROCESSED): $(GENERATED_BUILTIN_CODE) | core-tracers
$(shell_PREPROCESSED): $(GENERATED_BUILTIN_CODE) | core-tracers
$(shell_PREPROCESSED): $(GENERATED_SHELL_CODE) | shell-tracers

$(avmplus_CXXOBJS): $(vmbase_PCH).$(PCH_SUFFIX) $(MMgc_PCH).$(PCH_SUFFIX) $(avmplus_PCH).$(PCH_SUFFIX)
$(MMgc_CXXOBJS): $(vmbase_PCH).$(PCH_SUFFIX) $(MMgc_PCH).$(PCH_SUFFIX) $(avmplus_PCH).$(PCH_SUFFIX)
$(vmbase_CXXOBJS): $(vmbase_PCH).$(PCH_SUFFIX)

echo:
	@echo avmplus_CXXFLAGS = $(avmplus_CXXFLAGS)
	@echo avmplus_CXXSRCS = $(avmplus_CXXSRCS)
	@echo avmplus_CXXOBJS = $(avmplus_CXXOBJS)
	@echo avmplus_OBJS = $(avmplus_OBJS)
	@echo avmplus_NAME = $(avmplus_NAME)
	@echo avmplus_BUILTINFLAGS = $(avmplus_BUILTINFLAGS)
	@echo avmplus_PCH_OBJ = $(avmplus_PCH_OBJ)
	@echo MMgc_CXXSRCS = $(MMgc_CXXSRCS)
	@echo MMgc_CXXOBJS = $(MMgc_CXXOBJS)
	@echo MMgc_OBJS = $(MMgc_OBJS)
	@echo MMgc_NAME = $(MMgc_NAME)
	@echo MMgc_BUILTINFLAGS = $(MMgc_BUILTINFLAGS)
	@echo MMgc_PCH = $(MMgc_PCH)
	@echo MMgc_PCH_OBJ = $(MMgc_PCH_OBJ)
	@echo vmbase_CXXSRCS = $(vmbase_CXXSRCS)
	@echo vmbase_CXXOBJS = $(vmbase_CXXOBJS)
	@echo vmbase_OBJS = $(vmbase_OBJS)
	@echo vmbase_NAME = $(vmbase_NAME)
	@echo vmbase_BUILTINFLAGS = $(vmbase_BUILTINFLAGS)
	@echo vmbase_PCH_OBJ = $(vmbase_PCH_OBJ)

# hm-aot-sdk gathers the build results destined for the hm aot SDK into a staging area.
# hm-aot-sdk target is NOT a dependency of "all", rather, the idea is to
# run "make hm-aot-sdk" separately after make all has completed.
# Rational is that the makefiles should gather their own build results into a staging area.

PSEUDO_SDK=$(curdir)/../hm-aot-sdk

# Mac host variables
darwin_AVMSHELLOBJ=$(curdir)/shell/avmshellMac.o
darwin_MTRIPLE=$(MTRIPLE_arch)-apple-darwin9
darwin_EXE_WRAPPER=

# Windows host variables
windows_AVMSHELLOBJ=$(curdir)/shell/avmshellWin.obj
windows_MTRIPLE=i686-pc-win32
windows_EXE_WRAPPER=$(topsrcdir)/build/cygwin-wrapper.sh

AVMSHELLOBJ=$($(HOST_OS)_AVMSHELLOBJ)
MTRIPLE=$($(HOST_OS)_MTRIPLE)
EXE_WRAPPER=$($(HOST_OS)_EXE_WRAPPER)

ifeq (1,$(ENABLE_HALFMOON_AOT_RUNTIME))

#these are build results
SHELLFIELDS=$(curdir)/shell-fields.txt

hm-aot-sdk: $(AVMSHELLOBJ)
	mkdir -p $(PSEUDO_SDK)
	mkdir -p $(PSEUDO_SDK)/lib
	mkdir -p $(PSEUDO_SDK)/bin
	cp -fp $(SHELLFIELDS) $(AVMSHELLOBJ) $(PSEUDO_SDK)
	cp -fp $(curdir)/*.$(LIB_SUFFIX) $(PSEUDO_SDK)/lib

endif #ENABLE_HALFMOON_AOT_RUNTIME


ifeq (1,$(ENABLE_HALFMOON_AOT_COMPILER))

#these are all in the source tree and need to be copied to the sdk
COMPILE_ABC_WRAPPER  = $(topsrcdir)/aot-compiler/utils/compile-shell-abc.py
SHELLABC             = $(topsrcdir)/generated/shell_toplevel.abc
BUILTINABC           = $(topsrcdir)/generated/builtin.abc

#these are build results
COMPILE_ABC=$(curdir)/aot-compiler/compile-abc$(PROGRAM_SUFFIX)
RUN_COMPILE_ABC=$(EXE_WRAPPER) $(COMPILE_ABC)

# TODO:. this depends on being run AFTER hm-aot-sdk for runtime because want to use shell-fields.txt for runtime!
#
hm-aot-sdk: $(SHELLABC) $(BUILTINABC) $(COMPILE_ABC) $(COMPILE_ABC_WRAPPER)
	if test ! -d $(PSEUDO_SDK); then \
		echo no  $(PSEUDO_SDK) suggests you have not run hm-aot-sdk from runtime yet..; \
		exit 2;\
	fi
	cp -fp $(COMPILE_ABC_WRAPPER) $(PSEUDO_SDK)/bin
	cp -fp $(COMPILE_ABC) $(PSEUDO_SDK)/bin
	cp -fp $(SHELLABC) $(PSEUDO_SDK)
	rm -f builtin_abc.$(OBJ_SUFFIX)
	$(RUN_COMPILE_ABC) -mtriple=$(MTRIPLE) -sdk $(SHELLABC) -fields $(PSEUDO_SDK)/shell-fields.txt -emit-sdk
	cp -fp builtin_abc.$(OBJ_SUFFIX)  $(PSEUDO_SDK)

#this requires the "staging area" (aka pseudo-sdk) to have been built. 
hello_0.$(OBJ_SUFFIX): hm-aot-sdk $(curdir)/hello.abc
	$(RUN_COMPILE_ABC) -mtriple=$(MTRIPLE) -sdk $(PSEUDO_SDK) -fields $(SHELLFIELDS) $(curdir)/hello.abc

endif #ENABLE_HALFMOON_AOT_COMPILER


