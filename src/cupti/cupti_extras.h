#ifndef __CUPTI_EXTRAS_H
#define __CUPTI_EXTRAS_H

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
    CUpti_EventID id;                   // event id
    char name[NAME_SHORT];              // event name
    char shortDesc[DESC_SHORT];         // short desc of the event
    char longDesc[DESC_LONG];           // long desc of the event
    CUpti_EventCategory category;       // category of the event
}ptiData;

typedef struct domain {
    CUpti_EventDomainID id;             // domain id
    char name[NAME_SHORT];              // domain name
    uint32_t profiled_inst;             // number of domain instances (profiled)
    uint32_t total_inst;                // number of domain instances (total)
    ptiData *events;                    // array of events
    uint32_t numEvents;                 // number of events
} domain_st;

/**
 * \brief Find an event by name.
 *
 * \param device    The CUDA device.
 * \param eventName The name of the event to find.
 * \param event     The ID of the found event.
 *
 * \return Returns 1 if the event has been found, 0 otherwise.
 */
int cupti_findEvent(CUdevice device, const char *eventName, CUpti_EventID *event);

/**
 * \brief Get a list of domains in the device.
 *
 * \param device     The CUDA device.
 * \param numDomains The number of domains.
 *
 * \return Returns the list of domains when success, NULL otherwise.
 */
struct domain *cupti_getDomains(CUdevice device, uint32_t *numDomains);

/**
 * \brief Get a list of events in the domain.
 *
 * \param domain    The domain id.
 * \param numEvents The number of events.
 *
 * \return Returns the list of events when success, NULL otherwise.
 */
ptiData *cupti_getEventByDomain(CUpti_EventDomainID domain, uint32_t *numEvents);

#endif /* __CUPTI_EXTRAS_H */
