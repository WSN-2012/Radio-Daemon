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
 * datacollection.c
 *
 *  Created on: Jun 26, 2012
 *      Author: alpsayin
 */

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#include "datacollection.h"
#include "util.h"

static FILE* logfile=NULL;

void openLogFile(char* logfile_name)
{
	logfile = fopen(logfile_name,"a+");
	if(!logfile)
	{
		printf("Unable to open the log file!\n");
	}
}
void registerEvent(char* event, char* param)
{
	struct timeval tv;
	struct timezone tz;
	if(logfile)
	{
		gettimeofday(&tv, &tz);
		if(param!=NULL)
			fprintf(logfile, "%d.%06d\t[%s->%s]\n", tv.tv_sec, tv.tv_usec, event,param);
		else
			fprintf(logfile, "%d.%06d\t[%s]\n", tv.tv_sec, tv.tv_usec, event);

		fflush(logfile);
	}
}
void closeLogFile()
{
	if(logfile)
	{
		fclose(logfile);
		logfile=NULL;
	}
}
