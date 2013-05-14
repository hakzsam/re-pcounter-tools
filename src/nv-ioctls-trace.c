#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

#include <cupti.h>

#define PROFILE_CONFIG "/tmp/compute_profile_config.txt"

/**
 * TODO:
 *  - do not hardcode chipset (use nvalist).
 *  - use CUPti instead of these bad env vars.
 *  - do not use lookup through popen() (it's bad).
 *  - use env vars for setting valgrind-mmt.
 */

static void init_profiler(char *profile_config, int profile_csv,
                          char *profile_log)
{
    // Set to either 1 or 0 (or unset) to enable or disable profiling.
    setenv("COMPUTE_PROFILE", "1", 1);

    // Set to either 1 (set) or 0 (unset) to enable or disable a comma separated
    // version of the log output.
    if (profile_csv) {
        setenv("COMPUTE_PROFILE_CSV=", "1", 1);
    } else {
        setenv("COMPUTE_PROFILE_CSV=", "0", 1);
    }

    // Set to the desired file path for profiling output. If there is no
    // log path specified, the profiler will log data to ./compute_profile.log.
    // In case of multiple devices you can add '%d' in the COMPUTE_PROFILE_LOG
    // name. This will generate separate profiler output files for each device
    // - with '%d' substituted by the device number.
    if (profile_log) {
        setenv("COMPUTE_PROFILE_LOG", profile_log, 1);
    }

    // Used to specify a config file for enabling performance counters in the GPU. 
    setenv("COMPUTE_PROFILE_CONFIG", profile_config, 1);
}

static int create_profile_config(const char *filename, char *signal)
{
    FILE *f;

    if (!(f = fopen(filename, "w+"))) {
        perror("fopen");
        return -errno;
    }

    fwrite(signal, strlen(signal), 1, f);
    fwrite("\n", 1, 1, f);

    if (fclose(f) < 0) {
        perror("fclose");
        return -errno;
    }

    return 0;
}

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
    char *profile_sample = NULL, *profile_signal = NULL, *profile_log = NULL;
    char trace_log[1024];
    int profile_csv = 0;
    char line[1024];
    pid_t pid;
    FILE *f;
    int ret;
    int c;

    if (argc < 3) {
        fprintf(stderr,
                "Usage: %s <profile_sample> <profile_signal> [options]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    profile_sample = argv[1];
    profile_signal = argv[2];

    while (1) {
        static struct option long_options[] = {
            {"csv",     no_argument,        0, 'c'},
            {"log",     required_argument,  0, 'l'},
            {0, 0, 0, 0}
        };

        /* getopt_long stores the option index here. */
        int option_index = 0;

        argv -= 2;
        argv += 2;
        c = getopt_long(argc, argv, "c:l:", long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c) {
            case 'c':
                profile_csv = 1;
                break;
            case 'l':
                profile_log = optarg;
                break;
            case '?':
                /* getopt_long already printed an error message. */
                break;
            default:
                abort ();
        }
    }

    // Create the config file for enabling performance counters in the GPU.
    if ((ret = create_profile_config(PROFILE_CONFIG, profile_signal)) < 0)
        return ret;

    // Init environnement variables in order to enable profiling.
    init_profiler(PROFILE_CONFIG, profile_csv, profile_log);

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
        dup2(fileno(f), 1);
        dup2(fileno(f), 2);

        // Launch valgrind-mmt with a CUDA/OpenCL sample.
        execlp("/usr/local/bin/valgrind", "valgrind",
               "--tool=mmt",
               "--mmt-trace-file=/dev/nvidia0",
               "--mmt-trace-nvidia-ioctls",
               profile_sample,
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
