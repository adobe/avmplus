# build hm-aot

# Warning, this Makefiles makes assumptions about how you have mapped your P4 client.
# Specifically, it assumes you have mapped:
# //depot/users/stan/V11halfmoonAOT/code/... 
# //depot/users/stan/V11halfmoonAOT/tools/...
# //Runtime/unbranched
# to all be in the same directory of your workspace, 

# the simplest way to use this Makefile:
# 1. cd to the directory mapped to //depot/main/FlashRuntime/Main/code/third_party/avmplus
# 2. mkdir objdir
# 3. cd objdir
# 4. cp ../aot-compiler/utils/Makefile .
# 5. make
#
# objdir can be anywhere but then you will have to edit a few macros below. eg. MAIN_MAPPED_DIR.
# 
#
P4_CLIENT_ROOT               = $(PWD)/../../../../
AVMPLUS                      = $(P4_CLIENT_ROOT)/code/third_party/avmplus

OBJDIR                       = .

LLVM_VER                     = 3.5

UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
        OS=darwin
else
        OS=windows
endif

darwin_TRIPLE_32 = x86-apple-darwin
darwin_TARGET_32 = i686-darwin

darwin_TRIPLE_64 = x86_64-apple-darwin
darwin_TARGET_64 = x86_64-darwin

# TRADITIONAL in this context means: ./configure; make; etc.
darwin_LLVM_BUILD_SYS = TRADITIONAL

windows_TRIPLE_32 = i686-pc-win32
windows_TARGET_32 = i686-win32
windows_TRIPLE_64 = x86_64-pc-win32
windows_TARGET_64 = x86_64-win32
windows_LLVM_BUILD_SYS = CMAKE

TRIPLE_32=$($(OS)_TRIPLE_32)
TARGET_32=$($(OS)_TARGET_32)
TRIPLE_64=$($(OS)_TRIPLE_64)
TARGET_64=$($(OS)_TARGET_64)
LLVM_BUILD_SYS=$($(OS)_LLVM_BUILD_SYS)

#Min supported osx = 10.6
export MACOSX_DEPLOYMENT_TARGET=10.7

# set LLVM_DEBUG 1 link to llvm Debug build, default llvm Release build
# nb. llvm debug compiles about 10x more slowly than release
#LLVM_DEBUG=1

# set AOT_COMPILER_DEBUG 1 to make a debug AOT compiler. default Release build
#AOT_COMPILER_DEBUG=1

# set AOT_RUNTIME_DEBUG 1 to make a debug AOT runtime. default Release build
#AOT_RUNTIME_DEBUG=1

ifeq ($(LLVM_DEBUG),1)
	LLVM_FLAVOR              =DEBUG
	LLVM_SDK_32                 =$(P4_CLIENT_ROOT)/tools/products/Packager/llvm$(LLVM_VER)-debug/$(TRIPLE_32)
	LLVM_SDK_64                 =$(P4_CLIENT_ROOT)/tools/products/Packager/llvm$(LLVM_VER)-debug/$(TRIPLE_64)
else
	LLVM_FLAVOR              =RELEASE
	LLVM_SDK_32                 =$(P4_CLIENT_ROOT)/tools/products/Packager/llvm$(LLVM_VER)/$(TRIPLE_32)
	LLVM_SDK_64                 =$(P4_CLIENT_ROOT)/tools/products/Packager/llvm$(LLVM_VER)/$(TRIPLE_64)
endif

ifeq ($(AOT_COMPILER_DEBUG),1)
	AOT_COMPILER_ENABLE_DEBUG = --enable-debug
	OBJDIR_HALFMOON_AOT_COMPILER_32 = $(OBJDIR)/objdir-compiler-debug-32
	OBJDIR_HALFMOON_AOT_COMPILER_64 = $(OBJDIR)/objdir-compiler-debug-64
else
	OBJDIR_HALFMOON_AOT_COMPILER_32 = $(OBJDIR)/objdir-compiler-32
	OBJDIR_HALFMOON_AOT_COMPILER_64 = $(OBJDIR)/objdir-compiler-64
