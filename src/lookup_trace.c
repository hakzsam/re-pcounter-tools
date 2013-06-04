#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <inttypes.h>

#define LOOKUP_PATH     "../envytools/build/rnn/lookup"

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

int main(int argc, char **argv)
{
    char *chipset, *trace;
    struct trace *t;
    FILE *f;
    int i, code = 0;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <chipset> <trace> [<nv_perfmon>]\n", argv[0]);
        return 1;
    }
    chipset = argv[1];
    trace   = argv[2];

    if (argc > 3)
        code    = atoi(argv[3]); // Hack? :)

    if (!(f = fopen(trace, "r+"))) {
        perror("fopen");
        return 1;
    }

    if (!(t = parse_trace(f)))
        return 1;

    for (i = 0; i < t->nb_ioctl; i++) {
        if (!code) {
            printf("(%c) register: %06x, value: %08x, mask: %08x ",
                   (t->ioctls[i].dir ? 'w' : 'r'),
                   t->ioctls[i].reg, t->ioctls[i].val,
                   t->ioctls[i].mask);
            printf("%s ", (t->ioctls[i].dir ? "<==" : "==>"));

            if (lookup(chipset, t->ioctls[i].reg, t->ioctls[i].val) < 0) {
                fprintf(stderr, "Cannot run lookup.\n");
                return 1;
            }
        } else {
            if (t->ioctls[i].dir) {
                printf("nv_wr32(priv, 0x%08x, 0x%08x);\n", t->ioctls[i].reg, t->ioctls[i].val);
            } else {
                printf("nv_rd32(priv, 0x%08x);\n", t->ioctls[i].reg);
            }
        }
    }
    free(t);

    if (fclose(f) < 0) {
        perror("fclose");
        return 1;
    }

    return 0;
}
