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
 * uhx1_commander.c
 *
 *  Created on: Jul 6, 2012
 *      Author: alpsayin
 *  Updated on: Nov 5, 2012
 *      Updater: andreastorbiornsson
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "uhx1_commander.h"
#include "serial.h"
#include "util.h"

char buffer[512];

char* uhx1_readMode() {
    char retVal;
    serial_transmitSerialData(COMMAND_IDENT, strlen(COMMAND_IDENT));
    if (read(serial_getSerialPortFd(), &retVal, 1) == 1) {
        if (retVal == 'S')
            strcpy(buffer, "SERIAL");
        else if (retVal == 'P')
            strcpy(buffer, "PARALLEL");
        else if (retVal == 'M')
            strcpy(buffer, "MODEM");
        else
            sprintf(buffer, "UNKNOWN: %c", retVal);
    } else {
        strcpy(buffer, "N/A");
    }
    return buffer;
}

char* uhx1_setMode(char* mode) {
    if (!strcmp(COMMAND_LOCKSERIAL, mode)) {
        serial_transmitSerialData(COMMAND_LOCKSERIAL, strlen(COMMAND_LOCKSERIAL));
        if (read(serial_getSerialPortFd(), &buffer, 3) == 3) //one byte is CR
        {
            if (!strncmp(RESPONSE_OK, buffer, 2)) {
                strcpy(buffer, "OK");
            } else {
                strcat(buffer, "-UKNOWN");
            }
        } else {
            strcpy(buffer, "N/A");
        }
    } else if (!strcmp(COMMAND_PARALLEL, mode)) {
        serial_transmitSerialData(COMMAND_PARALLEL, strlen(COMMAND_PARALLEL));
        strcpy(buffer, "No response expected");
    }
    return buffer;
}

char* uhx1_setDefCh(int ch) {
    int length;
    length = sprintf(buffer, "%s %d%s", COMMAND_DEFCH, ch, COMMAND_NEWLINE);
    serial_transmitSerialData(buffer, length);
    if (read(serial_getSerialPortFd(), &buffer, 3) == 3) //one byte is CR
    {
        if (!strncmp(RESPONSE_OK, buffer, 2)) {
            strcpy(buffer, "OK");
        } else {
            strcat(buffer, "-UKNOWN");
        }
    } else {
        strcpy(buffer, "N/A");
    }
    return buffer;
}

char* uhx1_setDefPow(int power) {
    int length;
    length = sprintf(buffer, "%s %d%s", COMMAND_DEFPOW, power, COMMAND_NEWLINE);
    serial_transmitSerialData(buffer, length);
    if (read(serial_getSerialPortFd(), &buffer, 3) == 3) //one byte is CR
    {
        if (!strncmp(RESPONSE_OK, buffer, 2)) {
            strcpy(buffer, "OK");
        } else {
            strcat(buffer, "-UKNOWN");
        }
    } else {
        strcpy(buffer, "N/A");
    }
    return buffer;
}

void uhx1_setCh(int ch) {
    int length;
    length = sprintf(buffer, "%s %d%s", COMMAND_CHAN, ch, COMMAND_NEWLINE);
    serial_transmitSerialData(buffer, length);
}

void uhx1_setPow(int power) {
    int length;
    length = sprintf(buffer, "%s %d%s", COMMAND_POWER, power, COMMAND_NEWLINE);
    serial_transmitSerialData(buffer, length);
}

int uhx1_readRSSI() {
    char retVal;
    serial_transmitSerialData(COMMAND_RSSI, strlen(COMMAND_RSSI));
    if (read(serial_getSerialPortFd(), &retVal, 1) == 1) {
        return (int) (retVal & 0xFF);
    } else {
        return -1;
    }
}

char* uhx1_dumpMemory() {
    int numOfBytes, i;
    serial_transmitSerialData(COMMAND_DUMP, strlen(COMMAND_DUMP));
    for (i = 0; i < 4 * (16 * 3 + 1) + 1; i++) {
        do {
            numOfBytes = read(serial_getSerialPortFd(), buffer + i, 1);
        } while (numOfBytes < 1);
        if (buffer[i] == 0x0d) {
            buffer[i] = '\n';
        }
    }

    return buffer;
}

char* uhx1_loadChannel(int targetFrequencyKhz) {
    int length, nValue;
    nValue = targetFrequencyKhz / CHANNEL_SPACING;
    length = sprintf(buffer, "%s 01 %d%s", COMMAND_LOAD, nValue, COMMAND_NEWLINE);
    serial_transmitSerialData(buffer, length);
    if (read(serial_getSerialPortFd(), &buffer, 3) == 3) //one byte is CR
    {
        if (!strncmp(RESPONSE_OK, buffer, 2)) {
            strcpy(buffer, "OK");
        } else {
            strcat(buffer, "-UKNOWN");
        }
    } else {
        strcpy(buffer, "N/A");
    }
    return buffer;
}

char* uhx1_startChan(int startFrequency){
    int length, nValue;
    nValue = startFrequency / CHANNEL_SPACING;
    if(startFrequency % CHANNEL_SPACING){
        strcpy(buffer, "DIV ERROR");
        return buffer;
    }
    length = sprintf(buffer, "%s %d%s", COMMAND_START, nValue, COMMAND_NEWLINE);
    serial_transmitSerialData(buffer, length);
    if (read(serial_getSerialPortFd(), &buffer, 3) == 3) //one byte is CR
    {
        if (!strncmp(RESPONSE_OK, buffer, 2)) {
            strcpy(buffer, "OK");
        } else {
            strcat(buffer, "-UKNOWN");
        }
    } else {
        strcpy(buffer, "N/A");
    }
    return buffer;
}

char* uhx1_step(int step){
    int length;
    length = sprintf(buffer, "%s %d%s", COMMAND_STEP, step, COMMAND_NEWLINE);
    serial_transmitSerialData(buffer, length);
    if (read(serial_getSerialPortFd(), &buffer, 3) == 3) //one byte is CR
    {
        if (!strncmp(RESPONSE_OK, buffer, 2)) {
            strcpy(buffer, "OK");
        } else {
            strcat(buffer, "-UKNOWN");
        }
    } else {
        strcpy(buffer, "N/A");
    }
    return buffer;
}

