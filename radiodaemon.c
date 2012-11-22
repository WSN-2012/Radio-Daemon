/* 
Author: Xiaohang Chen, xiachen@kth.se, KTH Royal Institude of Technology
Created on 22nd October 2012
*/

#include <unistd.h> 
#include <signal.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <sqlite3.h>
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
#include <sys/wait.h>

#include "sdb.h"
#include "devtag-allinone.h"
#include "lock.h"
#include "printAsciiHex.h"
#include "serial.h"
#include "uhx1_commander.h"
#include "util.h"
#include "datacollection.h"
#include "uhx1_control.h"
#include "radio_conf.h"

#ifndef MAIN 
#define NOFILE 3
#endif

int pid_radiotunnel;

//init_daemon is used to initialize a daemon process running in the system background, which can hardly be affected by the foreground user. 
//In the following steps, a normal process will be adapted into a daemon:
void init_daemon() 
{ 

	int pid; 
	int i; 

//fork is used to create a new process(child) which is almost the same with the initial one(father). 
//In father process fork returns the process id of the child, while in child process it returns zero. The return value will be negative if an error ouccurs when forking.
//To get rid of the terminal the father should quit:
	if (pid = fork()) 
	{
		exit(0);
	}
//If forking fails, value one will be returned:
	else if (pid < 0)
	{
		exit(1); 
	}

//Each process belongs to a process group. The group ID(GID) is the process ID(PID) of the group leader.
//A session contains multiple process groups. All these groups share the same terminal.
//setsid is used to make the child a new session leader to get rid of the terminal, session and process group, which are inherited from the father:
	setsid(); 

//Prevent child getting control of terminal
	if (pid = fork()) 
	{
		printf("%d",pid);
		exit(0);
	}
	else if (pid < 0)
	{
		exit(1); 
	} 

//Child inherits the opened file discriptors from the father. To save system resource they should be closed:
	for (i = 0; i < NOFILE; i++) 
	{ 
		close(i); 
	} 

//Change directory where the log is proposed to saved:
	chdir("/tmp");  
//Reset file creation mask which is inherited from the father:
	umask(0);  
	return; 
	}

void exit_daemon(int exit_val) 
{
    FILE* fp;
    time_t current_time = time(NULL);
    
    if ((fp = fopen(get_logfile(), "a")) >= 0) 
    {
        fprintf(fp, "%s\nExit radiodaemon. Kill radiotunnel and close serial ports\n\n", asctime(localtime(&current_time)));
        fclose(fp);
    }
    
    if(pid_radiotunnel)
    {
        kill(pid_radiotunnel, SIGTERM);
        waitpid(pid_radiotunnel, NULL, 0);
    }
    
    serial_closeSerialPort();
    exit(0);
}


