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

/*********PID����*********/
/* ��� */
#define MOTOR_PID_MAX         (500)   //���PID�������
#define MOTOR_PID_MIN         (-500)      //���PID�������
/* ת�� */
#define PWM_SVO_MAX     5000      //�����ת�����ֵ4600
#define PWM_SVO_MIN      3000         //�����ת�����ֵ3800
#define PWM_SVO_MIDDLE  4200          //�����ֵ
#define turn_amplitude  MAX(PWM_SVO_MAX-PWM_SVO_MIDDLE,PWM_SVO_MIDDLE-PWM_SVO_MIN)

#define TURN_PID_MAX         (turn_amplitude)  
#define TURN_PID_MIN         (-turn_amplitude)     

//����
#define VV_DEADLINE 1	//�ٶ�PID������������Χ

typedef struct PID			//����������������
{
    int32 vi_Ref;		//�ٶ�PID���ٶ��趨ֵ
    int32 vi_FeedBack;		//�ٶ�PID���ٶȷ���ֵ


    int32 vi_PreError;	  	//�ٶ�PID��ǰһ�Σ��ٶ����,,vi_Ref - vi_FeedBack
    int32 vi_PreDerror;	//�ٶ�PID��ǰһ�Σ��ٶ����֮�d_error-PreDerror;

    float v_Kp;		//�ٶ�PID��Ka = Kp
    float v_Ki;		//�ٶ�PID��Kb = Kp * ( T / Ti )
    float v_Kd;		//�ٶ�PID��

    int32 v_MAX;
    int32 v_MIN;

    int32 vl_PreU;  //�������
    int32 motor_PreU;

} PID;

extern PID motorPID;
extern PID turnPID;

//ת�����
extern float g_turn_p;
extern float g_turn_d;
extern float g_turn_i; 

//�ٶȿ��Ʋ���
extern float g_speed_p;
extern float g_speed_i;
extern float g_speed_d;

extern int v_PIDCalc(PID *pp);
extern void Motor_PIDInit(void);
extern void Turn_PIDInit(void);
extern void v_PIDInit(void);

#endif