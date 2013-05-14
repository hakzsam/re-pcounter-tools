#include <stdio.h>
#include <cuda.h>
#include <cupti.h>

#define NAME_SHORT      64
#define NAME_LONG       128
#define DESC_SHORT      512
#define DESC_LONG       2048
#define CATEGORY_LENGTH sizeof(CUpti_EventCategory)

#define CHECK_CU_ERROR(err, cufunc)                                            \
    if (err != CUDA_SUCCESS) {                                                 \
        fprintf(stderr, "%s:%d:Error %d for CUDA Driver API function '%s'.\n", \
                __FILE__, __LINE__, err, cufunc);                              \
        exit(-1);                                                              \
    }

#define CHECK_CUPTI_ERROR(err, cuptifunc)                                 \
    if (err != CUPTI_SUCCESS) {                                           \
        const char *errstr;                                               \
        cuptiGetResultString(err, &errstr);                               \
        fprintf(stderr, "%s:%d:Error %s for CUPTI API function '%s'.\n",  \
                __FILE__, __LINE__, errstr, cuptifunc);                   \
        exit(-1);                                                         \
    }

typedef struct ptiEventData_st {
    CUpti_EventID eventId;              // event id
    char eventName[NAME_SHORT];         // event name
    char shortDesc[DESC_SHORT];         // short desc of the event
    char longDesc[DESC_LONG];           // long desc of the event
    CUpti_EventCategory  category;      // category of the event
}ptiData;

struct domain {
    CUpti_EventDomainID id;             // domain id
    char name[NAME_SHORT];              // domain name
    uint32_t profiled_inst;             // number of domain instances (profiled)
    uint32_t total_inst;                // number of domain instances (total)
    ptiData *events;                    // array of events
    uint32_t numEvents;                 // number of events
} domain_st;

// add a null terminator to the end of a string if the string
// length equals the maximum length (as in that case there was no
// room to write the null terminator)
static void checkNullTerminator(char *str, size_t len, size_t max_len)
{
    if (len >= max_len) {
        str[max_len - 1] = '\0';
    }
}

static struct domain *getDomains(CUdevice dev, uint32_t *numDomains)
{
    CUptiResult ptiStatus = CUPTI_SUCCESS;
    CUpti_EventDomainID *domainId = NULL;
    struct domain *domains = NULL;
    size_t size = 0;

    ptiStatus = cuptiDeviceGetNumEventDomains(dev, numDomains);
    CHECK_CUPTI_ERROR(ptiStatus, "cuptiDeviceGetNumEventDomains");

    if (*numDomains == 0) {
        fprintf(stderr, "No domain is exposed by dev = %d.\n", dev);
        ptiStatus = CUPTI_ERROR_UNKNOWN;
        goto fail;
    }

    size = sizeof(CUpti_EventDomainID) * (*numDomains);
    domainId = (CUpti_EventDomainID *)calloc(1, size);
    if (domainId == NULL) {
        fprintf(stderr, "Failed to allocate memory to domain ID.\n");
        ptiStatus = CUPTI_ERROR_OUT_OF_MEMORY;
        goto fail;
    }

    domains = (struct domain *)calloc(1, sizeof(*domains) * (*numDomains));
    if (!domains) {
        fprintf(stderr, "Failed to allocated memory to domain data.\n");
        ptiStatus = CUPTI_ERROR_OUT_OF_MEMORY;
        goto fail;
    }

    ptiStatus = cuptiDeviceEnumEventDomains(dev, &size, domainId);
    CHECK_CUPTI_ERROR(ptiStatus, "cuptiDeviceEnumEventDomains");

