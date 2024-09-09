#include <LPC17xx.h>

int main()
{
	int i=0,j,x;
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0=0;  //For the LEDs P0.11 to P0.4
	LPC_PINCON->PINSEL4=0; //For the switch P2.12
	LPC_GPIO0->FIODIR=0XFF<<4; //Output mode for LED
	LPC_GPIO2->FIODIR=0<<12; //Input mode for switch
	while(1)
	{
		x=LPC_GPIO2->FIOPIN;
		x=x & 1<<12;
		if(x==0)
		{
			i++;
		}
		else
		{
			i--;
			if(i==-1)
				i=7;
		}
		
		LPC_GPIO0->FIOPIN=1<<(4+i%8);
		for(j=0;j<10000;j++);//delay
	}
	
}

/*
for(i=0;i<=8;i++)
		{
			LPC_GPIO0->FIOPIN=1<<(4+i%8);
			for(j=0;j<10000;j++);//delay
		}
*/
