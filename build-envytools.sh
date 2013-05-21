#!/bin/bash

git clone git://github.com/pathscale/envytools.git

cd envytools
mkdir build
cd build
cmake ..
make
