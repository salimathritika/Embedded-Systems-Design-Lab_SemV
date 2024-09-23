//Static number
#include <LPC17xx.h>
int main()
{
	int seven_seg[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	int n=6;
	SystemInit();
	SystemCoreClockUpdate();
//Configuring lines P0.11 to P0.4+
	LPC_PINCON->PINSEL0=0;
LPC_PINCON->PINSEL3=0;
LPC_GPIO0->FIODIRL=0XFF0;
LPC_GPIO1->FIODIR=0XF<<23; //P1.23 TO P1.26
LPC_GPIO1->FIOPIN=0;

LPC_GPIO0->FIOPIN=seven_seg[n]<<4;
while(1);	
}
