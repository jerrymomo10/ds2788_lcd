#include "ds2788.h"
#define  FREQ  8
#include "lcd.h"
unsigned char ds_reset(void)
//ds18b20初始化正常返回1 忙时返回0
{
	unsigned char i;			
	DQ_OUT;
	DQ_CLR;
	_delay_us(600);				
	
	DQ_IN;
	DQ_SET;
	_delay_us(80);				
	i=DQ_R;
	_delay_us(500);				
	if (i) 
		{
			return(0);
		}
	else 
		{
			return(1);
		}
}

unsigned char ds_read_byte(void)
//ds18b20读出一个字节数据
{
	unsigned char i;
	unsigned char value=0;			       				
	for (i=8;i!=0;i--) 
		{
			value>>=1;
			DQ_OUT;
			DQ_CLR;
			_delay_us(4);			
			
			DQ_IN;
            DQ_SET;
			_delay_us(10);			
			if (DQ_R) 
				{
					value|=0x80;
				}
			_delay_us(60);			
		}
	return(value);
}

void ds_write_byte(unsigned char value) 
//ds18b20写入一个字节数据
{  
	unsigned char i;		       
	for (i=8; i!=0;i--)
		{
			DQ_OUT;
			DQ_CLR;
			_delay_us(4);			
			if(value&0x01) 
				{
					DQ_SET;
				}
			_delay_us(80);			
			DQ_SET;				
			value>>=1;
		}
}
// return temperature C
float ds_get_temperature(void)
{
	float temperature;
	while(!ds_reset());
	ds_write_byte(CMD_ONEWIRE_SKIP_ROM);
	ds_write_byte(CMD_ONEWIRE_READ);
	ds_write_byte(CMD_ADDR_TEMP);
	uint16_t msb =ds_read_byte();
	uint16_t lsb =ds_read_byte();
	uint16_t t = (msb<<8)|lsb;
	temperature=(float)t/32*0.125;
	return(temperature);
}
//return volt v
float ds_get_volt(void)
{
	float volt;
	while(!ds_reset());
	ds_write_byte(CMD_ONEWIRE_SKIP_ROM);
	ds_write_byte(CMD_ONEWIRE_READ);
	ds_write_byte(CMD_ADDR_VOLT);
	uint16_t msb =ds_read_byte();
	uint16_t lsb =ds_read_byte();
	uint16_t t = (msb<<8)|lsb;
	volt=(float)(t>>5)*0.00488;
	return(volt);
}
//return current ma
float ds_get_current(void)
{
	float current;
	while(!ds_reset());
	ds_write_byte(CMD_ONEWIRE_SKIP_ROM);
	ds_write_byte(CMD_ONEWIRE_READ);
	ds_write_byte(CMD_ADDR_CURRENT);
	uint16_t msb =ds_read_byte();
	int16_t lsb =ds_read_byte();
	int16_t t = (msb<<8)|lsb;
	current=(float)(t*0.07813);
	return(current);
}
//return current mahr 可以读写
float ds_get_acr(void)
{
	float acr;
	while(!ds_reset());
	ds_write_byte(CMD_ONEWIRE_SKIP_ROM);
	ds_write_byte(CMD_ONEWIRE_READ);
	ds_write_byte(CMD_ADDR_ACR);
	uint8_t msb =ds_read_byte();
	acr=(float)(msb);
	return(acr);
}
