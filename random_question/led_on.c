//turn on led
#include<LPC17xx.h>
int main()
{
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0=0;
	LPC_GPIO0->FIODIR=1<<4;
	LPC_GPIO0->FIOSET=1<<4;
}
