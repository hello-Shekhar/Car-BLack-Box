/*
 * File:   download_log.c
 * Author: SHEKHAR
 *
 * Created on 27 January, 2024, 10:26 AM
 */

/*
 */
#include <xc.h>
#include "adc.h"
#include "mkp.h"
#include "clcd.h"
#include "main.h"
#include "i2c.h"
#include"eeprom.h"
#include"uart.h"

extern int shift;
extern unsigned short k;
int address = 0;
char array1[10][16];
extern int clear_flag;
extern int event_count;
/*
 * WE ARE READING ALL THE THINGS.
 * JUST PRINTING ALL THE CONTAIN IN TERATERM.
 * IF NO EVENT ARE THERE THEN PRINTING THE NO EVENTS PRESENT. 
 */
void download_log() {
    init_uart();
    if (clear_flag == 0 && event_count > 0) {
        clcd_print(" downloading...", LINE1(0));
        __delay_ms(500);
        puts("     DOWNLOAD LOG     \n \r");
        puts("#  TIME    EV SP\n \r");
        int onetime = 1;
        if (onetime == 1) {
            for (int i = 0; i < event_count; i++) {
                for (int j = 0; j < 14; j++) {
                    if (j == 8 || j == 11) {
                        array1[i][j] = ' ';
                    } else {
                        array1[i][j] = read_external_eeprom(address++);
                    }
                }
                puts(array1[i]);
                puts("\n\r");
            }
            onetime = 0;
        }
        if (address == 0x78) {
            address = 0x00;
        }
        shift = MENU;
        CLEAR_DISP_SCREEN;
        return;
    }
    else {
        clcd_print("NO LOGS PRESENT", LINE1(0));
        __delay_ms(500);
        shift = MENU;
        puts("NO LOGS PRESENT\n \r");
        puts("\n\r");
        CLEAR_DISP_SCREEN;
    }
}