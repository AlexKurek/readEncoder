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
	printf("Usage: [-s] value [-l] value or [-h] for help\n");
}

int main(int argc, char *argv[]) {

    static struct option long_options[] = {
        {"help",   no_argument,       0,  'h' },
        {"start",  required_argument, 0,  's' },
        {"length", required_argument, 0,  'l' },
        {0,        0,                 0,  0   }
    };

    int long_index = 0;
	int start      = 0;
	int length     = 0;
    while ((opt = getopt_long(argc, argv,"hs:l:", long_options, &long_index )) != -1) {
        switch (opt) {
             case 'h' :
			 {
				printf("Reading encoder for SRT software\n");
				exit(0);
                break;
			 }
             case 's':
				start  = atoi(optarg); 
                break;
             case 'l':
				length = atoi(optarg);
                break;
             default:
				print_usage();
                exit(EXIT_FAILURE);
        }
    }

    if (start == -1 || length == -1) {
        print_usage();
        exit(EXIT_FAILURE);
    }
	
	if ((start > 0) && (length > 0)) {
		readEncoder(start, length);
	}

	return 0;

}