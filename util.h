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
 * util.h
 *
 *  Created on: Apr 30, 2012
 *      Author: alpsayin
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <stdint.h>

#define BUILD __DATE__" "__TIME__
#define GMT_OFFSET (+1)

#if 1
#define CHECKPOINT(x) do{ printf("===== CHECKPOINT #%d ===== %s()\n", x, __FUNCTION__); }while(0)
#else
#define CHECKPOINT(x) ;;
#endif

void usage(void);
void print_time(char* prefix);
uint8_t text_to_ip(uint8_t* in_and_out, uint8_t in_length);
uint8_t readnline(FILE* fptr, uint8_t* out, uint8_t length);
void print_callsign(uint8_t* callsign);
void print_addr_hex(uint8_t* addr);
void print_addr_dec(uint8_t* addr);

#endif /* UTIL_H_ */
