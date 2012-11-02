/*
 * freq_changer.c
 *
 *  Created on: Nov 1, 2012
 *      Author: Andreas Torbiörnsson
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <termio.h>
#include <time.h>
#include <sys/fcntl.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <inttypes.h>
#include <sys/time.h>
#include <sys/select.h>
#include <stdint.h>

#include "devtag-allinone.h"
#include "lock.h"
#include "printAsciiHex.h"
#include "serial.h"
#include "uhx1_commander.h"
#include "util.h"
#include "datacollection.h"
#include "freq_changer.h"

int freq_changer(int target_freq, char* device){
    char* uhx1_readback;
    
    serial_openSerialPort(device, B115200, 50000, 50000);
    
    uhx1_readback = uhx1_loadChannel(target_freq);
    if(strncmp(uhx1_readback, RESPONSE_OK, 2)){
        printf("\nError setting frequency for channel\n");
        serial_closeSerialPort();
        return ERROR_CODE;
    }
    
    uhx1_setCh(CHANNEL);
    serial_closeSerialPort();
    return OK_CODE;
}