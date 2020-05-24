#include "sys.h"
#ifndef HDL_KEY_H
#define HDL_KEY_H



#define KEY PAin(5)  

void HDL_KEY_INIT(void);
	
void HDL_KEY_SCAN(void);

u8 HDL_KEY_CLICK_N_DOUBLE (u8 time);

u8 HDL_KEY_LONG_PRESS(void);
u8  select(void);

#endif


