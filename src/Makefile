CUPTI_PATH=/opt/cuda/extras/CUPTI
INCLUDES=-I$(CUPTI_PATH)/include

ifndef OS
 OS   := $(shell uname)
 HOST_ARCH := $(shell uname -m)
endif

ifeq ($(OS),Windows_NT)
    export PATH := $(PATH):$(CUPTI_PATH)/libWin32:$(CUPTI_PATH)/libx64
    LIBS= -lcuda -L $(CUPTI_PATH)/libWin32 -L $(CUPTI_PATH)/libx64 -lcupti
    OBJ = obj
else
    ifeq ($(OS), Darwin)
        export DYLD_LIBRARY_PATH := $(DYLD_LIBRARY_PATH):$(CUPTI_PATH)/lib
        LIBS= -Xlinker -framework -Xlinker cuda -L $(CUPTI_PATH)/lib -lcupti
    else
        export LD_LIBRARY_PATH := $(LD_LIBRARY_PATH):$(CUPTI_PATH)/lib:$(CUPTI_PATH)/lib64
        LIBS= -lcuda -L $(CUPTI_PATH)/lib -L $(CUPTI_PATH)/lib64 -lcupti
    endif
    OBJ = o
endif

all: cupti_trace cuda_sample

cupti_trace: cupti_trace.$(OBJ)
	nvcc -o $@ cupti_trace.$(OBJ) $(LIBS)

cupti_trace.$(OBJ): cupti_trace.cpp
	nvcc -c $(INCLUDES) $<

cuda_sample: cuda_sample.$(OBJ)
	nvcc -o $@ cuda_sample.$(OBJ) $(LIBS)

cuda_sample.$(OBJ): cuda_sample.cu
	nvcc -c $(INCLUDES) $<

clean:
	rm -f cupti_trace cupti_trace.$(OBJ) cuda_sample cuda_sample.$(OBJ)
