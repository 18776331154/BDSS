#include "HDL_MGR.h"
#include "HDL_LED.h"
#include "HDL_MOTOR.h"
#include "HDL_KEY.h"
#include "HDL_ENCODER.h"
#include "HDL_OLED.h"
#include "HDL_EXTI.h"

void Hdl_Mgr_Init(void)
{  
		
	HDL_LED_INIT();
	HDL_KEY_INIT();
	HDL_ENCODER_TIM2_INIT();            ///<��ʼ����������TIM2�ı������ӿ�ģʽ�� 
	HDL_ENCODER_TIM3_INIT();            ///<��ʼ����������TIM3�ı������ӿ�ģʽ��
//	EXTIX_Init();                    //=====������ʼ��(�ⲿ�жϵ���ʽ)
	HDL_SERVO_PWM_INIT(99,71);
	HDL_MOTOR_INIT(7199,0);  		///<��ʼ��PWM 10KHZ������������� 
	OLED_Init();					///<��ʼ��OLED
	
}

