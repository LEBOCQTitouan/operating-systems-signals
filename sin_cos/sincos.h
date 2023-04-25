//
// Created by Titouan LEBOCQ on 24/04/2023.
//

#ifndef OPERATING_SYSTEM_SYSTEM_SIGNALS_SINCOS_H
#define OPERATING_SYSTEM_SYSTEM_SIGNALS_SINCOS_H

#include <signal.h>
#include <printf.h>

#define TYPE_SIN 0
#define TYPE_COS 1

void child_routine(int type);

void sin_signal_handler(int sig);

void cos_signal_handler(int sig);

void parent_routine(int pid_sin, int pid_cos);

#endif //OPERATING_SYSTEM_SYSTEM_SIGNALS_SINCOS_H
