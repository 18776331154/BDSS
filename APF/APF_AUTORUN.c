#include "APF_AUTORUN.h"
#include "HDL_ENCODER.h"
#include "BSL_ENCODER.h"
#include "HDL_OLED.h"
#include "HDL_MOTOR.h"
#include "HDL_KEY.h"
#include "BSL_MOTOR.h"
#include "HDL_LED.h"
#include "BSL_ENCODER.h"
int Encoder_Left=0;
int Encoder_Right=0;
extern u8 i;

ENCODER_NUM encoder_num_auto;

 extern ENCODER_NUM encoder_num_t;

int dis;
	u16 led0pwmval=0;
	u8 dir=1;




void APF_CAR_RUN(void)
{
	if(distance<30)
		BSL_Set_Pwm(10,10);
}


event_type_t APF_RUN30CM(event_type_t event)
{
	if(event==EVENT_KEY_PRESSED)
	{
//		Led_Flash(2000);
//		APF_CAR_RUN();
		
		encoder_num_t.distance=0;
	
		LED1=~LED1;
		BSL_Set_Pwm(2000,2000);
	}
	
	return event;
}



void APF_RUN30CM_INIT(void)
{ 
	
	resgister_event_handle(APF_RUN30CM ,EVENT_KEY_PRESSED);//注册LED事件	

}


void TIM1_UP_IRQHandler(void)  
{    
	if(TIM_GetFlagStatus(TIM1,TIM_FLAG_Update)==SET)//5ms定时中断
	{   
		 TIM_ClearITPendingBit(TIM1,TIM_IT_Update);                             //===清除定时器1中断标志位	      
		 Encoder_Left=BSL_ENCODER_READ(2);
		 Encoder_Right=BSL_ENCODER_READ(3);
		 HDL_KEY_SCAN();
	     encoder_num_auto=BSL_DISTANCE_READ_ENCODER_NUM(Encoder_Left,Encoder_Right);
		
		if(encoder_num_auto.distance>3000)
		{
			LED1=0;
			BSL_Set_Pwm(0,0);
			
		
		}
		else 
		{
			LED1=1;
			
		}
//		if(dir)led0pwmval+=100;
//		else led0pwmval-=100;

// 		if(led0pwmval>5000)dir=0;
//		if(led0pwmval==0)dir=1;				
		
	}
} 
void APF_AUTORUN_OLED_SHOW(void)
{
	   
	   OLED_ShowString(00,20,"EncoLEFT");    //编码器数据
		if( Encoder_Left<0)		OLED_ShowString(80,20,"-"),
		                      OLED_ShowNumber(95,20,-Encoder_Left,5,12);
		else                 	OLED_ShowString(80,20,"+"),
		                      OLED_ShowNumber(95,20, Encoder_Left,5,12);

		                      OLED_ShowString(00,30,"EncoRIGHT");
		if(Encoder_Right<0)	  OLED_ShowString(80,30,"-"),
		                      OLED_ShowNumber(95,30,-Encoder_Right,5,12);
		else               		OLED_ShowString(80,30,"+"),
		                      OLED_ShowNumber(95,30,Encoder_Right,5,12);
//          OLED_ShowNumber(00,40,average,5,12);
		  OLED_ShowNumber(00,40,encoder_num_auto.distance ,7,12);
		 OLED_ShowNumber(46,40,i,2,12);
		OLED_ShowNumber(80,40,led0pwmval,5,12);
		
		OLED_Refresh_Gram();	

}	




