/*
 * File:   ext_eeprom.c
 * Author: Dell
 *
 * Created on 9 January, 2024, 1:24 PM
 */

#include<xc.h>
#include"i2c.h"
#include "eeprom.h"
#include "adc.h"
#include"main.h"
#include"clcd.h"
#include"mkp.h"

/* 
 * AT24C04 (external eeprom) Slave address
 * A0  -  Write Mode
 * A1  -  Read Mode
 */

void write_external_eeprom(unsigned char address1, unsigned char data)
{
	i2c_start();
	i2c_write(SLAVE_WRITE);
	i2c_write(address1);
	i2c_write(data);
	i2c_stop();
	for(unsigned int i = 3000;i--;);
}

unsigned char read_external_eeprom(unsigned char address1)
{
	unsigned char data;

	i2c_start();
	i2c_write(SLAVE_WRITE);
	i2c_write(address1);
	i2c_rep_start();
	i2c_write(SLAVE_READ);
	data = i2c_read();
	i2c_stop();

	return data;
}