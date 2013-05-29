#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <math.h>

#include <cuda.h>
#include <cupti.h>

/**
 * TODO:
 *  - do not use lookup through popen() (it's bad).
 *  - use env vars for setting valgrind-mmt.
 */

#define LOOKUP_PATH     "../envytools/build/rnn/lookup"
#define NAME_SHORT      64
#define NAME_LONG       128
#define DESC_SHORT      512
#define DESC_LONG       2048
#define CATEGORY_LENGTH sizeof(CUpti_EventCategory)
#define CUDA_SAMPLE     "./cuda_sample"

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

struct ioctl_call {
    int dir;
    uint32_t reg;
    uint32_t val;
    uint32_t mask;
};

struct trace {
    struct ioctl_call ioctls[2048];
    int nb_ioctl;
};

static uint32_t method0(struct trace *t);
static uint32_t method1(struct trace *t);
static uint32_t method2(struct trace *t);
static uint32_t method3(struct trace *t);

static const char *method0_events[] = {
    "active_cycles",
    "active_warps",
    "atom_count",
    "branch",
    "divergent_branch",
    "gld_inst_128bit",
    "gld_inst_16bit",
    "gld_inst_32bit",
    "gld_inst_64bit",
    "gld_inst_8bit",
    "gld_request",
    "gred_count",
    "gst_inst_128bit",
    "gst_inst_16bit",
    "gst_inst_32bit",
    "gst_inst_64bit",
    "gst_inst_8bit",
    "gst_request",
    "inst_executed",
    "inst_issued1_0",
    "inst_issued1_1",
    "inst_issued2_0",
    "inst_issued2_1",
    "local_load",
    "local_store",
    "prof_trigger_00",
    "prof_trigger_01",
    "prof_trigger_02",
    "prof_trigger_03",
    "prof_trigger_04",
    "prof_trigger_05",
    "prof_trigger_06",
    "prof_trigger_07",
    "shared_load",
    "shared_store",
    "thread_inst_executed_0",
    "thread_inst_executed_1",
    "thread_inst_executed_2",
    "thread_inst_executed_3",
    "threads_launched",
    "warps_launched",
    NULL
};

static const char *method1_events[] = {
    "global_store_transaction",
    "l1_global_load_hit",
    "l1_global_load_miss",
    "l1_local_load_hit",
    "l1_local_load_miss",
    "l1_local_store_hit",
    "l1_local_store_miss",
    "l1_shared_bank_conflict",
    "sm_cta_launched",
    "uncached_global_load_transaction",
    NULL
};

static const char *method2_events[] = {
    "fb0_subp0_read_sectors",
    "fb0_subp0_write_sectors",
    "fb0_subp1_read_sectors",
    "fb0_subp1_write_sectors",
    "fb1_subp0_read_sectors",
    "fb1_subp0_write_sectors",
    "fb1_subp1_read_sectors",
    "fb1_subp1_write_sectors",
    "l2_subp0_read_sector_misses",
    "l2_subp0_write_sector_misses",
    "l2_subp1_read_sector_misses",
    "l2_subp1_write_sector_misses",
    NULL
};

static const char *method3_events[] = {
    "l2_subp0_read_hit_sectors",
    "l2_subp0_read_sector_queries",
    "l2_subp0_read_sysmem_sector_queries",
    "l2_subp0_read_tex_hit_sectors",
    "l2_subp0_read_tex_sector_queries",
    "l2_subp0_total_read_sector_queries",
    "l2_subp0_total_write_sector_queries",
    "l2_subp0_write_sector_queries",
    "l2_subp0_write_sysmem_sector_queries",
    "l2_subp1_read_hit_sectors",
    "l2_subp1_read_sector_queries",
    "l2_subp1_read_sysmem_sector_queries",
    "l2_subp1_read_tex_hit_sectors",
    "l2_subp1_read_tex_sector_queries",
    "l2_subp1_total_read_sector_queries",
    "l2_subp1_total_write_sector_queries",
    "l2_subp1_write_sector_queries",
    "l2_subp1_write_sysmem_sector_queries",
    NULL
};

static struct method {
    const char *name;
    uint32_t (*func)(struct trace *t);
    const char **events;
} methods[] = {
    {"method0", method0, method0_events},
    {"method1", method1, method1_events},
    {"method2", method2, method2_events},
    {"method3", method3, method3_events}
};

