#!/bin/bash

#
# Build valgrind-mmt.
#
valgrind_dir=valgrind-mmt
valgrind_git=https://github.com/envytools/valgrind.git
vex_dir=VEX
vex_git=https://github.com/envytools/VEX.git
prefix=$(echo $(pwd)/local)

if [ ! -d ${valgrind_dir} ]; then
    git clone ${valgrind_git} ${valgrind_dir}
    git clone ${vex_git} ${valgrind_dir}/${vex_dir}
    cd ${valgrind_dir}
    cd ${vex_dir} && git checkout -f VEX_3_10_BRANCH && cd ..
    git checkout -f mmt-3.10
    cd ..
else
    cd ${valgrind_dir} && git fetch origin && git rebase &&
    cd ${vex_dir} && git fetch origin && git rebase && cd ../..
fi

cd ${valgrind_dir} && ./autogen.sh && ./configure --prefix=${prefix} \
                   && make && make install && cd ..
if [ $? != 0 ]; then
    echo "Failed to build 'valgrind-mmt'"!
    exit 1
fi

#
# Build envytools.
#
envytools_dir=envytools
envytools_git=git://github.com/envytools/envytools.git

if [ ! -d ${envytools_dir} ]; then
    git clone ${envytools_git} ${envytools_dir}
else
    cd ${envytools_dir} && git fetch origin && git rebase && cd ..
fi
if [ $? != 0 ]; then
    echo "Failed to update 'envytools' repo!"
    exit 1
fi

cd ${envytools_dir} && mkdir -p build && cd build && cmake .. && make && cd ../..
if [ $? != 0 ]; then
    echo "Failed to build 'envytools'"!
    exit 1
fi

#
# Build cupti_trace.
#
cd src && make && cd ..
if [ $? != 0 ]; then
    echo "Failed to build 'cupti_trace'"!
    exit 1
fi
