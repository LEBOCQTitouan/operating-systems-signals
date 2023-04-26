#include <unistd.h>
#include <stdlib.h>
#include "sin_cos/sincos.h"

int main() {

    FILE *fp_sin = fopen(SIN_COMMAND_FILE, "w");
    FILE *fp_cos = fopen(COS_COMMAND_FILE, "w");

    fprintf(fp_sin, "plot \"%s\" using 1:2 smooth csplines\n", SIN_DATA_FILE);
    fprintf(fp_cos, "plot \"%s\" using 1:2 smooth csplines\n", COS_DATA_FILE);

    fclose(fp_sin);
    fclose(fp_cos);

    FILE *fp_data_sin = fopen(SIN_DATA_FILE, "w");
    FILE *fp_data_cos = fopen(SIN_DATA_FILE, "w");

    fclose(fp_data_sin);
    fclose(fp_data_cos);

    int pid_cos = fork();
    if (pid_cos == 0) {
        child_process_routine(TYPE_COS);
        return EXIT_SUCCESS;
    }
    int pid_sin = fork();
    if (pid_sin == 0) {
        child_process_routine(TYPE_SIN);
        return EXIT_SUCCESS;
    }

    sleep(1); // waiting for child to print data
    parent_routine(pid_sin, pid_cos);

    display_routine();

    return EXIT_SUCCESS;
}
