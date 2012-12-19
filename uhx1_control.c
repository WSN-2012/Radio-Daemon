/*
 * Copyright 2012 KTH
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this
 * file except in compliance with the License. You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS
 * OF ANY KIND, either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
 */

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
    serial_openSerialPort(get_uhx1_prog_device(), B115200, 50000, 50000);
    
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
    serial_openSerialPort(get_uhx1_prog_device(), B115200, 50000, 50000);
    steps = (targetFrequency-get_start_frequency())/CHANNEL_SPACING;
    if((targetFrequency % CHANNEL_SPACING) || steps < 0 || steps > MAX_CHANNEL){
        serial_closeSerialPort();
        return 1;
    }
    uhx1_setCh(steps+16);
    serial_closeSerialPort();
    return 0;
}

