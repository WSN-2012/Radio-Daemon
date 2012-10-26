#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <errno.h>
//#include <GetCurrentTimeString.h>
//#include <dos.h>
#if(0)
void main( ) 
{
	int GetCurrentTime();
	int a;
	a=GetCurrentTime();
	printf("%d",a);
	delay_50us(100000000);
	a=GetCurrentTime();
	printf("%d",a);
}
int GetCurrentTime()
{
	time_t t = time(0); 
	char tmp[7]; 
	int b;
	strftime(tmp,sizeof(tmp),"%H%M%S%",localtime(&t)); 
	b=(int)tmp;
	return b; 
} 
void delay_50us(uint t)
{
int j; 
for(;t>0;t--) 
for(j=19;j>0;j--) 
;
}
#endif

#if(0)
void main ()
{
time_t rawtime;
struct tm timeinfo;
int i;
time ( &rawtime );
timeinfo = *localtime( &rawtime );
for(i=1;i++;i<100000)
{;}
time ( &rawtime );
timeinfo = *localtime( &rawtime );
printf("1");
//if(asctime(timeinfo2)<asctime(timeinfo1))
//{
//	printf("Yes\n");
//}
//printf ( "\007The current date/time is: %d\n", asctime (timeinfo1) );
//printf ( "\007The current date/time is: %d\n", asctime (timeinfo2) );
//exit(0);
//}
#endif 

#if(0)
int main(void)
{
	struct time t;
	gettime(&t);
	printf("The current time is: %2d:%02d:%02d.%02d\n",
	t.ti_hour, t.ti_min, t.ti_sec, t.ti_hund);
	return 0;
} 
#endif

#if(0)
void main()
{time_t seconds1;
	time_t seconds2;
	int i;
seconds1=time(NULL);
printf("%d\n",seconds1/(3600*24) );
sleep(200);
seconds2=time(NULL);
printf("%d\n",seconds2/(3600*24) );
}
#endif

#if(0)
void main()
{time_t sec = time(NULL); 
struct tm t = *localtime(&sec); 
//第一次 
//printf ( "\007The current date/time is: %d\n", asctime (t) );
int i;
for(i=1;i++;i<1000000)
{;}
sec = time(NULL);
t = *localtime(&sec);
//printf ( "\007The current date/time is: %d\n", asctime (t) );
}
#endif

#if(0)
void main()
{time_t sec = time(NULL); 
	printf("%d\n", sec);
//struct tm *t = localtime(&sec); 
//time_t s=mktime(t);
sleep(3);
sec = time(NULL);
struct tm *t = localtime(&sec);
printf ( "The current date/time is:%s\n", asctime (t) );
time_t s=mktime(t);
printf("%d\n", s);
}
#endif

#if(0)
void main()
{
//	struct tm *s="Tue Oct 16 14:17:13 2012";
	time_t sec=time(NULL);
	struct tm *t=localtime(&sec);
	printf("%d %d %d %d %d %d %d %d %d\n", t->tm_sec, t->tm_min, t->tm_hour, t->tm_mday, t->tm_mon, t->tm_year, t->tm_wday, t->tm_yday, t->tm_isdst );
	char s[10];
	int a = t->tm_sec+10;
	sprintf(s, "0%d", a);
	printf("%s\n,%d\n", s,t->tm_sec+10);
}
#endif
int GetCurrentTimeString(char *);
#if(0)
void main()
{
	
	char CurrentTimeString[30];
	GetCurrentTimeString(CurrentTimeString);
	printf("%s\n", CurrentTimeString);
}
int GetCurrentTimeString(char *date) 
{
	//Get the current system time and save it as tm structure
	time_t seconds= time(NULL);
	struct tm *t = localtime(&seconds);
	//char date[30];
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
	//char input[30];
	//printf("The current time and date is:%s\n", date);
	//scanf("Please input the beginning time(yymmddhhmmss):%s", &input);
	//if (strcmp(date, input)>0)
	//{
	//	printf("Yes\n");
	//}
	//else
	//{
	//	printf("No\n");
	//}
	
	return 0;
} 
#endif

#if(0)
void main()
{
	time_t sec1=time(NULL);
	printf("%d\n", sec1);
	//sleep(3);
int i;
for(i=1;i++;i<1000000)
{;}
	time_t sec2=time(NULL);
	printf("%d\n", sec2);
	if (sec2>sec1)
	{
		printf("Yes\n");
	}
}
#endif

#if(0)
void main()
{
	time_t sec=time(NULL);
	printf("%ld\n", sec/3600);
	long min;
	scanf("%ld",&min);
	if (min*3600>sec)
	{
		printf("Yes\n");
	}
}
#endif

#if(0)
void main()
{
	//while(1)
	//{
		sleep(1);
		system("/mnt/sharepoint/test/radiotunnel/radiotunnel vhf radio0 10.0.0.1/24 /dev/pts/4");
		printf("child\n");
	//}
}
#endif

 

void main(int argc, char *argv[]) 
{ 
   int i; 

   printf("Command line arguments:\n"); 
   for (i=0; i<argc; i++) 
      printf("[%2d] : %s\n", i, argv[i]); 

   printf("About to exec child with arg1 arg2 ...\n"); 
   execv("/mnt/sharepoint/build/subtest", argv); 

   perror("exec error"); 

   exit(1); 
} 