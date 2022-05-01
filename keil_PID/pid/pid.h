#ifndef _PID_H_
#define _PID_H_

#include "stm32f10x.h"

#define MAX_SPEED 1000			//���ռ�ձ�

#define MAX_LINE_DATA	50			//�����������

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
	u8 distance_x;//����֮���x�����̶�
	int linedata[MAX_LINE_DATA];//y������
}__Line_Graph;



typedef struct
{
  int SetValue;  //�趨Ŀ��ֵ
	float P_Value;   //Pֵ---����
	float I_Value;   //Iֵ---����
	float D_Value;   //Dֵ---΢��
	int LastErr;  //ǰ1�����
	int PreErr;   //ǰ�������
	int Dif_U;   //������ƫ��
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
