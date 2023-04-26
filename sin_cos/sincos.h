//
// Created by Titouan LEBOCQ on 24/04/2023.
//

#ifndef OPERATING_SYSTEM_SYSTEM_SIGNALS_SINCOS_H
#define OPERATING_SYSTEM_SYSTEM_SIGNALS_SINCOS_H

#include <signal.h>
#include <printf.h>

/**
 * util for signal handling.
 */
#define TYPE_SIN 0
#define TYPE_COS 1
/**
 * utils for file handling.
 */
#define COS_COMMAND_FILE "cos.gp"
#define COS_DATA_FILE "cos.txt"
#define SIN_COMMAND_FILE "sin.gp"
#define SIN_DATA_FILE "sin.txt"

/**
 * Function defining the child processing routine.
 * @param type
 */
void child_process_routine(int type);

/**
 * Function defining the display routine for the application.
 */
void display_routine();

/**
 * Signal handler for sinus.
 * @param sig the signal
 */
void sin_signal_handler(int sig);

/**
 * Signal handler for cosinus.
 * @param sig the signal
 */
void cos_signal_handler(int sig);

/**
 * The function defining the parent routine sequencing data creation.
 * @param pid_sin pid of the process used to compute the sin
 * @param pid_cos pid of the process used to compute the cos
 */
void parent_routine(int pid_sin, int pid_cos);

/**
 * Function used to write data to a data file (gnuplot)
 * @param filename the name of the file
 * @param input the x value
 * @param output the f(x) = y value
 */
void write_data_to_file(char *filename, int input, double output);

#endif //OPERATING_SYSTEM_SYSTEM_SIGNALS_SINCOS_H
