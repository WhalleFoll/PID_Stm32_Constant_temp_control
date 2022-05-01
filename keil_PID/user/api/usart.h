#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"

void Usart1_Init(void);
void Usart1_SendByte(u8 data);
u8 Usart1_RecvByte(void);
#endif
