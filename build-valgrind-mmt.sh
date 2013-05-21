#!/bin/bash
#
# This script builds a modified version of valgrind-mmt which displays
# NVidia ioctl calls.
#
VALGRIND="valgrind-mmt"
PREFIX=$(echo $(pwd)/local)

git clone git://people.freedesktop.org/~mslusarz/valgrind $VALGRIND
git clone git://people.freedesktop.org/~mslusarz/vex $VALGRIND/VEX

cd $VALGRIND
./autogen.sh
./configure --prefix=$PREFIX
git apply ../valgrind/trace_nv_ioctls.diff
make
make install
