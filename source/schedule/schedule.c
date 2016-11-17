/**************************************************************
** Copyright(c) 2016 Smartcar Lab of USTB
** All Rights Reserve
**-------------------------------------------------------------
** MCU         : K66
** Crystal     :
** Module Name : sensorcollect.c
** Author      : Haoyu Tang
** Date        : 2014.09.21
** Version     : V1.0
** description :
** Notes       :
**-------------------------------------------------------------
** Reversion    : V1.1
** Modified By  : WZY
** Modified Date: 2016.09.19
** Notes        :
**************************************************************/

#include "common.h"
#include "schedule.h"

/******************************************************************************/

/*--------------- V A R I A B L E S ------------------*/
//CCD变量
uint8 middle = 0;

//速控变量
int16 g_motor_set = 0;
int g_speedvalue_temp = 0;      //保存码盘反馈顺时值
int16 g_speed_feedback = 0;      //速度采集
float g_speed_slowdown = 0;
signed int PWM_motor_value = 0;      //电机PWM值
float g_speed = 0;
//舵机变量
int16 g_servo_set = PWM_SVO_MIDDLE;
unsigned int PWM_turn_value = 0;     //转向舵机PWM值
uint8 turn_p = 25;
uint8 turn_d = 40;
unsigned int g_turn = PWM_SVO_MIDDLE;
//上位机调试标记
int g_ccd_sendflag = 0;

//计时
uint16 time=0;


//起跑加速变量
uint8 g_runFaster = 1;
uint8 g_runFasterTime = 0;
uint8 g_gameBegin = 0;
uint16 g_gameBeginTime = 0;
uint8 g_gameEnd = 0;
uint16 g_gameEndTime = 0;

uint8 g_slowdown = 0;
uint16 g_slowdownTime = 0;
/*--------------- F U N C T I O N S ----------------------------------*/

/**************************************************************
Function Name: pit0_isr
Date         : 2016.09.19
Description  :
Input		 : None
Output		 : None
Notes		 : 定时器0中断服务函数
**************************************************************/
void pit0_isr(void)
{
    //clear the interrupt flag to avoid re-entrance
    CLR_FLAG_PIT0();

    //计时重置
    TIME0_RESET();

    //CCD采集
    CCD_Collect(&ccd0);
    middle = CCD_Identify(&ccd0);

    //速度采集
    PULSE_COUNTER_GET(g_speedvalue_temp);       //读取码盘反馈值
    g_speed_feedback =  g_speedvalue_temp;

    //速度控制
    Car_Run();

    //转向控制
    Car_Turn();

    //CCD调试
    g_ccd_sendflag = 1;

	//当游戏开始且过了加速时间，才会开始检测终点 终止时间开始计时（在Car_Run里）(CCDIdentify.c中  当g_gameBegin=1时才会开始检测终点（即两秒后）。
	if (g_gameBegin == 1 && g_runFaster == 0)
	{
		if (g_endleftbreak_num > 2 && g_endrightbreak_num > 2 && g_endmiddlebreak_num>3 )
		{
			g_gameEnd = 1;
		}
	}

	//重置CCD图像识别状态
	g_leftbreak_num = 0;
	g_rightbreak_num = 0;
	g_endleftbreak_num = 0;
	g_endrightbreak_num = 0;
	g_endmiddlebreak_num = 0;

	if (g_gameBegin == 0)				//2000ms后 正常工作 启动部分判定（终点停止判定） 码盘反馈值为0时，重置为未开始状态。
	{
		g_gameBeginTime++;
		if (g_gameBeginTime > 400)		//400
			g_gameBegin = 1;
	}


	if (motorPID.vi_FeedBack == 0)				//码盘反馈值为0时，重置加速、开始状态。
	{
		g_runFaster = 1;
		g_runFasterTime = 0; 
		//g_gameBegin = 0;
		//g_gameBeginTime = 0;
	}

	time++;
}


