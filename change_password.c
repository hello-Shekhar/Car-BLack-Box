#include <xc.h>
#include "clcd.h"
#include "mkp.h"
#include"main.h"
#include"eeprom.h"
#include"i2c.h"
char new[4];
char renew[4];
int worng = 0;
short delay = 0;
extern int shift;
#define waa 500

//COMMENTS
/* log in screen password we are changing here.
 * asking a new password 
 * then confirm the password
 * if success then write in eeprom.
 * fail then return to menu.
 * 
 * switch 11 & 12 short pressed => prompting the password 
 * switch 11 long pressed => without save comeout.
 * switch 12 long pressed => save comeout.
 
 */
void change_password() {
    static int i = 0, count2 = 4, delay12;
    int key = read_switches(LEVEL_CHANGE);
    static int flag = 1;
    if (flag == 1) {
        clcd_print("Enter password", LINE1(0));
        if (MK_SW11 == key) {
            delay++;
        } else if (delay > 0 && delay < waa) {
            delay = 0;
            clcd_putch('*', LINE2(i));
            new[i++] = '1';
            count2--;
        } else {
            delay = 0;
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
            clcd_putch('*', LINE2(i));
            new[i++] = '0';
            count2--;
        }

        if (count2 == 0) {
            flag = 2;
            i = 0;
            count2 = 4;
            CLEAR_DISP_SCREEN;
        }
    } else if (flag == 2) {
        clcd_print("ReEnter password", LINE1(0));
        if (MK_SW11 == key) {
            delay++;
            if (delay > waa) {
                delay = 0;
            }
        } else if (delay > 0 && delay < waa) {
            delay = 0;
            clcd_putch('*', LINE2(i));
            renew[i++] = '1';
            count2--;
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
            clcd_putch('*', LINE2(i));
            renew[i++] = '0';
            count2--;
        }
        if (count2 == 0) {
            flag = 0;
            i = 0;
            count2 = 4;
            CLEAR_DISP_SCREEN;
        }
    }
    /*compare both password.*/
    if (flag == 0) {
        for (int j = 0; j < 4; j++) {
            if (new[j] != renew[j]) {
                worng = 1;
            }
        }
        if (worng == 0) {
            clcd_print("SUCCESS", LINE1(0));
            for (unsigned int w = 0; w < 4; w++) {
                write_external_eeprom(0x80 + w, new[w]);
            }
            __delay_ms(500);
            shift = MENU;
            flag = 1;
            CLEAR_DISP_SCREEN;

        } else {
            clcd_print("WORNG PASSWORD", LINE1(0));
            __delay_ms(500);
            shift = DASHBOARD;
            flag = 1;
            CLEAR_DISP_SCREEN;

        }
    }
}