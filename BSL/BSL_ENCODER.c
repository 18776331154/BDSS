#include "BSL_ENCODER.h"

/**************************************************************************
�������ܣ���λʱ���ȡ����������
��ڲ�������ʱ��
����  ֵ���ٶ�ֵ
**************************************************************************/
int BSL_ENCODER_READ(u8 TIMX)
{
    int Encoder_TIM;    
   switch(TIMX)
	 {
	     case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0; break;
		 case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0; break;	
		 case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0; break;	
		 default:  Encoder_TIM=0;
	 }
		return Encoder_TIM;
}
 ENCODER_NUM encoder_num_t;
ENCODER_NUM   BSL_DISTANCE_READ_ENCODER_NUM(int Encoder_Left,int Encoder_Right)
{
	encoder_num_t.distance+=((Encoder_Left)/1561.00)*21;
	
	encoder_num_t.quanshu=0;
	encoder_num_t.speed=Encoder_Left;
	return encoder_num_t;
}
