#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "stm32f10x.h"


extern u16 Motor_Speed ;

void Tim3_Config(u16 psc, u16 arr, u16 ccr);
void Motor_SetSpeed(u16 speed);


#endif
