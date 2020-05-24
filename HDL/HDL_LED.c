#include "HDL_LED.h"



void HDL_LED_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);  //ʹ�� PORTA ʱ�� 
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;        //�������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);                       //PA4 ����ߵ�ƽ
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;        //�������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);   
}

/**************************************************************************
�������ܣ�LED��˸
��ڲ�������˸Ƶ�� 
����  ֵ����
**************************************************************************/
void Led_Flash(u16 time)
{
	  static int temp;
	  if  (0==time) LED=0;                               //�͵�ƽ����
	  else if(++temp==time)	LED=~LED,temp=0;
}


