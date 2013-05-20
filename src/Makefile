GCC		= gcc
NVCC		= nvcc
EXEC		= cupti_trace
CUDA_PATH	= /opt/cuda
CUDA_INC_PATH	= $(CUDA_PATH)/include
CUPTI_PATH	= $(CUDA_PATH)/extras/CUPTI
CUPTI_INC_PATH	= $(CUPTI_PATH)/include
INCLUDES	= -I$(CUDA_INC_PATH) -I$(CUPTI_INC_PATH)
LIBS		= -L$(CUPTI_PATH)/lib64 -lcupti -lcuda

cupti_trace: cupti_trace.o
	$(NVCC) -o $@ $< $(LIBS)

cupti_trace.o: cupti_trace.cpp
	$(NVCC) -c $(INCLUDES) $<

clean:
	rm -f cupti_trace cupti_trace.o
