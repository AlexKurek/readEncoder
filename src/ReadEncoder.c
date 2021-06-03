/** @file readEncoder.c
 *  @brief Reads encoder registers
 *
 *  Reading registers
 *
 *  @author Fred Hacker (fhacker)
 *  @bug No known bugs.
 */

/* -- Includes -- */
/* Header of this function */
#include "readEncoder.h"

int readEncoder(int start, int length, const char *dName, int baud, char parity, int data_bit, int stop_bit)
{
	modbus_t *mb;
	uint16_t tab_reg[32];

	printf("Trying to connect...\n");
	mb = modbus_new_rtu(*dName, baud, parity, data_bit, stop_bit);   /* modbus_new_rtu(const char *device, int baud, char parity, int data_bit, int stop_bit) */
	if (modbus_connect(mb) == -1) {
		fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
		modbus_free(mb);
		return -1;
	} 

	/* Read and print registers from the address in 'start' */
	int read_val = modbus_read_registers(mb, start, length, tab_reg);
	if(read_val==-1) {
		printf("ERROR: %s\n", modbus_strerror(errno));
		return -1;
	}
	else {
		printf("Read registers: %d\n", read_val);
		for(int i=0; i<length; i++) {
			printf("%d ", tab_reg[i]);
		}
		printf("\n");
	}

	modbus_close(mb);
	modbus_free(mb);
	
	return 0;
}