    // enum domains
    for (uint32_t i = 0; i < *numDomains; i++) {
        struct domain *d = &domains[i];

        // domain id
        d->id = domainId[i];

        // domain name
        size = NAME_SHORT;
        ptiStatus = cuptiEventDomainGetAttribute(d->id,
                                                 CUPTI_EVENT_DOMAIN_ATTR_NAME,
                                                 &size,
                                                 (void *)d->name);
        checkNullTerminator(d->name, size, NAME_SHORT);
        CHECK_CUPTI_ERROR(ptiStatus, "cuptiEventDomainGetAttribute");

        // num of profiled instances in the domain
        size = sizeof(d->profiled_inst);
        ptiStatus = cuptiDeviceGetEventDomainAttribute(dev,
                                                       d->id,
                                                       CUPTI_EVENT_DOMAIN_ATTR_INSTANCE_COUNT, 
                                                       &size,
                                                       (void *)&d->profiled_inst);
        CHECK_CUPTI_ERROR(ptiStatus, "cuptiDeviceEventDomainGetAttribute");

        // num of total instances in the domain
        size = sizeof(d->total_inst);
        ptiStatus = cuptiDeviceGetEventDomainAttribute(dev,
                                                       d->id,
                                                       CUPTI_EVENT_DOMAIN_ATTR_TOTAL_INSTANCE_COUNT, 
                                                       &size,
                                                       (void *)&d->total_inst);
        CHECK_CUPTI_ERROR(ptiStatus, "cuptiDeviceEventDomainGetAttribute");
    }

fail:
    free(domainId);
    if (ptiStatus != CUPTI_SUCCESS)
        return NULL;

    return domains;
}

ptiData *getEventByDomain(CUpti_EventDomainID domainId, uint32_t *numEvents)
{
    ptiData *events;
    CUptiResult ptiStatus = CUPTI_SUCCESS;
    CUpti_EventID *eventId = NULL;
    size_t size = 0;

    // query num of events available in the domain
    ptiStatus = cuptiEventDomainGetNumEvents(domainId,
                                             numEvents);
    CHECK_CUPTI_ERROR(ptiStatus, "cuptiEventDomainGetNumEvents");

    size = sizeof(CUpti_EventID) * (*numEvents);
    eventId = (CUpti_EventID *)malloc(size);
    if (eventId == NULL) {
        fprintf(stderr, "Failed to allocate memory to event ID\n");
        return NULL;
    }
    memset(eventId, 0, size);

    if (!(events = (ptiData *)malloc(sizeof(*events) * (*numEvents)))) {
        fprintf(stderr, "Failed to allocate memory to event data.\n");
        return NULL;
    }

    ptiStatus = cuptiEventDomainEnumEvents(domainId,
                                           &size,
                                           eventId);
    CHECK_CUPTI_ERROR(ptiStatus, "cuptiEventDomainEnumEvents");

#define GET_EVENT_ATTRIBUTE(attr, valueSize, value)                         \
        size = valueSize;                                                   \
        ptiStatus = cuptiEventGetAttribute(event->eventId,                  \
                                           attr,                            \
                                           &size,                           \
                                           (uint8_t *)value);               \
        CHECK_CUPTI_ERROR(ptiStatus, "cuptiEventGetAttribute");             \
        checkNullTerminator(events->eventName, size, NAME_SHORT);

    // query event info
    for (uint32_t i = 0; i < *numEvents; i++) {
        ptiData *event = &events[i];

        event->eventId = eventId[i];
        GET_EVENT_ATTRIBUTE(CUPTI_EVENT_ATTR_NAME, NAME_SHORT,
                            event->eventName);
        GET_EVENT_ATTRIBUTE(CUPTI_EVENT_ATTR_SHORT_DESCRIPTION, DESC_SHORT,
                            event->shortDesc);
        GET_EVENT_ATTRIBUTE(CUPTI_EVENT_ATTR_LONG_DESCRIPTION, DESC_LONG,
                            event->longDesc);

        size = CATEGORY_LENGTH;
        ptiStatus = cuptiEventGetAttribute(events->eventId,
                                           CUPTI_EVENT_ATTR_CATEGORY,
                                           &size,
                                           (&event->category));
        CHECK_CUPTI_ERROR(ptiStatus, "cuptiEventGetAttribute");
    }

#undef GET_EVENT_ATTRIBUTE

    return events;
}

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
    if (!(domains = getDomains(dev, &numDomains))) {
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
        if (!(d->events = getEventByDomain(d->id, &d->numEvents))) {
            fprintf(stderr, "Failed to get events by domain.\n");
            ret = -1;
            goto fail;
        }

        for (uint32_t j = 0; j < d->numEvents; j++) {
            ptiData *event = &d->events[j];

            printf("\t\t<event>\n");
            printf("\t\t\t<id>%d</id>\n", event->eventId);
            printf("\t\t\t<name>%s</name>\n", event->eventName);
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
