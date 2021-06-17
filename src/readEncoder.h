#ifndef readEncoder_DOT_H
#define readEncoder_DOT_H

#include <modbus.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "print_debug.h"

/* global variable declaration */
modbus_t *ctx;

int readEncoder(int, int, const char*, int, char, int, int, int, uint32_t, uint32_t, int, int, bool, bool);

#endif