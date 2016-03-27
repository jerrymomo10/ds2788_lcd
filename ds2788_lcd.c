/*
 * ds2788_lcd.c
 * lcd.h 是2002的显示LCD驱动
 * ds2788.h 是ds2788的读写驱动
 * Created: 2016/2/25 19:56:36
 *  Author: Jerry
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"
#include "key.h"
#include "ds2788.h"
uchar mode = 0;
uchar yes = 0;
char volt[50];
char current[50];
char temperature[50];
char percent[50];
char fullc[50]="6899 mah";
char nowc[50]="3423 mah";
void characters_init();
char res[50]="0000 OM";
void update();
void mode_pro();
void switch_mode();
int main()
{
	characters_init();
	PORT_INIT();
	LCD_INIT();
	init_key();
	//设定mah 2580 为3000mah 4b00 为6000
	/*while(!ds_reset());
	ds_write_byte(CMD_ONEWIRE_SKIP_ROM);
	ds_write_byte(CMD_ONEWIRE_WRITE);
	ds_write_byte(CMD_ADDR_ACR);
	ds_write_byte(0X4b);
	ds_write_byte(0X00);*/
	int count = 5; 
	char key;
	while(1)
	{
		key = get_key();
		if(key==1)
		{	
			switch_mode();
			mode = (mode+1)%3;
		}
		if(count==0){count=4;LCD_CLEAR();}
		count--;
		update();
		mode_pro();
		_delay_ms(400);
	}

}
void switch_mode()
{
	if(mode==0)
	{
		DISPLAY(0,0,res);
		LCD_WR_COM(0x02);
		LCD_WR_COM(0x0f);
		
	}
	if(mode==1)
	{
		DISPLAY(0,0,fullc);
		DISPLAY(1,0,nowc);
		LCD_WR_COM(0X02);
		LCD_WR_COM(0X0f);
	}
	if(mode==2)
	{
		LCD_WR_COM(0X0C);	
	}
}
void mode_pro()
{
	if(mode==0)
	{
		DISPLAY(0,0,volt); 
		DISPLAY(0,8,current);
		DISPLAY(1,0,temperature);
		DISPLAY(1,8,percent);	
	}
	if(mode==1)
	{

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
	sprintf(percent,"%.0f %%",acr);
	
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
		percent[i] = '\0';
	}
}

