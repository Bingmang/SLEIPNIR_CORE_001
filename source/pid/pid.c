/**************************************************************
** Copyright(c) 2011~2012 Smartcar Lab of USTB
** All Rights Reserve
**-------------------------------------------------------------
** MCU         : k60
** Crystal     :
** Module Name : pid.c
** Author      : QI
** Date        : 2012.09.11
** Version     : v1.0
** description :
** Notes       :
**-------------------------------------------------------------
** Reversion    :
** Modified By  :
** Modified Date:
** Notes        :
**************************************************************/

#include "common.h"
#include "pid.h"

int VV_MAX;  //PID输出上限
int VV_MIN;  //PID输出下限
float g_turn_p = 0;
float g_turn_d = 0;
float g_turn_i = 0; 
float g_speed_p = 18;
float g_speed_i = 4;
float g_speed_d = 1;


PID motorPID;
PID turnPID;

void v_PIDInit(void)
{
  Motor_PIDInit();
  Turn_PIDInit();
}

//电机PID初始化
void Motor_PIDInit (void)
{
    motorPID.vi_Ref = 0;	      	//速度设定值
    motorPID.vi_FeedBack = 0;		//速度反馈值

    motorPID.vi_PreError = 0 ;	  	//前一次，速度误差,,vi_Ref - vi_FeedBack
    motorPID.vi_PreDerror = 0 ;	  	//前一次，速度误差之差，d_error-PreDerror;

    motorPID.v_Kp = g_speed_p;
    motorPID.v_Ki = g_speed_i;
    motorPID.v_Kd = g_speed_d;

    motorPID.v_MAX = MOTOR_PID_MAX;
    motorPID.v_MIN = MOTOR_PID_MIN;

    motorPID.motor_PreU = 0;		//电机控制输出值
}

//转向PID初始化
void Turn_PIDInit(void)
{
    turnPID.vi_Ref = 0;         //转向初始化为中值
    turnPID.vi_FeedBack = 0;

    turnPID.vi_PreError = 0 ;	  	//前一次，速度误差,,vi_Ref - vi_FeedBack
    turnPID.vi_PreDerror = 0 ;	  	//前一次，速度误差之差，d_error-PreDerror;

    turnPID.v_Kp = g_turn_p;
    turnPID.v_Ki = g_turn_i;
    turnPID.v_Kd = g_turn_d;

    turnPID.v_MAX = TURN_PID_MAX;
    turnPID.v_MIN = TURN_PID_MIN;

    turnPID.motor_PreU = 0;	//舵机控制输出值
}


//PID 核心算法
int v_PIDCalc( PID *pp )
{
    int  error,d_error,dd_error;

    error = (int)(pp->vi_Ref) - ABS((int)(pp->vi_FeedBack));	// 偏差计算
    d_error = error - (int)(pp->vi_PreError);
    dd_error = d_error - (int)pp->vi_PreDerror;

    pp->vi_PreError = error;		//存储当前偏差
    pp->vi_PreDerror = d_error;

    pp->motor_PreU +=  (int)(pp -> v_Kp * d_error + pp -> v_Ki * error+ pp->v_Kd*dd_error)/10;

    if( pp->motor_PreU >= pp->v_MAX ) 		//速度PID，防止调节最高溢出
    {
         pp->motor_PreU = pp->v_MAX ;
    }
    else if( pp->motor_PreU <= pp->v_MIN)	//速度PID，防止调节最低溢出
    {
         pp->motor_PreU = pp->v_MIN;
    }

    return (ABS(pp->motor_PreU));		// 返回预调节占空比
}
