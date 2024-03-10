
#ifndef XC_HEADER_MAIN_H
#define	XC_HEADER_MAIN_H

#define DASHBOARD               0
#define PASSWORD                1
#define MENU                    2
//#define MENU_ENTER              3
#define VIEWLOG                 3
#define DOWNLOADLOG             5
#define CLEARLOG                4
#define SETTIME                 6
#define CHANGEPASS              7
void init_config();
void store_event();
//void menu(char key);
void view_log(void);
void download_log(void);
void clear_log(void);
void set_time(void);

void menu_car(void);
void dash_board(void);
void login(void);
 void get_time(void);
 void display_time(void);
void change_password(void);
void e_store(void);
#endif	/* XC_HEADER_TEMPLATE_H */

