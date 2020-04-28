#include "sys.h"
#ifndef HDL_ENCODER_H
#define HDL_ENCODER_H
#define ENCODER_TIM_PERIOD (u16)(65535)   //不可大于65535 因为F103的定时器是16位的

void HDL_ENCODER_TIM2_INIT(void);             //把TIM2初始化为编码器接口模式
void HDL_ENCODER_TIM3_INIT(void);             //把TIM3初始化为编码器接口模式









#endif

