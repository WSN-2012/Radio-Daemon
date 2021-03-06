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

#include <stdio.h>
#include <stdlib.h>

#include <sqlite3.h>
#include "sdb.h"

/*Callback function for sqlite3_exec. Stores query result in a timeslot_t*/
int exec_callback(void* user_param,int columns,char** result,char** names){
	timeslot_t t = (timeslot_t) user_param;
	t->start_time = (time_t)atoi(result[1]);
	t->stop_time = (time_t)atoi(result[2]);
	t->frequency = atoi(result[0]);
	t->is_changed = 1;

	return 0;
}

/*Function that looks up a timeslot for a given location at the present time and stores the timeslot info in the timeslot_t referenced by its second parameter
 *Parameters:
 *      *First parameter is an integer representening the location
 *      *Second parameter is a pointer to the timeslot that information is to be stored in
 *Returns:
 *      0 if a new times have been stored in timeslot_t
 *      1 if timeslot hasn't changed or can't be trusted
 */
int get_timeslot(int location, timeslot_t tslot){
	sqlite3* db;
	int retval;
	char query[QUERY_LEN];
	tslot->is_changed = 0;

	/*Insert location into the sql query string*/
	if(get_radio_mode()!=2){
                sprintf(query, SQL_SELECT, location);
        }
        else{
            sprintf(query, SQL_STATIC_FREQ_SELECT, location, get_soundmodem_frequency());
        }

	/*Open database*/
	retval = sqlite3_open(get_db_path(), &db);
	if(retval){
		perror("\nCould not connect to db... exiting\n");
		return 1;
	}

	/*Execute sql query*/
	retval = sqlite3_exec(db, query, exec_callback, tslot, NULL);
	
	if(retval!=SQLITE_OK){
		perror("\nSomething went wrong when querying. SQL Error Code: \n");
		printf("%d", retval);
		return 2;
	}

	/*Close database connection*/
	sqlite3_close(db);

	/*Printing results for debugging purposes*/
//	printf("Got start time: %s",asctime(localtime(&(tslot->start_time))));
//	printf("\n");
//	printf("Got stop time: %s",asctime(localtime(&(tslot->stop_time))));
//	printf("\n");
//	printf("Got frequency: %d",tslot->frequency);
//	printf("\n");
//	printf("Got is_changed: %d",tslot->is_changed);
//	printf("\n");

	if(tslot->is_changed)
		return 0;
	else
		return 3;

}
