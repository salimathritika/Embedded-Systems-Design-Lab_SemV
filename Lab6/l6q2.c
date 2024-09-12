//if switch closed(pressed) -> 0 in P2.12 -> 1 in LED
//           else(grounded) -> 1 in P2.12 -> 0 in LED

//HAVE TO CHECK IF WORKS

#include <LPC17xx.h>

int main()
{
	int x;
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0=0; //PO.4
	LPC_PINCON->PINSEL4=0; //P2.12
	LPC_GPIO0->FIODIR=1<<4; //For LED
	LPC_GPIO2->FIODIR=0<<12; //For Switch
	
	
	while(1)
	{
		//Reading value of port 2 to x
		x=LPC_GPIO2->FIOPIN;
		x=x&1 << 12;
		if(x==0)
			LPC_GPIO0->FIOSET=1<<4;
		else
			LPC_GPIO0->FIOCLR=1<<4;
	}
}
