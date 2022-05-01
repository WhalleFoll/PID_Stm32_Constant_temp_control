#include "key.h"

//������ʼ��	PA1 PA2
//				KEY 1  2  
void Key_Config(void)
{
	//��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef KEY_TYPE;
	
	KEY_TYPE.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	KEY_TYPE.GPIO_Speed = GPIO_Speed_50MHz;
	KEY_TYPE.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2|GPIO_Pin_3 | GPIO_Pin_4;
	
	GPIO_Init(GPIOA,&KEY_TYPE);
}


////������⺯��
//u8 Get_KeyValue(void)
//{
//	u8 keyvalue = 0;
//	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)==RESET)//���������������ʾ��������
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




//������⺯��		�����ɿ���Ż���Ӧ
/*
0 û�а������£�1 ��PA1��Ӧ�İ���
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


