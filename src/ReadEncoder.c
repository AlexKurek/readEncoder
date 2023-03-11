/** @file readEncoder.c
 *  @brief Reads encoder registers
 *
 *  Read encoder registers via Modbus protocol
 *
 *  @author Aleksander Kurek
 *  @bug No known bugs
 */

/* -- Includes -- */
/* Header of this function */
#include "readEncoder.h"
modbus_t *ctx;


void closeMB (void)
{
    modbus_close(ctx);
    modbus_free(ctx);
}

/* Reads register values to read_val table */
int readEncoder(int start, int length, const char* dName, int baud, char parity, int data_bit, int stop_bit, int slaveAddr, uint32_t resTimeSec, uint32_t resTimeuSec, int loops, int repTime, char* inPlace, char* setTerm, char* recovery, char* debug)
{
    uint16_t tab_reg[length];   // The results of reading are stored here
    uint16_t tab_regSN_lo[1];
    uint16_t tab_regSN_hi[1];
    uint16_t tab_regVer[1];
    uint16_t tab_regTer[1];
    struct   timeval response_timeout;
    uint32_t tv_sec  = 0;
    uint32_t tv_usec = 0;
    uint32_t pos32   = 0;
    response_timeout.tv_sec  = tv_sec;
    response_timeout.tv_usec = tv_usec;
    int rc;
    int setTermInt = 0;

    /* Create a context for RTU */
    printf("\n");
    printf("Trying to connect...\n");
    ctx = modbus_new_rtu (dName, baud, parity, data_bit, stop_bit);  // modbus_new_rtu (const char *device, int baud, char parity, int data_bit, int stop_bit)

    if ( (strcmp(debug, "true") == 0) || (strcmp(debug, "TRUE") == 0) || (strcmp(debug, "1") == 0) )
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

    /* Set slave number in the context */
    rc = modbus_set_slave(ctx, slaveAddr);
    printf("modbus_set_slave return: %d\n", rc);
    if (rc != 0)
    {
        printf("modbus_set_slave: %s \n", modbus_strerror(errno));
        closeMB ();
        return -1;
    }

    /* Establish a Modbus connection */
    if (modbus_connect(ctx) == -1)
    {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        closeMB ();
        return -1;
    }
    if (NULL == ctx)
    {
        printf("Unable to create modbus context\n");
        closeMB ();
        return -1;
    }
    printf("Created modbus context\n");

    /* Get termination */
    printf("Trying to read termination register...\n");
    int ter = modbus_read_registers (ctx, TERMINREG, 1, tab_regTer);
    if (ter == -1)
        printf("ERROR: %s\n", modbus_strerror(errno));
    else
        printf("Termination: %d\n", tab_regTer[0]);

    /* Set termination */
    if ( (strcmp(setTerm, "0") == 0) || (strcmp(setTerm, "off") == 0) || (strcmp(setTerm, "OFF") == 0) || (strcmp(setTerm, "1") == 0) || (strcmp(setTerm, "on") == 0) || (strcmp(setTerm, "ON") == 0) )
    {
        if ( (strcmp(setTerm, "0") == 0)   || (strcmp(setTerm, "1") == 0) )
            setTermInt = atoi(setTerm);
        if ( (strcmp(setTerm, "off") == 0) || (strcmp(setTerm, "OFF") == 0) )
            setTermInt = 0;
        if ( (strcmp(setTerm, "on") == 0)  || (strcmp(setTerm, "ON") == 0) )
            setTermInt = 1;
        if (tab_regTer[0] != setTermInt)   // checking, if termination register is already set to the requested value
        {
            printf("Trying to set termination register to %d...\n", setTermInt);
            int terWrite = modbus_write_register(ctx, TERMINREG, setTermInt);
            if (terWrite == -1)
            {
                printf("ERROR: %s\n", modbus_strerror(errno));
                closeMB ();
                return -1;
            }
            int terWriteSet = modbus_write_register(ctx, TERMINREGEXE, 1);   // execute the above
            if (terWriteSet == -1)
            {
                printf("ERROR: %s\n", modbus_strerror(errno));
                closeMB ();
                return -1;
            }
            ter = modbus_read_registers (ctx, TERMINREG, 1, tab_regTer);     // veryfying
            if (ter == -1)
                printf("ERROR: %s\n", modbus_strerror(errno));
            else
                printf("Termination: %d\n", tab_regTer[0]);
        }
        else
            printf("Termination register already set to this value, so not writing it again\n");
    }

    /* Get response timeout */
    modbus_get_response_timeout(ctx, &tv_sec, &tv_usec); 
    printf("Default response timeout: %ld sec %ld usec \n", response_timeout.tv_sec, response_timeout.tv_usec );

    /* Set response timeout */
    modbus_set_response_timeout(ctx, resTimeSec, resTimeuSec); 
    modbus_get_response_timeout(ctx, &tv_sec, &tv_usec); 
    printf("Set response timeout:     %d sec %d usec \n", tv_sec, tv_usec );

    if ( (strcmp(recovery, "true") == 0) || (strcmp(recovery, "TRUE") == 0) || (strcmp(recovery, "1") == 0) )
    {
        printf("Setting error recovery mode\n");
        modbus_set_error_recovery(ctx, MODBUS_ERROR_RECOVERY_LINK | MODBUS_ERROR_RECOVERY_PROTOCOL);
    }

    /* Read and print SN register */
    printf("Trying to read SN...\n");
    int SNhi = modbus_read_registers (ctx, SERIALNOREGHI, 1, tab_regSN_hi);
    int SNlo = modbus_read_registers (ctx, SERIALNOREGLO, 1, tab_regSN_lo);
    if ((SNhi == -1) || (SNlo == -1))
        printf("ERROR: %s\n", modbus_strerror(errno));
    else
    {
        uint32_t SN = tab_regSN_lo[0] | (tab_regSN_hi[0] << 16);
        printf("SN: %d\n", SN);
    }

    /* Read and print version register */
    printf("Trying to read version...\n");
    int ver = modbus_read_registers (ctx, VERREG, 1, tab_regVer);
    if (ver == -1)
        printf("ERROR: %s\n", modbus_strerror(errno));
    else
    {
        printf("Version: %d\n", tab_regVer[0]);
        if ( (tab_regVer[0] != 101) && ( (strcmp(debug, "true") == 0) || (strcmp(debug, "TRUE") == 0) || (strcmp(debug, "1") == 0) ) )
            printf("We tested only version 101\n");
    }

    /* Read and print registers from the address in 'start' */
    if (loops == 0)
    {
        for (;;)
        {
            printf("Trying to read the registers...\n");
            int read_val = modbus_read_registers (ctx, start, length, tab_reg);
            if (read_val == -1)
            {
                printf("ERROR: %s\n", modbus_strerror(errno));
                closeMB ();
                return -1;
            }
            else
            {
                if ( (strcmp(inPlace, "true") == 0) || (strcmp(inPlace, "TRUE") == 0) || (strcmp(inPlace, "1") == 0) )  // for basic in place printing
                    if (system ("clear")){};
                printf("Got data from the encoder\n");
                printf("Read %d registers: \n", read_val);
                for(int i=0; i<length; i++)
                    printf("%d ", tab_reg[i]);
                printf("\n");
                if ( (2-start)*(2-(length+start)) <= 0 )      // check if 2 (address of position register) was read
                {
                    double posRegister = tab_reg[1];
                    double posDeg = ( posRegister / 65536 ) * 360;
                    printf("Position is among read registers. In degrees: %f\n", posDeg);
                }
                if ( (tab_reg[0] !=0) && (tab_reg[1] != 0) )  // quick check if both address of position registers were read
                {
                    pos32 = tab_reg[0] | (tab_reg[1]<<16);
                    printf("Both position adresses were read. In 32-bit format: %d\n", pos32);
                }
                else
                    printf("Position is not among read registers\n");
            }
            sleep (repTime);
        }
    }
    if (loops > 0)
    {
        for (int j=0; j<loops; j++)
        {
            if (loops == 1)
                printf("Trying to read the registers...\n");
            if (loops > 1)
            {
                int k = j+1;
                printf("( %d / %d ) Trying to read the registers...\n", k, loops);
            }
            int read_val = modbus_read_registers (ctx, start, length, tab_reg);
            if (read_val == -1)
            {
                printf("ERROR: %s\n", modbus_strerror(errno));
                closeMB ();
                return -1;
            }
            else
            {
                printf("Got data from the encoder\n");
                printf("Read %d registers: \n", read_val);
                for(int i=0; i<length; i++)
                    printf("%d ", tab_reg[i]);
                printf("\n");
                if ( (2-start)*(2-(length+start)) <= 0 )      // check if 2 (address of position register) was read
                {
                    double posRegister = tab_reg[1];
                    double posDeg = ( posRegister / 65536 ) * 360;
                    printf("Position is among read registers. In degrees: %f\n", posDeg);
                }
                if ( (tab_reg[0] !=0) && (tab_reg[1] != 0) )  // quick check if both address of position registers were read
                {
                    pos32 = tab_reg[0] | (tab_reg[1]<<16);
                    printf("Both position adresses were read. In 32-bit format: %d\n", pos32);
                }
                else
                    printf("Position is not among read registers\n");
            }
            sleep (repTime);
        }
    }

    /* Closing the context */
    closeMB ();
    return 0;
}