void Car_Run(void)
{
	motorPID.vi_FeedBack = g_speed_feedback;   //反馈值采样
	g_speed_feedback = 0;     //速度采集清零

	//默认慢速
	if (ABS(g_angerror_temp) < 3)
		g_speed_slowdown = 1;
	else
		g_speed_slowdown = 1.5;
	g_speed = 185 - ABS(g_angerror_temp) * ABS(g_angerror_temp) * g_speed_slowdown;
	if (g_speed < 150)
		g_speed = 150;

	//中速
	if (JM_1 != 0)
	{
		if (ABS(g_angerror_temp) < 5)
			g_speed_slowdown = 1;
		else if (ABS(g_angerror_temp) > 12)
			g_speed_slowdown = 0.4;
		else g_speed_slowdown = 0.85;
		g_speed = 260 - ABS(g_angerror_temp) * ABS(g_angerror_temp) * g_speed_slowdown;
		if (g_speed < 190)
			g_speed = 190;
	}

	//快速
	if (JM_2 != 0)
	{
		if (ABS(g_angerror_temp) < 3)
			g_speed_slowdown = 1;
		else if (ABS(g_angerror_temp) > 13)
			g_speed_slowdown = 1.8;
		else
			g_speed_slowdown = 1.5;
		g_speed = 260 - ABS(g_angerror_temp) * ABS(g_angerror_temp) * g_speed_slowdown;
		if (g_speed < 210)
			g_speed = 210;
	}

	//慢速
	if (JM_1 != 0 && JM_2 != 0)
		g_speed = 170;

	////四号开关启动PID算法
	//if (JM_4 != 0)
	//{
	//	if (ABS(g_angerror_temp) < 3)
	//		g_speed_slowdown = 1;
	//	else
	//		g_speed_slowdown = 1.5;
	//	motorPID.vi_Ref = 200 - ABS(g_angerror_temp) * ABS(g_angerror_temp);// *g_speed_slowdown;
	//	if (g_speed < 175)
	//		g_speed = 175;
	//	g_speed = v_PIDCalc(&motorPID);         //调用电机PID

	//}

	



	//起跑加速
	if (g_runFaster)
	{
		g_speed = 300;     //400
		g_runFasterTime++;
		if (ABS(g_angerror_temp)>3 || g_runFasterTime >120  )			//偏角大于3或加速时间超过500ms则停止加速
			g_runFaster = 0;						//码盘反馈值feedback为0时会重置为1

	}

	if (g_gameBegin == 0)
	{
		g_speed = 0;
	}
	//遇到终点停止
	if (g_gameEnd == 1)
	{
		g_gameEndTime++;
		if (g_gameEndTime > 40)
		{
			g_speed = 0;
		}

	}

	PWM_motor_value = 500 - (int)g_speed;
	SET_PWM_MOT(PWM_motor_value);
}

void Car_Turn(void)
{
    //中值转换为偏离量，方便计算舵机转向
    g_angerror_temp = (middle - g_ccd_middle);

	//如果两边找不到跳变沿，让差角等于上次的角
	if (g_leftbreak_num > 50 && g_rightbreak_num > 50)
	{
		g_angerror_temp = last_g_angerror_temp;
	}

	last_g_angerror_temp = g_angerror_temp;

	//启用拐弯增大拐角,直道减小拐角

	if (JM_3 != 0)
	{
		if (ABS(g_angerror_temp) > 4)
			turn_p = 30;
		else
			turn_p = 5;
	}
	turn_d = turn_p;
	g_turn = (int)(PWM_SVO_MIDDLE - (g_angerror_temp * turn_p)) -((g_angerror_temp - last_g_angerror_temp) *turn_d);

	if (g_turn <= PWM_SVO_MIN)
    {
		g_turn = PWM_SVO_MIN;
    }
	else if (g_turn >= PWM_SVO_MAX)
    {
		g_turn = PWM_SVO_MAX;
    }


	PWM_turn_value = PWM_SVO_MIDDLE * 2 - (int)g_turn;

	if (PWM_turn_value <= PWM_SVO_MIN)
	{
		PWM_turn_value = PWM_SVO_MIN;
	}
	else if (PWM_turn_value >= PWM_SVO_MAX)
	{
		PWM_turn_value = PWM_SVO_MAX; 
	}


	if (g_gameEnd == 1)
		return;
    SET_PWM_SVO(PWM_turn_value);

}
//ccd调试
/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：SendImageData
*  功能说明：
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void SendImageData(char ph[])
{
    unsigned char ccd_data[128];
    unsigned char i;
    unsigned char crc = 0;

    /* Send Data */
    uart_putchar('*');
    uart_putchar('L');
    uart_putchar('D');

    SendHex(0);
    SendHex(0);
    SendHex(0);
    SendHex(0);
    for(i=0; i<128; i++)
    {
      ccd_data[i] = ph[i];
    }
    for(i=0; i<128; i++) {
      SendHex( ccd_data[i]);
    }

    SendHex(crc);
    uart_putchar('#');
}



/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：SendHex
*  功能说明：采集发数程序
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void SendHex(unsigned char hex)
{
    unsigned char temp;
    temp = hex >> 4;
    if(temp < 10) {
      uart_putchar(temp + '0');
    } else {
      uart_putchar(temp - 10 + 'A');
    }
    temp = hex & 0x0F;
    if(temp < 10) {
      uart_putchar(temp + '0');
    } else {
     uart_putchar(temp - 10 + 'A');
    }
}