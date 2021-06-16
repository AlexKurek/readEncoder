/** @file readEncoder.c
 *  @brief Reads encoder registers
 *
 *  Reading encopder registers via modbus protocol
 *
 *  @author Aleksander Kurek
 *  @bug No known bugs
 */

/* -- Includes -- */
/* Header of this function */
#include "readEncoder.h"

/* Reads register values to read_val table */
int readEncoder(int start, int length, const char* dName, int baud, char parity, int data_bit, int stop_bit, int slaveAddr, uint32_t resTimeSec, uint32_t resTimeuSec, int loops, int repTime, bool recovery, bool debug)
{
    modbus_t *mb;
    uint16_t tab_reg[length];         // The results of reading are stored here
    struct timeval response_timeout;
    uint32_t tv_sec  = 0;             // defaults
    uint32_t tv_usec = 500;
    response_timeout.tv_sec  = tv_sec;
    response_timeout.tv_usec = tv_usec;
    int rc;

    /* Create a context for RTU */
    printf("\n");
    printf("Trying to connect...\n");
    mb = modbus_new_rtu(dName, baud, parity, data_bit, stop_bit);  // modbus_new_rtu(const char *device, int baud, char parity, int data_bit, int stop_bit)
    if (debug)
	{
        modbus_set_debug(mb, TRUE);                                // set debug flag of the context
		printf("Entered debud moge\n");
		int getRTS = modbus_rtu_get_rts(mb);
		printf("Return of get_rts:           %d\n", getRTS);    // why 0? https://libmodbus.org/docs/v3.1.6/modbus_rtu_get_rts.html
		int getSerial = modbus_rtu_get_serial_mode(mb);
		printf("Return of get_serial_mode:   %d\n", getSerial); // why 0? https://libmodbus.org/docs/v3.0.8/modbus_rtu_get_serial_mode.html
		int getDelay = modbus_rtu_get_rts_delay(mb);
		printf("Return of get_rts_delay:     %d\n", getDelay);
		int getHeader = modbus_get_header_length(mb);
		printf("Return of get_header_length: %d\n", getHeader);
	}

    /* Set slave number in the context */
    rc = modbus_set_slave(mb, slaveAddr);
    printf("modbus_set_slave return: %d\n", rc);
    if (rc != 0)
    {
        printf("modbus_set_slave: %s \n", modbus_strerror(errno));
        modbus_close(mb);
        modbus_free(mb);
        return -1;
    }

    /* Establish a Modbus connection */
    if (modbus_connect(mb) == -1)
    {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_close(mb);
        modbus_free(mb);
        return -1;
    }
    if (NULL == mb)
    {
        printf("Unable to create libmodbus context\n");
        modbus_close(mb);
        modbus_free(mb);
        return -1;
    }
    printf("Created modbus context\n");

    /* Get response timeout */
    modbus_get_response_timeout(mb, &tv_sec, &tv_usec); 
    printf("Default response timeout: %ld sec %ld usec \n", response_timeout.tv_sec, response_timeout.tv_usec );

    /* Set response timeout */
    modbus_set_response_timeout(mb, resTimeSec, resTimeuSec); 
    modbus_get_response_timeout(mb, &tv_sec, &tv_usec); 
    printf("Set response timeout:     %d sec %d usec \n", tv_sec, tv_usec );

    if (recovery)
    {
        printf("Setting error recovery mode\n");
        modbus_set_error_recovery(mb, MODBUS_ERROR_RECOVERY_LINK | MODBUS_ERROR_RECOVERY_PROTOCOL);
    }


    /* Read and print registers from the address in 'start' */
    for (int j=0; j<loops; j++)
    {
        if (loops == 1)
            printf("Trying to read the registers...\n");
        else
        {
            int k = j+1;
            printf("( %d / %d ) Trying to read the registers...\n", k, loops);
        }
        int read_val = modbus_read_registers (mb, start, length, tab_reg);
        if (read_val == -1)
            printf("ERROR: %s\n", modbus_strerror(errno));
        else
        {
            printf("Got data from the encoder\n");
            printf("Read registers: %d\n", read_val);
            for(int i=0; i<length; i++)
                printf("%d ", tab_reg[i]);
            printf("\n");
            if ( (2-start)*(2-(length+start)) <= 0 )   // check if 2 (address of position register) was read
            {
                double posRegister = tab_reg[1];
                double posDeg = ( posRegister / 65536 ) * 360;
                printf("Position is among read registers. In degrees: %f\n", posDeg);
            }
            else
                printf("Position is not among read registers\n");
        }
        sleep (repTime);
    }

    /* Closing the context */
    modbus_close(mb);
    modbus_free(mb);
    return 0;
}