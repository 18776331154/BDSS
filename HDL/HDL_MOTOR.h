#include "sys.h"

#ifndef HDL_MOTOR_H
#define HDL_MOTOR_H

#define PWMA1   TIM4->CCR1  
#define PWMA2   TIM4->CCR2 

#define PWMB1   TIM4->CCR3  
#define PWMB2   TIM4->CCR4


void HDL_MOTOR_SET_PWM(int motor_a,int motor_b);

void HDL_SERVO_PWM_INIT(u16 arr,u16 psc) ;

void HDL_MOTOR_INIT(u16 arr,u16 psc)  ;




#endif

