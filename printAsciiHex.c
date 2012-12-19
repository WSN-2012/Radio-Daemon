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


#include <stdio.h>
#include "printAsciiHex.h"

void printAsciiHex(char* buffer, int nread)
{
	int i,j;
	for(i=0; i<16; i++)
	{
		printf("%02x", i);
		if(i%2==1)
			printf(" ");
	}
	putchar('\t');
	for(i=0; i<16; i++)
	{
		printf("%1x", i);
	}
	putchar('\n');
	for(i=0; i<16; i++)
	{
		printf("__");
		if(i%2==1)
			printf(" ");
	}
	putchar('\t');
	for(i=0; i<16; i++)
	{
		putchar('_');
	}
	putchar('\n');
	for(i = 1; i <= nread; i++)
	{
		printf("%02x", buffer[i - 1] & (0xFF));
		if(i%2==0 && i!=0)
			printf(" ");
		if(i%COLUMN_SIZE == 0)
		{
			putchar('\t');
			for(j=i-COLUMN_SIZE; j<i; j++)
			{
				if(buffer[j] >= 32 && buffer[j] <= 126)
					putchar(buffer[j]);
				else
					putchar('.');
			}
			putchar('\n');
		}
		else if(i==nread)
		{

			for(j=0; j<(COLUMN_SIZE-(nread%COLUMN_SIZE))*3; j++)
				putchar(' ');
			putchar('\t');
			for(j=(nread/COLUMN_SIZE)*COLUMN_SIZE; j<nread; j++)
			{
				if(buffer[j] >= 32 && buffer[j] <= 126)
					putchar(buffer[j]);
				else
					putchar('.');
			}
			putchar('\n');
		}
	}
	putchar('\n');
}
