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

struct device_info *cuda_get_device_info(int id)
{
    struct device_info *device_info;
    CUdevice dev;
    CUresult res;

    if (!(device_info = (struct device_info *)malloc(sizeof(*device_info)))) {
        fprintf(stderr, "Out of memory.\n");
        return NULL;
    }
    device_info->id = id;

    // Returns a handle to a compute device.
    res = cuDeviceGet(&dev, device_info->id);
    CHECK_CU_ERROR(res, "cuDeviceGet");

    // Returns an identifer string for the device.
    res = cuDeviceGetName(device_info->name, sizeof(device_info->name), dev);
    CHECK_CU_ERROR(res, "cuDeviceGetName");

    // Returns the compute capability of the device.
    res = cuDeviceComputeCapability(&device_info->compute_capability_major,
                                    &device_info->compute_capability_minor,
                                    dev);
    CHECK_CU_ERROR(res, "cuDeviceComputeCapability");

    return device_info;
}

void cuda_print_device_info(struct device_info *device_info)
{
    printf("CUDA Device Id  : %d\n", device_info->id);
    printf("CUDA Device Name: %s\n", device_info->name);
    printf("CUDA Compute Capability: %d.%d\n",
           device_info->compute_capability_major,
           device_info->compute_capability_minor);
}
