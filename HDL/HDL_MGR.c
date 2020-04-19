#include "HDL_MGR.h"
#include "HDL_LED.h"
#include "HDL_MOTOR.h"
#include "HDL_KEY.h"
#include "HDL_ENCODER.h"


void Hdl_Mgr_Init(void)
{
	Motor_PWM_Init(7199,0);  				///<初始化PWM 10KHZ，用于驱动电机 
	Hdl_Key_Init();




}

