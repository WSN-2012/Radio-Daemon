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
 *      radio_conf.c
 *      Created on 15 Nov
 *      Author: andreastorbiornsson 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "radio_conf.h"

//introduction on the following vaiables found in rd.conf
int run_place;  
int radio_mode;  
char* radio_if;     
char* ip_gw;    
char* ip_bs;         
char* uhx1_prog_device;         
char* uhx1_data_device;       
int geolocation;    
int start_frequency;         
char* db_path;        
char* radiotun_path;         
char* log_path;     
int soundmodem_frequency;

int get_run_place(){
    return run_place;
}

int get_radio_mode(){
    return radio_mode;
}

char* get_radio_if(){
    return radio_if;
}

char* get_ip_gw(){
    return ip_gw;
}

char* get_ip_bs(){
    return ip_bs;
}

char* get_uhx1_prog_device(){
    return uhx1_prog_device;
}

char* get_uhx1_data_device(){
    return uhx1_data_device;
}

int get_geolocation(){
    return geolocation;
}

int get_start_frequency(){
    return start_frequency;
}

char* get_db_path(){
    return db_path;
}

char* get_radiotun_path(){
    return radiotun_path;
}

char* get_log_path(){
    return log_path;
}

int get_soundmodem_frequency(){
    return soundmodem_frequency;
}

int read_config(){
    int is_valid;
    int list_index;
    char line[512];
    char* attribute;
    char* value;
    char* allowedAttributes[] = {"run_place", "radio_mode", "radio_if", "ip_gw", "ip_bs", "uhx1_prog_device", "uhx1_data_device", 
                                 "geolocation", "start_frequency", "db_path", "radiotun_path", "log_path", "soundmodem_frequency"};
    
    FILE* conffile = fopen(CONF_PATH,"r");
    if(conffile == NULL){
        return -1;
    }
    
    while(fgets(line, 512, conffile)){
        is_valid = 0;
        attribute = strtok(line, " \n");
        
        if(line[0] == '#' || !(attribute)) continue;
        
        for(list_index = 0; list_index < 13; list_index++){
            if(!strcmp(allowedAttributes[list_index], attribute)){
                is_valid = 1;
                break;
            }
        }
        if(!is_valid) continue;
        
        value = strtok(NULL, " \n");
        
        switch(list_index){
            case 0:
                run_place = atoi(value);
                if(!run_place) return -1;
                break;
            case 1:
                radio_mode = atoi(value);
                if(!radio_mode) return -1;
                break;
            case 2:
                radio_if = (char*) malloc((sizeof(char)*strlen(value))+1);
                strcpy(radio_if, value);
                break;
            case 3:
                ip_gw = (char*) malloc((sizeof(char)*strlen(value))+1);
                strcpy(ip_gw, value);
                break;
            case 4:
                ip_bs = (char*) malloc((sizeof(char)*strlen(value))+1);
                strcpy(ip_bs, value);
                break;
            case 5:
                uhx1_prog_device = (char*) malloc((sizeof(char)*strlen(value))+1);
                strcpy(uhx1_prog_device, value);
                break;
            case 6:
                uhx1_data_device = (char*) malloc((sizeof(char)*strlen(value))+1);
                strcpy(uhx1_data_device, value);
                break;
            case 7:
                geolocation = atoi(value);
                if(!geolocation) return -1;
                break;
            case 8:
                start_frequency = atoi(value);
                if(!start_frequency) return -1;
                break;
            case 9:
                db_path = (char*) malloc((sizeof(char)*strlen(value))+1);
                strcpy(db_path, value);
                break;
            case 10:
                radiotun_path = (char*) malloc((sizeof(char)*strlen(value))+1);
                strcpy(radiotun_path, value);
                break; 
            case 11:
                log_path = (char*) malloc((sizeof(char)*strlen(value))+1);
                strcpy(log_path, value);
                break; 
            case 12:
                soundmodem_frequency = atoi(value);
                if(!soundmodem_frequency) return -1;
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