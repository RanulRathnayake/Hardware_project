
uint8_t hx711H=0; //Load Scale High Bits
uint16_t hx711L=0;//Load Scale Low Bits

#define Load_data 0
#define Load_clk 1
#define LCD PORTD
#define EN 6
#define RS 7

unsigned char keypad();
void lcdcmd(unsigned char cmd);
void lcd_init();
void lcddata(unsigned char data);
void lcd_print(char *str);




float loadCellRead();
float hx=0;



unsigned char keypad(){
	PORTB = 0b11111110;
	
	if ((PINB & (1<<PINB4)) ==0)
	{
		_delay_ms(15);
		return '7';
	}
	else if((PINB & (1<<PINB5)) ==0)
	{
		_delay_ms(15);
		return '8';
	}
	else if((PINB & (1<<PINB6)) ==0)
	{
		_delay_ms(15);
		return '9';
	}
	else if((PINB & (1<<PINB7)) ==0)
	{
		_delay_ms(15);
		return '/';
	}
	PORTB = 0b11111101;
	
	if ((PINB & (1<<PINB4)) ==0)
	{
		_delay_ms(15);
		return '4';
	}
	else if((PINB & (1<<PINB5)) ==0)
	{
		_delay_ms(15);
		return '5';
	}
	else if((PINB & (1<<PINB6)) ==0)
	{
		_delay_ms(15);
		return '6';
	}
	else if((PINB & (1<<PINB7)) ==0)
	{
		_delay_ms(15);
		return 'X';
	}
	
	PORTB = 0b11111011;
	
	if ((PINB & (1<<PINB4)) ==0)
	{
		_delay_ms(15);
		return '1';
	}
	else if((PINB & (1<<PINB5)) ==0)
	{
		_delay_ms(15);
		return '2';
	}
	else if((PINB & (1<<PINB6)) ==0)
	{
		_delay_ms(15);
		return '3';
	}
	else if((PINB & (1<<PINB7)) ==0)
	{
		_delay_ms(15);
		return '-';
	}
	PORTB = 0b11110111;
	
	if ((PINB & (1<<PINB4)) ==0)//C
	{
		_delay_ms(15);
		lcd_init();
	}
	else if((PINB & (1<<PINB5)) ==0)
	{
		_delay_ms(15);
		return '0';
	}
	else if((PINB & (1<<PINB6)) ==0)
	{
		_delay_ms(15);
		return '=';
	}
	else if((PINB & (1<<PINB7)) ==0)///+
	{
		_delay_ms(15);
		return '+';
	}
	
}

void lcdcmd(unsigned char cmd){
	PORTC &= ~(1<<RS);
	LCD = cmd & 0XF0;
	PORTC |= (1<<EN);
	_delay_ms(1);
	PORTC &= ~(1<<EN);
	
	LCD = cmd<<4;
	PORTC |= (1<<EN);
	_delay_ms(1);
	PORTC &= ~(1<<EN);
}

void lcd_init(){
	DDRD = 0XFF;
	PORTC &= ~(1<<EN);
	lcdcmd(0X33);
	lcdcmd(0X32);
	lcdcmd(0X28);
	lcdcmd(0X0E);
	lcdcmd(0X01);
	_delay_ms(2);
}

void lcddata(unsigned char data){
	PORTC |= (1<<RS);
	LCD = data & 0XF0;//CHECK
	PORTC |= (1<<EN);
	_delay_ms(1);
	PORTC &= ~(1<<EN);
	
	LCD = data<<4;
	PORTC |= (1<<EN);
	_delay_ms(1);
	PORTC &= ~(1<<EN);
}

void lcd_print(char *str)
{
	unsigned char i =0;
	while (str[i]!=0){
		lcddata(str[i]);
		i++;
	}
}

/*
float loadCellRead(){
	hx711H=0;hx711L=0;  //clear variables
	for(uint8_t i=0;i<8;i++){  // Load cell data high 8 bits
		PORTA|=(1<<Load_clk); //Clock pin high
		_delay_us(10);
		if ((PINA&(1<<Load_data))>>Load_data)  //read data pin
		{hx711H|=(1<<(7-i));//set hx 711 variable
		}
		else
		{hx711H&=~(1<<(7-i));
		}
		PORTA&=~(1<<Load_clk); //Clock pin low
		_delay_us(5);
	}
	
	
	for(uint8_t i=0;i<16;i++){ // Load cell data low 16 bits
		PORTA|=(1<<Load_clk); //Clock pin high
		_delay_us(10);
		if ((PINA&(1<<Load_data))>>Load_data) //read data pin
		{hx711L|=(1<<(15-i));
		}
		else
		{hx711L&=~(1<<(15-i));
		}
		PORTA&=~(1<<Load_clk); //Clock pin low
		_delay_us(5);
	}
	
	hx711L=hx711L>>1; //shift bits
	
	if (hx711H&1)  //bit setup
	{hx711L|=(1<<15);
	}
	else
	{hx711L&=~(1<<15);
	}
	hx711H=hx711H>>1;
	
	return (hx711H*(65536/18029.6))+hx711L/18029.6; //load cell calibration
}
*/


	
	/*while (1)
	{
		hx=loadCellRead();
		if (hx>15)
		{
			PORTD |= (1<<1);
		}
	}*/

