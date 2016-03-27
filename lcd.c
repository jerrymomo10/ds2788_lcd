#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
void LCD_INIT()
{
	LCD_DATA_OUT;
	LCD_DDRB;
	LCD_DDRC;
	LCD_WR_COM(0X30);
	_delay_ms(50);
	LCD_WR_COM(0X30);
	_delay_ms(50);
	LCD_WR_COM(0X30);
	_delay_ms(50);
	LCD_WR_COM(0X3c);
	_delay_ms(50);
	LCD_WR_COM(0X06);
	_delay_ms(50);
	LCD_WR_COM(0X0C);
	_delay_ms(50);
	LCD_WR_COM(0X01);
}

void LCD_WR_COM(uchar com)
{
	_delay_ms(20);
	LCD_DATA_OUT;
	LCD_DDRB;
	LCD_DDRC;
	LCD_RS_0;
	_delay_us(10);
	LCD_WR_0;
	LCD_EN_1;
	_delay_us(10);
	LCD_DATA=com;
	LCD_EN_0;
	LCD_RS_1;
	LCD_WR_1;
}
void LCD_WR_DATA(uchar data)
{
	_delay_ms(20);
	LCD_DATA_OUT;
	LCD_DDRB;
	LCD_DDRC;
	LCD_RS_1;
	_delay_us(10);
	LCD_WR_0;
	LCD_EN_1;
	_delay_us(10);
	LCD_DATA=data;
	LCD_EN_0;
	LCD_RS_0;
	LCD_WR_1;
}
void PORT_INIT()
{
	LCD_DATA_OUT;
	LCD_DDRB;
	LCD_DDRC;
	LCD_DATA_A;
	LCD_PORTB;
	LCD_PORTC;
	LCD_WR_0;
	LCD_EN_0;
	LCD_WR_0;
}
void DISPLAY(uchar x,uchar y,char *data)
{
	x==0?LCD_WR_COM(0x80+y):LCD_WR_COM(0xc0+y);
	while(*data)
	{
 		LCD_WR_DATA(*data);
		data++;
	}
}
void LCD_CLEAR(void)
{
	LCD_WR_COM(0x01);
}
