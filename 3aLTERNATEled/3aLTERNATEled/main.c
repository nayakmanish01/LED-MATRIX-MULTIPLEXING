/*
 * main.c
 *
 * Created: 6/30/2022 11:16:19 PM
 *  Author: MANISH
 */ 

#include <xc.h>
#include <util/delay.h>

int main(void)
{
    DDRB=0b00000111;
	PORTB=0b00000001;
	while(1)
    {   
		for(int i=1;i<=3;i++)
		{_delay_ms(1000);
		PORTB=PORTB<<1;	
		}
		PORTB=0b00000001;
		             }
}