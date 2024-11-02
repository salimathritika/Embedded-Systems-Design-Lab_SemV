#include <stdio.h>
#include <LPC17xx.h>

int temp1,temp2,flag1,flag2;
float adc_temp1, adc_temp2, diff;
char vtg1[20],vtg2[20];

void port_write()
{
  int i;
  LPC_GPIO0->FIOPIN=temp2<<23;
  if(flag1==0)
    LPC_GPIO0->FIOCLR=1<<27;
  else
    LPC_GPIO0->FIOSET=1<<27;
  LPC_GPIO0->FIOSET=1<<28;
  for(i=0;i<50;i++);
  LPC_GPIO0->FIOCLR=1<<28;
  for(i=0;i<50;i++);
}

void lcd_write()
{
  if((flag1==0) && ((temp1==0x30) || (temp1==0x20)))
    flag2=1;
  else
    flag2=0;
  temp2=temp1<<4;
  port_write();
  if(flag2==0)
  {
    temp2=temp1 & 0xF;
    port_write();
  }
}

void lcd_init()
{
  int i;
  int init[]={0x30,0x30,0x30,0x20,0x28,0x0C,0x01,0x80,0x06};
  flag1=0;
  for(i=0;i<9;i++)
    {
      temp1=init[i];
      lcd_write();
    }
  flag1=1;
}

void display_voltage()
{
  int i;
  sprintf(vtg1,"V1:%.2fV V2:%.2fV",adc_temp1,adc_temp2);
  sprintf(vtg2,"Diff:%.2fV",diff);
  flag1=0;
  temp1=0x80;
  lcd_write();
  flag1=1;
  for(i=0;vtg1[i]!='\0';i++)
    {
      temp1=vtg1[i];
      lcd_write();
    }
  flag1=0xC0;
  lcd_write();
  flag1=1;
  for(i=0;vtg2[i]!='\0';i++)
    {
      temp1=vtg2[i];
      lcd_write();
    }
}

int main()
{
  SystemInit();
  SystemCoreClockUpdate();
  LPC_PINCON->PINSEL1=0;
  LPC_GPIO0->FIODIR=0XF<<23 | 1<<27 | 1<<28;
  lcd_write();
  LPC_PINCON->PINSEL3=3<<30;
  LPC_SC->PCONP=1<<12;
  LPC_SC->PCONP=1<<15;

  while(1)
    {
      LPC_ADC->ADCR=(1<<4) | (1<<5) | (1<<21) | (1<<16) | (1<<5);
      while(!(LPC_ADC->ADDR4>>31)); //WAIT FOR CONVERSION
      adc_temp1=(LPC_ADC->ADDR4>>4)&0xFFF;
      adc_temp1=(adc_temp1 * 3.3/0xFFF);
      while(!(LPC_ADC->ADDR5>>31)); //WAIT FOR CONVERSION
      adc_temp2=(LPC_ADC->ADDR5>>4)&0xFFF;
      adc_temp2=(adc_temp2 * 3.3/0xFFF);
      diff=adc_temp1-adc_temp2;
      display_voltage();
    }
}
