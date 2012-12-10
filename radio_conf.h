/* 
 * File:   radio_conf.h
 * Author: andreas
 *
 * Created on November 15, 2012, 2:26 PM
 */

#ifndef RADIO_CONF_H
#define	RADIO_CONF_H

#define CONF_PATH "/root/Radio-Daemon/rd.conf"

int get_run_place();
int get_radio_mode();
char* get_radio_if();
char* get_ip_gw();
char* get_ip_bs();
char* get_uhx1_prog_device();
char* get_uhx1_data_device();
int get_geolocation();
int get_start_frequency();
char* get_db_path();
char* get_radiotun_path();
char* get_log_path();
int get_soundmodem_frequency();

#endif	/* RADIO_CONF_H */

