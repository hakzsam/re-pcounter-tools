#include <stdio.h>
#include <cuda.h>

#include "cuda_extras.h"

int main(int argc, char **argv)
{
    struct device_info *device_info;

    if (!cuda_init()) {
        fprintf(stderr, "There is no device supporting CUDA.\n");
        return -1;
    }

    device_info = cuda_get_device_info(0);
    if (device_info) {
        cuda_print_device_info(device_info);
    }

    free(device_info);

    return 0;
}
