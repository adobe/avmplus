To build on Windows 7 with Microsoft Visual Studio 11 ( 2012 ) 


** Make sure the following is installed on system:

Visual Studio 11 (2012 ) / Visual Studio 2013 
Cygwin 
  - Install 'python' version 2.7.3 using Cygwin's setup.exe
  - Install 'make: The GNU version of the 'make' utility'
  - Install 'makedepend: X Makefile dependency tool' 
    NOTE THAT THIS IS NOT THE DEFAULT CHOICE -- you have to click it a few
    times to get this version.
CMake (version 2.8):
  - cygwin version of cmake does not include generators for Visual Studio by 
    default, so you must install the windows native version (for now).
Python (version 2.7.3, into C:\Program Files\Python), 
  - (might be installed as part of CMake)
  - You need this even with cygwin's python because CMake will use this one
    and can't use cygwin's.
  - CMake will look for python in the folder "C:\Program Files\", so for a 
    64 bit machine python for 64 bit should be installed otherwise when the
    Makefile is run, it will find an old version of python (python 1.4) in Program Files.

** Before build:
 Make sure that visual studio version and python path are correct in avmplus/aot-compiler/util/Makefile

** To build:
32-bit Compiler: Go to Visual Studio Tools and Open Developer command prompt for your version of Visual studio
64-bit Compiler: Go to C:\Program Files (x86)\Common7\Tools\Shortcuts and start "VS2013 x64 Native Tools Command Prompt"

chdir <path to cygwin>\bin
bash --login -i

cd /cygdrive/d/....../code/third_party/avmplus; 
mkdir objdir
cd objdir
cp ../aot-compiler/utils/Makefile .
chmod 777 Makefile

#Build llvm 32-bit, 64-bit (should be done only once)
make -j8 llvm-sdk-32/llvm-sdk-64
NOTE:Somehow install step is skipping llvm/Config/config.h file so manually copy that file from 
<current_dir>/obj-llvm-32/include/llvm/Config/config.h to tools/products/Packager/llvm3.5/include/llvm/Config

#Build compiler ( if it fails please read NOTE below)
32-bit: make -j8 aot-compiler-32
64-bit: make -j8 aot-compiler-64

NOTE: With LLVM3.5, some more changes are required in the generated Makefile inside objdir-compiler-32. The changes are
-convert all '\' to '/' 
-convert all -ID:\<path> to -I/cygdrive/d/<path>. Don't convert path in LLVM_LDFLAGS.
-convert -L to -LIBPATH:
-convert all libraies from -lXXX  to XXX.lib

For 64-bit ml64.exe is required to compile 64-bit desktop assembly. So, add C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\bin\x86_amd64 to system path.

Now without deleting any folder try again
cd objdir-compiler-32
make -j8

If the Makefile is unable to build objdir/objdir-compiler/aot-compiler/compile-abc.exe by throwing an error which says:
link: unknown option -- n
Then cygwin's link.exe gets into the way of msvc's link.exe. Simply move it out of the way: 
mv /usr/bin/link.exe /usr/bin/link_cyg.exe #this renaming is used then cygwin update may install a new version of link.exe

Right now the recipe for aot-runtime fails.
- We were required to build only aot-compiler to package iOS applications from Windows which will be running on iOS devices
- But if we need to run the application on Windows phone then aot-runtime must be built successfully.

If you are building compile-abc.exe to check-in in the perforce. please make a release build and check-in at tools\products\Packager\compile-abc-windows