int main() 
{ 
//Ignore child ending signal, avoiding zombie process
	signal(SIGCHLD, SIG_IGN); 	
    signal(SIGHUP, exit_daemon);
    signal(SIGINT, exit_daemon);
    signal(SIGTERM, exit_daemon);
	init_daemon(); 
    read_config();
 
	int pid_kill;
	int frequency = 0;
	int freq_indicator;
	char command[20];
	struct timeslot timeslot;
	time_t current_time, start_time, stop_time;
	time_t secs_to_radio_on, secs_to_radio_down;
	FILE *fp;
//Set the starttime and endtime once raido daemon starts running
	get_timeslot(get_location(), &timeslot);
	start_time = timeslot.start_time;
	stop_time = timeslot.stop_time;
	current_time = time(NULL);
	secs_to_radio_on = start_time - current_time;

	if (secs_to_radio_on > 0)
	{
		secs_to_radio_down = stop_time - start_time;
	}
	else
	{
		secs_to_radio_on = 0;
		secs_to_radio_down = stop_time - current_time;
	}
	
	if ((fp = fopen(get_logfile(), "a")) >= 0) 
	{  
		fprintf(fp, "%s\nGet next timeslot and working frequency for gateway at geolocation %d from spectrum database:\nnumber of secs left to establish radiotunnel:%d\nduration of the timeslot:%d\n", asctime(localtime(&current_time)), get_location(), secs_to_radio_on, secs_to_radio_down); 
		fclose(fp); 	
	}

//Set the working frequency once raido daemon starts running
	if (frequency != timeslot.frequency)
	{
		frequency = timeslot.frequency;
		freq_indicator = 1;
	}
	else
	{
		freq_indicator = 0;
	}

	if ((fp = fopen(get_logfile(), "a")) >= 0) 
	{  
		fprintf(fp, "frequency: %dKHz\n\n", frequency); 
		fclose(fp); 	
	}

	while (1) 
	{ 
		sleep(secs_to_radio_on);
		current_time = time(NULL);
//Establish radiotunnel
		pid_radiotunnel = fork();
			
		if (pid_radiotunnel == 0)
		{
				
			if (freq_indicator)
			{
				int retval_changeFrequency = uhx1_changeFrequency(frequency);

				if (!retval_changeFrequency)
				{
					if ((fp = fopen(get_logfile(), "a")) >= 0) 
					{  
						fprintf(fp, "%s\nChange working frequency into %dHz\n\n", asctime(localtime(&current_time)), frequency); 
						fclose(fp); 	
					}
				}
			}

			execl(get_rt_path(), get_rt_path(), "vhf", get_ifName(), get_ipInfo(), get_dataDevice(), NULL);
		}

		if (pid_radiotunnel > 0)
		{
			if ((fp = fopen(get_logfile(), "a")) >= 0) 
			{  
				fprintf(fp, "%s\nEstablish radiotunnel. radiotunnel pid: %d daemon pid: %d\n\n", asctime(localtime(&current_time)), pid_radiotunnel, getpid()); 
				fclose(fp); 				
			}
		}

		if (pid_radiotunnel < 0)
		{
			if ((fp = fopen(get_logfile(), "a")) >= 0) 
			{  
				fprintf(fp, "%s\nFailed establishing radiotunnel\n\n", asctime(localtime(&current_time))); 
				fclose(fp); 				
			}
		}

		sleep(secs_to_radio_down);
		current_time = time(NULL);
//Destroy radiotunnel
		pid_kill = fork();

		if (pid_kill == 0)
		{
			sprintf(command, "%d", pid_radiotunnel);		
			execlp("kill", "kill", command, NULL);
		}

		if (pid_kill > 0)
		{
			if ((fp = fopen(get_logfile(), "a")) >= 0) 
			{  
				fprintf(fp, "%s\nKill radiotunnel. kill pid: %d daemon pid: %d\n\n", asctime(localtime(&current_time)), pid_kill, getpid()); 
				fclose(fp); 				
			}
            
            pid_radiotunnel = 0;
		}

		if (pid_kill < 0)
		{
			if ((fp = fopen(get_logfile(), "a")) >= 0) 
			{  
				fprintf(fp, "%s\nFailed killing radiotunnel\n\n", asctime(localtime(&current_time))); 
				fclose(fp); 				
			}
		}

		sleep(1);
//Set the starttime and endtime once raido daemon starts running
		get_timeslot(get_location(), &timeslot);
		current_time = time(NULL);
		start_time = timeslot.start_time;
		stop_time = timeslot.stop_time;
		secs_to_radio_on = start_time - current_time;
		secs_to_radio_down = stop_time - start_time;
	
		if ((fp = fopen(get_logfile(), "a")) >= 0) 
		{  
			fprintf(fp, "%s\nGet next timeslot and working frequency for gateway at geolocation %d from spectrum database:\nnumber of secs left to establish radiotunnel:%d\nduration of the timeslot:%d\n", asctime(localtime(&current_time)), get_location(), secs_to_radio_on, secs_to_radio_down); 
			fclose(fp); 	
		}

//Set the next working frequency
		if (frequency != timeslot.frequency)
		{
			frequency = timeslot.frequency;
			freq_indicator = 1;
		}
		else
		{
			freq_indicator = 0;
		}

		if ((fp = fopen(get_logfile(), "a")) >= 0) 
		{  
			fprintf(fp, "frequency: %dKHz\n\n", frequency); 
			fclose(fp); 	
		}
		
	} 
}