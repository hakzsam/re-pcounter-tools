ROOT=/opt/cuda/extras/CUPTI
INCLUDES=-I$(ROOT)/include -I../cuda -I../cupti

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

callback_event: callback_event.$(OBJ) cuda_extras.o cupti_extras.o
	nvcc -o $@ callback_event.$(OBJ) cuda_extras.o cupti_extras.o $(LIBS)

callback_event.$(OBJ): callback_event.cu
	nvcc -c $(INCLUDES) $<

cuda_extras.$(OBJ): ../cuda/cuda_extras.cpp
	nvcc -c $(INCLUDES) $<

cupti_extras.$(OBJ): ../cupti/cupti_extras.cpp
	nvcc -c $(INCLUDES) $<
clean:
	rm -f callback_event callback_event.$(OBJ) cuda_extras.o cupti_extras.o
