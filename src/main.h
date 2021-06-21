#ifndef main_DOT_H
#define main_DOT_H

#include <stdio.h>       /* printf  */
#include <getopt.h>      /* getopt API */
#include "print_usage.h"
#include "readEncoder.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int opt;

int      long_index  = 0;
int      start       = 0;
int      length      = 0;
char     dName[12]   = "/dev/"; // 12 for e.g. /dev/ttyUSB0
char*    dNameInp    = '\0';
int      baud        = 0;
char     parity      = '\0';
int      data_bit    = 0;
int      stop_bit    = 0;
int      slaveAddr   = 0;
uint32_t resTimeSec  = 0;
uint32_t resTimeuSec = 0;
bool     optionsDone = false;
int      loops       = 0;
int      repTime     = 0;
char*    recovery    = (char*)"false";
char*    debug       = (char*)"false";

#endif