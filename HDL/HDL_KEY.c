#include "HDL_KEY.h"
#include "HDL_OLED.h"
#include "delay.h"
#include "APF_AUTORUN.h"



/**************************************************************************
�������ܣ�������ʼ��
��ڲ�������
����  ֵ���� 
**************************************************************************/
void HDL_KEY_INIT(void)
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


u8 i=0;
void HDL_KEY_SCAN(void)
{
	static u8 key_up=1;//�������ɿ���־	  
	if(key_up==1&&KEY==0)
	{
		key_up=0;
		if(KEY==0)
			i++;
	
			event_establish(EVENT_KEY_PRESSED);
	}
	else if(KEY==1)
		key_up=1; 	    
 	
}

/**************************************************************************
�������ܣ�����ɨ��
��ڲ�����˫���ȴ�ʱ��
����  ֵ������״̬ 0���޶��� 1������ 2��˫�� 
**************************************************************************/
u8 HDL_KEY_CLICK_N_DOUBLE (u8 time)
{
		static	u8 flag_key,count_key,double_key;	
		static	u16 count_single,Forever_count;
	  if(KEY==0)  Forever_count++;   //������־λδ��1
     else        Forever_count=0;
		if(0==KEY&&0==flag_key)		flag_key=1;	
	  if(0==count_key)
		{
				if(flag_key==1) 
				{
					double_key++;
					count_key=1;	
				}
				if(double_key==2) 
				{
					double_key=0;
					count_single=0;
					return 2;//˫��ִ�е�ָ��
				}
		}
		if(1==KEY)			flag_key=0,count_key=0;
		
		if(1==double_key)
		{
			count_single++;
			if(count_single>time&&Forever_count<time)
			{
			double_key=0;
			count_single=0;	
			return 1;//����ִ�е�ָ��
			}
			if(Forever_count>time)
			{
			double_key=0;
			count_single=0;	
			}
		}	
		return 0;
}
/**************************************************************************
�������ܣ��������
��ڲ�������
����  ֵ������״̬ 0���޶��� 1������2s
**************************************************************************/
u8 HDL_KEY_LONG_PRESS(void)
{
			static u16 Long_Press_count,Long_Press;
	    if(Long_Press==0&&KEY==0)  Long_Press_count++;   //������־λδ��1
      else                       Long_Press_count=0; 
		  if(Long_Press_count>200)		
			{
				Long_Press=1;
				Long_Press_count=0;
				return 1;
			}				
			 if(Long_Press==1)     //������־λ��1
			{
				  Long_Press=0;
			}
			return 0;
}

