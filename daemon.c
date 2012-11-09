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

#include "sdb.h"
#include "devtag-allinone.h"
#include "lock.h"
#include "printAsciiHex.h"
#include "serial.h"
#include "uhx1_commander.h"
#include "util.h"
#include "datacollection.h"
#include "freq_changer.h"

#ifndef MAIN 
#define NOFILE 3
#define GWGEO 2
#define SERDEV "/dev/pts/4"
#endif

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

int main() 
{ 
//Ignore child ending signal, avoiding zombie process
	signal(SIGCHLD, SIG_IGN); 	
	init_daemon(); 

	int gateway_geolocation; 
	int timer_return;
	int pid;
	int cpid;
	int ref1, ref2, flag1, flag2;
	int frequency;
	char command[20];
	char serial_device[30] = SERDEV;
	struct timeslot timeslot;
	time_t current_time;
	time_t start_time, end_time;
	FILE *fp;

	gateway_geolocation = GWGEO;

	while (1) 
	{ 
		sleep(1);
		int retval = get_timeslot(gateway_geolocation, &timeslot);
		current_time = time(NULL);
		start_time = timeslot.start_time;
		end_time = timeslot.stop_time;
		frequency = timeslot.frequency;

//timer
		if (current_time < start_time)
		{
			ref1 = 0;
			flag1 = 0;
			timer_return = -1;
		}
		else 
		{
			flag1 = 1;
		
			if (ref1 + flag1 == 1)
			{
				timer_return = 1;
			}
			else
			{
				timer_return = -1;
			}
		
			ref1 = flag1;
		}
		
		if (current_time < end_time)
		{
			ref2 = 1;
			flag2 = 1;
		}		
		else 
    	{
    		flag2 = 0;

			if (ref2 + flag2 == 1)
			{
				timer_return = 0;
			}
			else
			{
				timer_return = -1;
			}
			
			ref2 = flag2;
		}

		if((fp = fopen("/tmp/timerlog.log", "a")) >= 0) 
			{  
				fprintf(fp, "current time: %s(number of secs: %d)\n starttime(number of secs: %d)\n endtime(number of secs: %d)\n frequency: %d\n get_timeslot_return: %d\n timer_return: %d\n\n", asctime(localtime(&current_time)), current_time, start_time, end_time, frequency, retval, timer_return); 
				fclose(fp); 	
			} 

//Establish radiotunnel
		if (timer_return == 1)
		{
			pid = fork();
			
			if (pid == 0)
			{
				//int retval_f = freq_changer(frequency, serial_device)；
				int retval_e = execl("/mnt/sharepoint/test/radiotunnel/radiotunnel", "/mnt/sharepoint/test/radiotunnel/radiotunnel", "vhf", "radio0", "10.0.0.1/24", SERDEV, NULL);
			}

			if (pid > 0)
			{
				if ((fp = fopen("/tmp/forklog.log", "a")) >= 0) 
				{  
					fprintf(fp, "Establishes radiotunnel at %s\npid of radiotunnel is %d, pid of daemon is %d\n\n", asctime(localtime(&current_time)), pid, getpid()); 
					fclose(fp); 				
				}
			}

			if (pid < 0)
			{
				if ((fp = fopen("/tmp/forklog.log", "a")) >= 0) 
				{  
					fprintf(fp, "forking failed at %s\n", asctime(localtime(&current_time))); 
					fclose(fp); 				
				}
			}

		}

//Destroy radiotunnel
		else if (timer_return == 0)
		{
			cpid = fork();

			if (cpid == 0)
			{
				sprintf(command, "%d", pid);		
				execlp("kill", "kill", command, NULL);
			}

			if (cpid > 0)
			{
				if ((fp = fopen("/tmp/test1.log", "a")) >= 0) 
				{  
					fprintf(fp, "Destroy radiotunnel at %s\npid of kill is %d, pid of daemon is %d\n\n", asctime(localtime(&current_time)), cpid, getpid()); 
					fclose(fp); 				
				}
			}

		}
		
	} 
	return 0; 
}