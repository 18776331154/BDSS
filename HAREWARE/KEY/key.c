#include "key.h"
#include "event_queue.h"
#include "control.h"
event_type_t LED_ON(event_type_t event)
{  
	if(EVENT_CAR_RUN==event)
	{
	CAR_Dis(5);
	}
	
	
	return EVENT_CAR_RUN;

	
}

void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);              //ʹ�� PORTA ʱ�� 
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;                       //��������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;                           // PA5 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	resgister_event_handle(LED_ON ,EVENT_KEY_PRESSED|EVENT_KEY_LONGPRESSED);//ע��LED�¼�	
} 


/**************************************************************************
�������ܣ�����ɨ��
��ڲ�������
����  ֵ������״̬ 0���޶��� 1������ 
**************************************************************************/
u8 click(void)
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
