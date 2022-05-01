#include "dht11.h"
#include "delay.h"

//切换数据线模式
//输入
//输出
//PB6
void DHT11_ChangeMode(__DHT11_MODE mode)
{
	RCC_APB2PeriphClockCmd(DHT11_CLK, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
	
	if(mode == MODE_OUTPUT)
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出
	else
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	
	GPIO_Init(DHT11_PORT, &GPIO_InitStructure);	
	
}


__DHT11_DATA dht_data;

__DHT11_DATA test;

//读取数据
//失败返回 0
//成功返回 1
u8 DHT11_ReadData(__DHT11_DATA * dht11)
{
	u8 result = 0;
	u8 count = 0;
	u8 data[5] = {0};
	
	DHT11_ChangeMode(MODE_OUTPUT);//切换输出模式
	DHT11_OUTPUT(1);//开始信号
	DHT11_OUTPUT(0);
	Delay_ms(20);//延时，持续输出低电平18~30ms
	DHT11_OUTPUT(1);
	
	//等待响应
	DHT11_ChangeMode(MODE_INPUT);//切换输入模式
	while(DHT11_ReadPinState() == 1)
	{
		count++;
		Delay_us(1);
		if(count >= 100)	return 0;
	}
	count = 0;
	while(DHT11_ReadPinState() == 0)
	{
		count++;
		Delay_us(1);
		if(count >= 100)	return 0;
	}
	count = 0;	
	for(u8 i=0; i<40; i++)
	{
		while(DHT11_ReadPinState() == 1)
		{
			count++;
			Delay_us(1);
			if(count >= 100)	return 0;
		}
		count = 0;
		while(DHT11_ReadPinState() == 0)
		{
			count++;
			Delay_us(1);
			if(count >= 100)	return 0;
		}
		count = 0;	
		Delay_us(30);
		if(DHT11_ReadPinState() == 1)
		{
			data[i/8] |= (1<<(7-(i%8))); //置一
		}
		else
		{
			data[i/8] &= ~(1<<(7-(i%8)));//清零
		}
	}
	//校验
	if(data[0]+data[1]+data[2]+data[3] == data[4])
	{
		dht11->Hum = data[0];
		dht11->Tem = data[2];
		result = 1;
	}
	else
	{
		result = 0;
	}
	return result;
}












