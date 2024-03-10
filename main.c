/*
 * File:   main.c
 * Author: SHEKHAR VERMA 
 * PROJECT -> CAR BLCAK BOX .
 * REG NO. 23013_031.
 */

#include <xc.h>
#include "clcd.h"
#include "mkp.h"
#include"adc.h"
#include"main.h"
#include "i2c.h"
#include "ds1307.h"
#include"eeprom.h"

void init_config(void) {
    init_clcd();
    init_matrix_keypad();
    init_adc();
    init_i2c();
    init_ds1307();
}

int key_mkp, key;
int shift;
/*
 * USING 1 FLAG (SHIFT) VALUE WE ARE MOVING TO FUNCTIO TO FUNCTION.
 * ALL FUNCTION CALLS ARE HERE.
 */
void main(void) {
    /*variable declaration & initialization*/
    init_config();
    while (1) {
        /*here DASH BOARD PROGRAM IS THERE*/
        if (shift == DASHBOARD) {
            dash_board();
        } else if (shift == PASSWORD) {
            login();
        } else if (shift == MENU) {
            menu_car();
        } else if (shift == VIEWLOG) {
            view_log();
        } else if (shift == CLEARLOG) {
            clear_log();
        } else if (shift == DOWNLOADLOG) {
            download_log();
        } else if (shift == SETTIME) {
            set_time();
        } else if (shift == CHANGEPASS) {
            change_password();
        }
    }
}