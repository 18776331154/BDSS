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
	HDL_ENCODER_TIM2_INIT();            ///<初始化编码器（TIM2的编码器接口模式） 
	HDL_ENCODER_TIM3_INIT();            ///<初始化编码器（TIM3的编码器接口模式）
//	EXTIX_Init();                    //=====按键初始化(外部中断的形式)
	HDL_SERVO_PWM_INIT(99,71);
	HDL_MOTOR_INIT(7199,0);  		///<初始化PWM 10KHZ，用于驱动电机 
	OLED_Init();					///<初始化OLED
	
}

