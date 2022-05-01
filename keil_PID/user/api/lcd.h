#ifndef __LCD_H
#define __LCD_H

#include "stm32f10x.h"

//��ʱ��proteus�����б�����nop��׼ȷ
#define delay_ms(x)	Delay_nms(x)

#define SPI_CTRL   	  	GPIOB				//����TFT���ݶ˿�
#define SPI_SCLK        GPIO_Pin_13	//PB13--->>TFT --SCL/SCK
#define SPI_MISO        GPIO_Pin_14	
#define SPI_MOSI        GPIO_Pin_15	//PB15 MOSI--->>TFT --SDA/DIN

#define	SPI_MOSI_SET  	SPI_CTRL->BSRR=SPI_MOSI    
#define	SPI_SCLK_SET  	SPI_CTRL->BSRR=SPI_SCLK    

#define	SPI_MOSI_CLR  	SPI_CTRL->BRR=SPI_MOSI    
#define	SPI_SCLK_CLR  	SPI_CTRL->BRR=SPI_SCLK 

#define LCD_TYPE  			GPIOB  		//GPIO������
#define LCD_CS   				11       	//Ƭѡ����            PB11
#define LCD_RS   				10       	//�Ĵ���/����ѡ������ PB10 
#define LCD_RST  				12       	//��λ����            PB12

#define	LCD_CS_SET  	LCD_TYPE->BSRR=1<<LCD_CS    //Ƭѡ�˿�  	PB11
#define	LCD_RS_SET		LCD_TYPE->BSRR=1<<LCD_RS    //����/����  PB10	  
#define	LCD_RST_SET		LCD_TYPE->BSRR=1<<LCD_RST   //��λ			  PB12
							    
#define	LCD_CS_CLR  	LCD_TYPE->BRR=1<<LCD_CS     //Ƭѡ�˿�  	PB11
#define	LCD_RS_CLR		LCD_TYPE->BRR=1<<LCD_RS     //����/����  PB10	 
#define	LCD_RST_CLR		LCD_TYPE->BRR=1<<LCD_RST    //��λ			  PB12



#define LCD_W 240
#define LCD_H 320
#define USE_HORIZONTAL  	 0//����Һ����˳ʱ����ת���� 	0-0����ת��1-90����ת��2-180����ת��3-270����ת

extern u16 POINT_COLOR;

//LCD��Ҫ������
typedef struct  
{										    
	u16 width;			//LCD ���
	u16 height;			//LCD �߶�
	u16 id;				  //LCD ID
	u8  dir;			  //���������������ƣ�0��������1��������	
	u16	 wramcmd;		//��ʼдgramָ��
	u16  setxcmd;		//����x����ָ��
	u16  setycmd;		//����y����ָ��	 
}_lcd_dev; 

//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����

//������ɫ
#define UNKNOWBLUE	0x2D7D		//�Լ���ӵ�һ����ɫ
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0XBC40 //��ɫ
#define BRRED 			0XFC07 //�غ�ɫ
#define GRAY  			0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	0X841F //ǳ��ɫ
#define LIGHTGRAY     0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 		0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE      	0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE          0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)


void  SPIv_WriteData(u8 Data);

void LCD_Init(void);//��Ļ��ʼ��
void LCD_DisplayOn(void);//������
void LCD_DisplayOff(void);
void LCD_Clear(u16 Color);	 //����
void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_DrawPoint(u16 x,u16 y);//����
u16  LCD_ReadPoint(u16 x,u16 y); //����
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);

u16 LCD_RD_DATA(void);//��ȡLCD����									    
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
void LCD_WR_DATA(u8 data);
u16 LCD_ReadReg(u8 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
u16 LCD_ReadRAM(void);		   
u16 LCD_BGR2RGB(u16 c);
void LCD_SetParam(void);
void Lcd_WriteData_16Bit(u16 Data);
void LCD_direction(u8 direction );

void GUI_DrawPoint(u16 x,u16 y,u16 color);
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);
void Draw_Circle(u16 x0,u16 y0,u16 fc,u8 r);
void Draw_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2);
void Fill_Triangel(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2);
void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size,u8 mode);
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);
void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len,u8 size,u8 mode);
void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p,u8 mode);
void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);
void GUI_DrawFont24(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);
void GUI_DrawFont32(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);
void gui_circle(int xc, int yc,u16 c,int r, int fill);
void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode);
void LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2);

void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode);//��ʾ���֣���ĸ
void Paint_Bmp(int x0,int y0,int width,int high,const unsigned char bmp[]);//��ʾͼƬ




void LCD_ShowString_red(u16 x,u16 y,u8 size,u8 *p,u8 mode);
#endif
