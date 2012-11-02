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

#include "sdb.h"

#ifndef MAIN 
#define NOFILE 3
#define GWGEO 2
#endif

//int timer(time_t start_time, time_t end_time);

void init_daemon() 
{ 

	int pid; 
	int i; 

//Father process quits
	if (pid = fork()) 
	{
		exit(0);
	}
//Fork fails
	else if (pid < 0)
	{
		exit(1); 
	}

//Create new session group. Child precess becomes leader and parts from terminal 
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

//Close opened file descriptor
	for (i = 0; i < NOFILE; i++) 
	{ 
		close(i); 
	} 

//Change directory
	chdir("/tmp");  
//Reset file creation mask
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
	int ref1, ref2, flag1, flag2;
	char command[20];
	struct timeslot timeslot;
	time_t t;
	time_t current_time;
	time_t start_time, end_time;
	FILE *fp;

	gateway_geolocation = GWGEO;

	while (1) 
	{ 
		sleep(1);
		get_timeslot(gateway_geolocation, &timeslot);
		current_time = time(NULL);
		start_time = timeslot.start_time;
		end_time = timeslot.stop_time;

//Timer
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

//Establish radiotunnel
		if (timer_return == 1)
		{
			if (pid = fork() == 0)
			{
				break;
				execl("/mnt/sharepoint/test/radiotunnel/radiotunnel", "/mnt/sharepoint/test/radiotunnel/radiotunnel", "vhf", "radio0", "10.0.0.1/24", "/dev/pts/2", NULL);
			}
			
		}
//Destroy radiotunnel
		else if (timer_return == 0)
		{
			sprintf(command, "%d", pid);		
			execlp("kill", "kill", command, NULL);
		}
		
	} 
	return 0; 
}