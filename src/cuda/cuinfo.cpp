#include <stdio.h>
#include <cuda.h>

#include "cuda_extras.h"

#define DEVICE_NAME 512

struct device_info {
    int id;                         /**< device id */
    char name[DEVICE_NAME];         /**< device name */
    int compute_capability_major;   /**< major revision number */
    int compute_capability_minor;   /**< minor revision number */
    CUdevprop prop;                 /**< properties of the device */
} device_info_st;


/**
 * \brief Returns informations about the given device number.
 *        CUDA environement must be initialized before calling this function.
 *
 * \param id Device number to get handle for.
 */
static struct device_info *get_device_info(int id)
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

    // Returns properties for a selected device.
    res = cuDeviceGetProperties(&device_info->prop, dev);
    CHECK_CU_ERROR(res, "cuDeviceGetProperties");

    return device_info;
}

static void print_device_info(struct device_info *device_info)
{
    printf("CUDA Device Id  : %d\n", device_info->id);
    printf("CUDA Device Name: %s\n", device_info->name);
    printf("CUDA Compute Capability: %d.%d\n",
           device_info->compute_capability_major,
           device_info->compute_capability_minor);
    printf("CUDA Max Threads Per Block: %d\n",
           device_info->prop.maxThreadsPerBlock);
    printf("CUDA Max Threads Dim: %d %d %d\n", device_info->prop.maxThreadsDim[0],
           device_info->prop.maxThreadsDim[1], device_info->prop.maxThreadsDim[2]);
    printf("CUDA Max Grid Size: %d %d %d\n", device_info->prop.maxGridSize[0],
           device_info->prop.maxGridSize[1], device_info->prop.maxGridSize[2]);
    printf("CUDA Shared Mem Per Block: %d\n", device_info->prop.sharedMemPerBlock);
    printf("CUDA Total Constant Memory: %d\n", device_info->prop.totalConstantMemory);
    printf("CUDA SIMD Width: %d\n", device_info->prop.SIMDWidth);
    printf("CUDA Mem Pitch: %d\n", device_info->prop.memPitch);
    printf("CUDA Regs Per Block: %d\n", device_info->prop.regsPerBlock);
    printf("CUDA Clock Rate: %d\n", device_info->prop.clockRate);
    printf("CUDA Texture Align: %d\n", device_info->prop.textureAlign);
}

int main(int argc, char **argv)
{
    struct device_info *device_info;
    CUresult res;
    int count;

    if (!cuda_init()) {
        fprintf(stderr, "There is no device supporting CUDA.\n");
        exit(-1);
    }

    // Returns and displays informations about the device.
    device_info = get_device_info(0);
    if (device_info) {
        print_device_info(device_info);
    }

    free(device_info);

    return 0;
}
