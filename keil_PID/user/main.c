#include "main.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "dht11.h"
#include "lcd.h"
#include "MOTOR.h"
#include "pid.h"

u8 data =0;
u8 temp_d=25;
//u16 temp_da;
u8 Ping=1;
char buff3[32]={'\0'};


//从上到下执行，从main开始到main结束
//像素40*40
extern const unsigned char gImage_temperature[3200];
extern const unsigned char gImage_humidity[3200];
extern const unsigned char gImage_logo[8192] ;
extern __PID PID;

void  interface_one(void);
void  interface_two(void);
void Pid_Fan(u8 i);
void key_scan(void);
int main(void)
{
	SysTick_Init(72000);
	LED_Init();
	Key_Config();
	Usart1_Init();
	Delay_ms(10);
	LCD_Init();
	Tim3_Config(72,1000,Motor_Speed);//Motor_Speed = 500
	//LCD_ShowString(16,120,16,"191360228",0);
	interface_one();
	//LCD_Clear(WHITE);
	//
	printf("初始化完成\r\n");
  while (1)
  {
		if( Led_RunTime >= 15)
		{
			Led_RunTime=0;
			//写要执行的语句
			//Motor_SetSpeed(Motor_Speed);
			DCMotor_PIDControl(IncPID_Ctrl(test.Tem));
		}
	    key_scan();
		//
		if(DHT11_RunTime>=500)
		{
			DHT11_RunTime=0;
				if(DHT11_ReadData(&test)==1)
				{
					char buff[64]={'\0'};
					char buff1[32]={'\0'};
					char buff2[32]={'\0'};
					sprintf(buff,"温度:%d度湿度:%d%%RH",test.Tem,test.Hum);
					sprintf(buff1,"%d",test.Tem);
					sprintf(buff2,"%d",test.Hum);
					printf("%s\r\n",buff);
                    //temp_da=test.Tem;
					if(Ping==1)
					{
						Show_Str(120,44,BRRED,WHITE,(u8 *)buff1,16,0);
						Show_Str(120,92,BRRED,WHITE,(u8 *)buff2,16,0);
						Pid_Fan(test.Tem);
					}
				}else
				{
					printf("温湿度读取失败\r\n");
				}
		}
		
		
  }
}

void Pid_Fan(u8 i)
{
	int c=i-PID.SetValue;
    if(c<=0)
  {
    LCD_ShowString_red(24,190,16,"FAN                  ",0);
	//Motor_Speed=500;
	 // IncPID_Ctrl(300);
  }
  if(c>0&&c<=1)
  {
	  LCD_ShowString_red(24,190,16,"      LOW            ",0);
	  //Motor_Speed=600;
  }
  if(c>1&&c<=2)
  {
	  LCD_ShowString_red(24,190,16,"            MID      ",0);
	 // Motor_Speed=750;
  }
  if(c>=3)     // 
  {
	  LCD_ShowString_red(24,190,16,"                   HI",0);
	  //Motor_Speed=950;
  }
  
}

void key_scan(void)
{
		//按键
		switch(Get_KeyValue())
		{
			case 1: 
				if(Ping==2)
				{
					LCD_Clear(WHITE);
					interface_one();
					Ping=1;
				}					
				break ;
			
			case 2: 
				if(Ping==1)
				{
					LCD_Clear(WHITE);
					interface_two();
					Ping=2;
				}
				break ;
			
			case 3: 
				if(Ping==1)
				{
				  PID.SetValue++;
					sprintf(buff3,"%d",PID.SetValue);
					Show_Str(96,132,BRRED,WHITE,(u8 *)buff3,16,0);
				}
				break ;
			
			case 4: 
				if(Ping==1)
				{
					PID.SetValue--;
					sprintf(buff3,"%d",PID.SetValue);
					Show_Str(96,132,BRRED,WHITE,(u8 *)buff3,16,0);
				}
//				Motor_Speed -=100;
//				if(Motor_Speed <= 0) Motor_Speed = 0;
				break ;
			default: break;
		}
}


void  interface_one(void)
{
	Paint_Bmp(16,32,40,40,gImage_temperature);
	Show_Str(72,44,LIGHTBLUE,WHITE,(u8 *)"温度:",16,0);
	Show_Str(144,44,LIGHTBLUE,WHITE,(u8 *)"℃",16,0);
	
	Paint_Bmp(16,80,40,40,gImage_humidity);
	Show_Str(72,92,LIGHTBLUE,WHITE,(u8 *)"湿度:",16,0);
    Show_Str(144,92,LIGHTBLUE,WHITE,(u8 *)"%",16,0);
	
	Show_Str(16,132,LIGHTBLUE,WHITE,(u8 *)"预定温度:",16,0);
	Show_Str(136,132,LIGHTBLUE,WHITE,(u8 *)"℃",16,0);
	
	Show_Str(24,164,LIGHTBLUE,WHITE,(u8 *)"风速",16,0);
	Show_Str(72,164,LIGHTBLUE,WHITE,(u8 *)"低速",16,0);
	Show_Str(120,164,LIGHTBLUE,WHITE,(u8 *)"中速",16,0);
	Show_Str(168,164,LIGHTBLUE,WHITE,(u8 *)"高速",16,0);
	LCD_ShowString(24,190,16,"FAN   LOW   MID    HI",0);
    sprintf(buff3,"%d",temp_d);
	Show_Str(96,132,BRRED,WHITE,(u8 *)buff3,16,0);
}


void  interface_two(void)
{
	char member2[64]={'\0'};
// 组员:闫鹏，石起超，刘良珂，张玉豪
//范培栋，张正金，田柏帆，李伟德，
	Paint_Bmp(80,32,64,64,gImage_logo);
	sprintf(member2,"PID恒温控制管理系统");
	Show_Str(40,96,RED,WHITE,(u8 *)member2,16,0);
	Show_Str(60,130,LIGHTBLUE,WHITE,(u8 *)"闫鹏",16,0);
	LCD_ShowString(60,150,16,"191360228",0);
//	Show_Str(60,130,LIGHTBLUE,WHITE,(u8 *)"闫鹏，刘良珂",16,0);
//	Show_Str(60,150,LIGHTBLUE,WHITE,(u8 *)"石起超，张玉豪",16,0);
//	Show_Str(60,170,LIGHTBLUE,WHITE,(u8 *)"范培栋，张正金",16,0);
//	Show_Str(60,190,LIGHTBLUE,WHITE,(u8 *)"田柏帆，李伟德",16,0);
}

//下载管脚重映射
void Close_JTAG(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);//完全禁用SWD及JTAG 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);     //禁用JTAG		
}
