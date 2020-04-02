#include "led.h"

void LED_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //使能 PORTA 时钟 
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;        //推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);                       //PA4 输出高电平
	
}

void Led_Flash(u16 time)
{
	  static int temp;
	  if  (0==time) LED=0;                               //低电平点亮
	  else if(++temp==time)	LED=~LED,temp=0;
}
