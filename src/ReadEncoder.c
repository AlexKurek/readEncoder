/** @file readEncoder.c
 *  @brief Reads encoder registers
 *
 *  Reading registers
 *
 *  @author Aleksander Kurek
 *  @bug No known bugs
 */

/* -- Includes -- */
/* Header of this function */
#include "readEncoder.h"

/* Reads register values to read_val table */
int readEncoder(int start, int length, const char* dName, int baud, char parity, int data_bit, int stop_bit, int slaveAddr)
{
    modbus_t *mb;
    uint16_t tab_reg[length];     // The results of reading are stored here
    struct timeval response_timeout;
    uint32_t tv_sec = 0;
    uint32_t tv_usec = 0;
    response_timeout.tv_sec = 5;  // defaults
    response_timeout.tv_usec = 0;
    float avgVlt = -1;
    int rc;

    /* Create a context for RTU */
    printf("Trying to connect...\n");
    mb = modbus_new_rtu(dName, baud, parity, data_bit, stop_bit);  // modbus_new_rtu(const char *device, int baud, char parity, int data_bit, int stop_bit)
    modbus_set_debug(mb, TRUE);                                    // set debug flag of the context

    /* Set slave number in the context */
    rc = modbus_set_slave(mb, slaveAddr);
    printf("modbus_set_slave return: %d\n",rc);
    if (rc != 0)
    {
        printf("modbus_set_slave: %s \n",modbus_strerror(errno));
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
    printf("Default response timeout:%ld sec %ld usec \n", response_timeout.tv_sec, response_timeout.tv_usec );

    /* Set response timeout */
    // tv_sec = 60;
    // tv_usec = 0;
    // modbus_set_response_timeout(mb, tv_sec,tv_usec); 
    // modbus_get_response_timeout(mb, &tv_sec, &tv_usec); 
    // printf("Set response timeout:%d sec %d usec \n",tv_sec,tv_usec );

    modbus_set_error_recovery(mb, MODBUS_ERROR_RECOVERY_LINK | MODBUS_ERROR_RECOVERY_PROTOCOL);

    /* Read and print registers from the address in 'start' */
    int read_val = modbus_read_registers(mb, start, length, tab_reg);
    if(read_val==-1)
    {
        printf("ERROR: %s\n", modbus_strerror(errno));
        modbus_close(mb);
        modbus_free(mb);
        return -1;
    }
    else
    {
        printf("Modbus server connected successfully\n");
        printf("Read registers: %d\n", read_val);
        for(int i=0; i<length; i++)
            printf("%d ", tab_reg[i]);
        printf("\n");
    }

    avgVlt = modbus_get_float(tab_reg);
    printf("Average Line to Line Voltage = %f\n", avgVlt);

    /* Closing the context */
    modbus_close(mb);
    modbus_free(mb);
    
    return read_val;
}