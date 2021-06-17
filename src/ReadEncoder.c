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
    ctx = modbus_new_rtu(dName, baud, parity, data_bit, stop_bit);  // modbus_new_rtu (const char *device, int baud, char parity, int data_bit, int stop_bit)
    if (debug)
        printDebug(ctx);

    /* Set slave nuctxer in the context */
    rc = modbus_set_slave(ctx, slaveAddr);
    printf("modbus_set_slave return: %d\n", rc);
    if (rc != 0)
    {
        printf("modbus_set_slave: %s \n", modbus_strerror(errno));
        modbus_close(ctx);
        modbus_free(ctx);
        return -1;
    }

    /* Establish a Modbus connection */
    if (modbus_connect(ctx) == -1)
    {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_close(ctx);
        modbus_free(ctx);
        return -1;
    }
    if (NULL == ctx)
    {
        printf("Unable to create modbus context\n");
        modbus_close(ctx);
        modbus_free(ctx);
        return -1;
    }
    printf("Created modbus context\n");

    /* Get response timeout */
    modbus_get_response_timeout(ctx, &tv_sec, &tv_usec); 
    printf("Default response timeout: %ld sec %ld usec \n", response_timeout.tv_sec, response_timeout.tv_usec );

    /* Set response timeout */
    modbus_set_response_timeout(ctx, resTimeSec, resTimeuSec); 
    modbus_get_response_timeout(ctx, &tv_sec, &tv_usec); 
    printf("Set response timeout:     %d sec %d usec \n", tv_sec, tv_usec );

    if (recovery)
    {
        printf("Setting error recovery mode\n");
        modbus_set_error_recovery(ctx, MODBUS_ERROR_RECOVERY_LINK | MODBUS_ERROR_RECOVERY_PROTOCOL);
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
        int read_val = modbus_read_registers (ctx, start, length, tab_reg);
        if (read_val == -1)
            printf("ERROR: %s\n", modbus_strerror(errno));
        else
        {
            printf("Got data from the encoder\n");
            printf("Read %d registers: \n", read_val);
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
    modbus_close(ctx);
    modbus_free(ctx);
    return 0;
}