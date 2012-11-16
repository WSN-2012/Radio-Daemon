/* 
 * File:   radio_conf.h
 * Author: andreas
 *
 * Created on November 15, 2012, 2:26 PM
 */

#ifndef RADIO_CONF_H
#define	RADIO_CONF_H

#define CONF_PATH "./rd.conf"

int read_config();
char* get_logfile();
char* get_ipInfo();
char* get_ifName();
char* get_soundmodem_path();
char* get_rt_path();
int get_location();
int get_mode();
char* get_db_path();
int get_startFrequency();
char* get_dataDevice();
char* get_progDevice();

#endif	/* RADIO_CONF_H */

