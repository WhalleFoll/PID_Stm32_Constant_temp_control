#ifndef _PID_H_
#define _PID_H_

#include "stm32f10x.h"

#define MAX_SPEED 1000			//最大占空比

#define MAX_LINE_DATA	50			//最大数据数量

/*
	|
	|
	|	high
	|
	|
	|____________________________
x0 y0				width
*/
typedef struct {
	u8 showflag;
	u16 backcolor;
	u16 linecolor;
	int x0;
	int y0;
	int width;
	int high;
	u8 distance_x;//两点之间的x轴距离刻度
	int linedata[MAX_LINE_DATA];//y轴数据
}__Line_Graph;



typedef struct
{
  int SetValue;  //设定目标值
	float P_Value;   //P值---比例
	float I_Value;   //I值---积分
	float D_Value;   //D值---微分
	int LastErr;  //前1拍误差
	int PreErr;   //前两拍误差
	int Dif_U;   //控制量偏差
	u8 cnt;
}__PID;


extern __PID PID;

extern int targetspeed;

int IncPID_Ctrl(int newvalue);
void DCMotor_PIDControl(int inc);

void Graph_Creat(u16 backcolor, u16 linecolor, int x0, int y0, int width, int high, u8 distance_x);
void Graph_Delete(u16 backgroundcolor);
void Draw_Graph(void);
void Graph_SetValue(u16 value);

void Graph_SetBackColor(u16 color);
void Graph_SetLineColor(u16 color);
void Graph_SetSIZE(int x0, int y0, int width, int high, u16 backgroundcolor);
#endif
