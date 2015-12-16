#!/usr/bin/env python
# -*- Mode: Python; indent-tabs-mode: nil; tab-width: 4 -*-
# vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5)
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

#export SDK=/Users/brbaker/dev/p4/stan/objdir-aot-sdk
#$SDK/bin/compile-abc -mtriple=i386-apple-darwin -filetype=obj -sdk $SDK/shell_toplevel.abc -fields $SDK/shell-fields.txt ../test/acceptance/Assert.abc ../test/acceptance/Utils.abc ../test/acceptance/as3/Types/Number/abs.abc
#gcc -arch i386 -L$SDK/lib -o abs $SDK/avmshellMac.o $SDK/builtin_abc.o aotInfo.o Assert_0.o Utils_1.o abs_2.o -llzma -lzlib -lavmplus -lMMgc -lvmbase -lshell -lstdc++

#Making changes for x86_64

import getopt,os,re,subprocess,sys,tempfile,shutil

class ShellCompiler:
    sdk_dir=None
    arch_name="i386"
    output=None
    work_dir=None
    abc_files=[]
    executable_name=None
    debug=False     #to help debug this script (notably leave built .o's in temp dir)
    verbose=False   #to help users see what wrapper is doing
    
    options=''
    longOptions=['sdk=','arch=','output=','verbose','debug']
    
    def __init__(self):
        self.parseOptions()
        
        # The executable_name must be a canonical path since compilation will happen in a temp dir
        if self.executable_name is None:
        	self.executable_name = os.path.realpath("".join(self.abc_files[-1:]).replace(".abc", ""))

        # Need to have the abc files be canoncial paths since compilation will happen in a temp dir
        temp_abcfile = self.abc_files
        self.abc_files = []
        for abc in temp_abcfile:
        	self.abc_files.append(os.path.realpath(abc))


        if self.debug:
            print("sdk: %s" % self.sdk_dir)
            print("arch: %s" % self.arch_name)
            print("output: %s" % self.output)
            print("abc_files: %s " % self.abc_files)
            print("exe name: %s " % self.executable_name)
        
       	try:
       		self.work_dir = tempfile.mkdtemp() 
            self.AOT_compile()
        	self.AOT_link()
        except OSError, e:
        	raise e
        finally:
            try:
                if self.debug :
                    print "debug: leaving tree", self.work_dir
                else:
                    shutil.rmtree(self.work_dir) # delete directory
    		except OSError, e:
        		if e.errno != 2: # code 2 - no such file or directory
            		raise

        
        
    def usage(self,c):
        print('usage: %s [options] [abc files]' % sys.argv[0])
        print('    --sdk         SDK root direcotry')
        print('    --arch        Architecture i386/x86_64')
        print('    --output      generated binary name')
        print('    --verbose     to see what wrapper is doing')
        print('    --debug       to see more of what wrapper is doing.. and not clean up intermediate files')
        sys.exit(c)

    def parseOptions(self):
        try:
            opts, self.abc_files = getopt.getopt(sys.argv[1:], self.options,self.longOptions)
        except:
            print(sys.exc_info()[1])
            self.usage(2)
        if not self.abc_files:
        	print("Must pass in at least one abc file to compile")
            print(sys.exc_info()[1])
            self.usage(2)

        print "opts",opts
        for o,v in opts:
            if o in ('--sdk',):
                dir_arg = v
                if not os.path.isdir(dir_arg) :
                    print "arg to --sdk must be a directory"
                    self.usage(3)
                self.sdk_dir=os.path.abspath(dir_arg)
            if o in ('--arch',):
                self.arch_name = v
            if o in ('--output',):
                self.executable_name=v
            if o in ('--verbose',):
                self.verbose = True
            if o in ('--debug',):
                self.debug = True
            
    def AOT_compile(self):
        base_options = "-mtriple=" + self.arch_name + "-apple-darwin -filetype=obj -sdk %s/shell_toplevel.abc -fields %s/shell-fields.txt" % (self.sdk_dir, self.sdk_dir)
        if self.debug:
            base_options +=" -save-ll -O0"

        # AOT Compile the ABC files
        cmd="%s/bin/compile-abc %s %s" % (self.sdk_dir, base_options, " ".join(self.abc_files))
        if self.debug or self.verbose:
            print("AOT compiling ABC files with the following command:")
            print(cmd)
            
        stdout,exit = self.run_pipe(cmd=cmd,cwd=self.work_dir)

        #echo the output of the compiler ont stdout of this script so user can see
        for line in stdout:
            print line


	def AOT_link(self):
        base_options = "-arch " + self.arch_name + " -L%s/lib -llzma -lzlib -lavmplus -lMMgc -lvmbase -lshell -lc++ " % (self.sdk_dir)

        # AOT Compile the ABC files
        cmd="gcc -w %s %s/avmshellMac.o %s/builtin_abc.o *.o -o %s" % (base_options, self.sdk_dir, self.sdk_dir, self.executable_name)
        if self.debug or self.verbose:
            print("AOT linking ABC files with the following command:")
            print(cmd)
            
        stdout,exit = self.run_pipe(cmd=cmd,cwd=self.work_dir)

        #print ld output too
        for line in stdout:
            print line


    #aotInfo.o Assert_0.o Utils_1.o abs_2.o -o abs

    def run_pipe(self, cmd, cwd=None, env=None):
        if cwd==None:
            cwd="./"
        # run a command and return a tuple of (output, exitCode)
        if env==None:
            process = subprocess.Popen(cmd,cwd=cwd,shell=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
        else:
            process = subprocess.Popen(cmd,cwd=cwd,shell=True,env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
        
        (output,err) = process.communicate()
        output = output.split('\n') if output else []
        if output and output[-1].strip() == '': # strip empty line at end
            output = output[:-1]

        exitCode = process.returncode
        return (output,exitCode)

    
if __name__ == '__main__':
    p = ShellCompiler()


