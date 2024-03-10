/*
 * File:   clear_log.c
 * Author: SHEKHAR
 *
 * Created on 27 January, 2024, 10:08 AM
 */


#include <xc.h>
#include "clcd.h"
#include"main.h"
extern int shift;
 extern int address;
int clear_flag=0;
extern int event_count;
/*
 * HERE WE ARE JUST CLEAR A LOG AND THEN 500MS DELAY THEN COME OUT
 * AFTER THIS IF YOU GO TO VIEW AND DOWNLOAD LOG THEY WILL PRINT "NO LOGS".
 */
void clear_log() {
    clcd_print("ALL LOGS CLEARED", LINE1(0));
    __delay_ms(500);
    address = 0x00;
    clear_flag = 1;
    shift = 2;
    event_count=0;
    CLEAR_DISP_SCREEN;
}