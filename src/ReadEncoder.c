#include "readEncoder.h"

int readEncoder(void)
{
	modbus_t *mb;
	uint16_t tab_reg[32];
	int start  = 0;
	int length = 5;

	printf("Trying to connect...\n");
	mb = modbus_new_tcp("127.0.0.1", 1502);
	if (modbus_connect(mb) == -1) {
		fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
		modbus_free(mb);
		return -1;
	} 

	/* Read registers from the address in 'start' */
	int read_val = modbus_read_registers(mb, start, length, tab_reg);
	if(read_val==-1)
		printf("ERROR: %s\n", modbus_strerror(errno));
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