
#define lqd1 1  // how much time(ms) need to release 1 mili-liter of liquid 1
#define lqd2 1  // how much time(ms) need to release 1 mili-liter of liquid 2
#define lqd3 1  // how much time(ms) need to release 1 mili-liter of liquid 3
#define lqd4 1	// how much time(ms) need to release 1 mili-liter of liquid 4

int Solenoid(unsigned char oil1,int  measure);
void time_delay();



int Solenoid(unsigned char oil1,int measure)
{
	DDRD = 0x1F;	   //make PORTD0 to PORTD4 as outputs
	int time=0;
	
	while (1)
	{
		switch(oil1)
		{
			case '1':
				PORTD = PORTD | (1<<0);
				time = 50;
				while(!(time==0))
				{
					_delay_ms(10);
					time --;
				}
				PORTD = 0x00;
				break;
			case '2':
				PORTD = PORTD | (1<<1);
				time = measure*5*lqd2;
				while(time>0)
				{
					_delay_ms(10);
					time --;
				}
				PORTD = 0x00;
				break;
			case '3':
				PORTD = PORTD | (1<<2);
				time = measure*5*lqd3;
				while(time>0)
				{
					_delay_ms(1000);
					time--;
				}
				PORTD = 0x00;
				break;
			case '4':
				PORTD = PORTD | (1<<3);
				time = measure*5*lqd4;
				while(time>0)
				{
					_delay_ms(1000);
					time--;
				}
				PORTD = 0x00;
				break;
			default:
				break;
		}
		
		return 0;
	}
	
}

