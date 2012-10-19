#include <time.h> 
#include <stdio.h> 
#include <stdlib.h>

int Get_Current_Time_String(char * date) 
{
	//Get the current system time and save it as tm structure
	time_t seconds= time(NULL);
	struct tm *t = localtime(&seconds);
	int year = t->tm_year+1900;
	//Data type transform: int -> string
	sprintf(date, "%d", year);
	int month = t->tm_mon+1;
	char months[4];
	if (month<10)
	{
		sprintf(months, "0%d", month);
	}
	else
	{
		sprintf(months, "%d", month);
	}
	//String combination: year+month
	strcat(date,months);
	int day = t->tm_mday;
	char days[4];
	if (day<10)
	{
		sprintf(days, "0%d", day);
	}
	else
	{
		sprintf(days, "%d", day);
	}
	strcat(date,days);
	int hour = t->tm_hour;
	char hours[4];
	if (hour<10)
	{
		sprintf(hours, "0%d", hour);
	}
	else
	{
		sprintf(hours, "%d", hour);
	}
	strcat(date,hours);
	int min = t->tm_min;
	char mins[4];
	if (min<10)
	{
		sprintf(mins, "0%d", min);
	}
	else
	{
		sprintf(mins, "%d", min);
	}
	strcat(date,mins);
	int sec = t->tm_sec;
	char secs[4];
	if (sec<10)
	{
		sprintf(secs, "0%d", sec);
	}
	else
	{
		sprintf(secs, "%d", sec);
	}
	strcat(date,secs);
	return 0;
} 

void main( ) 
{
	time_t seconds;
	int flag = 0;
	char t1[30],t2[30];
	char CurrentTimeString[30];
	while(1)
	{
		if(flag == 0)
		{
			#if(1)
			Get_Current_Time_String(CurrentTimeString);
			printf("The current time is(YYYYMMDDhhmmss):%s\n", CurrentTimeString);
			//input start time t1 and end time t2
			printf("Please input the start time of transmission:\n");
			scanf("%s", t1);
			printf("Please input the end time of transmission:\n");
			scanf("%s", t2);
			#endif
			#if(0)
			long t1,t2;
			seconds = time(NULL);
			printf("The number of minutes is:%ld\n", seconds/3600);
			//input start time t1 and end time t2
			printf("Please input the start time of transmission:\n");
			scanf("%ld", &t1);
			printf("Please input the end time of transmission:\n");
			scanf("%ld", &t2);
			#endif
		}
		//before transmission
		while(flag == 0)
		{
			#if(1)
			Get_Current_Time_String(CurrentTimeString);
			if (strcmp(t1,CurrentTimeString)>0)
			#endif
			#if(0)
			seconds = time(NULL);
			if(t1*3600 > seconds)
			#endif
			{
				flag = 0;
			}
			else
			{
				flag = 1;
			}
			printf("%d",flag);
		}
		//during transmission
		while(flag == 1)
		{
			#if(1)
			Get_Current_Time_String(CurrentTimeString);
			if (strcmp(t2,CurrentTimeString)>0)
			#endif
			#if(0)
			seconds = time(NULL);
			if(t2*3600 > seconds)
			#endif
			{
				flag=1;
			}
			else
			{
				flag=0;
			}
			printf("%d",flag);
		}
	}
}