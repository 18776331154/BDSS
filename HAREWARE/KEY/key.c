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
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);              //使能 PORTA 时钟 
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;                       //上拉输入
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;                           // PA5 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	resgister_event_handle(LED_ON ,EVENT_KEY_PRESSED|EVENT_KEY_LONGPRESSED);//注册LED事件	
} 


/**************************************************************************
函数功能：按键扫描
入口参数：无
返回  值：按键状态 0：无动作 1：单击 
**************************************************************************/
u8 click(void)
{
			static u8 flag_key=1;//按键按松开标志
			if(flag_key&&KEY==0)
			{
			flag_key=0;
			return 1;	// 按键按下
			}
			else if(1==KEY)			flag_key=1;
			return 0;//无按键按下
}
