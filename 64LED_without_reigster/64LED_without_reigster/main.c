#include <avr/io.h>

#define F_CPU 16000000UL
#include "util/delay.h"

#define dTime 1

char letterA[8]={ 0b10000001,
	0b11000011,
	0b01100110,
	0b00111100,
	0b00011000,
	0b00011000,
	0b00011000,
0b00011000};

char dotControl[8]={1,2,4,8,16,32,64,128};

int main(void)
{
	DDRD=0xFF;
	DDRB=0xFF;
	while (1)
	{
		for (int i=0;i<8;i++)
		{
			PORTD=0x00;
			PORTB=~letterA[i];
			PORTD=dotControl[i];
			//_delay_ms(dTime);
		}
	}
}