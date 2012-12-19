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
 * File:   uhx1_control.h
 * Author: andreastorbiornsson
 *
 * Created on November 12, 2012, 12:47 PM
 */

#ifndef UHX1_CONTROL_H
#define	UHX1_CONTROL_H

#define MAX_CHANNEL 111

int uhx1_setupChannels(int startFrequencyKhz, int step);
int uhx1_changeFrequency(int targetFrequency);



#endif	/* UHX1_CONTROL_H */

