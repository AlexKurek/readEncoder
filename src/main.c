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
			printf("Reading encoder for SRT software\n");
			break;
		case 'c':
			readEncoder();
			break;
		}
	}
	return 0;

}