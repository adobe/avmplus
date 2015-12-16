#!/bin/bash -e

test "$WS" = "" && {
    echo WS must be set in the environment, should point to amvplus root dir
    exit
}

test "$ASC" = "" && {
    echo ASC must be set in the environment, should point to asc.jar
    exit
}

test "$MAKE_THREADS" = "" && {
    echo MAKE_THREADS not set, defaulting to 1, you really should be setting this...
    MAKE_THREADS=1
}



############################################
############################################
############################################
echo 
echo =======================================
echo         Build the AOT SDK
cd $WS
rm -rf objdir-hm-aot
make -j ${MAKE_THREADS} -f aot-compiler/utils/Makefile
echo =======================================





############################################
############################################
############################################
echo 
echo =======================================
echo         Run some acceptance tests
cd $WS/test/acceptance
export BUILTINABC=$WS/generated/builtin.abc
export SHELLABC=$WS/generated/shell_toplevel.abc
export SDK=$WS/objdir-hm-aot/hm-aot-sdk

rm -rf $WS/output

echo =======================================
echo         AOT Compile media
./runtests.py --aotsdk=$SDK --aotout=../../output --aotmode=HM --rebuildtests --cleanexit --showtimes --log compiletests.txt --config=x86-AOT-asc1 $TESTS
# convert compilation log to junit report
../util/convertAcceptanceToJunit.py --toplevel=compile --type=aot --ifile=compiletests.txt --ofile=compiletests.xml


echo =======================================
echo         Execute media
./runtests.py --aotsdk=$SDK --aotout=../../output --aotmode=HM --notimecheck  --showtimes --testtimeout=300 --log runtests.txt --logjunit=runtests.xml --logjunitname=$platform --config=x86-AOT-asc1 $TESTS
echo =======================================



