#include "MOTOR.h"

/*
   PB1
psc -- ��Ƶֵ
arr -- ��װ��ֵ
ccr -- �Ƚ�ֵ
*/
u16 Motor_Speed = 500;

/*******************************************
 *	������Tim3_Config() 
 *  ˵������ʱ��3��ʼ�� 72M
 *	      ����TIM3 CH4 ���PWM ���� ռ�ձ�
 *	      ��Ӧ	PB1 ���Ƶ��
 *  ������psc ��Ƶ  arr װ��ֵ  ccr �Ƚ�ֵ
 *******************************************
 */
void Tim3_Config(u16 psc, u16 arr, u16 ccr)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	//ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//����PB1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//����TIM3  ������ʱ
	TIM_TimeBaseStructure.TIM_Period = arr - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;//ʱ�ӷ�Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;//ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ARRPreloadConfig(TIM3, ENABLE);//��װ��ֵԤװ��ʹ��
	//����TIM3  ���ͨ��
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//���ģʽ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//�������
	TIM_OCInitStructure.TIM_Pulse = ccr;//�Ƚ�ֵ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);//�Ƚ�ֵ��Ԥװ��ʹ��
	
	
	TIM_Cmd(TIM3, ENABLE);
}

//����ٶ����ú���
void Motor_SetSpeed(u16 speed)
{
	TIM_SetCompare4(TIM3,speed);
}



