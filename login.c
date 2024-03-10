#include <xc.h>
#include "adc.h"
#include"main.h"
#include"clcd.h"
#include"mkp.h"
#include"eeprom.h"
#include"i2c.h"
#include"ds1307.h"

extern int shift;
 int i, count1;
int s = 120, one = 1, right = 0, key_mkp, flag = 1, j;
char arr1[4];
char arr[4];
int left = 3;
int second = 0;
unsigned long  wait1=0;
/*
 * HERE WE ASK FIRST PASSWORD.
 * IF ANY KEY NOT PRESSSED THEN AFTER 5 SECOND AUTOMETICALLY SHIFT TO DASH BOARD.
 * IF PRESSED WORNG THEN IT WILL ASKED AGAIN. 
 * 3 ATTEMPS ARE ALLOWED FOR WORNG ENTRY.
 * AFTER THAT 120 SECOND DELAY.
 * 
 * IF SUCCESS THEN MOVE TO MENU SCREEN.
 * 
 * SW11 & SW12-> PROMPTING THE PASSWORD. 
 */
void login() {

    if (one) {
        /*write_external_eeprom(0x80, '1');
        write_external_eeprom(0x81, '1');
        write_external_eeprom(0x82, '1');
        write_external_eeprom(0x83, '1');
         */
        arr1[0] = read_external_eeprom(0x80);
        arr1[1] = read_external_eeprom(0x81);
        arr1[2] = read_external_eeprom(0x82);
        arr1[3] = read_external_eeprom(0x83);
        one = 0;
    }
   
        static int left=3;
    //    clcd_print(arr1, LINE2(12));
    if (left != 0) {
        if (wait1++==2000) {
                second++;
                wait1=0;
            } 
        if (second==5) {
        second = 0;
        shift = DASHBOARD;
        CLEAR_DISP_SCREEN;
        return;
    }
        }
    key_mkp = read_switches(STATE_CHANGE);
    if (flag == 1) {
        clcd_print("Enter password", LINE1(0));
        if (MK_SW11 == key_mkp) {
            clcd_putch('*', LINE2(i));
            arr[i++] = '1';
            count1--;
            second = 0;
        } else if (MK_SW12 == key_mkp) {
            clcd_putch('*', LINE2(i));
            arr[i++] = '0';
            count1--;
            second = 0;
        }
    }
    if (count1 == 0) {
        for (j = 0; j < 4; j++) {
            if (arr[j] != arr1[j]) {
                i = 0;
                if (left == 0)
                    count1 = 0;
                else
                    count1 = 4;
                flag = 1;
                clcd_print("PASSWORD WORNG", LINE1(0));
                clcd_print("ATTEMP LEFT->", LINE2(0));
                clcd_putch(--left + 48, LINE2(13));
                __delay_ms(1000);
                CLEAR_DISP_SCREEN;
                second = 0;
                right = 0;
                break;
            }
            right = 1;
            CLEAR_DISP_SCREEN;
        }
    }
    if (right == 1) {
        clcd_print("SUCCESSFULL", LINE1(0));
        clcd_print("WELCOME SHEKHAR", LINE2(0));
        shift = MENU;
        left = 3;
        right = 0;
        CLEAR_DISP_SCREEN;
    } 
    else if (left == 0) {
        unsigned int i = 120;
        while (i) {
            second=0;
            CLEAR_DISP_SCREEN; // Display failure message
            clcd_print("you are blocked", LINE1(0));
            clcd_print("Wait ", LINE2(0));
            clcd_putch(('0' + (i / 100)), LINE2(8));
            clcd_putch(('0' + (i / 10) % 10), LINE2(9));
            clcd_putch(('0' + (i % 10)), LINE2(10));
            clcd_print("Sec...", LINE2(11));
            for (unsigned long j = 500000; j; j--);
            i--;
        }
        left = 3;
        shift = DASHBOARD;
        CLEAR_DISP_SCREEN;
    }
}
