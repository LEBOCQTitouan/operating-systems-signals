//
// Created by Titouan LEBOCQ on 24/04/2023.
//
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#include "sincos.h"

double data = 0;
int increment_value = 1;

void sin_signal_handler(int sig) {
    data = fmod(data + increment_value, 360);
    double processed_data = sin(data);
    printf("sin(%f) = %f\n", data, processed_data);
    write_data_to_file(SIN_DATA_FILE, data, processed_data);
}

void cos_signal_handler(int sig) {
    data = fmod(data + increment_value, 360);
    double processed_data = cos(data);
    printf("cos(%f) = %f\n", data, processed_data);
    write_data_to_file(COS_DATA_FILE, data, processed_data);
}

void child_process_routine(int type) {
    printf("[child] started\n");
    // setup custom signals handler
    struct sigaction sa = {0};
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (type == TYPE_SIN) {
        sa.sa_handler = sin_signal_handler;
        if (sigaction(SIGALRM, &sa, NULL) == -1) {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }
    } else if (type == TYPE_COS) {
        sa.sa_handler = cos_signal_handler;
        if (sigaction(SIGALRM, &sa, NULL) == -1) {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }
    }
    // infinite loop waiting for kill signal from parent
    while (1) {
        pause();
    };
}

void display_routine() {
    int pid;

    pid = fork();
    if (pid == 0) {
        if (execlp("gnuplot", "gnuplot", "-persist", COS_COMMAND_FILE, NULL) != 0) {
            perror("execv");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }

    pid = fork();
    if (pid == 0) {
        if (execlp("gnuplot", "gnuplot", "-persist", SIN_COMMAND_FILE, NULL) != 0) {
            perror("execv");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }

    wait(NULL);
}

void parent_routine(int pid_sin, int pid_cos) {
    printf("[parent] started\n");
    // simple for of 10 iterations instead of infinite loop asked in the subject
    for (int i = 0; i < 30; i++) {
        kill(pid_sin, SIGALRM);
        kill(pid_cos, SIGALRM);
        usleep(100); // used to display in terminal
    }
    printf("[parent] end parent and kill childs");
    kill(pid_sin, SIGKILL);
    kill(pid_cos, SIGKILL);
}

void write_data_to_file(char *filename, int input, double output) {
    FILE *fp = fopen(filename, "a");
    fprintf(fp, "%d\t%.2f\n", input, output);
    fclose(fp);
}