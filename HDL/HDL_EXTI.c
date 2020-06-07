#include "HDL_EXTI.h"
#include "HDL_KEY.h"

void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStruct;
	HDL_KEY_INIT();	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  //�ⲿ�жϣ���Ҫʹ��AFIOʱ��
	
	//GPIOA.5 �ж����Լ��жϳ�ʼ������
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource5);
  EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
 //GPIOA.0	  �ж����Լ��жϳ�ʼ������ �����ش��� PA0  WK_UP
 	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

	//����IO�����ж��ߵ�ӳ���ϵ
	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;         //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;            //ʹ���ⲿ�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2 
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;         //��Ӧ���ȼ�1
	NVIC_Init(&NVIC_InitStruct);

   	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStruct); 
}

//�ⲿ�ж�9~5�������
void EXTI9_5_IRQHandler(void)
{			

   if(KEY==0)	   //��/�ص��
	{
		EXTI_ClearITPendingBit(EXTI_Line5);  //���LINE5�ϵ��жϱ�־λ 
//		Flag_Next=1;
	}	
//	if(WK_UP==1)	 	 //WK_UP����
//	{				 
//		event_establish(EVENT_KEY_PRESSED);
//	}
	EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}





