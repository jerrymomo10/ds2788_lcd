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
#include "lcd.h"
#include "ds2788.h"
uchar* volt;
uchar* current;
uchar *temperature;
uchar *accrmulated;
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
	/* tem 0.001-99.999*/
	int tem_sign = tem>=0? 1:0;
	if(tem_sign==0){tem = -tem;}
	uchar t_10 = (uchar)((int)tem/10%10);
	uchar t_0 = (uchar)((int)tem%10);
	uchar t_1 = (uchar)((int)(tem*10)%10);
	uchar t_01 = (uchar)((int)(tem*100)%10);
	uchar t_001 = (uchar)((int)((tem-t_10*10)*1000)%10);
	int i=0;
	if(tem_sign==0){temperature[i]='-';i++;}
	if(t_10!=0)
	{
		temperature[i++] = t_10+'0';
		temperature[i++] = t_0+'0';
		temperature[i++] = '.';
		temperature[i++] = t_1+'0';
		temperature[i++] = t_01+'0';
		temperature[i++] = t_001+'0';
		temperature[i++] = ' ';
		temperature[i++] = 'C';
		temperature[i++] = 0;
	}
	else
	{
		temperature[i++] = t_0+'0';
		temperature[i++] = '.';
		temperature[i++] = t_1+'0';
		temperature[i++] = t_01+'0';
		temperature[i++] = t_001+'0';
		temperature[i++] = ' ';
		temperature[i++] = 'C';
		temperature[i++] = 0;
	}
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
	uchar c_10 = (uchar)((int)cur/10%10);
	uchar c_0 = (uchar)((int)cur%10);
	uchar c_1 = (uchar)((int)(cur*10)%10);
	uchar c_01 = (uchar)((int)(cur*100)%10);
	uchar c_001 = (uchar)((int)((cur-c_10*10)*1000)%10);
	i=0;
	if(cur_sign==0){current[i]='-';i++;}
	if(c_10!=0)
	{
		current[i++] = c_10+'0';
		current[i++] = c_0+'0';
		current[i++] = '.';
		current[i++] = c_1+'0';
		current[i++] = c_01+'0';
		current[i++] = c_001+'0';
		current[i++] = ' ';
		current[i++] = 'M';
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
		current[i++] = 'M';
		current[i++] = 'A';
		current[i++] = 0;
	}
	/*acr dis 0000-99999*/
	uchar a_10000 = (uchar)((int)acr/10000%10);
	uchar a_1000 = (uchar)((int)acr/1000%10);
	uchar a_100 = (uchar)((int)(acr/100)%10);
	uchar a_10 = (uchar)((int)(acr/10)%10);
	uchar a_1 = (uchar)((int)acr%10);
	i=0;
	if(a_10000!=0){accrmulated[i++]=a_10000+'0';};
	accrmulated[i++] = a_1000+'0';
	accrmulated[i++] = a_100+'0';
	accrmulated[i++] = a_10+'0';
	accrmulated[i++] = a_1+'0';
	accrmulated[i++] = ' ';
	accrmulated[i++] = 'M';
	accrmulated[i++] = 'A';
	accrmulated[i++] = 'H';
	accrmulated[i++] = 0;
	
}
void characters_init()
{
	volt = malloc(sizeof(uchar)*10);
	current = malloc(sizeof(uchar)*10);
	temperature = malloc(sizeof(uchar)*10);
	accrmulated = malloc(sizeof(uchar)*10);
}

