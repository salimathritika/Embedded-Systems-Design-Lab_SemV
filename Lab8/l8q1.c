//worksa
//Write a C program for 4 digit BCD up/down counter on seven segment using a switch and timer with a delay of 1-second between each count
//not using timers here
#include <LPC17xx.h>
//All the 7th pins of each connector are connected to switch
int main()
{
	int seven_seg[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	int n=0,temp,count=0,i,j,x;
	SystemInit();
	SystemCoreClockUpdate();

	LPC_PINCON->PINSEL0=0;//Configuring lines P0.11 to P0.4+
	LPC_PINCON->PINSEL3=0;//P1.26 to P1.23 for decoder
	LPC_PINCON->PINSEL4=0;//For switch at P2.0

LPC_GPIO0->FIODIRL=0XFF0;
LPC_GPIO1->FIODIR=0xF<<23;

LPC_GPIO2->FIODIR=0; //p2.0


while(1)
{
	
		
	temp=n;
	if(count==1000)
	{
		x=LPC_GPIO2->FIOPIN;
		x=x&1;
		//upcounter
		if(x==0)
		{
			n=(n+1)%10000;
		}
		//downcounter
		else //i.e for x= non zero
		{
			n--;
			if(n==-1)
				n=9999;
			
			
		}
		
		
		count=0;
	}
	for(i=0;i<4;i++)
	{
		LPC_GPIO1->FIOPIN=i<<23;//for decoder
		LPC_GPIO0->FIOPIN=seven_seg[temp%10]<<4;
		temp=temp/10;
		for(j=0;j<10000;j++);//delay
		count++;
		
	}
	
}
	
}
