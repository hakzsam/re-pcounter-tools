#include <stdio.h>
#include <cuda.h>

#include <cupti.h>

#define CHECK_CUPTI_ERROR(err, cuptifunc)                                 \
    if (err != CUPTI_SUCCESS) {                                           \
        const char *errstr;                                               \
        cuptiGetResultString(err, &errstr);                               \
        fprintf(stderr, "%s:%d:Error %s for CUPTI API function '%s'.\n",  \
                __FILE__, __LINE__, errstr, cuptifunc);                   \
        exit(-1);                                                         \
    }

#define CHECK_CU_ERROR(err, cufunc)                                            \
    if (err != CUDA_SUCCESS) {                                                 \
        fprintf(stderr, "%s:%d:Error %d for CUDA Driver API function '%s'.\n", \
                __FILE__, __LINE__, err, cufunc);                              \
        exit(-1);                                                              \
    }

// Structure to hold data collected by callback
typedef struct RuntimeApiTrace_st {
    CUpti_EventGroup eventGroup;
    CUpti_EventID eventId;
    uint64_t eventVal;
} RuntimeApiTrace_t;

// Device code
__global__ void vec_add(const int* A, const int* B, int* C, int N)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < N)
        C[i] = A[i] + B[i];
}

static void init_vec(int *vec, int n)
{
    int i;

    for (i = 0; i < n; i++)
        vec[i] = i;
}

static int run_vector_add()
{
    int N = 50000;
    size_t size = N * sizeof(int);
    int threadsPerBlock = 0;
    int blocksPerGrid = 0;
    int sum, i;
    int *h_A, *h_B, *h_C;
    int *d_A, *d_B, *d_C;

    // Allocate input vectors h_A and h_B in host memory
    h_A = (int*)malloc(size);
    h_B = (int*)malloc(size);
    h_C = (int*)malloc(size);

    // Initialize input vectors
    init_vec(h_A, N);
    init_vec(h_B, N);
    memset(h_C, 0, size);

    // Allocate vectors in device memory
    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);

    // Copy vectors from host memory to device memory
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    // Invoke kernel
    threadsPerBlock = 256;
    blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    vec_add<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);

    // Copy result from device memory to host memory
    // h_C contains the result in host memory
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    // Verify result
    for (i = 0; i < N; ++i) {
        sum = h_A[i] + h_B[i];
        if (h_C[i] != sum) {
            printf("kernel execution FAILED\n");
            goto Error;
        }
    }

    return 0;
Error:
    return -1;
}

void CUPTIAPI getEventValueCallback(void *userdata, CUpti_CallbackDomain domain,
                                    CUpti_CallbackId cbid,
                                    const CUpti_CallbackData *cbInfo)
{
    CUptiResult cuptiErr;
    RuntimeApiTrace_t *traceData = (RuntimeApiTrace_t*)userdata;
    size_t bytesRead;

    // This callback is enabled only for launch so we shouldn't see anything else.
    if (cbid != CUPTI_RUNTIME_TRACE_CBID_cudaLaunch_v3020) {
        printf("%s:%d: unexpected cbid %d\n", __FILE__, __LINE__, cbid);
        exit(-1);
    }

    if (cbInfo->callbackSite == CUPTI_API_ENTER) {
        cudaThreadSynchronize();
        cuptiErr = cuptiSetEventCollectionMode(cbInfo->context, 
                CUPTI_EVENT_COLLECTION_MODE_KERNEL);
        CHECK_CUPTI_ERROR(cuptiErr, "cuptiSetEventCollectionMode");
        cuptiErr = cuptiEventGroupEnable(traceData->eventGroup);
        CHECK_CUPTI_ERROR(cuptiErr, "cuptiEventGroupEnable");
    }

    if (cbInfo->callbackSite == CUPTI_API_EXIT) {
        bytesRead = sizeof (uint64_t);
        cudaThreadSynchronize();
        cuptiErr = cuptiEventGroupReadEvent(traceData->eventGroup, 
                CUPTI_EVENT_READ_FLAG_FORCE_INT, 
                traceData->eventId, 
                &bytesRead, &traceData->eventVal);
        CHECK_CUPTI_ERROR(cuptiErr, "cuptiEventGroupReadEvent");

        cuptiErr = cuptiEventGroupDisable(traceData->eventGroup);
        CHECK_CUPTI_ERROR(cuptiErr, "cuptiEventGroupDisable");
    }
}

