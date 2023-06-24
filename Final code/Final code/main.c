/*
 * Final code.c
 *
 * Created: 2022-05-23 8:20:41 PM
 * Author : Navindu
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "display.c"
#include "solenoid.c"


int main(void)
{
	//DDRA|=(1<<Load_clk); //Load cell clock pin
	//PORTA&=~(1<<Load_clk);//Clock pin low
	
	DDRC |= (11<<6);

	
	
	unsigned char x;
	DDRB = 0X0F;
	int position;
	int i=0;

	//for(int i=0;i<=9;i++)
	
	unsigned char W_array[8];
	//memset(W_array,0,8);
	while(1)
	{
		while(i<10)
		{
			PORTB = 0XF0;
			lcd_init();
			lcd_print("Enter patientID:");
			while(!(PINB!= 0XF0));
			if (PINB!= 0XF0)
			{
				W_array[0] = keypad();
			}
			lcd_init();
			lcddata(W_array[0]);
			_delay_ms(50);
			lcd_init();
			PORTB=0XF0;
			
			lcd_print("oil1 ml(*5):");
			while(!(PINB!= 0XF0));
			if (PINB!= 0XF0)
			{
				W_array[1] = keypad();
			}
			lcd_init();
			lcddata(W_array[1]);
			_delay_ms(50);
			lcd_init();
			PORTB=0XF0;
			
			lcd_print("oil2 ml(*5):");
			while(!(PINB!= 0XF0));
			if (PINB!= 0XF0)
			{
				W_array[2] = keypad();
			}
			lcd_init();
			lcddata(W_array[2]);
			_delay_ms(50);
			lcd_init();
			PORTB=0XF0;

			lcd_print("oil 3 ml(*5):");
			while(!(PINB!= 0XF0));
			if (PINB!= 0XF0)
			{
				W_array[3] = keypad();
			}
			lcd_init();
			lcddata(W_array[3]);
			_delay_ms(50);
			lcd_init();
			PORTB=0XF0;
			
			lcd_print("oil 4 ml(*5):");
			while(!(PINB!= 0XF0));
			if (PINB!= 0XF0)
			{
				W_array[4] = keypad();
			}
			lcd_init();
			lcddata(W_array[4]);
			_delay_ms(50);
			lcd_init();
			PORTB=0XF0;
			
			lcd_print("Drawer1 no.pills:");
			while(!(PINB!= 0XF0));
			if (PINB!= 0XF0)
			{
				W_array[5] = keypad();
			}
			lcd_init();
			lcddata(W_array[5]);
			_delay_ms(50);
			lcd_init();
			PORTB=0XF0;
			
			lcd_print("Drawer2 no.pills:");
			while(!(PINB!= 0XF0));
			if (PINB!= 0XF0)
			{
				W_array[6] = keypad();
			}
			lcd_init();
			lcddata(W_array[6]);
			_delay_ms(50);
			lcd_init();
			PORTB=0XF0;
			
			lcd_print("Powder yes-1no-0:");
			while(!(PINB!= 0XF0));
			if (PINB!= 0XF0)
			{
				W_array[7] = keypad();
			}
			lcd_init();
			lcddata(W_array[7]);
			_delay_ms(50);
			lcd_init();
			PORTB=0XF0;
			
			position=0;
			switch(W_array[0])
			{
				case '0':
				position =0;
				break;
				case '1':
				position =8;
				break;
				case '2':
				position =16;
				break;
				case '3':
				position =24;
				break;
				case '4':
				position =32;
				break;
				case '5':
				position =40;
				break;
				case '6':
				position =48;
				break;
				case '7':
				position =56;
				break;
				case '8':
				position =40;
				break;
				case '9':
				position =40;
				break;
			};
			
			eeprom_write_block(W_array,position,strlen(W_array));
			
			unsigned char condition;
			lcd_print("Do you need");
			_delay_ms(20);
			lcd_init();
			lcd_print("to add");
			_delay_ms(20);
			lcd_init();
			lcd_print("more record?");
			_delay_ms(20);
			lcd_init();
			lcd_print("Yes-1 No-0");
			_delay_ms(20);
			lcd_init();
			while(!(PINB!= 0XF0));
			if (PINB!= 0XF0)
			{
				condition = keypad();
			}
			lcd_init();
			lcddata(condition);
			_delay_ms(50);
			lcd_init();
			PORTB=0XF0;
			if(condition=='0')
			
			break;
			
		}
		
		unsigned char patientID;
		
		lcd_print("To retrieve data");
		lcd_init();
		lcd_print("enter patientID:");
		while(!(PINB!= 0XF0));
		if (PINB!= 0XF0)
		{
			patientID = keypad();
		}
		lcd_init();
		lcddata(patientID);
		_delay_ms(50);
		lcd_init();
		PORTB=0XF0;
		
		position = 0;
		switch(patientID)
		{
			case '0':
			position =0;
			break;
			case '1':
			position =8;
			break;
			case '2':
			position =16;
			break;
			case '3':
			position =24;
			break;
			case '4':
			position =32;
			break;
			case '5':
			position =40;
			break;
			case '6':
			position =48;
			break;
			case '7':
			position =56;
			break;
			case '8':
			position =40;
			break;
			case '9':
			position =40;
			break;
		};
		
		unsigned char R_array[8];
		memset(R_array,0,8);
		int measure=0;
		
		
		eeprom_read_block(R_array,position,strlen(W_array));
		
		lcd_init();
		lcd_print("PatientID:");
		lcddata(R_array[0]);
		_delay_ms(10);
		
		lcd_init();
		lcd_print("Tube 1(*5ml):");
		lcddata(R_array[1]);
		//measure = atoi(R_array[1]);
		measure = (int)(R_array[1]);
		Solenoid('1',measure);
		_delay_ms(10);
		measure=0;
		
		lcd_init();
		lcd_print("Tube 2(*5ml):");
		lcddata(R_array[2]);
		measure = atoi(R_array[2]);
		Solenoid('2',measure);
		_delay_ms(10);
		measure=0;
		
		lcd_init();
		lcd_print("Tube 3(*5ml):");
		lcddata(R_array[3]);
		measure = atoi(R_array[3]);
		Solenoid('3',measure);
		_delay_ms(10);
		measure=0;
		
		lcd_init();
		lcd_print("Tube 4(*5ml):");
		lcddata(R_array[4]);
		measure = atoi(R_array[1]);
		Solenoid('4',measure);
		_delay_ms(10);
		
		
		lcd_init();
		if(!(R_array[5]=='0'))
		{
			lcd_print("Drawer1 - ");
			lcddata(R_array[5]);
			lcd_print(" pills");
			_delay_ms(200);
			lcd_init();
			lcd_print("Please close the");
			_delay_ms(20);
			lcd_init();
			lcd_print("drawer 1 after");
			_delay_ms(20);
			lcd_init();
			lcd_print("you take pills");
			_delay_ms(20);
		}
		_delay_ms(10);
		
		lcd_init();
		if(!(R_array[6]=='0'))
		{
			lcd_print("Drawer2 - ");
			lcddata(R_array[6]);
			lcd_print(" pills");
			_delay_ms(200);
			lcd_init();
			lcd_print("Please close the");
			_delay_ms(20);
			lcd_init();
			lcd_print("drawer 2 after");
			_delay_ms(20);
			lcd_init();
			lcd_print("you take pills");
			_delay_ms(20);
			
		}
		_delay_ms(10);
		
		lcd_init();
		if(!(R_array[7]=='0'))
		{
			lcd_print("Take the powder");
		}
		_delay_ms(10);
		lcd_init();
		
		lcd_print("Thank you!!");
		
		
		return 0;
	}

	return 0;
}
