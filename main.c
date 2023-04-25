#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "sin_cos/sincos.h"

int main() {

    int pid_cos = fork();
    if (pid_cos == 0) {
        child_routine(TYPE_COS);
        return EXIT_SUCCESS;
    }
    int pid_sin = fork();
    if (pid_sin == 0) {
        child_routine(TYPE_SIN);
        return EXIT_SUCCESS;
    }

    sleep(1); // waiting for child to print data
    parent_routine(pid_sin, pid_cos);

    return EXIT_SUCCESS;
}
