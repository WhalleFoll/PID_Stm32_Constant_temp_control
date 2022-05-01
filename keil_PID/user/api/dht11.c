#include "dht11.h"
#include "delay.h"

//�л�������ģʽ
//����
//���
//PB6
void DHT11_ChangeMode(__DHT11_MODE mode)
{
	RCC_APB2PeriphClockCmd(DHT11_CLK, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
	
	if(mode == MODE_OUTPUT)
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
	else
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	
	GPIO_Init(DHT11_PORT, &GPIO_InitStructure);	
	
}


__DHT11_DATA dht_data;

__DHT11_DATA test;

//��ȡ����
//ʧ�ܷ��� 0
//�ɹ����� 1
u8 DHT11_ReadData(__DHT11_DATA * dht11)
{
	u8 result = 0;
	u8 count = 0;
	u8 data[5] = {0};
	
	DHT11_ChangeMode(MODE_OUTPUT);//�л����ģʽ
	DHT11_OUTPUT(1);//��ʼ�ź�
	DHT11_OUTPUT(0);
	Delay_ms(20);//��ʱ����������͵�ƽ18~30ms
	DHT11_OUTPUT(1);
	
	//�ȴ���Ӧ
	DHT11_ChangeMode(MODE_INPUT);//�л�����ģʽ
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
			data[i/8] |= (1<<(7-(i%8))); //��һ
		}
		else
		{
			data[i/8] &= ~(1<<(7-(i%8)));//����
		}
	}
	//У��
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












