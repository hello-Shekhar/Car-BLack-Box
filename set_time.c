/*
 * File:   set_time.c
 * Author: SHEKHAR VERMA
 * Created on 24 January, 2024, 2:45 PM
 */

#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "ds1307.h"
#include "i2c.h"
#include "mkp.h"
#include "eeprom.h"
#define waaa 500

extern int shift;
extern unsigned char time[9];
extern unsigned char clock_reg[3];
int delay11 = 0, delay12 = 0;
int flag_t = 0;
int hr, mn, sec;
int key, once = 1;
int wait = 0;
/*
 * HERE WE ARE SETIING THE TIME FIRST FETCHING THE TIME VALUE.
 * THEN USING SWITCHS CHNAGE FIELDS AND INCREMENT.
 * 
 * SW11-> INCREMENT
 * SW12-> FIELD CHANGE
 * SW12 -> SAVE AND COME OUT FROM FUNCTION. 
 */
void set_time() {
    clcd_print("TIME(HH:MM:SS)", LINE1(0));
    if (once == 1) {
        hr = ((time[0] - 48)*10)+(time[1] - 48);
        mn = ((time[3] - 48)*10)+(time[4] - 48);
        sec = ((time[6] - 48)*10)+(time[7] - 48);
        once = 0;
    }
    key = read_switches(LEVEL_CHANGE);
    if (MK_SW11 == key) {
        delay11++;
        if (delay11 > waaa) {
            delay11 = 0;
            CLEAR_DISP_SCREEN;
            clcd_print("   SET TIME    ", LINE1(0));
            clcd_print("SUCCSSFULL !!!", LINE2(0));
            write_ds1307(HOUR_ADDR, clock_reg[0]);
            write_ds1307(MIN_ADDR, clock_reg[1]);
            write_ds1307(SEC_ADDR, clock_reg[2]);
            //            get_time();
            for (unsigned long w = 500000; w--;);
            for (unsigned long w = 500000; w--;);
            CLEAR_DISP_SCREEN;
            shift = MENU;
            return;
        }
    } else if (delay11 > 0 && delay11 < waaa) {
        delay11 = 0;
        if (flag_t == 0) {
            if (hr < 23)
                hr++;
            else
                hr = 0;
        } else if (flag_t == 1) {
            if (mn < 59)
                mn++;
            else
                mn = 0;
        } else if (flag_t == 2) {
            if (sec < 59)
                sec++;
            else
                sec = 0;
        }
    }

    if (MK_SW12 == key) {
        delay12++;
        if (delay12 > waaa) {
            delay12 = 0;
            shift = MENU;
            CLEAR_DISP_SCREEN;
            return;
        }
    } else if (delay12 > 0 && delay12 < waaa) {
        delay12 = 0;
        if (flag_t < 2)
            flag_t++;
        else
            flag_t = 0;
    }
    if (flag_t == 0) {
        if (wait++ < 5000) {
            clcd_putch(' ', LINE2(4));
            clcd_putch(' ', LINE2(5));
            for (unsigned int w = 1000; w--;);
        } else if (wait >= 500 && wait < 1000) {
            clcd_putch((hr / 10) + 48, LINE2(4));
            clcd_putch((hr % 10) + 48, LINE2(5));
        } else
            wait = 0;

    }
    if (flag_t == 1) {
        if (wait++ < 500) {
            clcd_putch(' ', LINE2(7)); // Blink an character every 0.5 seconds
            clcd_putch(' ', LINE2(8));
            for (unsigned int w = 1000; w--;);
        } else if (wait >= 500 && wait < 1000) {
            clcd_putch((mn / 10) + 48, LINE2(7));
            clcd_putch((mn % 10) + 48, LINE2(8));
        } else
            wait = 0;
    }
    if (flag_t == 2) {
        if (wait++ < 500) {
            clcd_putch(' ', LINE2(10)); 
            clcd_putch(' ', LINE2(11));
            for (unsigned int w = 1000; w--;);
        } else if (wait >= 500 && wait < 1000) {
            clcd_putch((sec / 10) + 48, LINE2(10));
            clcd_putch((sec % 10) + 48, LINE2(11));
        } else
            wait = 0;
    }
    // DISPLAY TIME
    if (key == ALL_RELEASED) {
        clcd_putch((hr / 10) + 48, LINE2(4));
        clcd_putch((hr % 10) + 48, LINE2(5));

        clcd_putch((mn / 10) + 48, LINE2(7));
        clcd_putch((mn % 10) + 48, LINE2(8));

        clcd_putch((sec / 10) + 48, LINE2(10));
        clcd_putch((sec % 10) + 48, LINE2(11));

        clcd_putch(':', LINE2(6));
        clcd_putch(':', LINE2(9));

        clock_reg[0] = ((hr / 10) << 4 | ((hr % 10)));
        clock_reg[1] = ((mn / 10) << 4 | ((mn % 10)));
        clock_reg[2] = ((sec / 10) << 4 | ((sec % 10)));
    }
}
