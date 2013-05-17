#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

#include "cuda/cuda_extras.h"
#include "cupti/cupti_extras.h"

/**
 * TODO:
 *  - do not hardcode chipset (use nvalist).
 *  - do not use lookup through popen() (it's bad).
 *  - use env vars for setting valgrind-mmt.
 */

static int lookup(const char *reg, const char *val)
{
    char cmd[1024], buf[1024];
    FILE *f;

    /* Do not hardcode chipset name. */
    sprintf(cmd, "lookup -a NVC1 %s %s 2> /dev/null\n", reg, val);

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

static int mmiotrace(const char *event)
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

        lookup(reg, val);
    }

    if (fclose(f) < 0) {
        perror("fclose");
        return -errno;
    }

    printf("Trace of '%s' saved in the file '%s'\n", event, trace_log);

    return 0;
}

int main(int argc, char **argv)
{
    struct domain *domains;
    uint32_t num_domains;
    char *event_name;
    int ret = 0;

    if (argc < 2) {
        fprintf(stderr,
                "Usage: %s <event_name>\n", argv[0]);
        return EXIT_FAILURE;
    }
    event_name = argv[1];

    if (!cuda_init()) {
        fprintf(stderr, "There is no device supporting CUDA.\n");
        return -1;
    }

    domains = cupti_getDomains(0, &num_domains);
    if (!domains) {
        fprintf(stderr, "Failed to get domains.\n");
        return -1;
    }

    for (uint32_t i = 0; i < num_domains; i++) {
        struct domain *d = &domains[i];

        if (!(d->events = cupti_getEventByDomain(d->id, &d->numEvents))) {
            fprintf(stderr, "Failed to get events.\n");
            return -1;
        }

        for (uint32_t j = 0; j < d->numEvents; j++) {
            ptiData *event = &d->events[j];

            if ((ret = mmiotrace(event->name)) < 0)
                return ret;
        }
    }

    free(domains);

    return ret;
}
