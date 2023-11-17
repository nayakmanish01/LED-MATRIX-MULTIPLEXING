/*
 * main.c
 *
 * Created: 6/30/2022 7:02:18 PM
 *  Author: MANISH
 */ 

#include <xc.h>
#include<util/delay.h>

int main(void)
{   DDRB=0b00011111;
	PORTB=0X00;
    while(1)
    {
	/*	PORTB |=0b00000001;
		_delay_ms(1000);
        PORTB |=0b00000010;
        _delay_ms(1000);
        PORTB |=0b00000100;
        _delay_ms(1000);
        PORTB |=0b00001000;
        _delay_ms(1000);
        PORTB |=0b00010000;
        _delay_ms(1000);
        PORTB=0b00000000;     
    */
	for (int i;i<=5;i++)
	{PORTB=PORTB<<1;
	}
	}

}