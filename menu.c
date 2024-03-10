#include <xc.h>
#include"main.h"
#include"clcd.h"
#include"mkp.h"

#define HMM 500
int key, star_flag = 0;
static int flag = 0;
extern int shift;
char menu[5][16] = {"VIEW LOG      ", "CLEAR LOG     ", "DOWNLOAD LOG  ", "SET TIME      ", "CHANGE PWD    "};
short delay = 0, wait = 0;
int menu_index;
extern int clear_flag;
/*
 * MENU SCRREN 
 * PRINTING ALL THE MENU LIST.
 * 
 * SW11 & SW12 SHORT PRESS -> UP AND DOWN (SCROLLING)
 * SW11 LONG PRESS ->ENTER INSIDE MENU FUNCTION 
 */
void menu_car() {
    
    if (star_flag == 0) {
        clcd_putch('*', LINE1(0));
        clcd_putch(' ', LINE2(0));
        clcd_print(menu[menu_index], LINE1(2));
        clcd_print(menu[menu_index + 1], LINE2(2));
    }
    else if (star_flag == 1) {
        clcd_putch(' ', LINE1(0));
        clcd_putch('*', LINE2(0));
        clcd_print(menu[menu_index], LINE1(2));
        clcd_print(menu[menu_index + 1], LINE2(2));
    }
    key = read_switches(LEVEL_CHANGE);
    if (MK_SW12 == key) {
        wait++;
        if (wait > HMM) {
            wait = 0;
            shift = DASHBOARD;
            CLEAR_DISP_SCREEN;
        }
    }
    else if ((wait > 0)&&(wait < HMM)) {
        if(flag >=0 && flag <=4)
        {
            flag++;    
        }
        wait = 0;
        if (star_flag == 0) {
            star_flag = 1;
        }
        else if (menu_index < 3) {
            menu_index++;
            
        }
    }
    if (MK_SW11 == key) {
        delay++;
        if (delay > HMM) {
            delay = 0;
            if(flag==0){
                shift=3;
            }else if(flag==1){
                shift=4;
            }else if(flag==2){
                shift=5;
            }else if(flag==3){
                shift=6;
            }else if(flag==4){
                shift=7;
            }
            CLEAR_DISP_SCREEN;
        }
    } else if ((delay > 0)&&(delay < HMM)) 
    {
        if(flag > 0)
        {
            flag--;
        }
        delay = 0;
        if (star_flag == 1) {
            star_flag = 0;
        } 
        else if (menu_index > 0) {
            menu_index--;
        }
    }
}