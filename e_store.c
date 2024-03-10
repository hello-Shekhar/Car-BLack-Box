#include <xc.h>
#include"eeprom.h"
#include"i2c.h"
#include "main.h"
#include"clcd.h"

extern int val;
extern unsigned char time[9];
extern char str[8][3];
extern int event;
int e_flag = 0, view_flag = 0, event_count = 0;
extern int once;
/*
 * HERE ALL THE EVENTS MEANS TIME , SPEED , GEAR ALL WE ARE STORING IN EEPROM.
 * AFTER 10 EVENETS IT WILL OVERWRITE AND START FROM 00 ADDRESS.
 */
void e_store() {
    if (event_count < 10) {
        event_count++;
    }
    
    static int address = 0x00;
    
    for (int i = 0; i < 8; i++) {
        write_external_eeprom(address++, time[i]);
    }

    for (int j = 0; j < 2; j++) {
        write_external_eeprom(address++, str[event][j]);
    }

    write_external_eeprom(address++, val / 10 + 48);
    write_external_eeprom(address++, val % 10 + 48);

    if (address == 0x78) {
        address = 0x00;
        e_flag = 1;
    }
}