endif #AOT_COMPILER_DEBUG

ifeq ($(AOT_RUNTIME_DEBUG),1)
	AOT_RUNTIME_ENABLE_DEBUG = --enable-debug
	OBJDIR_HALFMOON_AOT_RUNTIME_32  = $(OBJDIR)/objdir-runtime-debug-32
	OBJDIR_HALFMOON_AOT_RUNTIME_64  = $(OBJDIR)/objdir-runtime-debug-64
else
	OBJDIR_HALFMOON_AOT_RUNTIME_32  = $(OBJDIR)/objdir-runtime-32
	OBJDIR_HALFMOON_AOT_RUNTIME_64  = $(OBJDIR)/objdir-runtime-64
endif #AOT_RUNTIME_DEBUG

CONFIGURE_HALFMOON_AOT_COMPILER_32 = \
	../../configure.py \
         $(AOT_COMPILER_ENABLE_DEBUG) \
		--enable-halfmoon-aot-compiler 	--enable-halfmoon \
		--enable-jit  --enable-debugger --disable-eval \
		--enable-llvm=$(LLVM_SDK_32) --target=$(TARGET_32)

CONFIGURE_HALFMOON_AOT_COMPILER_64 = \
	../../configure.py \
         $(AOT_COMPILER_ENABLE_DEBUG) \
		--enable-halfmoon-aot-compiler 	--enable-halfmoon \
		--enable-jit  --enable-debugger --disable-eval \
		--enable-llvm=$(LLVM_SDK_64) --target=$(TARGET_64)

CONFIGURE_HALFMOON_AOT_RUNTIME_32 = \
	../../configure.py \
         $(AOT_RUNTIME_ENABLE_DEBUG) \
		--enable-halfmoon-aot-runtime  --enable-aot --disable-halfmoon \
		--disable-jit --enable-debugger --disable-eval \
		--target=$(TARGET_32)

CONFIGURE_HALFMOON_AOT_RUNTIME_64 = \
	../../configure.py \
         $(AOT_RUNTIME_ENABLE_DEBUG) \
		--enable-halfmoon-aot-runtime  --enable-aot --disable-halfmoon \
		--disable-jit --enable-debugger --disable-eval

all_32: hm-aot-sdk-32
	ls -l $(OBJDIR)/hm-aot-sdk

all_64: hm-aot-sdk-64
	ls -l $(OBJDIR)/hm-aot-sdk

all: all_32 all_64


hm-aot-sdk-32: aot-compiler-32 aot-runtime-32
	cd $(OBJDIR_HALFMOON_AOT_RUNTIME_32);   $(MAKE)  hm-aot-sdk
	cd $(OBJDIR_HALFMOON_AOT_COMPILER_32);  $(MAKE)  hm-aot-sdk

hm-aot-sdk-64: aot-compiler-64 aot-runtime-64
	cd $(OBJDIR_HALFMOON_AOT_RUNTIME_64);   $(MAKE)  hm-aot-sdk
	cd $(OBJDIR_HALFMOON_AOT_COMPILER_64);  $(MAKE)  hm-aot-sdk


aot-compiler-32: $(LLVM_SDK_32)
	if test ! -d $(OBJDIR_HALFMOON_AOT_COMPILER_32); then \
		mkdir -p  $(OBJDIR_HALFMOON_AOT_COMPILER_32); \
		cd $(OBJDIR_HALFMOON_AOT_COMPILER_32); $(CONFIGURE_HALFMOON_AOT_COMPILER_32); \
	fi
	cd $(OBJDIR_HALFMOON_AOT_COMPILER_32); $(MAKE) 

aot-compiler-64: $(LLVM_SDK_64)
	if test ! -d $(OBJDIR_HALFMOON_AOT_COMPILER_64); then \
		mkdir -p  $(OBJDIR_HALFMOON_AOT_COMPILER_64); \
		cd $(OBJDIR_HALFMOON_AOT_COMPILER_64); $(CONFIGURE_HALFMOON_AOT_COMPILER_64); \
	fi
	cd $(OBJDIR_HALFMOON_AOT_COMPILER_64); $(MAKE)


