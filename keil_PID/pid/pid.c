/********************************************
����˵����PID�����㷨
��ע��PID�㷨������ʽ��λ��ʽ����  λ��ʽPIDȱ�㣺
��ǰ����ʱ�̵�������ȥ����״̬�йأ�����ʱҪ������ۼӣ�
�����������׳���
�������������ʽ,��Ҫ�������ֵ

diff_U(t)=Kp[e(t)-e(t-1)]+Ki*e(t)+Kd[[e(t)-e(t-1)]-[e(t-1)-e(t-2)]]
***********************************************/

#include "pid.h"
#include "delay.h"
#include "lcd.h"
#include "Motor.h"

int targetspeed =50;


__PID PID = {25,12,2.5,3,0,0,0};//PID������ʼ��


__Line_Graph graph = {0};//����ͼ������ʼ��

//����ʽPID���ƺ���
//���Σ���ǰֵ
//����ֵ������
int IncPID_Ctrl(int newvalue)
{
	int pErr;
	if(newvalue == 0) return 0;
	pErr = newvalue - PID.SetValue;
	if(PID.cnt < 3)       //�ɼ�ǰ�������
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

//ֱ�����PID���ƺ���
//���Σ���ǰ�ٶ�����ֵ
void DCMotor_PIDControl(int inc)
{
	targetspeed += inc;
	if(targetspeed > MAX_SPEED)	targetspeed = MAX_SPEED;
	if(targetspeed < 0) targetspeed = 0;
	
//	Graph_SetValue(targetspeed);
	//�����ٶ�
	Motor_SetSpeed(targetspeed);
}

////��������ͼ
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

////ɾ������ͼ
//void Graph_Delete(u16 backgroundcolor)
//{
//	LCD_Fill(graph.x0, graph.y0-graph.high-1,graph.x0+graph.width,graph.y0, backgroundcolor);
//	memset(&graph,0,sizeof(graph));
//}


////������ͼ׷������
//void Graph_SetValue(u16 value)
//{
//	if(graph.showflag == 0)	return;
//	//��������ͼ����
//	for(u16 i=0; i<MAX_LINE_DATA-1; i++)
//		graph.linedata[i] = graph.linedata[i+1];
//	graph.linedata[MAX_LINE_DATA-1] = value/(MAX_SPEED/graph.high);	
//}

////��������ͼ�ı���ɫ
//void Graph_SetBackColor(u16 color)
//{
//	graph.backcolor = color;
//}

////��������ͼ������ɫ
//void Graph_SetLineColor(u16 color)
//{
//	graph.linecolor = color;
//}

////��������ͼ��λ�úʹ�С
//void Graph_SetSIZE(int x0, int y0, int width, int high, u16 backgroundcolor)
//{
//	LCD_Fill(graph.x0, graph.y0-graph.high-1,graph.x0+graph.width,graph.y0, backgroundcolor);
//	graph.x0 = x0;
//	graph.y0 = y0;
//	graph.width = width;
//	graph.high = high;
//}

////��������ͼ
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
//	//����PID����
//	LCD_DrawLine(graph.x0, graph.y0, graph.x0, graph.y0-graph.high, BLACK);//y��
//	LCD_DrawLine(graph.x0, graph.y0, graph.x0+graph.width, graph.y0, BLACK);//x��	
//	//��������
//	for(i=0; i<MAX_LINE_DATA-1; i++)
//	{
//		if(graph.y0-graph.linedata[i] >= 0 && graph.y0 - graph.linedata[i+1]>=0)
//		{
//			if(graph.x0+(i+1)*graph.distance_x > graph.x0+graph.width)//�������򲻻�
//				continue;
//			LCD_DrawLine(graph.x0+i*graph.distance_x, graph.y0-graph.linedata[i], graph.x0+(i+1)*graph.distance_x, graph.y0 - graph.linedata[i+1], graph.linecolor);
//		}
//	}
//}




