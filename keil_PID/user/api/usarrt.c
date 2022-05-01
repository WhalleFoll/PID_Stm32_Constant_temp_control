#include "usart.h"
#include "stdio.h"


void Usart1_Init(void)
{
	//ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//GPIO���� TX PA9  /  RX PA10
	
	GPIO_InitTypeDef USARTGPIO_TYPE;
	USART_InitTypeDef USART_TYPE;
	
	USARTGPIO_TYPE.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
	USARTGPIO_TYPE.GPIO_Speed = GPIO_Speed_50MHz;
	USARTGPIO_TYPE.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA,&USARTGPIO_TYPE);
	
	USARTGPIO_TYPE.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������ģʽ
	USARTGPIO_TYPE.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&USARTGPIO_TYPE);
	
	//���ô���
	
	USART_TYPE.USART_BaudRate = 9600;//������
	USART_TYPE.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//Ӳ��������
	USART_TYPE.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_TYPE.USART_Parity = USART_Parity_No;//��żУ��
	USART_TYPE.USART_StopBits = USART_StopBits_1;//ֹͣλ
	USART_TYPE.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART1,&USART_TYPE);//��ʼ������
	
	USART_Cmd(USART1,ENABLE);//ʹ�ܴ���
	
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



