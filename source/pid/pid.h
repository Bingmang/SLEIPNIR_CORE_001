/********************************************************************
**	Module Name: PID.h
**	Module Date: 21/09/2014
**	Module Auth: Haoyu Tang
**  Description: caculate PID
**--------------------------------------------------------------------
**  Revision History:
**  Date:		month/day/year
**  Notes:
** ===================================================================
**********************************************************************/
#ifndef __PID_H__
#define __PID_H__

/*********PID参数*********/
/* 电机 */
#define MOTOR_PID_MAX         (500)   //电机PID输出上限
#define MOTOR_PID_MIN         (-500)      //电机PID输出下限
/* 转向 */
#define PWM_SVO_MAX     5000      //舵机左转的最大值4600
#define PWM_SVO_MIN      3000         //舵机右转的最大值3800
#define PWM_SVO_MIDDLE  4200          //舵机中值
#define turn_amplitude  MAX(PWM_SVO_MAX-PWM_SVO_MIDDLE,PWM_SVO_MIDDLE-PWM_SVO_MIN)

#define TURN_PID_MAX         (turn_amplitude)  
#define TURN_PID_MIN         (-turn_amplitude)     

//死区
#define VV_DEADLINE 1	//速度PID，设置死区范围

typedef struct PID			//定义数法核心数据
{
    int32 vi_Ref;		//速度PID，速度设定值
    int32 vi_FeedBack;		//速度PID，速度反馈值


    int32 vi_PreError;	  	//速度PID，前一次，速度误差,,vi_Ref - vi_FeedBack
    int32 vi_PreDerror;	//速度PID，前一次，速度误差之差，d_error-PreDerror;

    float v_Kp;		//速度PID，Ka = Kp
    float v_Ki;		//速度PID，Kb = Kp * ( T / Ti )
    float v_Kd;		//速度PID，

    int32 v_MAX;
    int32 v_MIN;

    int32 vl_PreU;  //控制输出
    int32 motor_PreU;

} PID;

extern PID motorPID;
extern PID turnPID;

//转向参数
extern float g_turn_p;
extern float g_turn_d;
extern float g_turn_i; 

//速度控制参数
extern float g_speed_p;
extern float g_speed_i;
extern float g_speed_d;

extern int v_PIDCalc(PID *pp);
extern void Motor_PIDInit(void);
extern void Turn_PIDInit(void);
extern void v_PIDInit(void);

#endif