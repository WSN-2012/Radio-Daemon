/* 
 * File:   radio_conf.h
 * Author: andreas
 *
 * Created on November 15, 2012, 2:26 PM
 */

#ifndef RADIO_CONF_H
#define	RADIO_CONF_H

#define CONF_PATH "./rd.conf"

int read_config(void);
char* get_logfile(void);
char* get_ipInfo(void);
char* get_ifName(void);
char* get_soundmodem_path(void);
char* get_rt_path(void);
int get_location(void);
int get_mode(void);
char* get_db_path(void);
int get_startFrequency(void);
char* get_dataDevice(void);
char* get_progDevice(void);

#endif	/* RADIO_CONF_H */

