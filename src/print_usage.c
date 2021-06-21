/* -- Printing usage -- */

/* -- Includes -- */
#include "print_usage.h"

void printUsage(void) {
    printf("Usage: [-s] value [-l] value [-n] devName (e.g. ttyUSB0) [-b] value [-p] 'N', 'E' or 'O' [-d] value [-s] value [-a] value [-e] value [-u] value [-o] value [-r] value [-i] value [-c] value [-g] value\n"
	"       or [-h] for help\n");
}