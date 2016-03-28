#include "key.h"

void init_key()
{
	KEY_DDR |= 0x03;
	KEY_PORT |= 0x03;
}
char get_key()
{
	char isPressed;
	KEY_DDR &= ~(0x03);
	isPressed = (KEY_PIN&0x03);
	if(isPressed!=0x03)
	{
		_delay_us(100);			
		if(isPressed==0x02)return 2;
		if(isPressed==0x00)return 3;
		if(isPressed==0x01)return 1;
	}
	return 0;
}
