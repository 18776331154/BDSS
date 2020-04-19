#include "HDL_KEY.h"



/**************************************************************************
�������ܣ�������ʼ��
��ڲ�������
����  ֵ���� 
**************************************************************************/
void Hdl_Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);              //ʹ�� PORTA ʱ�� 
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;                       //��������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;                           // PA5 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
} 

/**************************************************************************
�������ܣ�����ɨ��
��ڲ�������
����  ֵ������״̬ 0���޶��� 1������ 
**************************************************************************/
u8 HDL_KEY_SCAN(void)
{
	static u8 flag_key=1;//�������ɿ���־
	if(flag_key&&KEY==0)
	{
		flag_key=0;
		return 1;	// ��������
	}
	else if(1==KEY)			flag_key=1;
	return 0;//�ް�������
}

