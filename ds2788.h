#ifndef __ds2788_h__
#define __ds2788_h__

#include "avr/io.h"
#include "avr/interrupt.h"
#include "util/delay.h"
#include "math.h" 

	
#define DQ_SET	PORTC|=(1<<PC0)	      
#define DQ_CLR	PORTC&=~(1<<PC0)   
#define DQ_R	PINC&0x01	 
#define DQ_IN	DDRC&=~(1<<PC0)		
#define DQ_OUT	DDRC|=(1<<PC0)	

#define CMD_ONEWIRE_READ_ROM 0x33
#define CMD_ONEWIRE_SKIP_ROM 0xCC
#define CMD_ONEWIRE_READ 0x69
#define CMD_ONEWIRE_WRITE 0x6c
#define CMD_ADDR_TEMP 0x0A
#define CMD_ADDR_VOLT 0x0C
#define CMD_ADDR_CURRENT 0x0E
#define CMD_ADDR_ACR 0x06

#define uchar unsigned char 
#define uint unsigned int  
float ds_get_temperature(void);

float ds_get_volt(void);
float ds_get_current(void);
float ds_get_acr(void);
uchar ds_reset(void);
uchar ds_read_byte(void);
void ds_write_byte(unsigned char value);

#endif
