#include <stdio.h>  /* printf  */
#include <getopt.h> /* getopt API */
#include "readEncoder.h"

int main(int argc, char *argv[]) {
  int opt;

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