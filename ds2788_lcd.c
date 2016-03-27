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
	sprintf(temperature,"%.1f",tem);
	int i;
	
	/*volt dis 0.00-99.99*/
	int volt_sign = vol>=0? 1:0;
	if(volt_sign==0){vol = -vol;}
	uchar v_10 = (uchar)((int)vol/10%10);
	uchar v_0 = (uchar)((int)vol%10);
	uchar v_1 = (uchar)((int)(vol*10)%10);
	uchar v_01 = (uchar)((int)(vol*100)%10);
	uchar v_001 = (uchar)((int)((vol-v_10*10))%10);
	i=0;
	if(volt_sign==0){volt[i]='-';i++;}
	if(v_10!=0)
	{
		volt[i++] = v_10+'0';
		volt[i++] = v_0+'0';
		volt[i++] = '.';
		volt[i++] = v_1+'0';
		volt[i++] = v_01+'0';
		volt[i++] = v_001+'0';
		volt[i++] = ' ';
		volt[i++] = 'V';
		volt[i++] = 0;
	}
	else
	{
		volt[i++] = v_0+'0';
		volt[i++] = '.';
		volt[i++] = v_1+'0';
		volt[i++] = v_01+'0';
		volt[i++] = v_001+'0';
		volt[i++] = ' ';
		volt[i++] = 'V';
		volt[i++] = 0;
	}
	/*current dis 0.00-99.99*/
	int cur_sign = cur>=0? 1:0;
	if(cur_sign==0){cur = -cur;}
	uchar c_100 = (uchar)((int)cur/100%10);if(c_100<0||c_100>9){c_100=0;}
	uchar c_10 = (uchar)((int)cur/10%10);if(c_10<0||c_10>9){c_10=0;}
	uchar c_0 = (uchar)((int)cur%10);if(c_0<0||c_0>9){c_0=0;}
	uchar c_1 = (uchar)(((int)(cur*10))%10);if(c_1<0||c_1>9){c_1=0;}
	uchar c_01 = (uchar)(((int)(cur*100))%10);if(c_01<0||c_01>9){c_01=0;}
	uchar c_001 = (uchar)(((int)((cur-c_10*10))*1000)%10);if(c_001<0||c_001>9){c_001=0;}
	i=0;
	if(cur_sign==0){current[i]='-';i++;}
	if(c_100!=0)
	{
		current[i++] = c_100+'0';	
		current[i++] = c_10+'0';
		current[i++] = c_0+'0';
		current[i++] = '.';
		current[i++] = c_1+'0';
		current[i++] = c_01+'0';
		current[i++] = c_001+'0';
		current[i++] = ' ';
		current[i++] = 'm';
		current[i++] = 'A';
		current[i++] = 0;
	}
	else if(c_10!=0)
	{
		current[i++] = c_10+'0';
		current[i++] = c_0+'0';
		current[i++] = '.';
		current[i++] = c_1+'0';
		current[i++] = c_01+'0';
		current[i++] = c_001+'0';
		current[i++] = ' ';
		current[i++] = 'm';
		current[i++] = 'A';
		current[i++] = 0;
	}
	else
	{
		current[i++] = c_0+'0';
		current[i++] = '.';
		current[i++] = c_1+'0';
		current[i++] = c_01+'0';
		current[i++] = c_001+'0';
		current[i++] = ' ';
		current[i++] = 'm';
		current[i++] = 'A';
		current[i++] = 0;
	}

	uchar a_10 = (uchar)((int)(acr/10)%10);
	uchar a_1 = (uchar)((int)acr%10);
	i=0;
	accrmulated[i++] = a_10+'0';
	accrmulated[i++] = a_1+'0';
	accrmulated[i++] = 0x25;
	accrmulated[i++] = 0;
	
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

