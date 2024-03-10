#include <xc.h>
#include "clcd.h"
/*
 * function set page 27 read 23 and 45 see and understand.
 */
void clcd_write(unsigned char byte, unsigned char control_bit)
{
	CLCD_RS = control_bit;
	CLCD_PORT = byte;
//here we read data
	/* Should be atleast 200ns */ //  for instrction cycle 4 clock pluse so each instruction 200ns
	CLCD_EN = HI; //for enable and off because at a time it will run
	CLCD_EN = LO;

	PORT_DIR = INPUT;   //for checking evry time d7 pin is high 1
	CLCD_RW = HI;       //reading the value
	CLCD_RS = INSTRUCTION_COMMAND;  

	do
	{
		CLCD_EN = HI;
		CLCD_EN = LO;
	} while (CLCD_BUSY);    //continuslly chekcing for d7 is low or not

	CLCD_RW = LO;           
	PORT_DIR = OUTPUT;
}

void init_clcd()
{
	/* Set PortD as output port for CLCD data */
	TRISD = 0x00;
	/* Set PortC as output port for CLCD control */
	TRISC = TRISC & 0xF8;
//11111000 last 3 bit as output port for control bit.
	CLCD_RW = LO;
//first we want to write then only we read so set for write.
     /* Startup Time for the CLCD controller */
    __delay_ms(30);
    
    /* The CLCD Startup Sequence */
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND	);
    __delay_us(4100);
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND	);
    __delay_us(100);
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND	);
    __delay_us(1); 
    
    CURSOR_HOME;
    __delay_us(100);
    TWO_LINE_5x8_MATRIX_8_BIT;
    __delay_us(100);
    CLEAR_DISP_SCREEN;
    __delay_us(500);
    DISP_ON_AND_CURSOR_OFF;
    __delay_us(100);
}

void clcd_print(const unsigned char *data, unsigned char addr)
{
	clcd_write(addr, INSTRUCTION_COMMAND);
	while (*data != '\0')
	{
		clcd_write(*data++, DATA_COMMAND);
	}
}

void clcd_putch(const unsigned char data, unsigned char addr)
{
	clcd_write(addr, INSTRUCTION_COMMAND);
	clcd_write(data, DATA_COMMAND);
}