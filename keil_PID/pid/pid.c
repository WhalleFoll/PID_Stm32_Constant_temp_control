/********************************************
程序说明：PID控制算法
备注：PID算法有增量式和位置式两种  位置式PID缺点：
当前采样时刻的输出与过去各个状态有关，计算时要对误差累加，
计算量大，且易出错。
本程序采用增量式,需要三个误差值

diff_U(t)=Kp[e(t)-e(t-1)]+Ki*e(t)+Kd[[e(t)-e(t-1)]-[e(t-1)-e(t-2)]]
***********************************************/

#include "pid.h"
#include "delay.h"
#include "lcd.h"
#include "Motor.h"

int targetspeed =50;


__PID PID = {25,12,2.5,3,0,0,0};//PID参数初始化


__Line_Graph graph = {0};//折线图参数初始化

//增量式PID控制函数
//传参：当前值
//返回值：增量
int IncPID_Ctrl(int newvalue)
{
	int pErr;
	if(newvalue == 0) return 0;
	pErr = newvalue - PID.SetValue;
	if(PID.cnt < 3)       //采集前两次误差
	{
	  PID.cnt++;
		goto update;
	}	
	PID.Dif_U = (int)(PID.P_Value * (pErr - PID.LastErr) + PID.I_Value * pErr + PID.D_Value * ((pErr-PID.LastErr)-(PID.LastErr - PID.PreErr)));	
update:
	PID.PreErr = PID.LastErr;
	PID.LastErr = pErr;
	return PID.Dif_U;
}

//直流电机PID控制函数
//传参：当前速度增量值
void DCMotor_PIDControl(int inc)
{
	targetspeed += inc;
	if(targetspeed > MAX_SPEED)	targetspeed = MAX_SPEED;
	if(targetspeed < 0) targetspeed = 0;
	
//	Graph_SetValue(targetspeed);
	//设置速度
	Motor_SetSpeed(targetspeed);
}

////创建折线图
//void Graph_Creat(u16 backcolor, u16 linecolor, int x0, int y0, int width, int high, u8 distance_x)
//{
//	graph.backcolor  = backcolor;
//	graph.linecolor = linecolor;
//	graph.x0 = x0;
//	graph.y0 = y0;
//	graph.width = width;
//	graph.high = high;
//	graph.distance_x = distance_x;
//	graph.showflag = 1;
//}

////删除折线图
//void Graph_Delete(u16 backgroundcolor)
//{
//	LCD_Fill(graph.x0, graph.y0-graph.high-1,graph.x0+graph.width,graph.y0, backgroundcolor);
//	memset(&graph,0,sizeof(graph));
//}


////向折线图追加数据
//void Graph_SetValue(u16 value)
//{
//	if(graph.showflag == 0)	return;
//	//更新折线图数据
//	for(u16 i=0; i<MAX_LINE_DATA-1; i++)
//		graph.linedata[i] = graph.linedata[i+1];
//	graph.linedata[MAX_LINE_DATA-1] = value/(MAX_SPEED/graph.high);	
//}

////设置折线图的背景色
//void Graph_SetBackColor(u16 color)
//{
//	graph.backcolor = color;
//}

////设置折线图折线颜色
//void Graph_SetLineColor(u16 color)
//{
//	graph.linecolor = color;
//}

////设置折线图的位置和大小
//void Graph_SetSIZE(int x0, int y0, int width, int high, u16 backgroundcolor)
//{
//	LCD_Fill(graph.x0, graph.y0-graph.high-1,graph.x0+graph.width,graph.y0, backgroundcolor);
//	graph.x0 = x0;
//	graph.y0 = y0;
//	graph.width = width;
//	graph.high = high;
//}

////绘制折线图
//void Draw_Graph(void)
//{
//	u16 i=0;
//	if(graph.showflag == 0)	
//	{
////		Draw_Text_8_16_Str(10, graph.y0, WHITE, RED, "Please Create Graph!!");
//		return;
//	}
//	if(graph.y0-graph.high < 0 || graph.x0+graph.width > lcddev.width)
//	{
//		Draw_Text_8_16_Str(10, graph.y0, WHITE, RED, "Graph Region Set ERR!!");
//		return;
//	}
//	LCD_Fill(graph.x0, graph.y0-graph.high-1,graph.x0+graph.width,graph.y0, graph.backcolor);
//	//绘制PID坐标
//	LCD_DrawLine(graph.x0, graph.y0, graph.x0, graph.y0-graph.high, BLACK);//y轴
//	LCD_DrawLine(graph.x0, graph.y0, graph.x0+graph.width, graph.y0, BLACK);//x轴	
//	//绘制折线
//	for(i=0; i<MAX_LINE_DATA-1; i++)
//	{
//		if(graph.y0-graph.linedata[i] >= 0 && graph.y0 - graph.linedata[i+1]>=0)
//		{
//			if(graph.x0+(i+1)*graph.distance_x > graph.x0+graph.width)//超过区域不画
//				continue;
//			LCD_DrawLine(graph.x0+i*graph.distance_x, graph.y0-graph.linedata[i], graph.x0+(i+1)*graph.distance_x, graph.y0 - graph.linedata[i+1], graph.linecolor);
//		}
//	}
//}




