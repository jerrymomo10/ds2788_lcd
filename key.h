#ifndef __key_h__
#define __dey_h__

#include "avr/io.h"
#include "avr/interrupt.h"
#include "util/delay.h"

#define KEY_DDR DDRA
#define KEY_PORT PORTA
#define KEY_PIN PINA

/* return 0 nokey
   return 1 first key press
   return 2 second key press
   return 3 first and second key press
*/
void init_key();
char get_key();
#endif
