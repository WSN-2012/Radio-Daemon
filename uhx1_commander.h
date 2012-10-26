/*
 * uhx1_commander.h
 *
 *  Created on: Jul 6, 2012
 *      Author: alpsayin
 */

#ifndef UHX1_COMMANDER_H_
#define UHX1_COMMANDER_H_

#define COMMAND_IDENT ":IDENT\x0D"
#define COMMAND_LOCKSERIAL ":LOCKSERIALMODE\x0D"
#define COMMAND_PARALLEL ":PARALLEL\x0D"
#define COMMAND_DEFCH ":DEFCH"
#define COMMAND_DEFPOW ":DEFPOW"
#define COMMAND_CHAN ":CHAN"
#define COMMAND_POWER ":POWER"
#define COMMAND_RSSI ":RSSI\x0D"
#define COMMAND_DUMP ":DUMP\x0D"
#define COMMAND_NEWLINE "\x0D"
#define RESPONSE_OK "OK"

char* uhx1_readMode();
char* uhx1_setMode(char* mode);
char* uhx1_setDefCh(int ch);
char* uhx1_setDefPow(int power);
void uhx1_setCh(int ch);
void uhx1_setPow(int power);
int uhx1_readRSSI();
char* uhx1_dumpMemory();


#endif /* UHX1_COMMANDER_H_ */
