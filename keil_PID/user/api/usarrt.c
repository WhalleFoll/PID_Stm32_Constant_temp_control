#include "usart.h"
#include "stdio.h"


void Usart1_Init(void)
{
	//时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//GPIO配置 TX PA9  /  RX PA10
	
	GPIO_InitTypeDef USARTGPIO_TYPE;
	USART_InitTypeDef USART_TYPE;
	
	USARTGPIO_TYPE.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
	USARTGPIO_TYPE.GPIO_Speed = GPIO_Speed_50MHz;
	USARTGPIO_TYPE.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA,&USARTGPIO_TYPE);
	
	USARTGPIO_TYPE.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入模式
	USARTGPIO_TYPE.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&USARTGPIO_TYPE);
	
	//配置串口
	
	USART_TYPE.USART_BaudRate = 9600;//波特率
	USART_TYPE.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//硬件控制流
	USART_TYPE.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_TYPE.USART_Parity = USART_Parity_No;//奇偶校验
	USART_TYPE.USART_StopBits = USART_StopBits_1;//停止位
	USART_TYPE.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART1,&USART_TYPE);//初始化串口
	
	USART_Cmd(USART1,ENABLE);//使能串口
	
}

void Usart1_SendByte(u8 data)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET)
	{}
	USART_SendData(USART1,data);
	
}
u8 Usart1_RecvByte(void)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
	{}
	return USART_ReceiveData(USART1);
}

int fputc(int c, FILE *stream)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == 0);
	USART_SendData(USART1,c);
	return c;
}



