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
uchar pos_mode1 = 0;
uchar pos_mode2 = 0;
char volt[50];
char current[50];
char temperature[50];
char percent[50];
char fullc[50]="63899 Mah";
char nowc[50]="34233 Mah";
void characters_init();
char res[50]="00000 OM";
void update();
void mode_pro();
void switch_mode(char x);
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
		//switch mode and in edit edit.
		if(key==1)
		{	
			//in mode 1 go to next cursor 
			if(yes&&mode==1)
			{		
				//go back to the begining of the line
				if(pos_mode1==4){LCD_WR_COM(0X02);}
				else
				{
					//cursor to the next
					LCD_WR_COM(0X14);
				}
				//the position of mode1 add
				pos_mode1 = (pos_mode1+1)%5;
			}
			else if(yes&&mode==2)
			{
				//go
				if(pos_mode2==10){LCD_WR_COM(0X02);}
				else
				{
					if(pos_mode2<5)LCD_WR_COM(0x14);
					else 
					{
						LCD_WR_COM(0XC0);
						LCD_WR_DATA('0');
					}
				}
				pos_mode2 = (pos_mode2+1)%10;
			}
			else
			{
				switch_mode(1);
				mode = (mode+1)%3;
			}
		}
		if(key==3)
		{
			yes = ~yes;
			switch_mode(3);
		}
		if(key==2)
		{
			if(mode==1&&yes)
			{
				res[pos_mode1]=(res[pos_mode1]+1-'0')%10+'0';
				LCD_WR_COM(0X80+pos_mode1);
				LCD_WR_DATA(res[pos_mode1]);
				LCD_WR_COM(0X10);
			}
			if(mode==2&&yes)
			{
				if(pos_mode2>=5)
				{
					fullc[pos_mode2%5] = (fullc[pos_mode2%5]+1-'0')%10+'0';
					LCD_WR_COM(0xc0+pos_mode2%5);
					LCD_WR_DATA(fullc[pos_mode2%5]);
					LCD_WR_COM(0X10);
				}
				else
				{
					nowc[pos_mode2] = (nowc[pos_mode2]+1-'0')%10+'0';	
					LCD_WR_COM(0x80+pos_mode2);
					LCD_WR_DATA(nowc[pos_mode2]);
					LCD_WR_COM(0X10);
				}
			}
		}
		//if(count==0){count=4;LCD_CLEAR();}
		count--;
		update();
		mode_pro();
		_delay_ms(50);
	}

}
void switch_mode(char x)
{
	if(x==1)
	{
		if(mode==0)
		{	
			LCD_CLEAR();
			DISPLAY(0,0,res);
			
		}
		if(mode==1)
		{
			LCD_CLEAR();
			DISPLAY(0,0,fullc);
			DISPLAY(1,0,nowc);
		 }
    	if(mode==2)
     	{
	    	LCD_CLEAR();
	    	LCD_WR_COM(0X0C);	
    	}
		
	}
	if(x==3)
	{
		//in mode 1 2 and entry the edit.
		if(mode!=0&&yes)
		{
			//cursor to the up left
			LCD_WR_COM(0x02);
			//flicker the cursor and the letter
			LCD_WR_COM(0x0f);
		}
		//in mode 1 2 and exit the edit.
		if(mode!=0&&!yes)
		{
			LCD_WR_COM(0X0C);
		}

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
		//DISPLAY(0,0,res);
	}
	if(mode==2)
	{
		//DISPLAY(0,0,fullc);
		//DISPLAY(0,0,nowc);
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

