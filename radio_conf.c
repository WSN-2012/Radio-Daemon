/*
 *      radio_conf.c
 *      Created on 15 Nov
 *      Author: andreastorbiornsson 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "radio_conf.h"


char* uhx1_progDevice;  //device path for uhx1 programming port
char* uhx1_dataDevice;  //device path for uhx1 data port
int startFrequency;     //frequency for channel 16 in the uhx1
int soundmodem_freq;    //frequency for soundmodem 
char* db_path;          //path to the sqlite3 database file
int mode = -1;          //mode of operation for the radio. 0 for radiotunnel, 1 for soundmodem
int geoLoc = -1;        //location that the station is located at
char* radiotun_path;    //path to radiotunnel binary
char* soundmodem_path;  //path to soundmodem binary
char* ifaceName;        //name of the network interface created by radiotunnel
char* ipInfo;           //Ip adress and netmask of the link, in the format of x.x.x.x/yy
char* logfile_path;     //path to logfile

char* get_progDevice(){
    return uhx1_progDevice;
}

char* get_dataDevice(){
    return uhx1_dataDevice;
}

int get_startFrequency(){
    return startFrequency;
}

int get_soundmodem_freq(){
    return soundmodem_freq;
}

char* get_db_path(){
    return db_path;
}

int get_mode(){
    return mode;
}

int get_location(){
    return geoLoc;
}

char* get_rt_path(){
    return radiotun_path;
}

char* get_soundmodem_path(){
    return soundmodem_path;
}

char* get_ifName(){
    return ifaceName;
}

char* get_ipInfo(){
    return ipInfo;
}

char* get_logfile(){
    return logfile_path;
}

int read_config(){
    int is_valid;
    int list_index;
    char line[512];
    char* attribute;
    char* value;
    char* allowedAttributes[] = {"uhx1_progDevice", "uhx1_dataDevice", "ip", "ifName", "soundmodem_path", "radiotun_path",
                                "geolocation", "mode", "db", "startFrequency", "soundmodemFrequency", "logfile"};
    
    FILE* conffile = fopen(CONF_PATH,"r");
    if(conffile == NULL){
        return -1;
    }
    
    while(fgets(line, 512, conffile)){
        is_valid = 0;
        attribute = strtok(line, " \n");
        
        if(line[0] == '#' || !(attribute)) continue;
        
        for(list_index = 0; list_index < 12; list_index++){
            if(!strcmp(allowedAttributes[list_index], attribute)){
                is_valid = 1;
                break;
            }
        }
        if(!is_valid) continue;
        
        value = strtok(NULL, " \n");
        
        switch(list_index){
            case 0:
                uhx1_progDevice = (char*) malloc((sizeof(char)*strlen(value))+1);
                strcpy(uhx1_progDevice, value);
                break;
            case 1:
                uhx1_dataDevice = (char*) malloc((sizeof(char)*strlen(value))+1);
                strcpy(uhx1_dataDevice, value);
                break;
            case 2:
                ipInfo = (char*) malloc((sizeof(char)*strlen(value))+1);
                strcpy(ipInfo, value);
                break;
            case 3:
                ifaceName = (char*) malloc((sizeof(char)*strlen(value))+1);
                strcpy(ifaceName, value);
                break;
            case 4:
                soundmodem_path = (char*) malloc((sizeof(char)*strlen(value))+1);
                strcpy(soundmodem_path, value);
                break;
            case 5:
                radiotun_path = (char*) malloc((sizeof(char)*strlen(value))+1);
                strcpy(radiotun_path, value);
                break;
            case 6:
                geoLoc = atoi(value);
                if(!geoLoc) return -1;
                break;
            case 7:
                mode = atoi(value);
                if(!mode) return -1;
                break;
            case 8:
                db_path = (char*) malloc((sizeof(char)*strlen(value))+1);
                strcpy(db_path, value);
                break;
            case 9:
                startFrequency = atoi(value);
                if(!startFrequency) return -1;
                break;
            case 10:
                soundmodem_freq = atoi(value);
                if(!soundmodem_freq) return -1;
                break; 
            case 11:
                logfile_path = (char*) malloc((sizeof(char)*strlen(value))+1);
                strcpy(logfile_path, value);
                break; 
        }
        
    }
    
    if(ferror(conffile)){
        fclose(conffile);
        return -1;
    }
    
    fclose(conffile);
    return 0;

}