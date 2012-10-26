/*
 * uhx1_commander.c
 *
 *  Created on: Jul 6, 2012
 *      Author: alpsayin
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "uhx1_commander.h"
#include "serial.h"
#include "util.h"

char buffer[512];

char* uhx1_readMode()
{
	char retVal;
	serial_transmitSerialData(COMMAND_IDENT, strlen(COMMAND_IDENT));
	if(read(serial_getSerialPortFd(), &retVal, 1) == 1)
	{
		if(retVal == 'S')
			strcpy(buffer, "SERIAL");
		else if(retVal == 'P')
			strcpy(buffer, "PARALLEL");
		else if(retVal == 'M')
			strcpy(buffer, "MODEM");
		else
			sprintf(buffer, "UNKNOWN: %c", retVal);
	}
	else
	{
		strcpy(buffer, "N/A");
	}
	return buffer;
}
char* uhx1_setMode(char* mode)
{
	if(!strcmp(COMMAND_LOCKSERIAL, mode))
	{
		serial_transmitSerialData(COMMAND_LOCKSERIAL, strlen(COMMAND_LOCKSERIAL));
		if(read(serial_getSerialPortFd(), &buffer, 3) == 3)		//one byte is CR
		{
			if(!strncmp(RESPONSE_OK, buffer, 2))
			{
				strcpy(buffer, "OK");
			}
			else
			{
				strcat(buffer, "-UKNOWN");
			}
		}
		else
		{
			strcpy(buffer, "N/A");
		}
	}
	else if(!strcmp(COMMAND_PARALLEL, mode))
	{
		serial_transmitSerialData(COMMAND_PARALLEL, strlen(COMMAND_PARALLEL));
		strcpy(buffer, "No response expected");
	}
	return buffer;
}
char* uhx1_setDefCh(int ch)
{
	int length;
	length = sprintf(buffer, "%s %d%s", COMMAND_DEFCH, ch, COMMAND_NEWLINE);
	serial_transmitSerialData(buffer, length);
	if(read(serial_getSerialPortFd(), &buffer, 3) == 3)		//one byte is CR
	{
		if(!strncmp(RESPONSE_OK, buffer, 2))
		{
			strcpy(buffer, "OK");
		}
		else
		{
			strcat(buffer, "-UKNOWN");
		}
	}
	else
	{
		strcpy(buffer, "N/A");
	}
	return buffer;
}
char* uhx1_setDefPow(int power)
{
	int length;
	length = sprintf(buffer, "%s %d%s", COMMAND_DEFPOW, power, COMMAND_NEWLINE);
	serial_transmitSerialData(buffer, length);
	if(read(serial_getSerialPortFd(), &buffer, 3) == 3) 	//one byte is CR
	{
		if(!strncmp(RESPONSE_OK, buffer, 2))
		{
			strcpy(buffer, "OK");
		}
		else
		{
			strcat(buffer, "-UKNOWN");
		}
	}
	else
	{
		strcpy(buffer, "N/A");
	}
	return buffer;
}
void uhx1_setCh(int ch)
{
	int length;
	length = sprintf(buffer, "%s %d%s", COMMAND_CHAN, ch, COMMAND_NEWLINE);
	serial_transmitSerialData(buffer, length);
}
void uhx1_setPow(int power)
{
	int length;
	length = sprintf(buffer, "%s %d%s", COMMAND_POWER, power, COMMAND_NEWLINE);
	serial_transmitSerialData(buffer, length);
}
int uhx1_readRSSI()
{
	char retVal;
	serial_transmitSerialData(COMMAND_RSSI, strlen(COMMAND_RSSI));
	if(read(serial_getSerialPortFd(), &retVal, 1) == 1)
	{
		return (int)(retVal&0xFF);
	}
	else
	{
		return -1;
	}
}
char* uhx1_dumpMemory()
{
	int numOfBytes, i, mark=0;
	serial_transmitSerialData(COMMAND_DUMP, strlen(COMMAND_DUMP));
	for(i=0; i<4*(16*3 + 1)+1; i++)
	{
		do
		{
			numOfBytes = read(serial_getSerialPortFd(), buffer+i, 1);
		}
		while(numOfBytes<1);
		if(buffer[i]==0x0d)
		{
			buffer[i]='\n';
		}
	}

	return buffer;
}
