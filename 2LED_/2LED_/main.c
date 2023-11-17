/*
 * GccApplication24.cpp
 *
 * Created: 11-07-2022 18:46:19
 * Author : Tirth Jain
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include "util/delay.h"
#include <time.h>

char dotControl[8]={1,2,4,8,16,32,64,128};
unsigned char d[][8]={{
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
	},{
	0b10000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
	},{
	0b11000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
	},{
	0b11100000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
	},{
	0b11110000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000
	},{
	0b11111000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000
	},{
	0b11111100,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000
	},{
	0b11111110,
	0b00110000,
	0b00110000,
	0b00110000,
	0b00110000,
	0b00110000,
	0b00110000,
	0b00110000
	},{
	0b11111111,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000
	},{
	0b01111111,
	0b00001100,
	0b00001100,
	0b00001100,
	0b00001100,
	0b00001100,
	0b00001100,
	0b00001100
	},{
	0b00111111,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000110
	},{
	0b10011111,
	0b00000011,
	0b00000011,
	0b00000011,
	0b00000011,
	0b00000011,
	0b00000011,
	0b10000011
	},{
	0b11001111,
	0b00000001,
	0b00000001,
	0b00000001,
	0b00000001,
	0b00000001,
	0b00000001,
	0b11000001
	},{
	0b11100111,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b11100000
	},{
	0b11110011,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b11110000
	},{
	0b11111001,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11000000,
	0b11111000
	},{
	0b11111100,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b11111100
	},{
	0b11111110,
	0b00110000,
	0b00110000,
	0b00110000,
	0b00110000,
	0b00110000,
	0b00110000,
	0b11111110
	},{
	0b11111111,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b11111111
	},{
	0b01111111,
	0b00001100,
	0b00001100,
	0b00001100,
	0b00001100,
	0b00001100,
	0b00001100,
	0b01111111
	},{
	0b00111111,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00111111
	},{
	0b00011111,
	0b00000011,
	0b10000011,
	0b10000011,
	0b00000011,
	0b00000011,
	0b00000011,
	0b10011111
	},{
	0b00001111,
	0b10000001,
	0b01000001,
	0b01000001,
	0b10000001,
	0b00000001,
	0b10000001,
	0b01001111
	},{
	0b10000111,
	0b01000000,
	0b00100000,
	0b00100000,
	0b01000000,
	0b10000000,
	0b01000000,
	0b00100111
	},{
	0b11000011,
	0b10100000,
	0b10010000,
	0b10010000,
	0b10100000,
	0b11000000,
	0b10100000,
	0b10010011
	},{
	0b11100001,
	0b11010000,
	0b11001000,
	0b11001000,
	0b11010000,
	0b11100000,
	0b11010000,
	0b11001001
	},{
	0b01110000,
	0b01101000,
	0b01100100,
	0b01100100,
	0b01101000,
	0b01110000,
	0b01101000,
	0b01100100
	},{
	0b00111000,
	0b00110100,
	0b00110010,
	0b00110010,
	0b00110100,
	0b00111000,
	0b00110100,
	0b00110010
	},{
	0b10011100,
	0b00011010,
	0b00011001,
	0b00011001,
	0b00011010,
	0b00011100,
	0b00011010,
	0b00011001
	},{
	0b11001110,
	0b00001101,
	0b00001100,
	0b00001100,
	0b00001101,
	0b00001110,
	0b00001101,
	0b00001100
	},{
	0b11100111,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000111,
	0b00000110,
	0b00000110
	},{
	0b11110011,
	0b10000011,
	0b10000011,
	0b10000011,
	0b10000011,
	0b10000011,
	0b10000011,
	0b10000011
	},{
	0b11111001,
	0b11000001,
	0b11000001,
	0b11000001,
	0b11000001,
	0b11000001,
	0b11000001,
	0b11000001
	},{
	0b11111100,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000,
	0b01100000
	},{
	0b11111110,
	0b00110000,
	0b00110000,
	0b00110000,
	0b00110000,
	0b00110000,
	0b00110000,
	0b00110000
	},{
	0b11111111,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000
	},{
	0b01111111,
	0b00001100,
	0b00001100,
	0b00001100,
	0b00001100,
	0b00001100,
	0b00001100,
	0b00001100
	},{
	0b00111111,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000110,
	0b00000110
	},{
	0b10011111,
	0b10000011,
	0b10000011,
	0b10000011,
	0b10000011,
	0b10000011,
	0b10000011,
	0b10000011
	},{
	0b11001111,
	0b11000001,
	0b11000001,
	0b11000001,
	0b11000001,
	0b11000001,
	0b11000001,
	0b11000001
	},{
	0b01100111,
	0b01100000,
	0b01100000,
	0b11100000,
	0b11100000,
	0b01100000,
	0b01100000,
	0b01100000
	},{
	0b00110011,
	0b00110000,
	0b00110000,
	0b11110000,
	0b11110000,
	0b00110000,
	0b00110000,
	0b00110000
	},{
	0b00011001,
	0b00011000,
	0b00011000,
	0b11111000,
	0b11111000,
	0b00011000,
	0b00011000,
	0b00011000
	},{
	0b00001100,
	0b00001100,
	0b00001100,
	0b11111100,
	0b11111100,
	0b00001100,
	0b00001100,
	0b00001100
	},{
	0b10000110,
	0b10000110,
	0b10000110,
	0b11111110,
	0b11111110,
	0b10000110,
	0b10000110,
	0b10000110
	},{
	0b11000011,
	0b11000011,
	0b11000011,
	0b11111111,
	0b11111111,
	0b11000011,
	0b11000011,
	0b11000011
	},{
	0b01100001,
	0b01100001,
	0b01100001,
	0b01111111,
	0b01111111,
	0b01100001,
	0b01100001,
	0b01100001
	},{
	0b00110000,
	0b00110000,
	0b00110000,
	0b00111111,
	0b00111111,
	0b00110000,
	0b00110000,
	0b00110000
	},{
	0b00011000,
	0b00011000,
	0b00011000,
	0b10011111,
	0b10011111,
	0b00011000,
	0b00011000,
	0b00011000
	},{
	0b00001100,
	0b00001100,
	0b10001100,
	0b01001111,
	0b01001111,
	0b10001100,
	0b00001100,
	0b00001100
	},{
	0b00000110,
	0b10000110,
	0b01000110,
	0b00100111,
	0b00100111,
	0b01000110,
	0b10000110,
	0b00000110
	},{
	0b10000011,
	0b01000011,
	0b00100011,
	0b00010011,
	0b00010011,
	0b00100011,
	0b01000011,
	0b10000011
	},{
	0b01000001,
	0b10100001,
	0b10010001,
	0b00001001,
	0b00001001,
	0b10010001,
	0b10100001,
	0b01000001
	},{
	0b00100000,
	0b01010000,
	0b01001000,
	0b00000100,
	0b00000100,
	0b01001000,
	0b01010000,
	0b00100000
	},{
	0b00010000,
	0b00101000,
	0b10100100,
	0b10000010,
	0b10000010,
	0b10100100,
	0b00101000,
	0b00010000
	},{
	0b00001000,
	0b00010100,
	0b01010010,
	0b01000001,
	0b01000001,
	0b01010010,
	0b00010100,
	0b00001000
	},{
	0b00000100,
	0b00001010,
	0b00101001,
	0b00100000,
	0b00100000,
	0b00101001,
	0b00001010,
	0b00000100
	},{
	0b00000010,
	0b00000101,
	0b00010100,
	0b00010000,
	0b00010000,
	0b00010100,
	0b00000101,
	0b00000010
	},{
	0b00000001,
	0b00000010,
	0b00001010,
	0b00001000,
	0b00001000,
	0b00001010,
	0b00000010,
	0b00000001
	},{
	0b00000000,
	0b00000001,
	0b00000101,
	0b00000100,
	0b00000100,
	0b00000101,
	0b00000001,
	0b00000000
	},{
	0b00000000,
	0b00000000,
	0b00000010,
	0b00000010,
	0b00000010,
	0b00000010,
	0b00000000,
	0b00000000
	},{
	0b00000000,
	0b00000000,
	0b00000001,
	0b00000001,
	0b00000001,
	0b00000001,
	0b00000000,
	0b00000000
	},{
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
}};

#define dTime 0.1


void datx(unsigned char data){
	PORTC&=~(1<<3);//0b00000001 to 0b00001000 to 0b11110111 to 0b00000000&0b11110111
	for(int i=0;i<8;i++){
		PORTC&=~(1<<0);//
		if((data&0x80)!=0) PORTC|=(1<<1);
		else PORTC&=~(1<<1);
		PORTC|=(1<<0);
		data<<=1;
		_delay_us(1);
	}
	PORTC|=(1<<3);
}

void ctrlx(unsigned char data){
	PORTD&=~(1<<3);//0b00000001 to 0b00001000 to 0b11110111 to 0b00000000&0b11110111
	for(int i=0;i<8;i++){
		PORTD&=~(1<<0);//
		if((data&0x80)!=0) PORTD|=(1<<1);
		else PORTD&=~(1<<1);
		PORTD|=(1<<0);
		data<<=1;
		_delay_us(1);
	}
	PORTD|=(1<<3);
}

void daty(unsigned char data){
	PORTA&=~(1<<3);//0b00000001 to 0b00001000 to 0b11110111 to 0b00000000&0b11110111
	for(int i=0;i<8;i++){
		PORTA&=~(1<<0);//
		if((data&0x80)!=0) PORTA|=(1<<1);
		else PORTA&=~(1<<1);
		PORTA|=(1<<0);
		data<<=1;
		_delay_us(1);
	}
	PORTA|=(1<<3);
}

void ctrly(unsigned char data){
	PORTB&=~(1<<3);//0b00000001 to 0b00001000 to 0b11110111 to 0b00000000&0b11110111
	for(int i=0;i<8;i++){
		PORTB&=~(1<<0);//
		if((data&0x80)!=0) PORTB|=(1<<1);
		else PORTB&=~(1<<1);
		PORTB|=(1<<0);
		data<<=1;
		_delay_us(1);
	}
	PORTB|=(1<<3);
}

int main(void)
{
    DDRC=0xFF;
	DDRD=0xFF;//0b01111111
	DDRB=0xFF;
	DDRA=0xFF;
	PORTB=0x00;
	PORTA=0x00;
	PORTD=0x00;//0b10000000
	PORTC=0X00;
    int j = 0;
	int m = 0;
	int n = 0;
	float i = 0;
		while (1)
		{
			i=i+1;
			for (int k = 0;k<62;k++){
				for (int i=0;i<512;i++)
				{
					ctrlx(~dotControl[j]);
					datx(d[k][j]);
					j = j +1;
					_delay_ms(dTime);
					if (j>7){
						j = 0;
					}
					if (k>7)
					{
						m = k-8;
						ctrly(~dotControl[n]);
						daty(d[m][n]);
						n = n + 1;
						//_delay_ms(dTime);
						if (n>7){
							n = 0;
						}
					}
				}
				j = 0;
				n = 0;
			}
		}
	}