#ifndef __DHT11_H
#define __DHT11_H


#include "stm32f10x.h"

#define DHT11_CLK		RCC_APB2Periph_GPIOA
#define DHT11_PORT	GPIOA
#define DHT11_PIN		GPIO_Pin_11


//IO���������		1	�����   0�����
#define DHT11_OUTPUT(x)	(x)?(GPIO_SetBits(DHT11_PORT, DHT11_PIN)):(GPIO_ResetBits(DHT11_PORT, DHT11_PIN))

//Bit_SET		�����ߵ�ƽ		Bit_RESET	�����͵�ƽ
#define DHT11_ReadPinState()	(GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN))

typedef enum{
	MODE_INPUT = 0,
	MODE_OUTPUT = 1,
}__DHT11_MODE;



typedef struct{
	u8 Hum;
	u8 Tem;
}__DHT11_DATA;


extern __DHT11_DATA dht_data;
extern __DHT11_DATA test;

u8 DHT11_ReadData(__DHT11_DATA * dht11);

#endif
