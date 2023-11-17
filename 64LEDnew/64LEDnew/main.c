/*
 * main.c
 *
 * Created: 7/8/2022 9:07:22 PM
 *  Author: MANISH
 */ 

#include <avr/io.h>
#include<util/delay.h>

int main(void)
{   DDRD=0xff;
	DDRB=0xff;
	
	
	char ro[]={1,2,4,8,16,32,64,128};
    int row=0b00000001;
	while(1)
	    {   PORTB=row;
		for(int j=0;j<8;j++)
		{PORTD=ro[j];
		for (int i=0;i<8;i++)
		{
		PORTB=~(PORTB<<1);
		_delay_ms(50);
		}
		}
    }