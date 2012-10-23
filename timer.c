/* 
Author: Xiaohang Chen, xiachen@kth.se, KTH Royal Institude of Technology
Created on 22nd October 2012
*/

#include <time.h> 
#include <stdio.h> 

int timer(time_t start_time, time_t end_time)
{
	int ref, flag;
	time_t current_time;
	
	current_time = time(NULL);
	
	if (start_time > current_time)
	{
		ref = 0;
		flag = 0;
		return -1;
	}
	else
	{
		flag = 1;
		
		if (ref + flag == 1)
		{
			return 1;
		}
		else
		{
			return -1;
		}
		
		ref = flag;
		
		if (end_time > current_time)
		{
			flag = 0;
			
			if (ref + flag == 1)
			{
				return 0;
			}
			else
			{
				return -1;
			}
			
			ref = flag;
		}

	}
	
}