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

