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

/*Function that looks up a timeslot for a given location at the present time and stores the timeslot info in the timeslot_t referenced by its second parameter*/
int get_timeslot(int location, timeslot_t tslot){
	sqlite3* db;
	int retval;
	char query[QUERY_LEN];
	tslot->is_changed = 0;

	/*Insert location into the sql query string*/
	sprintf(query, SQL_SELECT, location);

	/*Open database*/
	retval = sqlite3_open(DB_PATH, &db);
	if(retval){
		perror("\nCould not connect to db... exiting\n");
		return 1;
	}

	/*Execute sql query*/
	retval = sqlite3_exec(db, query, exec_callback, tslot, NULL);
	
	if(retval!=SQLITE_OK){
		perror("\nSomething went wrong when querying. SQL Error Code: \n");
		printf("%d", retval);
		return 1;
	}

	/*Close database connection*/
	sqlite3_close(db);

	/*Printing results for debugging purposes*/
	printf("Got start time: %s",asctime(localtime(&(tslot->start_time))));
//	printf("\n");
	printf("Got stop time: %s",asctime(localtime(&(tslot->stop_time))));
//	printf("\n");
	printf("Got frequency: %d",tslot->frequency);
	printf("\n");
	printf("Got is_changed: %d",tslot->is_changed);
	printf("\n");

	if(tslot->is_changed)
		return 0;
	else
		return 1;

}

//int main(int argc, char** argv){
//	struct timeslot ts;
//	printf("Function exit code: %d\n", get_timeslot(3, &ts));
//	return 0;
//}
