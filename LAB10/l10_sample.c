//Does not work properly
#include <LPC17xx.h>
#include <stdio.h>

#define Ref_Vtg 3.300
#define Full_Scale 0xFFF

int flag1,flag2,temp1,temp2;


void port_write()
{
	int i;
	LPC_GPIO0->FIOPIN=temp2<<23;
	if(flag1==0)
	  LPC_GPIO0->FIOCLR=1<<27;
	else
		LPC_GPIO0->FIOSET=1<<27;
	LPC_GPIO0->FIOSET=1<<28;
	for(i=0;i<20;i++);
	LPC_GPIO0->FIOCLR=1<<28;
	for(i=0;i<300000;i++);
	
}

void LCD_Write()
{ flag2 = (flag1 == 1) ? 0 :((temp1 == 0x30) || (temp1 == 0x20)) ? 1 : 0;
	temp2=(temp1&0xF0)>>4;
	port_write();
	if(flag2==0)
	{
		temp2=temp1&0xf;
		port_write();
	}
}

/*
void LCD_Init()
{
	int LCD_init[]={0x30,0x30,0x30,0x20,0x28,0x0c,0x06,0x01,0x80};
	int i;
	flag1 = 0;
	for(i=0; i<=8; i++)
	{
		temp1 = LCD_init[i];
		LCD_Write();
	}
	flag1 = 1;
}*/

int main()
{
	int adc_temp;
	int i;
	float in_vtg;
	char vtg[7],dval[7];
	char Msg3[]="IP ";
	char Msg4[]="OUTPUT ";
	int LCD_init[]={0x30,0x30,0x30,0x20,0x28,0x0c,0x06,0x01,0x80};
	
	SystemInit();
	SystemCoreClockUpdate();
	//LCD_Init();
	
	
	
	LPC_PINCON->PINSEL1=0;
	LPC_GPIO0->FIODIR=3<<27 | 0xF<<23; //P0.27 FOR RS, P0.28 FOR ENABLE, P0.26 TO P0.23 FOR DATA LINES
	
	LPC_SC->PCONP=1<<12;//To enable ADC
	LPC_SC->PCONP|=(1<<15); //Power for GPIO block
	LPC_PINCON->PINSEL3=3<<30;

	flag1 = 0;
	for(i=0; i<=8; i++)
	{
		temp1 = LCD_init[i];
		LCD_Write();
	}
	flag1 = 1;
	
	flag1=0;
	temp1=0x80;
	LCD_Write();
	flag1=1;
	i=0;
	while(Msg3[i]!='\0')
	{
		temp1=Msg3[i++];
		LCD_Write();
	}
	
	flag1=0;
	temp1=0xC0;
	LCD_Write();
	flag1=1;
	i=0;
	while(Msg4[i]!='\0')
	{
		temp1=Msg4[i++];
		LCD_Write();
	}
	//while(1);
	
	while(1)
	{
		LPC_ADC->ADCR=(1<<5)|(1<<21)|(1<<24);//AD0.5 start conversion
		while(LPC_ADC->ADGDR & 1<<31 ==0);
		adc_temp=LPC_ADC->ADGDR;
		adc_temp>>=4;
		adc_temp&=0x00000FFF;
		in_vtg=(((float)adc_temp*(float)Ref_Vtg))/((float)Full_Scale);
		sprintf(vtg,"%3.2fV",in_vtg);
		sprintf(dval,"%d",adc_temp);
		
		flag1=0;
		temp1=0x8c;
		LCD_Write();
		flag1=1;
		i=0;
		while(vtg[i++]!='\0')
		{
			temp1=vtg[i];
			LCD_Write();
		}
		
		flag1=0;
		temp1=0xD4;
		LCD_Write();
		flag1=1;
		i=0;
		while(dval[i++]!='\0')
		{
			temp1=dval[i];
			LCD_Write();
		}
		
		for(i=0;i<7;i++)
		   vtg[i]=dval[i]=0;
	}
}
