//
// Created by Titouan LEBOCQ on 24/04/2023.
//
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#include "sincos.h"

double data = 0;
int increment_value = 10;

void sin_signal_handler(int sig) {
    data = fmod(data + increment_value, 360);
    printf("[SIN]%f\n", sin(data));
}

void cos_signal_handler(int sig) {
    data = fmod(data + increment_value, 360);
    printf("[COS]%f\n", cos(data));
}

void child_routine(int type) {
    printf("[child] started\n");
    // setup custom signals handler
    struct sigaction sa = {0};
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (type == TYPE_SIN) {
        sa.sa_handler = sin_signal_handler;
        if (sigaction(SIGUSR1, &sa, NULL) == -1) {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }
    } else if (type == TYPE_COS) {
        sa.sa_handler = cos_signal_handler;
        if (sigaction(SIGUSR1, &sa, NULL) == -1) {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }
    }
    // infinite loop waiting for kill signal from parent
    while (1) {
        pause();
    };
}

void parent_routine(int pid_sin, int pid_cos) {
    printf("[parent] started\n");
    // simple for of 10 iterations instead of infinite loop asked in the subject
    for (int i = 0; i < 10; i++) {
        printf("[parent] sending signals\n");

        kill(pid_sin, SIGUSR1);
        kill(pid_cos, SIGUSR1);

        sleep(1);
        printf("[parent] slept for 1sec\n");
    }
    printf("[parent] end parent and kill childs");
    kill(pid_sin, SIGKILL);
    kill(pid_cos, SIGKILL);
}