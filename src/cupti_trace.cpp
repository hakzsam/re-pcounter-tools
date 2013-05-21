#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

#include <cuda.h>
#include <cupti.h>

/**
 * TODO:
 *  - do not use lookup through popen() (it's bad).
 *  - use env vars for setting valgrind-mmt.
 *  - fix memleaks.
 *  - check error codes.
 */

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

#define SET_OPTS_FLAG(f)    (opts_flag |= (1 << f))
#define IS_OPTS_FLAG(f)     ((opts_flag & (1 << f)) ? 1 : 0)

static unsigned int opts_flag = 0;

struct event {
    CUpti_EventID id;                   // event id
    char name[NAME_SHORT];              // event name
    char short_desc[DESC_SHORT];        // short desc of the event
    char long_desc[DESC_LONG];          // long desc of the event
    CUpti_EventCategory category;       // category of the event
};

struct domain {
    CUpti_EventDomainID id;             // domain id
    char name[NAME_SHORT];              // domain name
    uint32_t profiled_inst;             // number of domain instances (profiled)
    uint32_t total_inst;                // number of domain instances (total)
    struct event *events;         // array of events
    uint32_t num_events;                // number of events
};

enum flags {
    FLAG_DEVICE_ID = 0,
    FLAG_DOMAIN_ID,
    FLAG_LIST_DOMAINS,
    FLAG_LIST_EVENTS,
    FLAG_LIST_METRICS,
    FLAG_TRACE
};

static void usage()
{
    printf("Usage: cupti_trace\n");
    printf("       --help                                                : displays help message\n");
    printf("       --device <dev_id> --list-domains                      : displays supported domains for specified device\n");
    printf("       --device <dev_id> --list-metrics                      : displays supported metrics for specified device\n");
    printf("       --device <dev_id> --domain <domain_id> --list-events  : displays supported events for specified domain and device\n");
    printf("       --trace <chipset>                                     : traces ioctl calls\n");
    printf("Note: default device is 0 and default domain is first domain for device\n");
}

static void check_null_terminator(char *str, size_t len, size_t max_len)
{
    if (len >= max_len) {
        str[max_len - 1] = '\0';
    }
}

struct domain *get_domains(CUdevice device, uint32_t *num_domains)
{
    CUpti_EventDomainID *domain_id = NULL;
    CUptiResult ret = CUPTI_SUCCESS;
    struct domain *domains = NULL;
    size_t size = 0;
    uint32_t i;

    ret = cuptiDeviceGetNumEventDomains(device, num_domains);
    CHECK_CUPTI_ERROR(ret, "cuptiDeviceGetNumEventDomains");

    if (*num_domains == 0) {
        fprintf(stderr, "No domain is exposed by device = %d.\n", device);
        ret = CUPTI_ERROR_UNKNOWN;
        goto fail;
    }

    size = sizeof(CUpti_EventDomainID) * (*num_domains);
    domain_id = (CUpti_EventDomainID *)calloc(1, size);
    if (domain_id == NULL) {
        fprintf(stderr, "Failed to allocate memory to domain ID.\n");
        ret = CUPTI_ERROR_OUT_OF_MEMORY;
        goto fail;
    }

    domains = (struct domain *)calloc(1, sizeof(*domains) * (*num_domains));
    if (!domains) {
        fprintf(stderr, "Failed to allocated memory to domain data.\n");
        ret = CUPTI_ERROR_OUT_OF_MEMORY;
        goto fail;
    }

    ret = cuptiDeviceEnumEventDomains(device, &size, domain_id);
    CHECK_CUPTI_ERROR(ret, "cuptiDeviceEnumEventDomains");

