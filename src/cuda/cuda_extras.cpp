#include "cuda_extras.h"

int cuda_init()
{
    CUresult res;
    int count;

    res = cuInit(0);
    CHECK_CU_ERROR(res, "cuInit");

    res = cuDeviceGetCount(&count);
    CHECK_CU_ERROR(res, "cuDeviceGetCount");

    return count;
}
