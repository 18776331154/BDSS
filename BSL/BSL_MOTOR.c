#include "BSL_MOTOR.h"
#include "HDL_MOTOR.h"



/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ���������PWM������PWM
����  ֵ����
**************************************************************************/
void BSL_Set_Pwm(int motor_a,int motor_b)
{
	    
    	if(motor_a<0)			PWMA1=7200,PWMA2=7200+motor_a;
			else 	            PWMA2=7200,PWMA1=7200-motor_a;
		
		  if(motor_b<0)			PWMB1=7200,PWMB2=7200+motor_b;
			else 	            PWMB2=7200,PWMB1=7200-motor_b;
}

/**************************************************************************
�������ܣ�����PWM��ֵ 
��ڲ�������
����  ֵ����
**************************************************************************/
void BSL_Xianfu_Pwm(void)
{	
//	  int Amplitude=6900;    //===PWM������7200 ������6900
//    if(Motor_A<-Amplitude) Motor_A=-Amplitude;	
//		if(Motor_A>Amplitude)  Motor_A=Amplitude;	
//	  if(Motor_B<-Amplitude) Motor_B=-Amplitude;	
//		if(Motor_B>Amplitude)  Motor_B=Amplitude;		
//		if(Servo<(SERVO_INIT-500))     Servo=SERVO_INIT-500;	  //����޷�
//		if(Servo>(SERVO_INIT+500))     Servo=SERVO_INIT+500;		  //����޷�
}

/**************************************************************************
�������ܣ��쳣�رյ��
��ڲ�������ѹ
����  ֵ��1���쳣  0������
**************************************************************************/
u8 BSL_Turn_Off( int voltage)
{
	    u8 temp;
//			if(voltage<740||Flag_Stop==1)//��ص�ѹ����7.4V�رյ��
//			{	                                                
//      temp=1;                                            
//      }
//			else
//      temp=0;
      return temp;			
}


