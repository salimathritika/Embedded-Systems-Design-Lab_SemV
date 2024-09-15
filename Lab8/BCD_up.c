#include <LPC17xx.h>
#include <stdio.h>

#define FIRST_SEG 0<<23
#define SECOND_SEG 1<<23
#define THIRD_SEG 2<<23
#define FOURTH_SEG 3<<23

unsigned int dig_count;
unsigned int digit_value={0,4,3,2,1};
unsigned int select_seg={0,0<<23,1<<23,2<<23,3<<23};
unsigned int seven_seg[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned long int temp1,temp2,i=0;

void Display(void);
void delay(void);

int main()
{
  SystemInit();
  SystemCoreClockUpdate();
  LPC_PINCON->PINSEL0=0; //P0.4 to P0.11 GPIO data lines
  LPC_PINCON->PINSEL3=0;  //P1.23 to P1.26 GPIO enable lines

  LPC_GPIO0->FIODIR=0x00000FF0;
  LPC_GPIO1->FIODIR=0X07800000;
  while(1)
    {
      delay();
      dig_count+=1;
      if(dig_count==5)
        dig_count=1;
      Display();
    }
}

void Display()
{
  LPC_GPIO1->FIOPIN=select_seg[dig_count];
  LPC_GPIO0->FIOPIN=seven_seg[digit_value[dig_count]]<<4;
  for(i=0;i<500;i++);
  LPC_GPIO0->FIOCLR=0X00000FF0;
}

void delay()  //Need to change to make it according to timer
{
  for(i=0;i<500;i++);
}

while