aot-runtime-32:
	if test ! -d $(OBJDIR_HALFMOON_AOT_RUNTIME_32); then \
		mkdir -p $(OBJDIR_HALFMOON_AOT_RUNTIME_32); \
		cd $(OBJDIR_HALFMOON_AOT_RUNTIME_32); $(CONFIGURE_HALFMOON_AOT_RUNTIME_32); \
	fi
	cd $(OBJDIR_HALFMOON_AOT_RUNTIME_32);  $(MAKE) 

aot-runtime-64:
	if test ! -d $(OBJDIR_HALFMOON_AOT_RUNTIME_64); then \
		mkdir -p $(OBJDIR_HALFMOON_AOT_RUNTIME_64); \
		cd $(OBJDIR_HALFMOON_AOT_RUNTIME_64); $(CONFIGURE_HALFMOON_AOT_RUNTIME_64); \
	fi
	cd $(OBJDIR_HALFMOON_AOT_RUNTIME_64);  $(MAKE) 


$(LLVM_SDK_32):
	$(MAKE) -f ../aot-compiler/utils/Makefile llvm-sdk-32

$(LLVM_SDK_64):
	$(MAKE) -f ../aot-compiler/utils/Makefile llvm-sdk-64

############ only if you need to build LLVM #################

LLVM_SRC_DIR         = $(P4_CLIENT_ROOT)/code/third_party/products/PackagerToolchain/llvm$(LLVM_VER)
LLVM_INSTALL_DIR_32     = $(LLVM_SDK_32)
LLVM_INSTALL_DIR_64     = $(LLVM_SDK_64)
LLVM_INSTALL_DIR_WIN_32 = `cygpath -w $(LLVM_SDK_32)`
LLVM_INSTALL_DIR_WIN_64 = `cygpath -w $(LLVM_SDK_64)`
LLVM_SRC_DIR_WIN     = `cygpath -w $(LLVM_SRC_DIR)`

CMAKE_PREPARE      = unset TMP TEMP tmp temp
CMAKE              = $(CMAKE_PREPARE); cmake

OBJDIR_LLVM_BUILD_DEBUG_32  = $(OBJDIR)/objdir-llvm-debug-32
OBJDIR_LLVM_BUILD_RELEASE_32 = $(OBJDIR)/objdir-llvm-32
OBJDIR_LLVM_BUILD_32 = $(OBJDIR_LLVM_BUILD_$(LLVM_FLAVOR)_32)

OBJDIR_LLVM_BUILD_DEBUG_64  = $(OBJDIR)/objdir-llvm-debug-64
OBJDIR_LLVM_BUILD_RELEASE_64 = $(OBJDIR)/objdir-llvm-64
OBJDIR_LLVM_BUILD_64 = $(OBJDIR_LLVM_BUILD_$(LLVM_FLAVOR)_64)

#TODO - remove --disable-compiler-version-checks
LLVM_CONFIGURE_TRADITIONAL_DEBUG_32 = \
	$(LLVM_SRC_DIR)/configure \
		--enable-targets=x86,arm --disable-docs --disable-jit \
		--host=i686-apple-darwin11 \
		--prefix=$(LLVM_INSTALL_DIR_32) --disable-optimized --enable-assertions --enable-cxx11 --enable-libcpp 

LLVM_CONFIGURE_TRADITIONAL_DEBUG_64 = \
	$(LLVM_SRC_DIR)/configure \
		--enable-targets=x86,arm,arm64 --disable-docs --disable-jit \
		--prefix=$(LLVM_INSTALL_DIR_64) --disable-optimized --enable-assertions --enable-cxx11 --enable-libcpp 

