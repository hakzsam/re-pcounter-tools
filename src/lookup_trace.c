#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <inttypes.h>

#define LOOKUP_PATH     "lookup"

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

static int lookup(const char *chipset, uint32_t reg, uint32_t val)
{
    char cmd[1024], buf[1024];
    FILE *f;

    sprintf(cmd, "%s -a %s %08x %08x 2> /dev/null\n",
            LOOKUP_PATH, chipset, reg, val);

    if (!(f = popen(cmd, "r"))) {
        perror("popen");
        return -1;
    }

    while (fgets(buf, sizeof(buf), f) != NULL)
        printf("%s", buf);

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

    if (!(t = (struct trace *)calloc(1, sizeof(*t)))) {
        perror("malloc");
        return NULL;
    }

    while (fgets (line, sizeof(line), f) != NULL) {
        char *token;

        // Read/write.
        token = strstr(line, "dir:");
        if (!token)
            goto bad_trace;
        sscanf(token + 5, "0x%08x", &t->ioctls[t->nb_ioctl].dir);

        // Register.
        token = strstr(line, "mmio:");
        if (!token)
            goto bad_trace;
        sscanf(token + 6, "0x%08x", &t->ioctls[t->nb_ioctl].reg);

        // Value.
        token = strstr(line, "value:");
        if (!token)
            goto bad_trace;
        sscanf(token + 7, "0x%08x", &t->ioctls[t->nb_ioctl].val);

        // Mask.
        token = strstr(line, "mask:");
        if (!token)
            goto bad_trace;
        sscanf(token + 6, "0x%08x", &t->ioctls[t->nb_ioctl].mask);

        t->nb_ioctl++;
    }

    return t;

bad_trace:
    free(t);
    return NULL;
}

int main(int argc, char **argv)
{
    char *chipset, *trace;
    struct trace *t;
    FILE *f;
    int i;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <chipset> <trace>\n", argv[0]);
        return 1;
    }
    chipset = argv[1];
    trace   = argv[2];

    if (!(f = fopen(trace, "r+"))) {
        perror("fopen");
        return 1;
    }

    if (!(t = parse_trace(f))) {
        fprintf(stderr, "Failed to parse the trace!\n");
        return 1;
    }

    for (i = 0; i < t->nb_ioctl; i++) {
        printf("(%c) register: %06x, value: %08x, mask: %08x ",
               (t->ioctls[i].dir ? 'w' : 'r'),
               t->ioctls[i].reg, t->ioctls[i].val,
               t->ioctls[i].mask);
        printf("%s ", (t->ioctls[i].dir ? "<==" : "==>"));

        if (lookup(chipset, t->ioctls[i].reg, t->ioctls[i].val) < 0) {
            fprintf(stderr, "Failed to run lookup!\n");
            return 1;
        }
    }
    free(t);

    if (fclose(f) < 0) {
        perror("fclose");
        return 1;
    }

    return 0;
}
