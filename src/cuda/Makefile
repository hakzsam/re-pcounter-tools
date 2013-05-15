ROOT=/opt/cuda/extras/CUPTI
INCLUDES=-I$(ROOT)/include

ifndef OS
 OS   := $(shell uname)
 HOST_ARCH := $(shell uname -m)
endif

ifeq ($(OS),Windows_NT)
    export PATH := $(PATH):$(ROOT)/libWin32:$(ROOT)/libx64
    LIBS= -lcuda -L $(ROOT)/libWin32 -L $(ROOT)/libx64 -lcupti
    OBJ = obj
else
    ifeq ($(OS), Darwin)
        export DYLD_LIBRARY_PATH := $(DYLD_LIBRARY_PATH):$(ROOT)/lib
        LIBS= -Xlinker -framework -Xlinker cuda -L $(ROOT)/lib -lcupti
    else
        export LD_LIBRARY_PATH := $(LD_LIBRARY_PATH):$(ROOT)/lib:$(ROOT)/lib64
        LIBS= -lcuda -L $(ROOT)/lib -L $(ROOT)/lib64 -lcupti
    endif
    OBJ = o
endif

cuinfo: cuinfo.$(OBJ) cuda_extras.$(OBJ)
	nvcc -o $@ cuinfo.$(OBJ) cuda_extras.$(OBJ) $(LIBS)

cuinfo.$(OBJ): cuinfo.cpp
	nvcc -c $(INCLUDES) $<

cuda_extras.$(OBJ): cuda_extras.cpp
	nvcc -c $(INCLUDES) $<

clean:
	rm -f cuinfo cuinfo.$(OBJ) cuda_extras.$(OBJ)
