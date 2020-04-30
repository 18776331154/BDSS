#ifndef BSL_ENCODER_H
#define BSL_ENCODER_H
#include "sys.h"

typedef struct
{ 

	uint8_t distance;
	uint8_t speed;
	uint8_t quanshu;
	
	
	
}ENCUDER_NUM;
int BSL_ENCODER_READ(u8 TIMX);


ENCUDER_NUM   BSL_DISTANCE_READ_ENCODER_NUM(int Encoder_Left,int Encoder_Right);

#endif



