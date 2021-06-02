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

int main(int argc, char *argv[]) {

	while ((opt = getopt(argc, argv, "hc")) != -1)
	{
		switch (opt) 
		{
			case 'h':
			{
				printf("Reading encoder for SRT software\n");
				exit(0);
				break;
			}
			case 'c':
			{
				int start  = 0;
				int length = 5;
				readEncoder(start, length);
				break;
			}
			default:
				fprintf(stderr, "Usage: %s [-s] value [-l] value or [-h] for help\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}
	return 0;

}