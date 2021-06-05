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
int readEncoder(int start, int length, const char* dName, int baud, char parity, int data_bit, int stop_bit)
{
	modbus_t *mb;
	uint16_t tab_reg[length]; // The results of reading are stored here

	/* create a context for RTU */
	printf("Trying to connect...\n");
	mb = modbus_new_rtu(dName, baud, parity, data_bit, stop_bit);   // modbus_new_rtu(const char *device, int baud, char parity, int data_bit, int stop_bit)
	if (modbus_connect(mb) == -1) {
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

	/* Get response timeout */
	modbus_get_response_timeout(ctx, &tv_sec, &tv_usec); 
	printf("Default response timeout:%d sec %d usec \n",tv_sec,tv_usec );

	/* Set response timeout */
	// tv_sec = 60;
	// tv_usec = 0;
	// modbus_set_response_timeout(ctx, tv_sec,tv_usec); 
	// modbus_get_response_timeout(ctx, &tv_sec, &tv_usec); 
	// printf("Set response timeout:%d sec %d usec \n",tv_sec,tv_usec );

	/* Read and print registers from the address in 'start' */
	printf("Created modbus context\n");
	int read_val = modbus_read_registers(mb, start, length, tab_reg);
	if(read_val==-1) {
		printf("ERROR: %s\n", modbus_strerror(errno));
		modbus_close(mb);
		modbus_free(mb);
		return -1;
	}
	else {
		printf("Modbus server connected successfully\n");
		printf("Read registers: %d\n", read_val);
		for(int i=0; i<length; i++) {
			printf("%d ", tab_reg[i]);
		}
		printf("\n");
	}

	/* Closing the context */
	modbus_close(mb);
	modbus_free(mb);
	
	return read_val;
}