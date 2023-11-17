#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

/***************************************

Configure Connections

****************************************/

#define HC595_PORT   PORTC
#define HC595_DDR    DDRC

#define HC595_DSC_POS PC0      //Data pin (DS) pin location col

#define HC595_SHC_CP_POS PC1      //Shift Clock (SH_CP) pin location col
#define HC595_STC_CP_POS PC2      //Store Clock (ST_CP) pin location col
#define HC595_DSR_POS PC3      //Data pin (DS) pin location row

#define HC595_SHR_CP_POS PC4      //Shift Clock (SH_CP) pin location row
#define HC595_STR_CP_POS PC5      //Store Clock (ST_CP) pin location row

/***************************************
Configure Connections ***ENDS***
****************************************/

//Initialize HC595 System  

void HC595Init()  
{
   //Make the Data(DS), Shift clock (SH_CP), Store Clock (ST_CP) lines output for both the registers
   HC595_DDR|=((1<<HC595_SHC_CP_POS)|(1<<HC595_STC_CP_POS)|(1<<HC595_DSC_POS)|(1<<HC595_SHR_CP_POS)|(1<<HC595_STR_CP_POS)|(1<<HC595_DSR_POS));
}
	

//Low level macros to change data (DS)lines
//For column data
#define HC595DataHighC() (HC595_PORT|=(1<<HC595_DSC_POS))
#define HC595DataLowC() (HC595_PORT&=(~(1<<HC595_DSC_POS)))
//For Row data
#define HC595DataHighR() (HC595_PORT|=(1<<HC595_DSR_POS))
#define HC595DataLowR() (HC595_PORT&=(~(1<<HC595_DSR_POS)))

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

// Main function from where program execution starts
void main()
{  
	
	//Defining array for carrying Patterns 
   uint8_t led_pattern[][8]={{
	   0b00000000,
	   0b00000000,
	   0b00000000,
	   0b00000000,
	   0b00000000,
	   0b00000000,
	   0b00000000,
	   0b00000000
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
	   0b00000011,
	   0b00000011,
	   0b00000010,
	   0b00000011,
	   0b00000011,
	   0b00000010,
	   0b00000011,
	   0b00000011
	   },{
	   0b00000111,
	   0b00000111,
	   0b00000100,
	   0b00000111,
	   0b00000111,
	   0b00000100,
	   0b00000111,
	   0b00000111
	   },{
	   0b00001111,
	   0b00001111,
	   0b00001000,
	   0b00001110,
	   0b00001110,
	   0b00001000,
	   0b00001111,
	   0b00001111
	   },{
	   0b00111110,
	   0b00111110,
	   0b00100000,
	   0b00111100,
	   0b00111100,
	   0b00100000,
	   0b00111110,
	   0b00111110
	   },{
	   0b01111100,
	   0b01111100,
	   0b01000000,
	   0b01111000,
	   0b01111000,
	   0b01000000,
	   0b01111100,
	   0b01111100
	   },{
	   0b11111001,
	   0b11111001,
	   0b10000000,
	   0b11110000,
	   0b11110000,
	   0b10000000,
	   0b11111000,
	   0b11111000
	   },{
	   0b11110010,
	   0b11110011,
	   0b00000001,
	   0b11100000,
	   0b11100000,
	   0b00000000,
	   0b11110000,
	   0b11110000
	   },{
	   0b11100100,
	   0b11100110,
	   0b00000011,
	   0b11000001,
	   0b11000000,
	   0b00000000,
	   0b11100000,
	   0b11100000
	   },{
	   0b11001000,
	   0b11001100,
	   0b00000110,
	   0b10000011,
	   0b10000001,
	   0b00000001,
	   0b11000001,
	   0b11000001
	   },{
	   0b10010000,
	   0b10011000,
	   0b00001100,
	   0b00000111,
	   0b00000011,
	   0b00000011,
	   0b10000011,
	   0b10000011
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
	   0b01000000,
	   0b01100001,
	   0b00110011,
	   0b00011110,
	   0b00001100,
	   0b00001100,
	   0b00001100,
	   0b00001100
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
	   0b00000010,
	   0b10000110,
	   0b11001100,
	   0b01111000,
	   0b00110000,
	   0b00110000,
	   0b00110000,
	   0b00110000
	   },{
	   0b00000100,
	   0b00001100,
	   0b10011000,
	   0b11110000,
	   0b01100000,
	   0b01100000,
	   0b01100000,
	   0b01100000
	   },{
	   0b00001001,
	   0b00011001,
	   0b00110001,
	   0b11100001,
	   0b11000001,
	   0b11000001,
	   0b11000001,
	   0b11000001
	   },{
	   0b00010011,
	   0b00110011,
	   0b01100010,
	   0b11000011,
	   0b10000011,
	   0b10000010,
	   0b10000011,
	   0b10000011
	   },{
	   0b00100111,
	   0b01100111,
	   0b11000100,
	   0b10000111,
	   0b00000111,
	   0b00000100,
	   0b00000111,
	   0b00000111
	   },{
	   0b01001111,
	   0b11001111,
	   0b10001000,
	   0b00001110,
	   0b00001110,
	   0b00001000,
	   0b00001111,
	   0b00001111
	   },{
	   0b10011111,
	   0b10011111,
	   0b00010000,
	   0b00011100,
	   0b00011100,
	   0b00010000,
	   0b00011111,
	   0b00011111
	   },{
	   0b00111110,
	   0b00111110,
	   0b00100000,
	   0b00111000,
	   0b00111000,
	   0b00100000,
	   0b00111110,
	   0b00111110
	   },{
	   0b01111100,
	   0b01111100,
	   0b01000000,
	   0b01110000,
	   0b01110000,
	   0b01000000,
	   0b01111100,
	   0b01111100
	   },{
	   0b11111000,
	   0b11111000,
	   0b10000000,
	   0b11100000,
	   0b11100000,
	   0b10000000,
	   0b11111000,
	   0b11111000
	   },{
	   0b11110000,
	   0b11110000,
	   0b00000000,
	   0b11000000,
	   0b11000000,
	   0b00000000,
	   0b11110000,
	   0b11110000
	   },{
	   0b11100000,
	   0b11100000,
	   0b00000000,
	   0b10000000,
	   0b10000000,
	   0b00000000,
	   0b11100000,
	   0b11100000
	   },{
	   0b11000000,
	   0b11000000,
	   0b00000000,
	   0b00000000,
	   0b00000000,
	   0b00000000,
	   0b11000000,
	   0b11000000
	   },{
	   0b10000000,
	   0b10000000,
	   0b00000000,
	   0b00000000,
	   0b00000000,
	   0b00000000,
	   0b10000000,
	   0b10000000
   }
};
   
   uint8_t dotcontrol[8]={0b00000001,0b00000010,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000};

   //Initialize HC595 system

   HC595Init();   
   
   int j=0;
   while(1)
   { 
	   for (int k=0;k<29;k++)//loop changing frame
     {   
         for(uint8_t i=0;i<105;i++)// loop for stabilizing same frame for extended period of time
       {   
         HC595WriteC(dotcontrol[j]);
		 HC595WriteR(~(led_pattern[k][j]));
		 j=j+1;                    //Write the data to HC595
         if (j>7)
         {j=0;}
	    _delay_ms(1.5);
        }
	    _delay_ms(1.5);
     }
	
   }

}
