/*
 * ds2788_lcd.c
 * lcd.h 是2002的显示LCD驱动
 * ds2788.h 是ds2788的读写驱动
 * Created: 2016/2/25 19:56:36
 *  Author: Administrator
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"
#include "ds2788.h"
char volt[50];
char current[50];
char temperature[50];
char accrmulated[50];
void characters_init();
void update();
int main()
{
	characters_init();
	PORT_INIT();
	LCD_INIT();
	//设定mah 2580 为3000mah 4b00 为6000
	/*while(!ds_reset());
	ds_write_byte(CMD_ONEWIRE_SKIP_ROM);
	ds_write_byte(CMD_ONEWIRE_WRITE);
	ds_write_byte(CMD_ADDR_ACR);
	ds_write_byte(0X4b);
	ds_write_byte(0X00);*/
	while(1)
	{
		LCD_CLEAR();
		update();
		DISPLAY(0,0,volt);
		DISPLAY(0,10,current);
		DISPLAY(1,0,temperature);
		DISPLAY(1,10,accrmulated);
		_delay_ms(500);
	}

}
void update()
{
	float tem = ds_get_temperature();
	float vol = ds_get_volt();
	float cur = ds_get_current();
	float acr = ds_get_acr();
	sprintf(temperature,"%.1f C",tem);
	sprintf(volt,"%.3f V",vol);
	sprintf(current,"%.3f mA",cur);
	sprintf(accrmulated,"%.1f",acr);
	
}
void characters_init()
{
	int size = 50;
	int i;
	for(i=0;i<size;i++)
	{
		volt[i] = '\0';
		current[i] = '\0';
		temperature[i] = '\0';
		accrmulated[i] = '\0';
	}
}

