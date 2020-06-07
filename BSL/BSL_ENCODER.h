#ifndef BSL_ENCODER_H
#define BSL_ENCODER_H
#include "sys.h"
typedef struct
{ 

	float distance;
	uint8_t speed;
	uint8_t quanshu;
}ENCODER_NUM;

int BSL_ENCODER_READ(u8 TIMX);


ENCODER_NUM   BSL_DISTANCE_READ_ENCODER_NUM(int Encoder_Left,int Encoder_Right);

#endif



