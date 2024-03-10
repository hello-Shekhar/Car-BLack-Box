/*
 * File:   dash_board.c
 * Author: shekhar verma
 * Created on 3 January, 2024, 5:49 PM
 */

#include <xc.h>
#include "adc.h"
#include "mkp.h"
#include "clcd.h"
#include "main.h"
#include "ds1307.h"
#include "i2c.h"

unsigned char clock_reg[3];
unsigned char time[9];
extern int shift;
int i, val, key, count1;
int event;
char str[8][3] = {"ON", "GN", "GR", "G1", "G2", "G3", "G4", "CO"};
char speed[2];
extern int clear_flag;
/*
 * HERE ALL THE DASH BOARD THINGS LIKE "EVENTS" "TIME" "SPEED" ALL THREE PRINTED HERE.
 * SW2 -> PRINT COLLSION
 * SW2 -> INCREMENT THE GEAR "EVENT"
 * SW2 -> DECREMENT THE GEAR "EVENT"
 * POTENCIOMETER -> INCREMENT OR DECREMENT THE SPPED.
 */
void dash_board() {
    short var = read_adc(CHANNEL4);
    val = var / 10.24;
    clcd_putch(val % 10 + 48, LINE2(14));
    clcd_putch((val / 10) % 10 + 48, LINE2(13));

    clcd_print("  TIME   EVT SPD", LINE1(0));
    int key = read_switches(STATE_CHANGE);
    
    if (MK_SW2 == key) {
        event++;
        if (event >= 6)
            event = 6;
        e_store();
    } else if (MK_SW3 == key) {
        event--;
        if (event <= 1)
            event = 1;
        e_store();
    } else if (MK_SW1 == key) {
        event = 7;
        e_store();
    }
    clcd_print(str[event], LINE2(9));
    get_time();
    display_time();

    /*LOGIN PROGRAM IS THERE*/
    if (MK_SW11 == key) {
        shift = PASSWORD;
         clear_flag=0;
        i = 0;
        count1 = 4;
        CLEAR_DISP_SCREEN;
    }
}
//DISPLAY THE TIME 
void display_time(void) 
{
    clcd_print(time, LINE2(0));
}
//GATTTING RTC TIME HERE
void get_time(void) 
{
    clock_reg[0] = read_ds1307(HOUR_ADDR);
    clock_reg[1] = read_ds1307(MIN_ADDR);
    clock_reg[2] = read_ds1307(SEC_ADDR);

    if (clock_reg[0] & 0x40) {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    } 
    else {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    }
    time[2] = ':';
    time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
    time[4] = '0' + (clock_reg[1] & 0x0F);
    time[5] = ':';
    time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
    time[7] = '0' + (clock_reg[2] & 0x0F);
    time[8] = '\0';
} 