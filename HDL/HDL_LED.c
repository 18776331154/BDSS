#include "HDL_LED.h"



void HDL_LED_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);  //使能 PORTA 时钟 
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;        //推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);                       //PA4 输出高电平
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;        //推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);   
}

/**************************************************************************
函数功能：LED闪烁
入口参数：闪烁频率 
返回  值：无
**************************************************************************/
void Led_Flash(u16 time)
{
	  static int temp;
	  if  (0==time) LED=0;                               //低电平点亮
	  else if(++temp==time)	LED=~LED,temp=0;
}