LLVM_CONFIGURE_TRADITIONAL_RELEASE_32 = \
	$(LLVM_SRC_DIR)/configure \
		--enable-targets=x86,arm --disable-docs --disable-jit \
		--host=i686-apple-darwin11 \
		--prefix=$(LLVM_INSTALL_DIR_32) --enable-optimized --disable-assertions  --enable-cxx11 --enable-libcpp 

LLVM_CONFIGURE_TRADITIONAL_RELEASE_64 = \
	$(LLVM_SRC_DIR)/configure \
		--enable-targets=x86,arm,arm64 --disable-docs --disable-jit \
		--prefix=$(LLVM_INSTALL_DIR_64) --enable-optimized --disable-assertions --enable-cxx11 --enable-libcpp 


LLVM_CONFIGURE_CMAKE_DEBUG_32 = \
	$(CMAKE) -G "Visual Studio 12" \
		 -DCMAKE_BUILD_TYPE:STRING=debug \
		 -DPYTHON_EXECUTABLE:FILEPATH="C:\Program Files\Python276\python.exe" \
		 -DCMAKE_INSTALL_PREFIX:PATH=$(LLVM_INSTALL_DIR_WIN_32) \
		 -DLLVM_TARGETS_TO_BUILD:STRING=X86\;ARM \
		 -DLLVM_USE_CRT_DEBUG:STRING=MTd \
		 -DLLVM_BUILD_32_BITS:BOOL=ON \
		 $(LLVM_SRC_DIR_WIN)
LLVM_CONFIGURE_CMAKE_RELEASE_32 = \
	$(CMAKE) -G "Visual Studio 12" \
		 -DCMAKE_BUILD_TYPE:STRING=Release \
		 -DPYTHON_EXECUTABLE:FILEPATH="C:\Program Files\Python276\python.exe" \
		 -DCMAKE_INSTALL_PREFIX:PATH=$(LLVM_INSTALL_DIR_WIN_32) \
		 -DLLVM_TARGETS_TO_BUILD:STRING=X86\;ARM \
		 -DLLVM_USE_CRT_RELEASE:STRING=MT \
		 -DLLVM_BUILD_32_BITS:BOOL=ON \
		 $(LLVM_SRC_DIR_WIN)
LLVM_CONFIGURE_CMAKE_DEBUG_64 = \
	$(CMAKE) -G "Visual Studio 12 Win64" \
		 -DCMAKE_BUILD_TYPE:STRING=debug \
		 -DPYTHON_EXECUTABLE:FILEPATH="C:\Program Files\Python276\python.exe" \
		 -DCMAKE_INSTALL_PREFIX:PATH=$(LLVM_INSTALL_DIR_WIN_64) \
		 -DLLVM_USE_CRT_DEBUG:STRING=MTd \
		 $(LLVM_SRC_DIR_WIN)
LLVM_CONFIGURE_CMAKE_RELEASE_64 = \
	$(CMAKE) -G "Visual Studio 12 Win64" \
		 -DCMAKE_BUILD_TYPE:STRING=Release \
		 -DPYTHON_EXECUTABLE:FILEPATH="C:\Program Files\Python276\python.exe" \
		 -DCMAKE_INSTALL_PREFIX:PATH=$(LLVM_INSTALL_DIR_WIN_64) \
		 -DLLVM_USE_CRT_RELEASE:STRING=MT \
		 $(LLVM_SRC_DIR_WIN)
LLVM_CONFIGURE_32 = $(LLVM_CONFIGURE_$(LLVM_BUILD_SYS)_$(LLVM_FLAVOR)_32)
LLVM_CONFIGURE_64 = $(LLVM_CONFIGURE_$(LLVM_BUILD_SYS)_$(LLVM_FLAVOR)_64)

LLVM_BUILD_TRADITIONAL = $(MAKE)
LLVM_BUILD_CMAKE = $(CMAKE) --build . --config $(LLVM_FLAVOR)
LLVM_BUILD = $(LLVM_BUILD_$(LLVM_BUILD_SYS))


