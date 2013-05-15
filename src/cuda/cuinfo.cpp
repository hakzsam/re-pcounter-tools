#include <stdio.h>
#include <cuda.h>

#include "cuda_extras.h"

int main(int argc, char **argv)
{
    struct device_info *device_info;
    int device_num = 0; /* Assuming device 0 by default */

    printf("Usage: %s [device_num]\n", argv[0]);

    if (!cuda_init()) {
        fprintf(stderr, "There is no device supporting CUDA.\n");
        return -1;
    }

    if (argc > 1) {
        device_num = atoi(argv[1]);
    }

    device_info = cuda_get_device_info(device_num);
    if (device_info) {
        cuda_print_device_info(device_info);
    }

    free(device_info);

    return 0;
}
