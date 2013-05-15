#include "cupti_extras.h"

static void checkNullTerminator(char *str, size_t len, size_t max_len);

int cupti_findEvent(CUdevice device, const char *eventName, CUpti_EventID *event)
{
    CUptiResult res;

    res = cuptiEventGetIdFromName(device, eventName, event);
    return res == CUPTI_SUCCESS;
}

struct domain *cupti_getDomains(CUdevice device, uint32_t *numDomains)
{
    CUptiResult ptiStatus = CUPTI_SUCCESS;
    CUpti_EventDomainID *domainId = NULL;
    struct domain *domains = NULL;
    size_t size = 0;

    ptiStatus = cuptiDeviceGetNumEventDomains(device, numDomains);
    CHECK_CUPTI_ERROR(ptiStatus, "cuptiDeviceGetNumEventDomains");

    if (*numDomains == 0) {
        fprintf(stderr, "No domain is exposed by device = %d.\n", device);
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

    ptiStatus = cuptiDeviceEnumEventDomains(device, &size, domainId);
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
        ptiStatus = cuptiDeviceGetEventDomainAttribute(device,
                                                       d->id,
                                                       CUPTI_EVENT_DOMAIN_ATTR_INSTANCE_COUNT,
                                                       &size,
                                                       (void *)&d->profiled_inst);
        CHECK_CUPTI_ERROR(ptiStatus, "cuptiDeviceEventDomainGetAttribute");

        // num of total instances in the domain
        size = sizeof(d->total_inst);
        ptiStatus = cuptiDeviceGetEventDomainAttribute(device,
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

ptiData *cupti_getEventByDomain(CUpti_EventDomainID domain, uint32_t *numEvents)
{
    ptiData *events;
    CUptiResult ptiStatus = CUPTI_SUCCESS;
    CUpti_EventID *eventId = NULL;
    size_t size = 0;

    // query num of events available in the domain
    ptiStatus = cuptiEventDomainGetNumEvents(domain,
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

    ptiStatus = cuptiEventDomainEnumEvents(domain,
                                           &size,
                                           eventId);
    CHECK_CUPTI_ERROR(ptiStatus, "cuptiEventDomainEnumEvents");

    // query event info
    for (uint32_t i = 0; i < *numEvents; i++) {
        ptiData *event = &events[i];

        event->id = eventId[i];

        // event name
        size = NAME_SHORT;
        ptiStatus = cuptiEventGetAttribute(event->id,
                                           CUPTI_EVENT_ATTR_NAME,
                                           &size,
                                           (uint8_t *)event->name);
        CHECK_CUPTI_ERROR(ptiStatus, "cuptiEventGetAttribute");
        checkNullTerminator(events->name, size, NAME_SHORT);

        // event short desc
        size = DESC_SHORT;
        ptiStatus = cuptiEventGetAttribute(event->id,
                                           CUPTI_EVENT_ATTR_SHORT_DESCRIPTION,
                                           &size,
                                           (uint8_t *)event->shortDesc);
        CHECK_CUPTI_ERROR(ptiStatus, "cuptiEventGetAttribute");
        checkNullTerminator(events->shortDesc, size, NAME_SHORT);

        // event long desc
        size = DESC_LONG;
        ptiStatus = cuptiEventGetAttribute(event->id,
                                           CUPTI_EVENT_ATTR_LONG_DESCRIPTION,
                                           &size,
                                           (uint8_t *)event->longDesc);
        CHECK_CUPTI_ERROR(ptiStatus, "cuptiEventGetAttribute");
        checkNullTerminator(events->shortDesc, size, NAME_SHORT);

        size = CATEGORY_LENGTH;
        ptiStatus = cuptiEventGetAttribute(events->id,
                                           CUPTI_EVENT_ATTR_CATEGORY,
                                           &size,
                                           (&event->category));
        CHECK_CUPTI_ERROR(ptiStatus, "cuptiEventGetAttribute");
    }

    return events;
}

static void checkNullTerminator(char *str, size_t len, size_t max_len)
{
    if (len >= max_len) {
        str[max_len - 1] = '\0';
    }
}
