# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# for AOT runtime build we want to create a library, libshell.a, to link
# otherwise build the avmshell executable.
#
ifeq (1,$(ENABLE_AOT))
STATIC_LIBRARIES += shell
shell_BUILD_ALL = 1
else
PROGRAMS += shell
shell_BASENAME = avmshell
shell_STATIC_LIBRARIES = lzma zlib avmplus MMgc vmbase
shell_DIR := $(curdir)/
endif

shell_INCLUDES += $(AVM_INCLUDES)
shell_INCLUDES += -I$(srcdir) -I$(topsrcdir)/extensions 
shell_DEFINES = -DAVMPLUS_SHELL

shell_EXTRA_CPPFLAGS := $(AVMSHELL_CPPFLAGS)
shell_EXTRA_LDFLAGS := $(AVMSHELL_LDFLAGS)

ifdef ENABLE_SHELL
shell_BUILD_ALL = 1
endif

shell_CXXSRCS := $(shell_CXXSRCS) \
  $(curdir)/avmshell.cpp \
  $(curdir)/ConsoleOutputStream.cpp \
  $(curdir)/DebugCLI.cpp \
  $(curdir)/DomainClass.cpp \
  $(curdir)/FileClass.cpp \
  $(curdir)/FileInputStream.cpp \
  $(curdir)/ShellCore.cpp \
  $(curdir)/SystemClass.cpp \
  $(curdir)/swf.cpp \
  $(curdir)/../extensions/SamplerScript.cpp \
  $(curdir)/../extensions/Selftest.cpp \
  $(curdir)/../extensions/SelftestInit.cpp \
  $(curdir)/../extensions/SelftestExec.cpp \
  $(curdir)/ShellWorkerGlue.cpp \
  $(curdir)/ShellWorkerDomainGlue.cpp \
  $(NULL)

ifeq (windows,$(TARGET_OS))
shell_CXXSRCS := $(shell_CXXSRCS) \
  $(curdir)/avmshellWin.cpp \
  $(curdir)/WinFile.cpp \
  $(NULL)
endif

ifeq (darwin,$(TARGET_OS))
shell_CXXSRCS := $(shell_CXXSRCS) \
  $(curdir)/avmshellMac.cpp \
  $(curdir)/PosixFile.cpp \
  $(curdir)/PosixPartialPlatform.cpp \
  $(NULL)
endif

ifeq (linux,$(TARGET_OS))
shell_CXXSRCS := $(shell_CXXSRCS) \
  $(curdir)/avmshellUnix.cpp \
  $(curdir)/PosixFile.cpp \
  $(curdir)/PosixPartialPlatform.cpp \
  $(NULL)
endif

ifeq (android,$(TARGET_OS))
shell_CXXSRCS := $(shell_CXXSRCS) \
  $(curdir)/avmshellUnix.cpp \
  $(curdir)/PosixFile.cpp \
  $(curdir)/PosixPartialPlatform.cpp \
  $(NULL)
endif

ifeq (sunos,$(TARGET_OS))
shell_CXXSRCS := $(shell_CXXSRCS) \
  $(curdir)/avmshellUnix.cpp \
  $(curdir)/PosixFile.cpp \
  $(curdir)/PosixPartialPlatform.cpp \
  $(NULL)
endif

# See manifest.mk in root directory for the dependencies
# on $(topsrcdir)/generated/shell_toplevel.h

# Use of '%' [to force a pattern-rule] instead of '$(curdir)/..' or
# '$(topsrcdir)' [which would then not be a pattern-rule] is crucial
# (ie "deliberate", ie "hack"); see Bug 632086
%/generated/shell_toplevel.h %/generated/shell_toplevel.cpp %/generated/shell_toplevel.abc: $(topsrcdir)/shell/shell_toplevel.as $(topsrcdir)/core/api-versions.as %/generated/builtin.abc
	cd $(topsrcdir)/shell; python shell_toplevel.py $(shell_BUILTINFLAGS)

.PHONY: shell-tracers
# Order dependence on core-tracers is to force a strict ordering
# because both tracer generation scripts will attempt to recompile
# exactgc.abc if it is missing.
shell-tracers: $(topsrcdir)/generated/builtin.abc $(topsrcdir)/generated/shell_toplevel.abc | core-tracers
ifdef AVMSHELL_TOOL
	$(MSG)true "Generating shell-tracers via AVMSHELL_TOOL=$(AVMSHELL_TOOL)"
	$(CMD)cd $(topsrcdir)/shell; AVM=$(AVMSHELL_TOOL) python ./shell_toplevel-tracers.py
else
	$(MSG)true "Skipping shell-tracers generation since AVMSHELL_TOOL unset"
endif

# 1. Use of '$(topsrcdir)/generated' is deliberate; we use absolute
#    paths for code being generated (or referenced) outside build dir.
#
# 2. Use of '$(curdir)/ShellCore.$(II_SUFFIX)' is also deliberate:
#    preprocessed file as target must be specified via same path that
#    is used in root manifest.mk.
#
# Further discussion at Bug 632086.
$(curdir)/ShellCore.$(II_SUFFIX): $(topsrcdir)/generated/shell_toplevel.cpp

#
# Generate shell field=offset data for AOT libraries
#
ifeq (1,$(ENABLE_HALFMOON_AOT_RUNTIME))
all:: shell-fields

SHELL_FIELDS_SRC := $(curdir)/avmshell-aot-fields.cpp
SHELL_FIELDS_OBJ := $(SHELL_FIELDS_SRC:%.cpp=%.$(OBJ_SUFFIX))
SHELL_FIELDS_IIFILE := $(SHELL_FIELDS_SRC:%.cpp=%.$(II_SUFFIX))

.PHONY: shell-fields
shell-fields: shell-fields.txt

shell-fields.txt: $(SHELL_FIELDS_OBJ)
	echo SHELL_FIELDS_SRC $(SHELL_FIELDS_SRC)
	$(CMD)python $(topsrcdir)/aot-compiler/generate-offset-data.py $< > $@

# careful: the final shell_CPPFLAGS, etc args aren't yet constructed, so use the vars that build them
fields_CPPFLAGS = $(COMPILE_CPPFLAGS) $(shell_EXTRA_CPPFLAGS)
fields_CXXFLAGS = $(COMPILE_CXXFLAGS) $(shell_EXTRA_CXXFLAGS)
fields_DEFINES = $(shell_DEFINES) $(DEFINES)
fields_INCLUDES = $(shell_INCLUDES) $(INCLUDES)

$(SHELL_FIELDS_OBJ):  $(SHELL_FIELDS_SRC)
	mkdir -p $(dir $(SHELL_FIELDS_IIFILE))  # shell dir might not exist yet..
	$(CMD)$(CXX) -E  $(fields_CPPFLAGS) $(fields_CXXFLAGS) $(fields_DEFINES) $(fields_INCLUDES) -c $< >  $(SHELL_FIELDS_IIFILE)
	$(CMD)$(CXX) $(OUTOPTION)$@ $(fields_CPPFLAGS) $(fields_CXXFLAGS) $(fields_DEFINES) $(fields_INCLUDES) -c $(SHELL_FIELDS_IIFILE)

$(SHELL_FIELDS_OBJ): $(topsrcdir)/aot/AOTfields-begin.h $(topsrcdir)/aot/AOTfields-end.h $(topsrcdir)/generated/builtin_aotslots.hh
endif #ENABLE_HALFMOON_AOT_RUNTIME
