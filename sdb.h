/* 
Author: Andreas Torbiörnsson, Technology Transfer Alliance 2012
Created on 19th October 2012
*/

#ifndef SDB_H_
#define SDB_H_

/*Path to the sqlite spectrum database file*/
#define DB_PATH "./sdb.sqlite3"

/*SQL Query string for getting a timeslot and frequency*/
#define SQL_SELECT "SELECT frequency, strftime('%%s',start_time), strftime('%%s',stop_time) FROM KistaSDB_2012 WHERE location = %d AND strftime('%%s', 'now') < strftime('%%s', stop_time) ORDER BY start_time ASC LIMIT 1"

/*Max length of the SQL Query string*/
#define QUERY_LEN 250

/*Format of the timeslot*/
struct timeslot {
	time_t start_time;
	time_t stop_time;
	int frequency;
};
typedef struct timeslot* timeslot_t;

/*Function definitions*/
int exec_callback(void* user_param,int columns,char** result,char** names);

int get_timeslot(int location, timeslot_t tslot);


#endif