    // enum domains
    for (i = 0; i < *num_domains; i++) {
        struct domain *d = &domains[i];

        // domain id
        d->id = domain_id[i];

        // domain name
        size = NAME_SHORT;
        ret = cuptiEventDomainGetAttribute(d->id,
                                                 CUPTI_EVENT_DOMAIN_ATTR_NAME,
                                                 &size,
                                                 (void *)d->name);
        check_null_terminator(d->name, size, NAME_SHORT);
        CHECK_CUPTI_ERROR(ret, "cuptiEventDomainGetAttribute");

        // num of profiled instances in the domain
        size = sizeof(d->profiled_inst);
        ret = cuptiDeviceGetEventDomainAttribute(device,
                                                       d->id,
                                                       CUPTI_EVENT_DOMAIN_ATTR_INSTANCE_COUNT,
                                                       &size,
                                                       (void *)&d->profiled_inst);
        CHECK_CUPTI_ERROR(ret, "cuptiDeviceEventDomainGetAttribute");

        // num of total instances in the domain
        size = sizeof(d->total_inst);
        ret = cuptiDeviceGetEventDomainAttribute(device,
                                                       d->id,
                                                       CUPTI_EVENT_DOMAIN_ATTR_TOTAL_INSTANCE_COUNT,
                                                       &size,
                                                       (void *)&d->total_inst);
        CHECK_CUPTI_ERROR(ret, "cuptiDeviceEventDomainGetAttribute");
    }

fail:
    free(domain_id);
    if (ret != CUPTI_SUCCESS)
        return NULL;

    return domains;
}

static int list_domains(CUdevice dev)
{
    struct domain *domains = NULL;
    uint32_t num_domains, i;

    if (!(domains = get_domains(dev, &num_domains)))
        return -1;

    for (i = 0; i < num_domains; i++) {
        struct domain *d = &domains[i];

        printf("Domain# %d\n",                     i + 1);
        printf("Id         = %d\n",                d->id);
        printf("Name       = %s\n",                d->name);
        printf("Profiled instance count = %d\n",   d->profiled_inst);
        printf("Total instance count = %d\n\n",    d->total_inst);
    }

    free(domains);
    return 0;
}

static struct event *get_events_by_domain(CUpti_EventDomainID domain, uint32_t *num_events)
{
    CUptiResult ret = CUPTI_SUCCESS;
    CUpti_EventID *event_id = NULL;
    struct event *events = NULL;
    size_t size = 0;
    uint32_t i;

    ret = cuptiEventDomainGetNumEvents(domain, num_events);
    CHECK_CUPTI_ERROR(ret, "cuptiEventDomainGetNumEvents");

    if (*num_events == 0) {
        fprintf(stderr, "No event is exposed by domain = %d.\n", domain);
        ret = CUPTI_ERROR_UNKNOWN;
        goto fail;
    }

    size = sizeof(CUpti_EventID) * (*num_events);
    event_id = (CUpti_EventID *)malloc(size);
    if (event_id == NULL) {
        fprintf(stderr, "Failed to allocate memory to event ID.\n");
        ret = CUPTI_ERROR_OUT_OF_MEMORY;
        goto fail;
    }
    memset(event_id, 0, size);

    if (!(events = (struct event *)malloc(sizeof(*events) * (*num_events)))) {
        fprintf(stderr, "Failed to allocate memory to event data.\n");
        ret = CUPTI_ERROR_OUT_OF_MEMORY;
        goto fail;
    }

    ret = cuptiEventDomainEnumEvents(domain,
                                           &size,
                                           event_id);
    CHECK_CUPTI_ERROR(ret, "cuptiEventDomainEnum_events");

