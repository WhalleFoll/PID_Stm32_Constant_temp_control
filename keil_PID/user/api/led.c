#include "led.h"
#include "delay.h"


// 电路 低电平有效  PC1 PC7  PA5

/*
void LED_Init(void)
初始化led
*/
void LED_Init(void)
{
	//开时钟
	RCC_APB2PeriphClockCmd(LED1_CLOCK | LED2_CLOCK,ENABLE);
	//配模式
	GPIO_InitTypeDef LED_TYPE;
	LED_TYPE.GPIO_Mode = GPIO_Mode_Out_PP;
	LED_TYPE.GPIO_Speed = GPIO_Speed_50MHz;
	
	LED_TYPE.GPIO_Pin = LED1_Pin |GPIO_Pin_2 |GPIO_Pin_3|GPIO_Pin_4;
	GPIO_Init(LED1_PORT,&LED_TYPE);

	LED_TYPE.GPIO_Pin =  LED2_Pin;
	GPIO_Init(LED2_PORT,&LED_TYPE);
	
	LED1(1);LED2(1);LED3(1);LED4(1);LED5(1);

}

void LED_SWITCH(void)
{
		static u8 num =0;
		switch(num)
		{
			case 0 :		LED2(0);LED3(1);LED4(1);LED5(1);
				break;
			case 1 :		LED2(1);LED3(0);LED4(1);LED5(1);
				break;			
			case 2 :		LED2(1);LED3(1);LED4(0);LED5(1);
				break;		
			case 3 :		LED2(1);LED3(1);LED4(1);LED5(0);
				break;
		}
		num++;
		if(num>3)		num=0;
	
}




