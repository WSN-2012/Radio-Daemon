/* 
Author: Xiaohang Chen, xiachen@kth.se, KTH Royal Institude of Technology
Created on 22nd October 2012
*/

#include <time.h> 
#include <stdio.h> 

int timer(time_t start_time, time_t end_time)
{
	int ref1, ref2, flag1, flag2;
	time_t current_time;
	
	current_time = time(NULL);
	
	if (current_time < start_time)
	{
		ref1 = 0;
		flag1 = 0;
		return -1;
	}
	else
	{
		flag1 = 1;
		
		if (ref1 + flag1 == 1)
		{
			return 1;
		}
		else
		{
			return -1;
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
				return 0;
			}
		else
			{
				return -1;
			}
			
		ref2 = flag2;
	}
	
}