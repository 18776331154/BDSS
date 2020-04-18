#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
#define PI 3.14159265
#define ZHONGZHI 0



void Kinematic_Analysis(float velocity,float angle);
void TIM2_IRQHandler(void) ;
void Set_Pwm(int motor_a,int motor_b,int servo);
void Key(void);
void Xianfu_Pwm(void);
u8 Turn_Off( int voltage);
void Get_Angle(u8 way);
int myabs(int a);
int Incremental_PI_A (int Encoder,int Target);
int Incremental_PI_B (int Encoder,int Target);
void Get_RC(void);
void  Find_CCD_Zhongzhi(void);
void CAR_Breaking(void);
void CAR_Move(int velocity);
int Distance_PID(int Now,int Target,FlagStatus* Arrive_Flag);
int  __abs(int number);
void Amplitude_Limiting(int* Variable,int Range);
void CAR_Dis(int Dis);
void caculation_distance(int encoder_Left ,int encoder_Right,int targe);
//void automatic_control(u8 now,u8 targe);
#endif
