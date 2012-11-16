/*
 * uhx1_control.c
 *
 *  Updated on: Nov 9, 2012
 *      By: andreastorbiornsson
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
#include "uhx1_control.h"
#include "radio_conf.h"

char *buffer;

int uhx1_setupChannels(int startFrequencyKhz, int step){
    
    //Open the serial port for communicating with uhx1 device
    serial_openSerialPort(get_progDevice(), B115200, 50000, 50000);
    
    buffer = uhx1_startChan(startFrequencyKhz);
    if(!strncmp("OK", buffer, 2)){
        serial_closeSerialPort();
        return 1;
    }
    buffer = uhx1_step(step);
    if(!strncmp("OK", buffer, 2)){
        serial_closeSerialPort();
        return 2;
    }
    serial_closeSerialPort();
    return 0;
}

int uhx1_changeFrequency(int targetFrequency){
    int steps;
    //Open the serial port for communicating with uhx1 device
    serial_openSerialPort(get_progDevice(), B115200, 50000, 50000);
    steps = (targetFrequency-get_startFrequency())/CHANNEL_SPACING;
    if((targetFrequency % CHANNEL_SPACING) || steps < 0 || steps > MAX_CHANNEL){
        serial_closeSerialPort();
        return 1;
    }
    uhx1_setCh(steps+16);
    serial_closeSerialPort();
    return 0;
}

