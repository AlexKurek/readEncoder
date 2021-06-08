/** @file main.c
 *  @brief Main function for the project
 *
 *  This file contains the main() function.
 *
 *  @author Aleksander Kurek
 *  @bug No known bugs.
 */

/* -- Includes -- */
#include "main.h"

/* -- Printing usage -- */
void print_usage(void) {
	printf("Usage: [-s] value [-l] value [-n] devName (e.g. ttyUSB0) [-b] value [-p] 'N' or 'E' [-d] value [-s] value [-a] value or [-h] for help\n");
}

int main(int argc, char *argv[]) {

	/* -- Defining inputs -- */
    static struct option long_options[] = {
        {"help",       no_argument,       0,  'h' },
        {"start",      required_argument, 0,  's' },  // where to start reading
        {"length",     required_argument, 0,  'l' },  // how many registers to read
		{"deviceName", required_argument, 0,  'n' },  // e.g. "ttyUSB0" for /dev/ttyUSB0
		{"baud",       required_argument, 0,  'b' },  // [bps]
		{"parity",     required_argument, 0,  'p' },  // 'N', 'P' or 'O'
		{"data_bit",   required_argument, 0,  'd' },  // number of bits of data, the allowed values are 5, 6, 7 and 8
		{"stop_bit",   required_argument, 0,  't' },  // bits of stop, the allowed values are 1 and 2
		{"slave_ad",   required_argument, 0,  'a' },  // slave address
        {0,            0,                 0,   0  }
    };

    int   long_index = 0;
	int   start      = 0;
	int   length     = 0;
	char  dName[12]  = "/dev/"; // 12 for e.g. /dev/ttyUSB0
	char* dNameShort = '\0';
	int   baud       = 0;
	char  parity     = '\0';
	int   data_bit   = 0;
	int   stop_bit   = 0;
	int   slaveAddr  = 0;
	
	/* -- Parsing inputs -- */
    while ((opt = getopt_long(argc, argv,"hs:l:n:b:p:d:t:a:", long_options, &long_index )) != -1) {
        switch (opt) {
             case 'h' :
			 {
				printf("Reading encoder for SRT software\n");
				exit(0);
                break;
			 }
             case 's':
				start      = atoi(optarg); 
                break;
             case 'l':
				length     = atoi(optarg);
                break;
             case 'n':
				dNameShort = optarg;
				break;
             case 'b':
				baud       = atoi(optarg);
				break;
             case 'p':
				parity     = *optarg;
				break;
             case 'd':
				data_bit   = atoi(optarg);
				break;
             case 't':
				stop_bit   = atoi(optarg);
				break;
             case 'a':
				slaveAddr  = atoi(optarg);
				break;
             case '?':
				printf("Wrong options passed\n");
				print_usage();
				exit(EXIT_FAILURE);
				break;
             default:
				print_usage();
                exit(EXIT_FAILURE);
        }
    }

	/* -- Veryying inputs -- */
	if ((parity != '\0') && (parity != 'N') && (parity != 'E') && (parity != 'O')) {
		printf("Wrong parity argument value\n");
		print_usage();
        exit(EXIT_FAILURE);
    }
	if (argc == 1) {
		printf("No options detected\n");
		print_usage();
        exit(EXIT_FAILURE);
	}

	/* -- Pass inputs to function readEncoder -- */
	if ((start >= 0) && (length > 0) && (*dNameShort != '\0') && (baud > 0) && (data_bit >= 5) && (data_bit <= 8) && ((stop_bit == 1) || (stop_bit == 2))) {
		strcat(dName, dNameShort);
		readEncoder(start, length, dName, baud, parity, data_bit, stop_bit, slaveAddr);
	}

	return 0;

}