static void cleanUp(int *h_A, int *h_B, int *h_C, int *d_A, int *d_B, int *d_C)
{
    if (d_A)
        cudaFree(d_A);
    if (d_B)
        cudaFree(d_B);
    if (d_C)
        cudaFree(d_C);

    // Free host memory
    if (h_A)
        free(h_A);
    if (h_B)
        free(h_B);
    if (h_C)
        free(h_C);
}

static uint64_t cupti_profile_event(CUdevice dev, CUpti_EventID event_id)
{
    CUpti_SubscriberHandle subscriber;
    CUpti_EventGroup event_group;
    RuntimeApiTrace_t trace;
    CUptiResult cupti_res;
    CUcontext context;
    CUresult cu_res;

    // Create a new CUDA context and associates it with the calling thread.
    cu_res = cuCtxCreate(&context, 0, dev);
    CHECK_CU_ERROR(cu_res, "cuCtxCreate");

    // Create a new event group for a context.
    cupti_res = cuptiEventGroupCreate(context, &event_group, 0);
    CHECK_CUPTI_ERROR(cupti_res, "cuptiEventGroupCreate");

    // Add an event to an event group.
    cupti_res = cuptiEventGroupAddEvent(event_group, event_id);
    CHECK_CUPTI_ERROR(cupti_res, "cuptiEventGroupAddEvent");

    // Configure trace.
    trace.eventGroup = event_group;
    trace.eventId    = event_id;

    // Initialize a callback subscriber with a callback function and user data.
    cupti_res = cuptiSubscribe(&subscriber,
            (CUpti_CallbackFunc)getEventValueCallback,
            &trace);
    CHECK_CUPTI_ERROR(cupti_res, "cuptiSubscribe");

    // Enable or disabled callbacks for a specific domain and callback ID.
    cupti_res = cuptiEnableCallback(1, subscriber, CUPTI_CB_DOMAIN_RUNTIME_API,
            CUPTI_RUNTIME_TRACE_CBID_cudaLaunch_v3020);
    CHECK_CUPTI_ERROR(cupti_res, "cuptiEnableCallback");

    // Run a CUDA sample.
    run_vector_add();

    // Unregister a callback subscriber.
    cupti_res = cuptiUnsubscribe(subscriber);
    CHECK_CUPTI_ERROR(cupti_res, "cuptiUnsubscribe");

    // Remove an event from an event group.
    cupti_res = cuptiEventGroupRemoveEvent(event_group, event_id);
    CHECK_CUPTI_ERROR(cupti_res, "cuptiEventGroupRemoveEvent");

    // Destroy an event group.
    cupti_res = cuptiEventGroupDestroy(event_group);
    CHECK_CUPTI_ERROR(cupti_res, "cuptiEventGroupDestroy");

    // Destroy the CUDA context.
    cu_res = cuCtxDestroy(context);
    CHECK_CU_ERROR(cu_res, "cuCtxDestroy");

    return trace.eventVal;
}

int main(int argc, char **argv)
{
    CUptiResult cupti_ret = CUPTI_SUCCESS;
    CUpti_EventID event_id;
    uint64_t event_val;
    int device_id = 0; /* Assuming device 0 by default */
    char *event_name;
    CUdevice dev = 0;
    int device_count;
    CUresult ret;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <event_name> [device_num]\n", argv[0]);
        return -1;
    }
    event_name = argv[1];

    if (argc > 2)
        device_id = atoi(argv[2]);

    ret = cuInit(0);
    CHECK_CU_ERROR(ret, "cuInit");

    ret = cuDeviceGetCount(&device_count);
    CHECK_CU_ERROR(ret, "cuDeviceGetCount");

    if (device_count == 0) {
        fprintf(stderr, "There is no device supporting CUDA.\n");
        return -1;
    }

    ret = cuDeviceGet(&dev, device_id);
    CHECK_CU_ERROR(ret, "cuDeviceGet");

    cupti_ret = cuptiEventGetIdFromName(dev, event_name, &event_id);
    CHECK_CUPTI_ERROR(cupti_ret, "cuptiEventGetIdFromName");

    event_val = cupti_profile_event(dev, event_id);

    printf("Event Name : %s \n",   event_name);
    printf("Event Value : %llu\n", (unsigned long long)event_val);

    cudaDeviceSynchronize();
    return 0;
}

