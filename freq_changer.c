/*
 * uhx1_commander.c
 *
 *  Created on: Jul 6, 2012
 *      Author: alpsayin
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

int freq_changer(int target_freq, char* device){
    char* uhx1_readback;
    int retval = 1;
    
    serial_openSerialPort(device, B115200, 50000, 50000);
    uhx1_readback = uhx1_loadChannel(target_freq);	serial_closeSerialPort();
    if(strncmp(uhx1_readback, "OK", 2)){
        printf("\nError setting frequency for channel\n");
        serial_closeSerialPort();
        return 1;
    }
    uhx1_setCh(1);
    serial_closeSerialPort();
    return 0;
}