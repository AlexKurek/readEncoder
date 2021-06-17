/* -- Printing debug info -- */

/* -- Includes -- */
#include "print_debug.h"

void printDebug (modbus_t *ctx)
{
    modbus_set_debug(ctx, TRUE);  // set debug flag of the context
    printf("Debud mode on\n");
    int getRTS = modbus_rtu_get_rts(ctx);
    printf("Return of get_rts:      %d\n", getRTS);
    printf("Return of RTU_RTS_NONE: %d\n", MODBUS_RTU_RTS_NONE);
    printf("Return of RTU_RTS_UP:   %d\n", MODBUS_RTU_RTS_UP);
    printf("Return of RTU_RTS_DOWN: %d\n", MODBUS_RTU_RTS_DOWN);
    int getSerial = modbus_rtu_get_serial_mode(ctx);
    if (getSerial == 0)
    {
        if (MODBUS_RTU_RS232 == 1)
            printf("RTU is in RS232 mode\n");
        if (MODBUS_RTU_RS485 == 1)
            printf("RTU is in RS485 mode\n");
    }
    int getDelay = modbus_rtu_get_rts_delay(ctx);
    if (getDelay != -1)
        printf("RTS delay:     %d [μs]\n", getDelay);
    int getHeader = modbus_get_header_length(ctx);
    if (getHeader != -1)
        printf("Header length: %d\n", getHeader);
}