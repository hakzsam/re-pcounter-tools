#ifndef __CUDA_EXTRAS_H
#define __CUDA_EXTRAS_H

#include <stdio.h>
#include <cuda.h>

#define CHECK_CU_ERROR(err, cufunc)                                            \
    if (err != CUDA_SUCCESS) {                                                 \
        fprintf(stderr, "%s:%d:Error %d for CUDA Driver API function '%s'.\n", \
                __FILE__, __LINE__, err, cufunc);                              \
        exit(-1);                                                              \
    }

/**
 * \brief Initializes the driver API and must be called before any other
 *        function from the driver API.
 *
 * \return Returns the the number of devices with compute capability greater
 *         than or equal to 1.0 that are available for execution. If there is no
 *         such device, 0 is returned.
 */
int cuda_init();

#endif /* __CUDA_EXTRAS_H */
