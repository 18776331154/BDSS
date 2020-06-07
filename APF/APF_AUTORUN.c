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
	int led0pwmval=2000;
	u8 dir=1;

#define  run_plan_num  5
int16_t run_plan[run_plan_num]={20,60,90,120,150};
int16_t run_plan_now=0;
int16_t run_targe_distance;
int16_t run_last_distance=0;
int16_t times;
u8 run_flag=0;

void APF_CAR_RUN(void)
{
	if(distance<30)
		BSL_Set_Pwm(10,10);
}


event_type_t APF_RUN30CM(event_type_t event)
{
	
	if(event==EVENT_KEY_PRESSED)
	{
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

void run_plan_spc(int16_t now,int16_t targe)
{
	int distance_error;
	static u8 is_run_last_point=1;
	distance_error=targe-now;
	if(0<=distance_error&&distance_error<=3&&is_run_last_point)//
	{ 
		BSL_Set_Pwm(0,0);
		times++;
         if(times==100)
		 {   
			 times=0;
		     run_plan_now++;	 
			if(run_plan_now==run_plan_num)
			{   
				LED1=1;
				BSL_Set_Pwm(0,0);
				run_plan_now=0;
			}
			else
			{
				BSL_Set_Pwm(1500,1500); 
				is_run_last_point=0;
			
			}   
		 }
	}
	else
		is_run_last_point=1;
	
}




void TIM1_UP_IRQHandler(void)  
{  
	if(TIM_GetFlagStatus(TIM1,TIM_FLAG_Update)==SET)//5ms定时中断
	{   
		 TIM_ClearITPendingBit(TIM1,TIM_IT_Update); 

		 Encoder_Left=BSL_ENCODER_READ(2);
		 Encoder_Right=BSL_ENCODER_READ(3);
		
		 HDL_KEY_SCAN();
		
	     encoder_num_auto=BSL_DISTANCE_READ_ENCODER_NUM(Encoder_Left,Encoder_Right);
		
        run_plan_spc(encoder_num_auto.distance,run_plan[run_plan_now]);

	}
} 
void APF_AUTORUN_OLED_SHOW(void)
{   
	OLED_ShowString(00,20,"EncoLEFT");    //编码器数据
	if( Encoder_Left<0)
		OLED_ShowString(80,20,"-"),
	OLED_ShowNumber(95,20,-Encoder_Left,5,12);
	else
		OLED_ShowString(80,20,"+"),
	OLED_ShowNumber(95,20, Encoder_Left,5,12);

	OLED_ShowString(00,30,"EncoRIGHT");
	if(Encoder_Right<0)	  
		OLED_ShowString(80,30,"-"),
	OLED_ShowNumber(95,30,-Encoder_Right,5,12);
	else               		
		OLED_ShowString(80,30,"+"),
	OLED_ShowNumber(95,30,Encoder_Right,5,12);
	
	
	
	OLED_ShowNumber(00,40,encoder_num_auto.distance ,4,12);
	OLED_ShowNumber(46,40,run_plan[run_plan_now],4,12);
	OLED_ShowNumber(80,40,times,4,12);
	OLED_Refresh_Gram();	

}	




