#include "BSL_MOTOR.h"
#include "HDL_MOTOR.h"



/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：左轮PWM、右轮PWM
返回  值：无
**************************************************************************/
void BSL_Set_Pwm(int motor_a,int motor_b)
{
	    
    	if(motor_a<0)			PWMA1=7200,PWMA2=7200+motor_a;
			else 	            PWMA2=7200,PWMA1=7200-motor_a;
		
		  if(motor_b<0)			PWMB1=7200,PWMB2=7200+motor_b;
			else 	            PWMB2=7200,PWMB1=7200-motor_b;
}

/**************************************************************************
函数功能：限制PWM赋值 
入口参数：无
返回  值：无
**************************************************************************/
void BSL_Xianfu_Pwm(void)
{	
//	  int Amplitude=6900;    //===PWM满幅是7200 限制在6900
//    if(Motor_A<-Amplitude) Motor_A=-Amplitude;	
//		if(Motor_A>Amplitude)  Motor_A=Amplitude;	
//	  if(Motor_B<-Amplitude) Motor_B=-Amplitude;	
//		if(Motor_B>Amplitude)  Motor_B=Amplitude;		
//		if(Servo<(SERVO_INIT-500))     Servo=SERVO_INIT-500;	  //舵机限幅
//		if(Servo>(SERVO_INIT+500))     Servo=SERVO_INIT+500;		  //舵机限幅
}

/**************************************************************************
函数功能：异常关闭电机
入口参数：电压
返回  值：1：异常  0：正常
**************************************************************************/
u8 BSL_Turn_Off( int voltage)
{
	    u8 temp;
//			if(voltage<740||Flag_Stop==1)//电池电压低于7.4V关闭电机
//			{	                                                
//      temp=1;                                            
//      }
//			else
//      temp=0;
      return temp;			
}


