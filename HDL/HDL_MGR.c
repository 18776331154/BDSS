#include "HDL_MGR.h"
#include "HDL_LED.h"
#include "HDL_MOTOR.h"
#include "HDL_KEY.h"
#include "HDL_ENCODER.h"


void Hdl_Mgr_Init(void)
{  
	HDL_LED_INIT();
	HDL_KEY_INIT();
	HDL_ENCODER_TIM2_INIT();            //=====初始化编码器（TIM2的编码器接口模式） 
	HDL_ENCODER_TIM3_INIT();            //=====初始化编码器（TIM3的编码器接口模式） 
	HDL_MOTOR_SET_PWM(7199,0);  				///<初始化PWM 10KHZ，用于驱动电机 





}

