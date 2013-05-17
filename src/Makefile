GCC		= gcc
NVCC		= nvcc
EXEC		= cupti_trace
CUDA_PATH	= /opt/cuda
CUDA_INC_PATH	= $(CUDA_PATH)/include
CUPTI_PATH	= $(CUDA_PATH)/extras/CUPTI
CUPTI_INC_PATH	= $(CUPTI_PATH)/include
INCLUDES	= -I$(CUDA_INC_PATH) -I$(CUPTI_INC_PATH)
LIBS		= -L$(CUPTI_PATH)/lib64 -lcupti -lcuda

cupti_trace: cupti_trace.o cupti_extras.o cuda_extras.o
	$(NVCC) -o $@ cupti_trace.o cupti_extras.o cuda_extras.o $(LIBS)

cupti_trace.o: cupti_trace.cpp
	$(NVCC) -c $(INCLUDES) $<

cupti_extras.o: cupti/cupti_extras.cpp
	$(NVCC) -c $(INCLUDES) $<

cuda_extras.o: cuda/cuda_extras.cpp
	$(NVCC) -c $(INCLUDES) $<

clean:
	rm -f cupti_trace cupti_trace.o cuda_extras.o cupti_extras.o
