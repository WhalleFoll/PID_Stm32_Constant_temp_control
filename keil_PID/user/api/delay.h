#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"



extern vu32 RunTime ;
extern vu32 Led_RunTime;
extern vu32 DHT11_RunTime;

#define delay_1us()	{\
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
	__NOP();__NOP();\
}



#define Delay_us Delay_nus

void Delay_nus(u32 n);
void Delay_nms(u32 n);
void Delay_ms(u32 n);
void SysTick_Init(u32 value);
#endif