LLVM_INSTALL_TRADITIONAL = $(MAKE) install
LLVM_INSTALL_CMAKE = $(CMAKE) --build . --config $(LLVM_FLAVOR) --target INSTALL
LLVM_INSTALL = $(LLVM_INSTALL_$(LLVM_BUILD_SYS))


llvm-sdk-32: llvm-install-32 
	ls -l $(LLVM_INSTALL_DIR_32)

llvm-sdk-64: llvm-install-64 
	ls -l $(LLVM_INSTALL_DIR_64)


llvm-install-32: llvm-build-32
	(cd $(OBJDIR_LLVM_BUILD_32); $(LLVM_INSTALL))

llvm-install-64: llvm-build-64
	(cd $(OBJDIR_LLVM_BUILD_64); $(LLVM_INSTALL))

llvm-build-32:
	if test ! -d $(OBJDIR_LLVM_BUILD_32); 	then \
		mkdir -p $(OBJDIR_LLVM_BUILD_32); \
		cd $(OBJDIR_LLVM_BUILD_32); $(LLVM_CONFIGURE_32); \
	fi
	cd $(OBJDIR_LLVM_BUILD_32); $(LLVM_BUILD)

llvm-build-64:
	if test ! -d $(OBJDIR_LLVM_BUILD_64); 	then \
		mkdir -p $(OBJDIR_LLVM_BUILD_64); \
		cd $(OBJDIR_LLVM_BUILD_64); $(LLVM_CONFIGURE_64); \
	fi
	cd $(OBJDIR_LLVM_BUILD_64); $(LLVM_BUILD)

############ additional goodies. mostly intended to document recipies #################

avmfeatures:
ifdef ASC
ifdef AVMSHELL_TOOL
	echo "Generating avmfeatures using ASC=$(ASC)"
	echo "Generating avmfeatures using AVMSHELL_TOOL=$(AVMSHELL_TOOL)"
	( \
		cd core \
		&& \
		java -jar $(ASC) -import ../generated/builtin.abc -import ../generated/shell_toplevel.abc -AS3 avmfeatures.as \
		&& \
		~/wrk-aot/avmshell-interpreter avmfeatures.abc\
	)
else
	$(MSG)true "Skipping avmfeatures since AVMSHELL_TOOL unset"
endif
else
	$(MSG)true "Skipping avmfeatures since ASC unset"
endif

# if the client spec is such that tools, code, and unbranched are all subdirs of the same dir
ASC  ?= $(P4_CLIENT_ROOT)/tools/asc/asc.jar

hello:
ifdef ASC
	$(MSG)true "compiling hello.as using ASC=$(ASC)"
	java -jar $(ASC) $(AVMPLUS)/halfmoon/test/hello.as
	rm -f ./hello
	hm-aot-sdk/bin/compile-shell-abc.py --verbose --debug --output=$(PWD)/hello --sdk=./hm-aot-sdk $(AVMPLUS)/halfmoon/test/hello.abc
	ls -l hello
	./hello
	$(MSG)true hello ran and returned zero
else
	$(MSG)true "Skipping compiling acceptance tests since ASC unset"
endif

#to run all the as3 tests shorten this to just as3
TESTS ?= as3/Math/MathUtils.as

#output dir for tests
OUTDIR ?=/tmp

#optional arguments to runtests.py ( -d for debug )
OPTARGS ?=

#Parallel threads 
THREADS ?= `sysctl -n hw.ncpu`

#Configuration
CONFIG ?= x86-HMA-asc1

#support for ASC2
ifdef ASH
ASHARG =--ash=$(ASH)
else
ASHARG =
endif


