#ifndef __CUDA_EXTRAS_H
#define __CUDA_EXTRAS_H

#include <stdio.h>
#include <cuda.h>

#define DEVICE_NAME 512

#define CHECK_CU_ERROR(err, cufunc)                                            \
    if (err != CUDA_SUCCESS) {                                                 \
        fprintf(stderr, "%s:%d:Error %d for CUDA Driver API function '%s'.\n", \
                __FILE__, __LINE__, err, cufunc);                              \
        exit(-1);                                                              \
    }

typedef struct device_info {
    int id;                         /**< device id */
    char name[DEVICE_NAME];         /**< device name */
    int compute_capability_major;   /**< major revision number */
    int compute_capability_minor;   /**< minor revision number */
} device_info_st;

/**
 * \brief Initializes the driver API and must be called before any other
 *        function from the driver API.
 *
 * \return Returns the the number of devices with compute capability greater
 *         than or equal to 1.0 that are available for execution. If there is no
 *         such device, 0 is returned.
 */
int cuda_init();

/**
 * \brief Returns informations about the given device number.
 *        CUDA environement must be initialized before calling this function.
 *
 * \param id Device number to get handle for.
 */
struct device_info *cuda_get_device_info(int id);

/**
 * \brief Prints informations about the device.
 *
 * \param device_info Informations of the device.
 */
void cuda_print_device_info(struct device_info *device_info);

#endif /* __CUDA_EXTRAS_H */
