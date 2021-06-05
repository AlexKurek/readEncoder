#ifndef readEncoder_DOT_H
#define readEncoder_DOT_H

#include <modbus.h>
#include <errno.h>
#include <stdio.h>

int readEncoder(int, int, const char*, int, char, int, int, int);

#endif