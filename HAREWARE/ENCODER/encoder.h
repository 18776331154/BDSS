#ifndef __ENCODER_H
#define __ENCODER_H
#include "sys.h"
#define ENCODER_TIM_PERIOD (u16)(65535)   //不可大于65535 因为F103的定时器是16位的。

typedef struct
{
	
int angle;
int angle_last;
int angle_speed;
int angle_speed_last;
int angle_acceleration;
int cnt;
int quanshu;	 
//static int distance;

}ENCODER_T;


void encoder_caculter(ENCODER_T * encoder_n);

ENCODER_T *control_return_to_show(void);

void car_control(void(*control_action)(int a,int b,int c));

void Encoder_Init_TIM2(void);             //把TIM2初始化为编码器接口模式
void Encoder_Init_TIM3(void);             //把TIM3初始化为编码器接口模式
int Read_Encoder(u8 TIMX);               //单位时间读取编码器计数
void TIM2_IRQHandler(void);               //定时器3的中断处理函数
void TIM3_IRQHandler(void);               //定时器2的中断处理函数
#endif
