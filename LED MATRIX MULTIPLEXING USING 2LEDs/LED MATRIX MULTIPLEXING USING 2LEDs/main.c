/*
 * main.c
 *
 * Created: 8/2/2022 6:59:46 PM
 *  Author: MANISH
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

/***************************************

Configure Connections

****************************************/
//For First Matrix
#define HC595_PORT   PORTC
#define HC595_DDR    DDRC

#define HC595_DSC_POS PC0      //Data pin (DS) pin location col
#define HC595_SHC_CP_POS PC1      //Shift Clock (SH_CP) pin location col
#define HC595_STC_CP_POS PC2      //Store Clock (ST_CP) pin location col
#define HC595_DSR_POS PC3      //Data pin (DS) pin location row
#define HC595_SHR_CP_POS PC4      //Shift Clock (SH_CP) pin location row
#define HC595_STR_CP_POS PC5      //Store Clock (ST_CP) pin location row

//For 2nd Matrix
#define HC595_PORT1   PORTB
#define HC595_DDR1    DDRB

#define HC595_DSC1_POS PB0      //Data pin (DS) pin location col
#define HC595_SHC1_CP_POS PB1      //Shift Clock (SH_CP) pin location col
#define HC595_STC1_CP_POS PB2      //Store Clock (ST_CP) pin location col
#define HC595_DSR1_POS PB3      //Data pin (DS) pin location row
#define HC595_SHR1_CP_POS PB4      //Shift Clock (SH_CP) pin location row
#define HC595_STR1_CP_POS PB5      //Store Clock (ST_CP) pin location row

/***************************************
Configure Connections ***ENDS***
****************************************/

//Initialize HC595 System  

void HC595Init()  
{
   //Make the Data(DS), Shift clock (SH_CP), Store Clock (ST_CP) lines output for both the registers of 1st LED
   HC595_DDR|=((1<<HC595_SHC_CP_POS)|(1<<HC595_STC_CP_POS)|(1<<HC595_DSC_POS)|(1<<HC595_SHR_CP_POS)|(1<<HC595_STR_CP_POS)|(1<<HC595_DSR_POS));
    //Make the Data(DS), Shift clock (SH_CP), Store Clock (ST_CP) lines output for both the registers of 2nd LED
   HC595_DDR1|=((1<<HC595_SHC1_CP_POS)|(1<<HC595_STC1_CP_POS)|(1<<HC595_DSC1_POS)|(1<<HC595_SHR1_CP_POS)|(1<<HC595_STR1_CP_POS)|(1<<HC595_DSR1_POS));
}
	

//Low level macros to change data (DS)lines for 1st LED
//For column data
#define HC595DataHighC() (HC595_PORT|=(1<<HC595_DSC_POS))
#define HC595DataLowC() (HC595_PORT&=(~(1<<HC595_DSC_POS)))
//For Row data
#define HC595DataHighR() (HC595_PORT|=(1<<HC595_DSR_POS))
#define HC595DataLowR() (HC595_PORT&=(~(1<<HC595_DSR_POS)))


//Low level macros to change data (DS)lines for 2nd LED
//For column data
#define HC595DataHighC1() (HC595_PORT1|=(1<<HC595_DSC1_POS))
#define HC595DataLowC1() (HC595_PORT1&=(~(1<<HC595_DSC1_POS)))
//For Row data
#define HC595DataHighR1() (HC595_PORT1|=(1<<HC595_DSR1_POS))
#define HC595DataLowR1() (HC595_PORT1&=(~(1<<HC595_DSR1_POS)))

//For 1st LED
//Sends a clock pulse on SH_CP line for column
void HC595PulseC()
{
   //Pulse the Shift Clock

   HC595_PORT|=(1<<HC595_SHC_CP_POS);//HIGH

   HC595_PORT&=(~(1<<HC595_SHC_CP_POS));//LOW

}

//Sends a clock pulse on ST_CP line for column
void HC595LatchC()
{
   //Pulse the Store Clock

   HC595_PORT|=(1<<HC595_STC_CP_POS);//HIGH
   _delay_loop_1(1);

   HC595_PORT&=(~(1<<HC595_STC_CP_POS));//LOW
   _delay_loop_1(1);
}

////Sends a clock pulse on SH_CP line for row
void HC595PulseR()
{
	//Pulse the Shift Clock

	HC595_PORT|=(1<<HC595_SHR_CP_POS);//HIGH

	HC595_PORT&=(~(1<<HC595_SHR_CP_POS));//LOW

}

//Sends a clock pulse on ST_CP line for row
void HC595LatchR()
{
	//Pulse the Store Clock

	HC595_PORT|=(1<<HC595_STR_CP_POS);//HIGH
	_delay_loop_1(1);

	HC595_PORT&=(~(1<<HC595_STR_CP_POS));//LOW
	_delay_loop_1(1);
}


//Sends a clock pulse on SH_CP line for column
void HC595PulseC1()
{
	//Pulse the Shift Clock

	HC595_PORT1|=(1<<HC595_SHC1_CP_POS);//HIGH

	HC595_PORT1&=(~(1<<HC595_SHC1_CP_POS));//LOW

}

