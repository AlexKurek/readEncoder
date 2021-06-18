#ifndef readEncoder_DOT_H
#define readEncoder_DOT_H

#include <modbus.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#define verReg      41
#define serialNoReg 42

int readEncoder(int, int, const char*, int, char, int, int, int, uint32_t, uint32_t, int, int, bool, bool);

#endif