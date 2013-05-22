re-pcounter-tools
=================

This repository contains useful tools in order to reverse NVidia's performance
counters.

Dependencies
============
The CUDA toolkit provided by NVidia is required for building re-pcounter-tools.
You can download it from https://developer.nvidia.com/cuda-downloads.

Build
=====
A modified version of valgrind-mmt which traces NVidia ioctl calls and lookup
(envytools) are also required. In order to install them locally to this
repository, please run ./build.sh.

How to generate a complete report ?
===================================
cd src
./cupti_trace --trace <chipset>

