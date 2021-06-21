#ifndef readEncoder_DOT_H
#define readEncoder_DOT_H

#include <modbus.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define verReg        41
#define serialNoRegHi 42
#define serialNoRegLo 43

int readEncoder(int, int, const char*, int, char, int, int, int, uint32_t, uint32_t, int, int, char*, char*);

#endif