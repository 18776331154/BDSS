#ifndef __ENCODER_H
#define __ENCODER_H
#include "sys.h"
#define ENCODER_TIM_PERIOD (u16)(65535)   //���ɴ���65535 ��ΪF103�Ķ�ʱ����16λ�ġ�

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

void Encoder_Init_TIM2(void);             //��TIM2��ʼ��Ϊ�������ӿ�ģʽ
void Encoder_Init_TIM3(void);             //��TIM3��ʼ��Ϊ�������ӿ�ģʽ
int Read_Encoder(u8 TIMX);               //��λʱ���ȡ����������
void TIM2_IRQHandler(void);               //��ʱ��3���жϴ�����
void TIM3_IRQHandler(void);               //��ʱ��2���жϴ�����
#endif
