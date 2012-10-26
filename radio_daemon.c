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

int timer(time_t start_time, time_t end_time);

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
	int gateway_geolocation; 
	int timer_return;
	int pid;
	char command[20];
	struct timeslot timeslot;
	time_t t;
	FILE *fp;

	gateway_geolocation = GWGEO;
//Ignore child ending signal, avoiding zombie process
	signal(SIGCHLD, SIG_IGN); 	
	init_daemon(); 

	while (1) 
	{ 
		get_timeslot(gateway_geolocation, &timeslot);
		timer_return = timer(timeslot.start_time, timeslot.stop_time);

//Establish radiotunnel
		if (timer_return == 1)
		{
			if (pid = fork() == 0)
			{
				break;
				if((fp = fopen("/tmp/test1.log", "a")) >= 0) 
				{ 
					t = time(0); 
					fprintf(fp, "Child here at %s\n", asctime(localtime(&t)) ); 
					fclose(fp); 	
				} 

			}
			
		}
//Destroy radiotunnel
		else if (timer_return == 0)
		{
			sprintf(command, "kill %d", pid);
			system(command);
		}
		
	} 
	return 0; 
}