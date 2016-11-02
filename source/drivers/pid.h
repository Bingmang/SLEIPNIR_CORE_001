/*
 * File:	pid.h
 * Purpose:	pid control 
 *
 * Notes:		
 */

#ifndef __PID_H__
#define __PID_H__

/******************************************************************************/
#define VV_MAX 30000 		 //速度PID，调节最大值
#define VV_MIN -30000 	    	 //速度PID，调节最小值
#define VV_DEADLINE 0	         //速度PID，设置死区范围

#define SPEED_KP      3           //定义比例系数
#define SPEED_KI      0            //定义积分系数
#define SPEED_KD      2            //定义微分系数

#define SPEED_KP_1    15           //定义比例系数
#define SPEED_KI_1    5            //定义积分系数
#define SPEED_KD_1    0            //定义微分系数

#define SPEED_KP_2    15           //定义比例系数
#define SPEED_KI_2    5            //定义积分系数
#define SPEED_KD_2    0            //定义微分系数

//struct
typedef struct PID			
{
	int16 vi_Ref;	         //速度PID，速度设定值
	int16 vi_FeedBack;       //速度PID，速度反馈值
        int16 vi_PreError;	 //速度PID，速度误差,vi_Ref - vi_FeedBack
	int16 vi_PreDerror;	 //速度PID，前一次，速度误差之差，d_error-PreDerror;
	int16 v_Kp;		 //比例系数，Kp = Kp
	int16 v_Ki;		 //积分系数，Ki = Kp * ( T / Ti )
	int16 v_Kd;		 //微分系数，Kd = KP * Td * T
	int16 vl_PreU;		 //PID输出值
}PID;
// Function prototypes
void PIDInit(void);  
int16 V_PIDCalc(PID *pp);

//extern
extern PID sPID;
extern PID sPID_1;
extern PID sPID_2;
/******************************************************************************/
#endif /* __SCHEDULE_H__ */