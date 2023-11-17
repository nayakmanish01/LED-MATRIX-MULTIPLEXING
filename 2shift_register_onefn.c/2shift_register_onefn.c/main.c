/*
 * main.c
 *
 * Created: 7/12/2022 9:28:26 PM
 *  Author: MANISH
 */ 
#define F_CPU 1600000UL
#include <avr/io.h>
#include <util/delay.h>
#define HC595_PORT   PORTC
#define HC595_DDR    DDRC

void HC595Write(int data,int b)
{ int lch,clock,datapin;
	//Send each 8 bits serially

	//Order is MSB first
	if (b==1)
	{  datapin=0;
		clock=1;
		lch=2;
	}
	else
	{  datapin=3;
		clock=4;
		lch=5;
	}
	for(uint8_t i=0;i<8;i++)
	{
		//Output the data on DS line according to the
		//Value of MSB
		if(data & 0b10000000)
		{
			//MSB is 1 so output high

			HC595_PORT|=(1<<datapin);
		}
		else
		{
			//MSB is 0 so output high
			HC595_PORT&=(~(1<<datapin));
		}
          //Pulse the Clock line
		 HC595_PORT|=(1<<clock);//HIGH

		 HC595_PORT&=(~(1<<clock));//LOW 
		data=data<<1;  //Now bring next bit at MSB position

	}

	//Now all 8 bits have been transferred to shift register
	//Move them to output latch at one
	HC595_PORT|=(1<<lch);//HIGH
	//_delay_loop_1(1);

	HC595_PORT&=(~(1<<lch));//LOW
	//_delay_loop_1(1);
}
/*void Wait()
{
   for(uint8_t i=0;i<30;i++)
   {
      _delay_loop_2(0);
   }
}*/

void main()
{  
   uint8_t led_pattern[][8]={{
	   
		   0b11111111,
		   0b10000000,
		   0b10000000,
		   0b11111111,
		   0b11111111,
		   0b10000000,
		   0b10000000,
		   0b11111111
		   },{
		   0b01111111,
		   0b01000000,
		   0b01000000,
		   0b01111111,
		   0b01111111,
		   0b01000000,
		   0b01000000,
		   0b01111111
		   },{
		   0b00111111,
		   0b00100000,
		   0b00100000,
		   0b00111111,
		   0b00111111,
		   0b00100000,
		   0b00100000,
		   0b00111111
		   },{
		   0b00011111,
		   0b00010000,
		   0b00010000,
		   0b00011111,
		   0b00011111,
		   0b00010000,
		   0b00010000,
		   0b00011111
		   },{
		   0b00001111,
		   0b00001000,
		   0b00001000,
		   0b00001111,
		   0b00001111,
		   0b00001000,
		   0b00001000,
		   0b00001111
		   },{
		   0b00000111,
		   0b00000100,
		   0b00000100,
		   0b00000111,
		   0b00000111,
		   0b00000100,
		   0b00000100,
		   0b00000111
		   },{
		   0b00000011,
		   0b00000010,
		   0b00000010,
		   0b00000011,
		   0b00000011,
		   0b00000010,
		   0b00000010,
		   0b00000011
		   },{
		   0b00000001,
		   0b00000001,
		   0b00000001,
		   0b00000001,
		   0b00000001,
		   0b00000001,
		   0b00000001,
		   0b00000001
		   },{
		   0b10000001,
		   0b11000011,
		   0b01100110,
		   0b00111100,
		   0b00011000,
		   0b00011000,
		   0b00011000,
		   0b00011000
		   },{
		   0b01000000,
		   0b01100001,
		   0b00110011,
		   0b00011110,
		   0b00001100,
		   0b00001100,
		   0b00001100,
		   0b00001100
		   },{
		   0b00100000,
		   0b00110000,
		   0b00011001,
		   0b00001111,
		   0b00000110,
		   0b00000110,
		   0b00000110,
		   0b00000110
		   },{
		   0b00010000,
		   0b00011000,
		   0b00001100,
		   0b00000111,
		   0b00000011,
		   0b00000011,
		   0b00000011,
		   0b00000011
		   },{
		   0b00001000,
		   0b00001100,
		   0b00000110,
		   0b00000011,
		   0b00000001,
		   0b00000001,
		   0b00000001,
		   0b00000001
		   },{
		   0b00000100,
		   0b00000110,
		   0b00000011,
		   0b00000001,
		   0b00000000,
		   0b00000000,
		   0b00000000,
		   0b00000000
		   },{
		   0b00000010,
		   0b00000011,
		   0b00000001,
		   0b00000000,
		   0b00000000,
		   0b00000000,
		   0b00000000,
		   0b00000000
		   },{
		   0b00000001,
		   0b00000001,
		   0b00000000,
		   0b00000000,
		   0b00000000,
		   0b00000000,
		   0b00000000,
		   0b00000000
	   }};
   uint8_t dotcontrol[8]={0b00000001,0b00000010,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000};

   //Initialize HC595 system

   HC595_DDR=0b00111111;   //0-row data 1-row clock 2-row latch 3- col data 4- col clock 5-col latch
 int j=0;
   while(1)
   { 
	    for (int k=0;k<17;k++)
    {    j=0;
         for(uint8_t i=0;i<512;i++)
      {   
         HC595Write(dotcontrol[j],1);
		 HC595Write((~led_pattern[k][j]),2);
		 j++;
		   _delay_ms(5);                    //Write the data to HC595
         //Wait();                 //Wait 
         if (j>6)
         {j=0;
         }
       }
	  // _delay_ms(10);
	 }
   }

}
