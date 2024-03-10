#include<xc.h>
#include"clcd.h"
#include"eeprom.h"
#include"i2c.h"
#include"mkp.h"
#include"main.h"

#define waa 500

extern int shift;
extern int once = 0;
int array[10][16];
int scroll = 0;
extern int address = 0x00;
extern int event_count;
extern int view_flag;
extern int e_flag;
extern unsigned char time[9];
extern int clear_flag;
extern int event_count;
/*
 * HERE ALL THE EVENTS WHICH WE ARE STORE IN EEPROM WE ARE JUST PRINTING.
 * AFTER CLEAR LOG JUST NO EVENTS FOUND.
 * 
 * SW11 & SW12 FOR SCROLLING (UP AND DOWN)
 * SW12 -> LONG PRESS COME OUT FROM FUCNTION TO MENU.
 */
void view_log() {
    if (e_flag == 1) {
        once = 1;
        e_flag = 0;
    }
    if (clear_flag == 0 && event_count>0) {
            clcd_print("LOGS :-", LINE1(0));
            static int delay11 = 0, delay12 = 0;
            if (once == 1) {
                for (int i = 0; i < event_count; i++) {
                    for (int j = 0; j < 14; j++) {
                        if (j == 8 || j == 11) {
                            array[i][j] = ' ';
                        } else {
                            array[i][j] = read_external_eeprom(address++);
                        }
                    }
                }
                once = 0;
            }

            int key = read_switches(LEVEL_CHANGE);
            if (MK_SW11 == key) {
                delay11++;
            } else if (delay11 > 0 && delay11 < waa) {
                delay11 = 0;
                if (view_flag-- <= 0) {
                    view_flag = 0;
                }
                if (scroll-- <= 0) {
                    scroll = 0;
                }
            } else {
                delay11 = 0;
            }

            if (MK_SW12 == key) {
                delay12++;
                if (delay12 > waa) {
                    delay12 = 0;
                    shift = MENU;
                    CLEAR_DISP_SCREEN;
                    return;
                }
            } else if (delay12 > 0 && delay12 < waa) {
                delay12 = 0;
                if (scroll < event_count - 1) {
                    view_flag++;
                    if (scroll++ >= 9) {
                        scroll = 9;
                    }
                }
            } else {
                delay12 = 0;
            }
            for (int i = 2; i <= 15; i++) {
                clcd_putch(scroll + 48, LINE2(0));
                clcd_putch('.', LINE2(1));

                clcd_putch(array[view_flag][i - 2], LINE2(i));
                if (address == 0x78) {
                    address = 0x00;
                }
            }
    } 
    else {
        clcd_print("No logs present", LINE1(0));
        __delay_ms(500);
        shift = MENU;
        CLEAR_DISP_SCREEN;
    }
}