#include "key.h"

//按键初始化	PA1 PA2
//				KEY 1  2  
void Key_Config(void)
{
	//开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef KEY_TYPE;
	
	KEY_TYPE.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	KEY_TYPE.GPIO_Speed = GPIO_Speed_50MHz;
	KEY_TYPE.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2|GPIO_Pin_3 | GPIO_Pin_4;
	
	GPIO_Init(GPIOA,&KEY_TYPE);
}


////按键检测函数
//u8 Get_KeyValue(void)
//{
//	u8 keyvalue = 0;
//	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)==RESET)//如果条件成立，表示按键按下
//	{
//		keyvalue = 1;
//	}
//	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==RESET)
//	{
//		keyvalue = 2;
//	}
//	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==RESET)
//	{
//		keyvalue = 3;
//	}
//	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)==RESET)
//	{
//		keyvalue = 4;
//	}
//	return keyvalue;
//}




//按键检测函数		按键松开后才会响应
/*
0 没有按键按下，1 ：PA1对应的按键
*/
u8 Get_KeyValue(void)
{
	u8 keyvalue = 0;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==RESET)
	{
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==RESET)
		{}
		keyvalue = 1;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==RESET)
	{
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==RESET)
		{}
		keyvalue = 2;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)==RESET)
	{
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)==RESET)
		{}
		keyvalue = 3;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==RESET)
	{
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==RESET)
		{}
		keyvalue = 4;
	}	
	return keyvalue;
}