    // enum events
    for (i = 0; i < *num_events; i++) {
        struct event *event = &events[i];

        // event id
        event->id = event_id[i];

        // event name
        size = NAME_SHORT;
        ret = cuptiEventGetAttribute(event->id,
                                           CUPTI_EVENT_ATTR_NAME,
                                           &size,
                                           (uint8_t *)event->name);
        CHECK_CUPTI_ERROR(ret, "cuptiEventGetAttribute");
        check_null_terminator(events->name, size, NAME_SHORT);

        // event short desc
        size = DESC_SHORT;
        ret = cuptiEventGetAttribute(event->id,
                                           CUPTI_EVENT_ATTR_SHORT_DESCRIPTION,
                                           &size,
                                           (uint8_t *)event->short_desc);
        CHECK_CUPTI_ERROR(ret, "cuptiEventGetAttribute");
        check_null_terminator(events->short_desc, size, NAME_SHORT);

        // event long desc
        size = DESC_LONG;
        ret = cuptiEventGetAttribute(event->id,
                                           CUPTI_EVENT_ATTR_LONG_DESCRIPTION,
                                           &size,
                                           (uint8_t *)event->long_desc);
        CHECK_CUPTI_ERROR(ret, "cuptiEventGetAttribute");
        check_null_terminator(events->short_desc, size, NAME_SHORT);

        // event category
        size = CATEGORY_LENGTH;
        ret = cuptiEventGetAttribute(events->id,
                                           CUPTI_EVENT_ATTR_CATEGORY,
                                           &size,
                                           (&event->category));
        CHECK_CUPTI_ERROR(ret, "cuptiEventGetAttribute");
    }

fail:
    free(event_id);
    if (ret != CUPTI_SUCCESS)
        return NULL;

    return events;
}


static int list_events(CUpti_EventDomainID domain_id)
{
    struct event *events = NULL;
    uint32_t num_events, i;

    if (!(events = get_events_by_domain(domain_id, &num_events)))
        return -1;

    for (i = 0; i < num_events; i++) {
        struct event *e = &events[i];

        printf("Event# %d\n",       i + 1);
        printf("Id        = %d\n",  e->id);
        printf("Name      = %s\n",  e->name);
        printf("Shortdesc = %s\n",  e->short_desc);
        printf("Longdesc  = %s\n",  e->long_desc);

        switch (e->category) {
            case CUPTI_EVENT_CATEGORY_INSTRUCTION:
                printf("Category  = CUPTI_EVENT_CATEGORY_INSTRUCTION\n\n");
                break;
            case CUPTI_EVENT_CATEGORY_MEMORY:
                printf("Category  = CUPTI_EVENT_CATEGORY_MEMORY\n\n");
                break;
            case CUPTI_EVENT_CATEGORY_CACHE:
                printf("Category  = CUPTI_EVENT_CATEGORY_CACHE\n\n");
                break;
            case CUPTI_EVENT_CATEGORY_PROFILE_TRIGGER:
                printf("Category  = CUPTI_EVENT_CATEGORY_PROFILE_TRIGGER\n\n");
                break;
            default:
                printf("Category  = CUPTI_EVENT_CATEGORY_UNKNOWN\n\n");
                break;
        }
    }

    free(events);
    return 0;
}

static int lookup(const char *chipset, const char *reg, const char *val)
{
    char cmd[1024], buf[1024];
    FILE *f;

    sprintf(cmd, "lookup -a %s %s %s 2> /dev/null\n", chipset, reg, val);

    if (!(f = popen(cmd, "r"))) {
        perror("popen");
        return -errno;
    }

    while (fgets(buf, sizeof(buf), f) != NULL) {
        printf("%s", buf);
    }

    if (pclose(f) < 0) {
        perror("pclose");
        return -errno;
    }

    return 0;
}

