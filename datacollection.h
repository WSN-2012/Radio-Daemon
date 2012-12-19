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
 * datacollection.h
 *
 *  Created on: Jun 26, 2012
 *      Author: alpsayin
 */

#ifndef DATACOLLECTION_H_
#define DATACOLLECTION_H_

#define UHF_LOGFILE_NAME "radiotunnel_uhf-event.log"
#define VHF_LOGFILE_NAME "radiotunnel_vhf-event.log"

void openLogFile(char* logfile_name);
void registerEvent(char* event, char* param);
void closeLogFile();


#endif /* DATACOLLECTION_H_ */
