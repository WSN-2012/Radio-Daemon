#include <time.h> 
#include <stdio.h> 

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
