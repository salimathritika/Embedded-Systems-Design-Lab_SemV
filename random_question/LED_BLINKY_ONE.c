//LED BLINKY WITH ONE LED
#include<LPC17xx.h>
int main()
{
	int i=0;
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0=0;
	LPC_GPIO0->FIODIR=1<<4;
	
	while(1)
	{
		LPC_GPIO0->FIOSET=1<<4;
		for(i=0;i<10000;i++);
		LPC_GPIO0->FIOCLR=1<<4;
		for(i=0;i<10000;i++);
	}
	
}