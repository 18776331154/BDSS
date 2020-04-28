#include "HDL_MGR.h"
#include "HDL_LED.h"
#include "HDL_MOTOR.h"
#include "HDL_KEY.h"
#include "HDL_ENCODER.h"


void Hdl_Mgr_Init(void)
{  
	HDL_LED_INIT();
	HDL_KEY_INIT();
	HDL_ENCODER_TIM2_INIT();            //=====��ʼ����������TIM2�ı������ӿ�ģʽ�� 
	HDL_ENCODER_TIM3_INIT();            //=====��ʼ����������TIM3�ı������ӿ�ģʽ�� 
	HDL_MOTOR_SET_PWM(7199,0);  				///<��ʼ��PWM 10KHZ������������� 





}

