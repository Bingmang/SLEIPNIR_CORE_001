/*
 * File:	pid.h
 * Purpose:	pid control 
 *
 * Notes:		
 */

#ifndef __PID_H__
#define __PID_H__

/******************************************************************************/
#define VV_MAX 30000 		 //�ٶ�PID���������ֵ
#define VV_MIN -30000 	    	 //�ٶ�PID��������Сֵ
#define VV_DEADLINE 0	         //�ٶ�PID������������Χ

#define SPEED_KP      3           //�������ϵ��
#define SPEED_KI      0            //�������ϵ��
#define SPEED_KD      2            //����΢��ϵ��

#define SPEED_KP_1    15           //�������ϵ��
#define SPEED_KI_1    5            //�������ϵ��
#define SPEED_KD_1    0            //����΢��ϵ��

#define SPEED_KP_2    15           //�������ϵ��
#define SPEED_KI_2    5            //�������ϵ��
#define SPEED_KD_2    0            //����΢��ϵ��

//struct
typedef struct PID			
{
	int16 vi_Ref;	         //�ٶ�PID���ٶ��趨ֵ
	int16 vi_FeedBack;       //�ٶ�PID���ٶȷ���ֵ
        int16 vi_PreError;	 //�ٶ�PID���ٶ����,vi_Ref - vi_FeedBack
	int16 vi_PreDerror;	 //�ٶ�PID��ǰһ�Σ��ٶ����֮�d_error-PreDerror;
	int16 v_Kp;		 //����ϵ����Kp = Kp
	int16 v_Ki;		 //����ϵ����Ki = Kp * ( T / Ti )
	int16 v_Kd;		 //΢��ϵ����Kd = KP * Td * T
	int16 vl_PreU;		 //PID���ֵ
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