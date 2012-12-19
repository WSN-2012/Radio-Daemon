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

/* 
Author: Andreas Torbiörnsson, Technology Transfer Alliance 2012
Created on 19th October 2012
*/

#ifndef SDB_H_
#define SDB_H_

/*SQL Query strings for getting a timeslot and frequency. First is for dynamic frequencies
 Second is for static frequencies*/
#define SQL_SELECT "SELECT frequency, strftime('%%s',start_time, 'utc'), strftime('%%s',stop_time, 'utc') FROM KistaSDB_2012 WHERE location = %d AND strftime('%%s', 'now','localtime') <= strftime('%%s', stop_time) ORDER BY start_time ASC LIMIT 1"
#define SQL_STATIC_FREQ_SELECT "SELECT frequency, strftime('%%s',start_time, 'utc'), strftime('%%s',stop_time, 'utc') FROM KistaSDB_2012 WHERE location = %d AND strftime('%%s', 'now','localtime') <= strftime('%%s', stop_time) AND frequency = %d ORDER BY start_time ASC LIMIT 1"

/*Max length of the SQL Query string*/
#define QUERY_LEN 300

/*Format of the timeslot*/
struct timeslot {
	time_t start_time;
	time_t stop_time;
	int frequency;
	int is_changed;
};
typedef struct timeslot* timeslot_t;

/*Function definitions*/
int exec_callback(void* user_param,int columns,char** result,char** names);

int get_timeslot(int location, timeslot_t tslot);


#endif
