#ifndef __lcd_h__
#define __lcd_h__


#define uint unsigned int
#define uchar unsigned char
#define LCD_DATA PORTD
#define LCD_RS_1 PORTB|=0X02
#define LCD_RS_0 PORTB&=~0X02
#define LCD_WR_1 PORTB|=0X01
#define LCD_WR_0 PORTB&=~0X01
#define LCD_EN_1 PORTC|=0X40
#define LCD_EN_0 PORTC&=~0X40

#define LCD_DATA_OUT DDRD=0XFF
#define LCD_DATA_IN DDRD=0X00
#define LCD_DATA_A PORTD=0XFF
#define LCD_DDRB DDRB|=0X03
#define LCD_DDRC DDRC|=0X40
#define LCD_PORTB PORTB|=0X03
#define LCD_PORTC PORTC|=0X40

void LCD_WR_COM(uchar com);
void LCD_WR_DATA(uchar data);
void PORT_INIT();
void LCD_INIT();
void DISPLAY(uchar x,uchar y,char *data);
void LCD_CLEAR(void);
#endif