compile-acceptance:
ifdef ASC
	echo "compiling acceptance tests using ASC=$(ASC)"
	( \
		cd $(AVMPLUS)/test/acceptance \
		&& \
		./runtests.py \
			-v \
			$(OPTARGS) \
			--aotmode=HM \
			--asc=$(ASC)  --config=$(CONFIG) \
			$(ASHARG) \
			--builtinabc=../../generated/builtin.abc \
			--shellabc=../../generated/shell_toplevel.abc \
			--aotsdk=../../objdir-hm-aot/hm-aot-sdk \
			--aotout=$(OUTDIR) \
			--log ../../objdir-hm-aot/compiletests-$(CONFIG).txt  \
			--rebuildtests --cleanexit --showtimes --threads=$(THREADS) $(TESTS) \
		&& \
		../util/convertAcceptanceToJunit.py \
			--toplevel=compile \
			--type=aot \
			--ifile=../../objdir-hm-aot/compiletests-$(CONFIG).txt \
			--ofile=../../objdir-hm-aot/compiletests-$(CONFIG).xml \
	)
else
	$(MSG)true "Skipping compiling acceptance tests since ASC unset"
endif


run-acceptance:
	( \
		cd $(AVMPLUS)/test/acceptance \
		&& \
		./runtests.py \
		-v \
		$(OPTARGS) \
		--aotmode=HM \
		--asc=$(ASC)  --config=$(CONFIG) \
		$(ASHARG) \
		--builtinabc=../../generated/builtin.abc \
		--shellabc=../../generated/shell_toplevel.abc \
		--aotsdk=../../objdir-hm-aot/hm-aot-sdk \
		--aotout=$(OUTDIR) \
		--log ../../objdir-hm-aot/runtests-$(CONFIG).txt \
		--logjunit=../../objdir-hm-aot/runtests-$(CONFIG).xml \
		--logjunitname=$(CONFIG).runtests \
		--showtimes --threads=$(THREADS) $(TESTS) \
	)

compile-perf:
ifdef ASC
	echo "compiling acceptance tests using ASC=$(ASC)"
	( \
		cd $(AVMPLUS)/test/performance \
		&& \
		./runtests.py \
			-v \
			$(OPTARGS) \
			--aotmode=HM \
			--asc=$(ASC)  --config=$(CONFIG) \
			$(ASHARG) \
			--builtinabc=../../generated/builtin.abc \
			--shellabc=../../generated/shell_toplevel.abc \
			--aotsdk=../../objdir-hm-aot/hm-aot-sdk \
			--aotout=$(OUTDIR) \
			--log ../../objdir-hm-aot/compiletests_perf-$(CONFIG).txt  \
			--rebuildtests --cleanexit --showtimes --threads=$(THREADS) $(TESTS) \
		&& \
		../util/convertAcceptanceToJunit.py \
			--toplevel=compile_perf \
			--type=aot \
			--ifile=../../objdir-hm-aot/compiletests_perf-$(CONFIG).txt \
			--ofile=../../objdir-hm-aot/compiletests_perf-$(CONFIG).xml \
	)
else
	$(MSG)true "Skipping compiling acceptance tests since ASC unset"
endif


run-perf:
	( \
		cd $(AVMPLUS)/test/performance \
		&& \
		./runtests.py \
		-v \
		$(OPTARGS) \
		--aotmode=HM \
		--asc=$(ASC)  --config=$(CONFIG) \
		$(ASHARG) \
		--builtinabc=../../generated/builtin.abc \
		--shellabc=../../generated/shell_toplevel.abc \
		--aotsdk=../../objdir-hm-aot/hm-aot-sdk \
		--aotout=$(OUTDIR) \
		--log ../../objdir-hm-aot/runtests_perf-$(CONFIG).txt \
		--logjunit=../../objdir-hm-aot/runtests_perf-$(CONFIG).xml \
		--logjunitname=$(CONFIG).runtests_perf \
		--showtimes  --threads=$(THREADS) $(TESTS) \
	)


really-clean:
	rm -rf $(OBJDIR_HALFMOON_AOT_RUNTIME) $(OBJDIR_HALFMOON_AOT_COMPILER) hm-aot-sdk

.PHONY: aot-compiler aot-runtime llvm-sdk llvm-install llvm-build  hm-aot-sdk avmfeatures compile-acceptance hello
