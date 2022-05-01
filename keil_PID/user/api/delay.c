#include "delay.h"


vu32 RunTime = 0;//时间轴
vu32 Led_RunTime =0;//LED
vu32 DHT11_RunTime =0;//

//系统定时器中断服务函数
void SysTick_Handler(void) //1mS
{
	RunTime++;
	Led_RunTime++;
	DHT11_RunTime++;
	
}

//初始化系统定时器
void SysTick_Init(u32 value)
{
	if(SysTick_Config(value))
	{
		while(1);//系统定时器初始化失败
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

