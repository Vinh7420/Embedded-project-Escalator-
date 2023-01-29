#include <REGX51.H>

int counter = 0;

void delay(int time) {
	while(time--);
}

void sensor_in(void) interrupt 0
{
	counter++;
	P1_0 = 0;
	delay(30000);
	P1_0 = 1;
}	

void sensor_out(void) interrupt 2
{
	counter--;
	P1_1 = 0;
	delay(30000);
	P1_1 = 1;
}
void main()
{	
	EX0 = 1;		//IE
	EX1 = 1;		//IE
	IT0 = 1;		//TCON
	IT1 = 1;		
	EA = 1;
	while(1)
	{
		if(counter == 0)
		{
			P2 = 0x00;
		}
		if(counter > 0)
		{
			P2 = 0xFF;
		}
	}
	
}