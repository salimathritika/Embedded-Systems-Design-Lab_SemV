#include <LPC17xx.h>

int main()
{
	int i=0,x,j;
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0=0;  //For the LEDs P0.11 to P0.4
	LPC_PINCON->PINSEL4=0; //For the switch P2.12
	LPC_GPIO0->FIODIR=0XFF<<4; //Output mode for LED
	LPC_GPIO2->FIODIR=0<<12; //Input mode for switch
	
	//Check if up counter or down counter
	
	while(1)
	{
		x=LPC_GPIO2->FIOPIN;
		x=x & 1<<12;
		if(x==0)  //if it is pressed it is a up counter
		{
			i++;
			if(i==256)
				i=0;
		}
		else   //if it is not pressed it is down counter
		{
			i--;
			if(i==-1)
				i=255;
		}
		LPC_GPIO0->FIOPIN=i<<4;
		for(j=0;j<10000000;j++);
		
	}
}
