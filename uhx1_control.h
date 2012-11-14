/* 
 * File:   uhx1_control.h
 * Author: andreastorbiornsson
 *
 * Created on November 12, 2012, 12:47 PM
 */

#ifndef UHX1_CONTROL_H
#define	UHX1_CONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif

int uhx1_setupChannels(int startFrequencyKhz, int step);
int uhx1_changeFrequency(int targetFrequency);


#ifdef	__cplusplus
}
#endif

#endif	/* UHX1_CONTROL_H */