//For 2nd LED
//Sends a clock pulse on ST_CP line for column
void HC595LatchC1()
{
	//Pulse the Store Clock

	HC595_PORT1|=(1<<HC595_STC1_CP_POS);//HIGH
	_delay_loop_1(1);

	HC595_PORT1&=(~(1<<HC595_STC1_CP_POS));//LOW
	_delay_loop_1(1);
}

////Sends a clock pulse on SH_CP line for row
void HC595PulseR1()
{
	//Pulse the Shift Clock

	HC595_PORT1|=(1<<HC595_SHR1_CP_POS);//HIGH

	HC595_PORT1&=(~(1<<HC595_SHR1_CP_POS));//LOW

}

//Sends a clock pulse on ST_CP line for row
void HC595LatchR1()
{
	//Pulse the Store Clock

	HC595_PORT1|=(1<<HC595_STR1_CP_POS);//HIGH
	_delay_loop_1(1);

	HC595_PORT1&=(~(1<<HC595_STR1_CP_POS));//LOW
	_delay_loop_1(1);
}

/*

Main High level function to write a single byte to
Output shift register 74HC595. 

Arguments:
   single byte to write to the 74HC595 IC

Returns:
   NONE

Description:
   The byte is serially transfered to 74HC595
   and then latched. The byte is then available on
   output line Q0 to Q7 of the HC595 IC.

*/

//For 1ST LED
//For Column
void HC595WriteC(uint8_t dataC)
{
	//Send each 8 bits serially

	//Order is MSB first
	for(uint8_t i=0;i<8;i++)
	{
		//Output the data on DS line according to the
		//Value of MSB
		if(dataC & 0b10000000)
		{
			//MSB is 1 so output high

			HC595DataHighC();
		}
		else
		{
			//MSB is 0 so output high
			HC595DataLowC();
		}

		HC595PulseC();  //Pulse the Clock line
		dataC=dataC<<1;  //Now bring next bit at MSB position

	}

	//Now all 8 bits have been transferred to shift register
	//Move them to output latch at one
	HC595LatchC();
}

//For row
void HC595WriteR(uint8_t dataR)
{
	//Send each 8 bits serially

	//Order is MSB first
	for(uint8_t i=0;i<8;i++)
	{
		//Output the data on DS line according to the
		//Value of MSB
		if(dataR & 0b10000000)
		{
			//MSB is 1 so output high

			HC595DataHighR();
		}
		else
		{
			//MSB is 0 so output high
			HC595DataLowR();
		}

		HC595PulseR();  //Pulse the Clock line
		dataR=dataR<<1;  //Now bring next bit at MSB position

	}

	//Now all 8 bits have been transferred to shift register
	//Move them to output latch at one
	HC595LatchR();
}

//For 2nd LED
//For Column
void HC595WriteC1(uint8_t dataC1)
{
	//Send each 8 bits serially

	//Order is MSB first
	for(uint8_t i=0;i<8;i++)
	{
		//Output the data on DS line according to the
		//Value of MSB
		if(dataC1 & 0b10000000)
		{
			//MSB is 1 so output high

			HC595DataHighC1();
		}
		else
		{
			//MSB is 0 so output high
			HC595DataLowC1();
		}

		HC595PulseC1();  //Pulse the Clock line
		dataC1=dataC1<<1;  //Now bring next bit at MSB position

	}

	//Now all 8 bits have been transferred to shift register
	//Move them to output latch at one
	HC595LatchC1();
}

//For row
void HC595WriteR1(uint8_t dataR1)
{
	//Send each 8 bits serially

	//Order is MSB first
	for(uint8_t i=0;i<8;i++)
	{
		//Output the data on DS line according to the
		//Value of MSB
		if(dataR1 & 0b10000000)
		{
			//MSB is 1 so output high

			HC595DataHighR1();
		}
		else
		{
			//MSB is 0 so output high
			HC595DataLowR1();
		}

		HC595PulseR1();  //Pulse the Clock line
		dataR1=dataR1<<1;  //Now bring next bit at MSB position

	}

	//Now all 8 bits have been transferred to shift register
	//Move them to output latch at one
	HC595LatchR1();
}


// Main function from where program execution starts
void main()
{  
	
	//Defining array for carrying Patterns 
   uint8_t led_pattern[][8]={
   {
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
}
};
   
   uint8_t dotcontrol[8]={0b00000001,0b00000010,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000};

   //Initialize HC595 system

   HC595Init();   
   
   int m=0,j=0,l=0;
   while(1)
   {    
	   for (int k=0;k<62;k++)//loop changing frame
     {   
         for(uint8_t i=0;i<105;i++)// loop for stabilizing same frame for extended period of time
       { 
		   //Write the data to HC595 
		   HC595WriteR(~(dotcontrol[j]));//column multiplexing and writing to column  LED 1
           HC595WriteC(led_pattern[k][j]);//writing to row LED 1  
		   j=j+1;
		   if (j>7)
		   {j=0;}
		   _delay_ms(1.5);
		   if(k>7)
		   {
			   m=k-8;
			   HC595WriteR1(~(dotcontrol[l]));//column multiplexing and writing to column  LED 2
			   HC595WriteC1(led_pattern[m][l]);//writing to row LED 2
			   l=l+1;
			   if (l>7)
			   {l=0;
			   }
			    _delay_ms(1.5);
		   }  
		   
		 
		   
		  
       }
	    _delay_ms(1.5);
		
     }
	
   }

}

