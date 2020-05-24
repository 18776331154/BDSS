#include "BSL_ENCODER.h"

/**************************************************************************
函数功能：单位时间读取编码器计数
入口参数：定时器
返回  值：速度值
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
	
//	u8 count,last_average,distance;
//	average=(Encoder_Left+Encoder_Right)/2;
//	
//	count+=average;
//	if(average>=65535)
//	count-=	65535;
//	last_average=average;
//	if(last_average>average)
//		count+=	65535;
	
	encoder_num_t.distance+=Encoder_Left;
	encoder_num_t.quanshu=0;
	encoder_num_t.speed=Encoder_Left;
	return encoder_num_t;
}
