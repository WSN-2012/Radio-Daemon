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

char buffer[15];
int startFrequency = 144000;
int maxChannel = 127-16;

int uhx1_setupChannels(int startFrequencyKhz, int step){
    
    uhx1_startChan(startFrequencyKhz);
    if(!strncmp("OK", buffer, 2)){
        return 1;
    }
    uhx1_step(step);
    if(!strncmp("OK", buffer, 2)){
        return 2;
    }
    return 0;
}

int uhx1_changeFrequency(int targetFrequency){
    int steps;
    steps = (targetFrequency-startFrequency)/CHANNEL_SPACING;
    if((targetFrequency % CHANNEL_SPACING) || steps < 0 || steps > maxChannel){
        return 1;
    }
    uhx1_setCh(steps+16);
    return 0;
}

