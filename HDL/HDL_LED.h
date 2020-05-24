#ifndef __HDL_LED_H
#define __HDL_LED_H
#include "sys.h"

void HDL_LED_INIT(void);

#define LED PAout(4) // PA4
#define LED1 PEout(5) // PA4

void Led_Flash(u16 time);

#endif










