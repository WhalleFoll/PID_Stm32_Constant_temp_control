#ifndef _LED_H
#define _LED_H

#include "stm32f10x.h"


	
	
	
#define	LED1_CLOCK 				RCC_APB2Periph_GPIOC
#define LED1_PORT  				GPIOC
#define LED1_Pin   				GPIO_Pin_0
	

#define	LED2_CLOCK 				RCC_APB2Periph_GPIOC
#define LED2_PORT  				GPIOC
#define LED2_Pin   				GPIO_Pin_1

#define	LED3_CLOCK 				RCC_APB2Periph_GPIOC
#define LED3_PORT  				GPIOC
#define LED3_Pin   				GPIO_Pin_2

#define	LED4_CLOCK 				RCC_APB2Periph_GPIOC
#define LED4_PORT  				GPIOC
#define LED4_Pin   				GPIO_Pin_3


#define	LED5_CLOCK 				RCC_APB2Periph_GPIOC
#define LED5_PORT  				GPIOC
#define LED5_Pin   				GPIO_Pin_4




#define LED1(X)  (X)?(GPIO_SetBits(LED1_PORT,LED1_Pin)):(GPIO_ResetBits(LED1_PORT,LED1_Pin))
#define LED2(X)  (X)?(GPIO_SetBits(LED2_PORT,LED2_Pin)):(GPIO_ResetBits(LED2_PORT,LED2_Pin))

//#define LED3(N)  (N)?(LED3_PORT->ODR &= ~(1 << 2)):(LED3_PORT->ODR |= (1 << 2))
#define LED3(X)  (X)?(GPIO_SetBits(LED3_PORT,LED3_Pin)):(GPIO_ResetBits(LED3_PORT,LED3_Pin))
#define LED4(X)  (X)?(GPIO_SetBits(LED4_PORT,LED4_Pin)):(GPIO_ResetBits(LED4_PORT,LED4_Pin))
#define LED5(X)  (X)?(GPIO_SetBits(LED5_PORT,LED5_Pin)):(GPIO_ResetBits(LED5_PORT,LED5_Pin))



void LED_Init(void);//³õÊ¼»¯
void LED_SWITCH(void);//ÉÁµÆ

#endif
