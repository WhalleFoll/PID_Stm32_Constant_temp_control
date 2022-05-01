#ifndef __LCD_H
#define __LCD_H

#include "stm32f10x.h"

//延时在proteus仿真中必须用nop才准确
#define delay_ms(x)	Delay_nms(x)

#define SPI_CTRL   	  	GPIOB				//定义TFT数据端口
#define SPI_SCLK        GPIO_Pin_13	//PB13--->>TFT --SCL/SCK
#define SPI_MISO        GPIO_Pin_14	
#define SPI_MOSI        GPIO_Pin_15	//PB15 MOSI--->>TFT --SDA/DIN

#define	SPI_MOSI_SET  	SPI_CTRL->BSRR=SPI_MOSI    
#define	SPI_SCLK_SET  	SPI_CTRL->BSRR=SPI_SCLK    

#define	SPI_MOSI_CLR  	SPI_CTRL->BRR=SPI_MOSI    
#define	SPI_SCLK_CLR  	SPI_CTRL->BRR=SPI_SCLK 

#define LCD_TYPE  			GPIOB  		//GPIO组类型
#define LCD_CS   				11       	//片选引脚            PB11
#define LCD_RS   				10       	//寄存器/数据选择引脚 PB10 
#define LCD_RST  				12       	//复位引脚            PB12

#define	LCD_CS_SET  	LCD_TYPE->BSRR=1<<LCD_CS    //片选端口  	PB11
#define	LCD_RS_SET		LCD_TYPE->BSRR=1<<LCD_RS    //数据/命令  PB10	  
#define	LCD_RST_SET		LCD_TYPE->BSRR=1<<LCD_RST   //复位			  PB12
							    
#define	LCD_CS_CLR  	LCD_TYPE->BRR=1<<LCD_CS     //片选端口  	PB11
#define	LCD_RS_CLR		LCD_TYPE->BRR=1<<LCD_RS     //数据/命令  PB10	 
#define	LCD_RST_CLR		LCD_TYPE->BRR=1<<LCD_RST    //复位			  PB12



#define LCD_W 240
#define LCD_H 320
#define USE_HORIZONTAL  	 0//定义液晶屏顺时针旋转方向 	0-0度旋转，1-90度旋转，2-180度旋转，3-270度旋转

extern u16 POINT_COLOR;

//LCD重要参数集
typedef struct  
{										    
	u16 width;			//LCD 宽度
	u16 height;			//LCD 高度
	u16 id;				  //LCD ID
	u8  dir;			  //横屏还是竖屏控制：0，竖屏；1，横屏。	
	u16	 wramcmd;		//开始写gram指令
	u16  setxcmd;		//设置x坐标指令
	u16  setycmd;		//设置y坐标指令	 
}_lcd_dev; 

//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数

//画笔颜色
#define UNKNOWBLUE	0x2D7D		//自己添加的一种蓝色
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
#define BROWN 			0XBC40 //棕色
#define BRRED 			0XFC07 //棕红色
#define GRAY  			0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	0X841F //浅绿色
#define LIGHTGRAY     0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 		0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE      	0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE          0X2B12 //浅棕蓝色(选择条目的反色)


void  SPIv_WriteData(u8 Data);

void LCD_Init(void);//屏幕初始化
void LCD_DisplayOn(void);//开背光
void LCD_DisplayOff(void);
void LCD_Clear(u16 Color);	 //清屏
void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_DrawPoint(u16 x,u16 y);//画点
u16  LCD_ReadPoint(u16 x,u16 y); //读点
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);

u16 LCD_RD_DATA(void);//读取LCD数据									    
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

void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode);//显示汉字，字母
void Paint_Bmp(int x0,int y0,int width,int high,const unsigned char bmp[]);//显示图片




void LCD_ShowString_red(u16 x,u16 y,u8 size,u8 *p,u8 mode);
#endif
