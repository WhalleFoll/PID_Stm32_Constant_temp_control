#include "delay.h"


vu32 RunTime = 0;//ʱ����
vu32 Led_RunTime =0;//LED
vu32 DHT11_RunTime =0;//

//ϵͳ��ʱ���жϷ�����
void SysTick_Handler(void) //1mS
{
	RunTime++;
	Led_RunTime++;
	DHT11_RunTime++;
	
}

//��ʼ��ϵͳ��ʱ��
void SysTick_Init(u32 value)
{
	if(SysTick_Config(value))
	{
		while(1);//ϵͳ��ʱ����ʼ��ʧ��
	}
}

void Delay_ms(u32 n)
{
	u32 Time = RunTime;
	while(Time+n > RunTime);
	
}


void Delay_nus(u32 n)
{
	while(n--)
	{
		delay_1us();
	}
}

void Delay_nms(u32 n)
{
	n *= 1000;
	while(n--)
	{
		delay_1us();
	}
}

