#include <stdio.h>
#include <cuda.h>
#include <cupti.h>

#include "cupti_extras.h"

int main(int argc, char **argv)
{
    CUdevice dev;
    CUresult err;
    CUptiResult cuptiErr = CUPTI_SUCCESS;
    int ret = 0;
    int deviceId = 0;
    int deviceCount = 0;
    int computeCapabilityMajor = 0, computeCapabilityMinor = 0;
    char deviceName[32];
    CUpti_EventDomainID domainId = 0;
    size_t size = 0;
    struct domain *domains;
    uint32_t numDomains;

    err = cuInit(0);
    CHECK_CU_ERROR(err, "cuInit");

    // number of devices
    err = cuDeviceGetCount(&deviceCount);
    CHECK_CU_ERROR(err, "cuDeviceGetCount");

    if (deviceCount == 0) {
        fprintf(stderr, "There is no device supporting CUDA.\n");
        ret = -2;
        goto fail;
    }

    // device id
    err = cuDeviceGet(&dev, deviceId);
    if (err == CUDA_ERROR_INVALID_DEVICE) {
        printf("Device (%d) out of range\n", deviceId);
        goto fail;
    }
    CHECK_CU_ERROR(err, "cuDeviceGet");

    // device name
    err = cuDeviceGetName(deviceName, 32, dev);
    CHECK_CU_ERROR(err, "cuDeviceGetName");

    // device compute capability
    err = cuDeviceComputeCapability(&computeCapabilityMajor,
                                    &computeCapabilityMinor,
                                    dev);
    CHECK_CU_ERROR(err, "cuDeviceComputeCapability");

    // display some useful informattions about the device
    printf("CUDA Device Id  : %d\n", deviceId);
    printf("CUDA Device Name: %s\n", deviceName);
    printf("CUDA Compute Capability: %d.%d\n\n", computeCapabilityMajor,
           computeCapabilityMinor);

    // get list of domains
    if (!(domains = cupti_getDomains(dev, &numDomains))) {
        fprintf(stderr, "Failed to get domains.\n");
        ret = -1;
        goto fail;
    }

    for (uint32_t i = 0; i < numDomains; i++) {
        struct domain *d = &domains[i];

        printf("<domain>\n");
        printf("\t<id>%d</id>\n", d->id);
        printf("\t<name>%s</name\n", d->name);
        printf("\t<profiled_inst>%d</profiled_inst>\n", d->profiled_inst);
        printf("\t<total_inst>%d</total_inst>\n", d->total_inst);
        printf("\t<events>\n");

        // get list of events in this domain
        if (!(d->events = cupti_getEventByDomain(d->id, &d->numEvents))) {
            fprintf(stderr, "Failed to get events by domain.\n");
            ret = -1;
            goto fail;
        }

        for (uint32_t j = 0; j < d->numEvents; j++) {
            ptiData *event = &d->events[j];

            printf("\t\t<event>\n");
            printf("\t\t\t<id>%d</id>\n", event->id);
            printf("\t\t\t<name>%s</name>\n", event->name);
            printf("\t\t\t<shortdesc>%s</shortdesc>\n", event->shortDesc);
            printf("\t\t\t<longdesc>%s</longdesc>\n", event->longDesc);

            printf("\t\t\t<category>\n");
            printf("\t\t\t\t<id>%d<id>\n", event->category);
            printf("\t\t\t\t<name>");
            switch (event->category) {
                case CUPTI_EVENT_CATEGORY_INSTRUCTION:
                    printf("INSTRUCTION");
                    break;
                case CUPTI_EVENT_CATEGORY_MEMORY:
                    printf("MEMORY");
                    break;
                case CUPTI_EVENT_CATEGORY_CACHE:
                    printf("CACHE");
                    break;
                case CUPTI_EVENT_CATEGORY_PROFILE_TRIGGER:
                    printf("PROFILE_TRIGGER");
                    break;
                default:
                    printf("UNKNOWN");
            }
            printf("</name>\n");
            printf("\t\t\t</category>\n");
            printf("\t\t</event>\n");
        }

        printf("\t</events>\n");
        printf("</domain>\n");
    }

fail:
    cudaDeviceSynchronize();
    return ret;
}
