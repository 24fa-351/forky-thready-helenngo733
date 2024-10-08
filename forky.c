#include "forky.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void random_sleep() {
    int sleep_time = rand() % 8 + 1;
    sleep(sleep_time);
}

void pattern_1(int num_of_things) {
    for (int ix = 1; ix <= num_of_things; ix++) {
        pid_t pid = fork();
        if (pid == 0) {
            fprintf(stderr, "Process %d (%d) beginning\n", ix, getpid());
            random_sleep();

            fprintf(stderr, "Process %d (%d) exiting\n", ix, getpid());
            exit(0);  // end the child process
        }
    }
    for (int ix = 1; ix <= num_of_things; ++ix) {
        wait(NULL);  // wait for all children to finish
    }
    fprintf(stderr, "\n");
}

void pattern_2(int num_of_things) {
    pid_t pid = fork();
    if (pid == 0) {
        for (int ix = 1; ix <= num_of_things; ix++) {
            fprintf(stderr, "process %d (%d) beginning\n", ix, getpid());
            random_sleep();

            if (ix < num_of_things) {  // Create next process
                pid_t child_pid = fork();
                if (child_pid == 0) {
                    continue;
                } else if (child_pid > 0) {
                    fprintf(stderr, "Process %d (%d) creating Process %d (%d)\n", ix, getpid(), ix + 1, child_pid);
                    wait(NULL);  // Wait for child to finish
                    fprintf(stderr, "Process %d (%d) exiting\n", ix, getpid());
                    exit(0);
                }
            } else {
                fprintf(stderr, "Process %d (%d) exiting\n", ix, getpid());
                exit(0);
            }
        }
    } else if (pid > 0) {
        wait(NULL);
    }
    fprintf(stderr, "\n");
}