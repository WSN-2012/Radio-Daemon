/*
 * uhx1_control.c
 *
 *  Updated on: Nov 9, 2012
 *      By: andreastorbiornsson
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "uhx1_commander.h"

char buffer[15];


int uhx1_setupChannels(int targetFrequencyKhz, int step){
    
    buffer = uhx1_startChan(targetFrequencyKhz);
    if(!strncmp("OK", buffer, 2)){
        return 1;
    }
    buffer = uhx1_step(step);
    if(!strncmp("OK", buffer, 2)){
        return 2;
    }
    return 0;
}

