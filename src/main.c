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


int main(int argc, char *argv[])
{
    /* -- Defining inputs -- */
    static struct option long_options[] = {
        {"help",         no_argument,       0,  'h' },
        {"start",        required_argument, 0,  's' },  // where to start reading (w/o offset)
        {"length",       required_argument, 0,  'l' },  // how many registers to read
        {"deviceName",   required_argument, 0,  'n' },  // e.g. "/dev/ttyUSB0" or shorter "ttyUSB0"
        {"baud",         required_argument, 0,  'b' },  // [bps]
        {"parity",       required_argument, 0,  'p' },  // 'N', 'E' or 'O'
        {"data_bit",     required_argument, 0,  'd' },  // number of bits of data, the allowed values are 5, 6, 7 and 8
        {"stop_bit",     required_argument, 0,  't' },  // bits of stop, the allowed values are 1 and 2
        {"slave_ad",     required_argument, 0,  'a' },  // slave address
        {"timeout_sec",  required_argument, 0,  'e' },  // timeout to set in [sec]
        {"timeout_μsec", required_argument, 0,  'u' },  // and the [μsec] part. At least 13000, better 20000 (20ms)
        {"loops",        required_argument, 0,  'o' },  // how many loops of reading
        {"repTime",      required_argument, 0,  'r' },  // time between loops [msec]
        {"recovery",     required_argument, 0,  'c' },  // error recovery mode. Bool type
        {"debug",        required_argument, 0,  'g' },  // debug mode. Bool type
        {0,              0,                 0,   0  }
    };


    /* -- Parsing inputs -- */
    while ( (opt = getopt_long(argc, argv,"hs:l:n:b:p:d:t:a:e:u:o:r:c:g:", long_options, &long_index )) != -1 )
    {
        optionsDone = true;
        switch (opt)
        {
             case 'h' :
             {
                printf("Reading encoder for SRT software\n");
                printUsage();
                exit(0);
                break;
             }
             case 's':
                start       = atoi(optarg); 
                break;
             case 'l':
                length      = atoi(optarg);
                break;
             case 'n':
                dNameInp    = optarg;
                break;
             case 'b':
                baud        = atoi(optarg);
                break;
             case 'p':
                parity      = *optarg;
                break;
             case 'd':
                data_bit    = atoi(optarg);
                break;
             case 't':
                stop_bit    = atoi(optarg);
                break;
             case 'a':
                slaveAddr   = atoi(optarg);
                break;
             case 'e':
                resTimeSec  = atoi(optarg);
                break;
             case 'u':
                resTimeuSec = atoi(optarg);
                break;
             case 'o':
                loops       = atoi(optarg);
                break;
             case 'r':
                repTime     = atoi(optarg);
                break;
             case 'c':
			 {
                recovery    = optarg;
				fputs(recovery ? "true\n" : "false\n", stdout);
                break;
			 }
             case 'g':
			 {
                debug       = optarg;
				fputs(debug ? "true\n" : "false\n", stdout);
			 }
                break;
             case '?':
             {
                printf("Wrong option(s) passed\n");
                printUsage();
                exit(EXIT_FAILURE);
                break;
             }
             default:
             {
                printUsage();
                exit(EXIT_FAILURE);
             }
        }
    }

    /* -- Verifying inputs -- */
    if ((parity != '\0') && (parity != 'N') && (parity != 'E') && (parity != 'O'))
    {
        printf("Wrong parity value\n");
        printUsage();
        exit(EXIT_FAILURE);
    }
    if ((resTimeSec + resTimeuSec == 0) && (optionsDone == true))
    {
        printf("Response time can't be = 0\n");
        exit(EXIT_FAILURE);
    }
    if (argc == 1)
    {
        printf("No options detected\n");
        printUsage();
        exit(EXIT_FAILURE);
    }
    if (strstr(dNameInp, "/dev/") == NULL)
    {
        strcat(dName, dNameInp);
        printf("Short device name in input, expanding it to: %s\n", dName);
    }

    /* -- Pass inputs to function readEncoder -- */
    if ( (start > 0) && (length > 0) && (*dNameInp != '\0') && (baud > 0) && (data_bit >= 5) && (data_bit <= 8) && ( (stop_bit == 1) || (stop_bit == 2) ) )
        readEncoder ( start, length, dName, baud, parity, data_bit, stop_bit, slaveAddr, resTimeSec, resTimeuSec, loops, repTime, recovery, debug );
    else
    {
        printf("Something went wrong\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}