static int mmiotrace(const char *chipset, const char *event)
{
    char trace_log[1204], line[1024];
    pid_t pid;
    FILE *f;

    sprintf(trace_log, "%s.trace", event);

    if ((pid = fork()) < 0) {
        perror("fork");
        return -errno;
    }

    if (!(f = fopen(trace_log, "w+"))) {
        perror("fopen");
        return -errno;
    }

    if (pid == 0) {
        dup2(fileno(f), 2);

        execlp("/usr/local/bin/valgrind", "valgrind",
                "--tool=mmt",
                "--mmt-trace-file=/dev/nvidia0",
                "--mmt-trace-nvidia-ioctls",
                "callback_event/callback_event",
                event,
                NULL);

        if (errno == ENOENT) {
            fprintf(stderr, "No such file or directory.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        int status;

        if (waitpid(pid, &status, 0) < 0) {
            if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                fprintf(stderr, "Failed to execute child process.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    while (fgets (line, sizeof(line), f) != NULL) {
        char *token, *s, *reg, *val, *mask;
        int dir;

        // Only show post ioctl calls.
        if (!(s = strstr(line, "RETURND")))
            continue;
        s += 9; // 'RETURND: '

        token = strtok(s, " ");
        while (token != NULL) {
            if (!strncmp(token, "DIR=", 4)) {
                dir = atoi(token + 4);
            } else if (!strncmp(token, "MMIO=", 5)) {
                reg = token + 5;
            } else if (!strncmp(token, "VALUE=", 6)) {
                val = token + 6;
            } else if (!strncmp(token, "MASK=", 5)) {
                mask = token + 5;
            }
            token = strtok(NULL, " ");
        }

        dir &= 0x00000001;
        printf("(%c) register: %s, value: %s, mask: %s ==> ",
               (dir ? 'w' : 'r'), reg, val, mask);

        lookup(chipset, reg, val);
    }

    if (fclose(f) < 0) {
        perror("fclose");
        return -errno;
    }

    printf("Trace of '%s' saved in the file '%s'\n", event, trace_log);

    return 0;
}

static int run(CUdevice dev, const char *chipset)
{
    struct domain *domains = NULL;
    uint32_t num_domains, i, j;
    int ret;

    domains = get_domains(dev, &num_domains);
    if (!domains) {
        fprintf(stderr, "Failed to get domains.\n");
        return -1;
    }

    for (i = 0; i < num_domains; i++) {
        struct domain *d = &domains[i];

        if (!(d->events = get_events_by_domain(d->id, &d->num_events))) {
            fprintf(stderr, "Failed to get events.\n");
            return -1;
        }

        for (j = 0; j < d->num_events; j++) {
            struct event *e = &d->events[j];

            if ((ret = mmiotrace(chipset, e->name)) < 0)
                return ret;
        }
    }

    free(domains);
    return 0;
}

int main(int argc, char **argv)
{
    CUdevice dev;
    CUresult cuda_ret;
    int device_id;
    int device_count;
    int c;
    int ret = 0;
    CUpti_EventDomainID domain_id = 0;
    CUptiResult cupti_ret = CUPTI_SUCCESS;
    size_t size;
    char chipset[128];

    if (argc < 2) {
        usage();
        return -1;
    }

    // Initialize the driver API.
    cuda_ret = cuInit(0);
    CHECK_CU_ERROR(cuda_ret, "cuInit");

    // Return the number of devices with compute capability greater than or
    // equal to 1.0 that are available for execution.
    cuda_ret = cuDeviceGetCount(&device_count);
    CHECK_CU_ERROR(cuda_ret, "cuDeviceGetCount");

    if (device_count == 0) {
        fprintf(stderr, "There is no device supporting CUDA.\n");
        ret = -1;
        goto fail;
    }

    while (1) {
        static struct option long_options[] = {
            {"device",          required_argument,  0,  'd'},
            {"domain",          required_argument,  0,  'o'},
            {"help",            no_argument,        0,  'h'},
            {"list-events",     no_argument,        0,  'e'},
            {"list-metrics",    no_argument,        0,  'm'},
            {"list-domains",    no_argument,        0,  'n'},
            {"trace",           required_argument,  0,  't'},
            {0, 0, 0, 0}
        };
        // getopt_long stores the option index here.
        int option_index = 0;

        c = getopt_long (argc, argv, "d:ehmnot:", long_options, &option_index);

        // Detect the end of the options.
        if (c == -1)
            break;

        switch (c) {
            case 'd':
                device_id = atoi(optarg);
                SET_OPTS_FLAG(FLAG_DEVICE_ID);
                break;
            case 'e':
                SET_OPTS_FLAG(FLAG_LIST_EVENTS);
                break;
            case 'm':
                SET_OPTS_FLAG(FLAG_LIST_METRICS);
                break;
            case 'n':
                SET_OPTS_FLAG(FLAG_LIST_DOMAINS);
                break;
            case 'o':
                domain_id = atoi(optarg);
                SET_OPTS_FLAG(FLAG_DOMAIN_ID);
                break;
            case 't':
                strncpy(chipset, optarg, sizeof(chipset));
                SET_OPTS_FLAG(FLAG_TRACE);
                break;
            case 'h':
            case '?':
                usage();
                exit(0);
                break;
            default:
                abort();
                break;
        }
    }

    if (!IS_OPTS_FLAG(FLAG_DEVICE_ID)) {
        printf("Assuming default device id 0.\n");
        device_id = 0;
    }

    // Return a device handle given an ordinal in the range.
    cuda_ret = cuDeviceGet(&dev, device_id);
    CHECK_CU_ERROR(cuda_ret, "cuDeviceGet");

    if (IS_OPTS_FLAG(FLAG_TRACE)) {
        // Trace ioctl calls.
        if (run(dev, chipset) < 0) {
            fprintf(stderr, "Cannot trace ioctl calls.\n");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (IS_OPTS_FLAG(FLAG_LIST_DOMAINS)) {
        if (list_domains(dev) < 0) {
            fprintf(stderr, "Cannot list domains.\n");
            return EXIT_FAILURE;
        }
    } else if (IS_OPTS_FLAG(FLAG_LIST_EVENTS)) {
        if (!IS_OPTS_FLAG(FLAG_DOMAIN_ID)) {
            // Query first domain on the device.
            size = sizeof(CUpti_EventDomainID);
            cupti_ret = cuptiDeviceEnumEventDomains(dev, &size,
                                                    (CUpti_EventDomainID *)&domain_id);
            CHECK_CUPTI_ERROR(cupti_ret, "cuptiDeviceEnumEventDomains");
            printf("Assuming default domain id %d.\n", domain_id);
        } else {
            // Validate the domain on the device.
            CUpti_EventDomainID *domain_id_arr = NULL;
            uint32_t max_domains = 0, i = 0;

            cupti_ret = cuptiDeviceGetNumEventDomains(dev, &max_domains);
            CHECK_CUPTI_ERROR(cupti_ret, "cuptiDeviceGetNumEventDomains");

            if (max_domains == 0) {
                printf("No domain is exposed by dev = %d.\n", dev);
                cupti_ret = CUPTI_ERROR_UNKNOWN;
                goto fail;
            }

            size = sizeof(CUpti_EventDomainID) * max_domains;
            domain_id_arr = (CUpti_EventDomainID*)malloc(size);
            if (domain_id_arr == NULL) {
                printf("Failed to allocate memory to domain ID.\n");
                cupti_ret = CUPTI_ERROR_OUT_OF_MEMORY;
                goto fail;
            }
            memset(domain_id_arr, 0, size);

            // enum domains
            cupti_ret = cuptiDeviceEnumEventDomains(dev, &size, domain_id_arr);
            CHECK_CUPTI_ERROR(cupti_ret, "cuptiDeviceEnumEventDomains");

            for (i = 0; i < max_domains; i++) {
                if (domain_id_arr[i] == domain_id) {
                    break;
                }
            }
            free(domain_id_arr);

            if (i == max_domains) {
                printf("Domain Id %d is not supported by device.\n", domain_id);
                goto fail;
            }
        }

        if (list_events(domain_id) < 0) {
            fprintf(stderr, "Cannot list events\n");
            return EXIT_FAILURE;
        }
    } else if (IS_OPTS_FLAG(FLAG_LIST_METRICS)) {
        fprintf(stderr, "Work in progress! ;)\n");
        return -1;
    }

fail:
   // cudaDeviceSynchronize();
    return ret;
}