enum flags {
    FLAG_DEVICE_ID = 0,
    FLAG_DOMAIN_ID,
    FLAG_EVENT,
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
    printf("       --trace <chipset> --event <event_name>                : traces ioctl calls\n");
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

static void print_domain(struct domain *d)
{
    printf("Id                      = %d\n",    d->id);
    printf("Name                    = %s\n",    d->name);
    printf("Profiled instance count = %d\n",    d->profiled_inst);
    printf("Total instance count    = %d\n",  d->total_inst);
}

static int list_domains(CUdevice dev)
{
    struct domain *domains = NULL;
    uint32_t num_domains, i;

    if (!(domains = get_domains(dev, &num_domains)))
        return -1;

    for (i = 0; i < num_domains; i++) {
        printf("\nDomain# %d\n", i + 1);
        print_domain(&domains[i]);
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

static void print_event(struct event *e, struct domain *d)
{
    printf("Id        = %d\n",      e->id);
    printf("Domain    = %s (%d)\n", d->name, d->id);
    printf("Name      = %s\n",      e->name);
    printf("Shortdesc = %s\n",      e->short_desc);
    printf("Longdesc  = %s\n",      e->long_desc);

    switch (e->category) {
        case CUPTI_EVENT_CATEGORY_INSTRUCTION:
            printf("Category  = CUPTI_EVENT_CATEGORY_INSTRUCTION\n");
            break;
        case CUPTI_EVENT_CATEGORY_MEMORY:
            printf("Category  = CUPTI_EVENT_CATEGORY_MEMORY\n");
            break;
        case CUPTI_EVENT_CATEGORY_CACHE:
            printf("Category  = CUPTI_EVENT_CATEGORY_CACHE\n");
            break;
        case CUPTI_EVENT_CATEGORY_PROFILE_TRIGGER:
            printf("Category  = CUPTI_EVENT_CATEGORY_PROFILE_TRIGGER\n");
            break;
        default:
            printf("Category  = CUPTI_EVENT_CATEGORY_UNKNOWN\n");
            break;
    }
}

static void list_events(struct domain *d)
{
    struct event *events = NULL;
    uint32_t num_events, i;

    if (!(events = get_events_by_domain(d->id, &num_events)))
        return;

    for (i = 0; i < num_events; i++) {
        printf("\nEvent# %d\n", i + 1);
        print_event(&events[i], d);
    }
    free(events);
}

static int lookup(const char *chipset, uint32_t reg, uint32_t val)
{
    char cmd[1024], buf[1024];
    FILE *f;

    sprintf(cmd, "%s -a %s %08x %08x 2> /dev/null\n", LOOKUP_PATH, chipset, reg,
            val);

    if (!(f = popen(cmd, "r"))) {
        perror("popen");
        return -1;
    }

    while (fgets(buf, sizeof(buf), f) != NULL) {
        printf("%s", buf);
    }

    if (pclose(f) < 0) {
        perror("pclose");
        return -1;
    }

    return 0;
}

static struct trace *parse_trace(FILE *f)
{
    struct trace *t;
    char line[1024];

    if (!(t = (struct trace *)malloc(sizeof(*t)))) {
        perror("malloc");
        return NULL;
    }

    t->nb_ioctl   = 0;

    while (fgets (line, sizeof(line), f) != NULL) {
        char *token, *s;
        int dir;

        // Only show post ioctl calls.
        if (!(s = strstr(line, "RETURND")))
            continue;
        s += 9; // 'RETURND: '

        token = strtok(s, " ");
        while (token != NULL) {
            if (!strncmp(token, "DIR=", 4)) {
                dir = atoi(token + 4);
                t->ioctls[t->nb_ioctl].dir = dir & 0x00000001;
            } else if (!strncmp(token, "MMIO=", 5)) {
                sscanf(token + 5, "%08x", &t->ioctls[t->nb_ioctl].reg);
            } else if (!strncmp(token, "VALUE=", 6)) {
                sscanf(token + 6, "%08x", &t->ioctls[t->nb_ioctl].val);
            } else if (!strncmp(token, "MASK=", 5)) {
                sscanf(token + 5, "%08x", &t->ioctls[t->nb_ioctl].mask);
            }
            token = strtok(NULL, " ");
        }
        t->nb_ioctl++;
    }

    return t;
}

static int get_nb_sources(struct trace *t, uint32_t reg)
{
    int nb_sources = 0;
    int i;

    for (i = 0; i < t->nb_ioctl; i++) {
        if (t->ioctls[i].reg == reg)
            break;
    }

    nb_sources += (t->ioctls[i].val & 0xff)       ? 1 : 0;
    nb_sources += (t->ioctls[i].val & 0xff00)     ? 1 : 0;
    nb_sources += (t->ioctls[i].val & 0xff0000)   ? 1 : 0;
    nb_sources += (t->ioctls[i].val & 0xff000000) ? 1 : 0;

    return nb_sources;
}

static uint32_t method0(struct trace *t)
{
    uint32_t val = 0;
    int nb_sources;
    int i, j;

    // Count the number of sources from 0x504604.
    nb_sources = get_nb_sources(t, 0x504604);
    if (nb_sources == 4) {
        // Maybe, more than 4 sources, let's check.
        nb_sources += get_nb_sources(t, 0x504608);
    }

    // Find the first counter.
    for (i = 0; i < t->nb_ioctl; i++) {
        if (t->ioctls[i].dir)
            continue;

        if (t->ioctls[i].reg == 0x504674)
            break;
    }

    // Compute the result.
    for (j = 0; j < nb_sources; j++) {
        val += t->ioctls[i + j].val * pow(2, j);
    }

    return val;
}

static int get_counter_value(struct trace *t, uint32_t addr, uint32_t *value)
{
    int found = 0;
    int i;

    // Find the counter (ie. CTR_PRE).
    for (i = 0; i < t->nb_ioctl; i++) {
        if (t->ioctls[i].dir)
            continue;

        if (t->ioctls[i].reg == addr) {
            found = 1;
            break;
        }
    }

    *value = t->ioctls[i].val;
    return found;
}

static uint32_t method1(struct trace *t)
{
    uint32_t value;
    int ret;

    ret = get_counter_value(t, 0x18008c, &value);
    return ret ? value : -1;
}

static uint32_t method2(struct trace *t)
{
    uint32_t value;
    int ret;

    ret = get_counter_value(t, 0x1a008c, &value);
    return ret ? value : -1;
}

static uint32_t method3(struct trace *t)
{
    uint32_t value;
    int ret;

    ret = get_counter_value(t, 0x1a0080, &value);
    return ret ? value : -1;
}

static int trace_event(const char *chipset, struct domain *d, struct event *e)
{
    char trace_log[1204];
    struct trace *t;
    int pipefd[2];
    int retval;
    pid_t pid;
    FILE *f;
    int i, j;

    sprintf(trace_log, "%s.trace", e->name);

    // Display information about the event.
    print_event(e, d);

    if (pipe(pipefd) < 0) {
        perror("pipe");
        return -1;
    }

    if ((pid = fork()) < 0) {
        perror("fork");
        return -1;
    }

    if (!(f = fopen(trace_log, "w+"))) {
        perror("fopen");
        return -1;
    }

    if (pid == 0) {
        dup2(fileno(f), 2);
        dup2(pipefd[1], 1);
        close(pipefd[0]);

        execlp("../local/bin/valgrind", "valgrind",
                "--tool=mmt",
                "--mmt-trace-file=/dev/nvidia0",
                "--mmt-trace-nvidia-ioctls",
                CUDA_SAMPLE,
                e->name,
                NULL);

        if (errno == ENOENT) {
            fprintf(stderr, "No such file or directory.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        int status;

        close(pipefd[1]);
        if (waitpid(pid, &status, 0) < 0) {
            if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                fprintf(stderr, "Failed to execute child process.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    // Read and display return value of the CUDA sample through CUPti.
    char tmp[512];
    memset(tmp, 0, sizeof(tmp));
    read(pipefd[0], tmp, sizeof(tmp));
    retval = atoi(tmp);
    printf("Value     = %llu (0x%02x) \n", retval, retval);

    if (!(t = parse_trace(f)))
        return -1;

    for (i = 0; i < t->nb_ioctl; i++) {
        printf("(%c) register: %06x, value: %08x, mask: %08x ",
               (t->ioctls[i].dir ? 'w' : 'r'),
               t->ioctls[i].reg, t->ioctls[i].val,
               t->ioctls[i].mask);
        printf("%s ", (t->ioctls[i].dir ? "<==" : "==>"));

        if (lookup(chipset, t->ioctls[i].reg, t->ioctls[i].val) < 0) {
            fprintf(stderr, "Cannot run lookup.\n");
            return -1;
        }
    }

    for (i = 0; i < sizeof(methods) / sizeof(methods[0]); i++) {
        for (j = 0; methods[i].events[j] != NULL; j++) {
            if (!strcmp(e->name, methods[i].events[j])) {
                uint32_t val;

                printf("Unit test using method '%s' : ", methods[i].name);

                val = methods[i].func(t);
                if (val == retval) {
                    printf("\e[1;32mPASS\e[m\n");
                } else {
                    printf("\e[1;31mFAIL (%02x != %02x)\e[m\n", val, retval);
                }
            }
        }
    }
    free(t);

    if (fclose(f) < 0) {
        perror("fclose");
        return -1;
    }

    printf("Trace of '%s' saved in the file '%s'\n\n", e->name, trace_log);
    fflush(stdout);

    return 0;
}

static int trace_all_events(CUdevice dev, const char *chipset)
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

        if (!(d->events = get_events_by_domain(d->id, &d->num_events)))
            continue;

        for (j = 0; j < d->num_events; j++) {
            struct event *e = &d->events[j];

            if ((ret = trace_event(chipset, d, e)) < 0)
                return ret;
        }
    }

    free(domains);
    return 0;
}

static int file_exists(const char *filename)
{
    FILE *f;

    if (!(f = fopen(filename, "r")))
        return 0;

    fclose(f);
    return 1;
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
    char chipset[128], device_name[128], event_name[128];
    int compute_capability_major, compute_capability_minor;

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
            {"event",           required_argument,  0,  'v'},
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
            case 'v':
                strncpy(event_name, optarg, sizeof(event_name));
                SET_OPTS_FLAG(FLAG_EVENT);
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

    // Returns an identifer string for the device.
    cuda_ret = cuDeviceGetName(device_name, sizeof(device_name), dev);
    CHECK_CU_ERROR(cuda_ret, "cuDeviceGetName");

    // Returns the compute capability of the device.
    cuda_ret = cuDeviceComputeCapability(&compute_capability_major,
                                         &compute_capability_minor,
                                         dev);
    CHECK_CU_ERROR(cuda_ret, "cuDeviceComputeCapability");

    printf("CUDA Device Id  : %d\n", device_id);
    printf("CUDA Device Name: %s\n", device_name);
    printf("CUDA Compute Capability: %d.%d\n\n", compute_capability_major,
           compute_capability_minor);
    fflush(stdout);

    // Trace ioctl calls.
    if (IS_OPTS_FLAG(FLAG_TRACE)) {
        // Check if the CUDA sample has been compiled by the user.
        if (!file_exists(CUDA_SAMPLE)) {
            fprintf(stderr, "CUDA sample not found! Please run 'make cuda_sample'.\n");
            return -1;
        }

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

            if (!(d->events = get_events_by_domain(d->id, &d->num_events)))
                continue;

            for (j = 0; j < d->num_events; j++) {
                struct event *e = &d->events[j];

                if (IS_OPTS_FLAG(FLAG_EVENT) && strcmp(e->name, event_name))
                    continue;

                if ((ret = trace_event(chipset, d, e)) < 0)
                    return ret;
            }
        }
        goto fail; // BAD HACK!!
    }

    if (IS_OPTS_FLAG(FLAG_LIST_DOMAINS)) {
        if (list_domains(dev) < 0) {
            fprintf(stderr, "Cannot list domains.\n");
            return EXIT_FAILURE;
        }
    } else if (IS_OPTS_FLAG(FLAG_LIST_EVENTS)) {
        if (IS_OPTS_FLAG(FLAG_DOMAIN_ID)) {
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

        // List all events.
        struct domain *domains = NULL;
        uint32_t num_domains, i;

        if (!(domains = get_domains(dev, &num_domains)))
            return -1;

        for (i = 0; i < num_domains; i++) {
            struct domain *d = &domains[i];

            if (IS_OPTS_FLAG(FLAG_DOMAIN_ID) && d->id != domain_id)
                continue;

            list_events(&domains[i]);
        }
    } else if (IS_OPTS_FLAG(FLAG_LIST_METRICS)) {
        fprintf(stderr, "Work in progress! ;)\n");
        return -1;
    }

fail:
    cudaDeviceSynchronize();
    return ret;
}
