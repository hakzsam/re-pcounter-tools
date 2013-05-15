#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

#include <cupti.h>

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

int main(int argc, char **argv)
{
    char *profile_signal = NULL;
    char trace_log[1024];
    char line[1024];
    pid_t pid;
    FILE *f;

    if (argc < 2) {
        fprintf(stderr,
                "Usage: %s <profile_signal>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    profile_signal = argv[1];

    if ((pid = fork()) < 0) {
        perror("fork");
        return -errno;
    }

    // Build filepath of trace log.
    sprintf(trace_log, "%s.trace", profile_signal);

    if (!(f = fopen(trace_log, "w+"))) {
        perror("fopen");
        return -errno;
    }

    if (pid == 0) {
        dup2(fileno(f), 2);

        // Launch valgrind-mmt with a CUDA/OpenCL sample.
        execlp("/usr/local/bin/valgrind", "valgrind",
               "--tool=mmt",
               "--mmt-trace-file=/dev/nvidia0",
               "--mmt-trace-nvidia-ioctls",
               "callback_event/callback_event",
                profile_signal,
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
                return EXIT_FAILURE;
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

    printf("Trace of '%s' saved in the file '%s'\n", profile_signal, trace_log);

    return EXIT_SUCCESS;
}
