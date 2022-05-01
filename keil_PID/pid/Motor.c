#include "MOTOR.h"

/*
   PB1
psc -- 分频值
arr -- 重装载值
ccr -- 比较值
*/
u16 Motor_Speed = 500;

/*******************************************
 *	函数：Tim3_Config() 
 *  说明：定时器3初始化 72M
 *	      配置TIM3 CH4 输出PWM 周期 占空比
 *	      对应	PB1 控制电机
 *  参数：psc 分频  arr 装载值  ccr 比较值
 *******************************************
 */
void Tim3_Config(u16 psc, u16 arr, u16 ccr)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	//时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//配置PB1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//配置TIM3  基本定时
	TIM_TimeBaseStructure.TIM_Period = arr - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;//时钟分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;//时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ARRPreloadConfig(TIM3, ENABLE);//重装载值预装载使能
	//配置TIM3  输出通道
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//输出模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性
	TIM_OCInitStructure.TIM_Pulse = ccr;//比较值
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);//比较值的预装载使能
	
	
	TIM_Cmd(TIM3, ENABLE);
}

//电机速度设置函数
void Motor_SetSpeed(u16 speed)
{
	TIM_SetCompare4(TIM3,speed);
}



