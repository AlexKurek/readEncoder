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

void print_usage() {
	printf("Usage: [-s] value [-l] value [-n] value [-b] value [-p] value [-d] value [-s] value or [-h] for help\n");
}

int main(int argc, char *argv[]) {

	/* -- Parsing inputs -- */
    static struct option long_options[] = {
        {"help",       no_argument,       0,  'h' },
        {"start",      required_argument, 0,  's' },
        {"length",     required_argument, 0,  'l' },
		{"deviceName", required_argument, 0,  'n' },
		{"baud",       required_argument, 0,  'b' },
		{"parity",     required_argument, 0,  'p' },
		{"data_bit",   required_argument, 0,  'd' },
		{"stop_bit",   required_argument, 0,  't' },
        {0,            0,                 0,   0  }
    };

    int   long_index = 0;
	int   start      = 0;
	int   length     = 0;
	char* dName      = '\0';   /* "/dev/ttyUSB0"; */
	int   baud       = 0;
	char  parity     = '\0';   /* 'N'; */
	int   data_bit   = 0;
	int   stop_bit   = 0;
    while ((opt = getopt_long(argc, argv,"hs:l:n:b:p:d:t:", long_options, &long_index )) != -1) {
        switch (opt) {
             case 'h' :
			 {
				printf("Reading encoder for SRT software\n");
				exit(0);
                break;
			 }
             case 's':
				start    = atoi(optarg); 
                break;
             case 'l':
				length   = atoi(optarg);
                break;
             case 'n':
				dName    = optarg;
				break;
             case 'b':
				baud     = atoi(optarg);
				break;
             case 'p':
				parity   = *optarg;
				break;
             case 'd':
				data_bit = atoi(optarg);
				break;
             case 't':
				stop_bit = atoi(optarg);
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

	if ((parity != '\0') && (parity != 'N') && (parity != 'E')) {
		printf("Wrong parity argument value\n");
		print_usage();
        exit(EXIT_FAILURE);
    }
	if (argc == 1) {
		printf("No options detected\n");
		print_usage();
        exit(EXIT_FAILURE);
	}
	if ((start >= 0) && (length > 0)) {
		readEncoder(start, length, dName, baud, parity, data_bit, stop_bit);
	}

	return 0;

}