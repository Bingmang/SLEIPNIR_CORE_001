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
//CCD����
uint8 middle = 0;

//�ٿر���
int16 g_motor_set = 0;
int g_speedvalue_temp = 0;      //�������̷���˳ʱֵ
int16 g_speed_feedback = 0;      //�ٶȲɼ�
float g_speed_slowdown = 0;
signed int PWM_motor_value = 0;      //���PWMֵ
float g_speed = 0;
//�������
int16 g_servo_set = PWM_SVO_MIDDLE;
unsigned int PWM_turn_value = 0;     //ת����PWMֵ
uint8 turn_p = 25;
uint8 turn_d = 40;
unsigned int g_turn = PWM_SVO_MIDDLE;
//��λ�����Ա��
int g_ccd_sendflag = 0;

//��ʱ
uint16 time=0;


//���ܼ��ٱ���
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
Notes		 : ��ʱ��0�жϷ�����
**************************************************************/
void pit0_isr(void)
{
    //clear the interrupt flag to avoid re-entrance
    CLR_FLAG_PIT0();

    //��ʱ����
    TIME0_RESET();

    //CCD�ɼ�
    CCD_Collect(&ccd0);
    middle = CCD_Identify(&ccd0);

    //�ٶȲɼ�
    PULSE_COUNTER_GET(g_speedvalue_temp);       //��ȡ���̷���ֵ
    g_speed_feedback =  g_speedvalue_temp;

    //�ٶȿ���
    Car_Run();

    //ת�����
    Car_Turn();

    //CCD����
    g_ccd_sendflag = 1;

	//����Ϸ��ʼ�ҹ��˼���ʱ�䣬�ŻῪʼ����յ� ��ֹʱ�俪ʼ��ʱ����Car_Run�(CCDIdentify.c��  ��g_gameBegin=1ʱ�ŻῪʼ����յ㣨������󣩡�
	if (g_gameBegin == 1 && g_runFaster == 0)
	{
		if (g_endleftbreak_num > 2 && g_endrightbreak_num > 2 && g_endmiddlebreak_num>3 )
		{
			g_gameEnd = 1;
		}
	}

	//����CCDͼ��ʶ��״̬
	g_leftbreak_num = 0;
	g_rightbreak_num = 0;
	g_endleftbreak_num = 0;
	g_endrightbreak_num = 0;
	g_endmiddlebreak_num = 0;

	if (g_gameBegin == 0)				//2000ms�� �������� ���������ж����յ�ֹͣ�ж��� ���̷���ֵΪ0ʱ������Ϊδ��ʼ״̬��
	{
		g_gameBeginTime++;
		if (g_gameBeginTime > 400)		//400
			g_gameBegin = 1;
	}


	if (motorPID.vi_FeedBack == 0)				//���̷���ֵΪ0ʱ�����ü��١���ʼ״̬��
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
	motorPID.vi_FeedBack = g_speed_feedback;   //����ֵ����
	g_speed_feedback = 0;     //�ٶȲɼ�����

	//Ĭ������
	if (ABS(g_angerror_temp) < 3)
		g_speed_slowdown = 1;
	else
		g_speed_slowdown = 1.5;
	g_speed = 185 - ABS(g_angerror_temp) * ABS(g_angerror_temp) * g_speed_slowdown;
	if (g_speed < 150)
		g_speed = 150;

	//����
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

	//����
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

	//����
	if (JM_1 != 0 && JM_2 != 0)
		g_speed = 170;

	////�ĺſ�������PID�㷨
	//if (JM_4 != 0)
	//{
	//	if (ABS(g_angerror_temp) < 3)
	//		g_speed_slowdown = 1;
	//	else
	//		g_speed_slowdown = 1.5;
	//	motorPID.vi_Ref = 200 - ABS(g_angerror_temp) * ABS(g_angerror_temp);// *g_speed_slowdown;
	//	if (g_speed < 175)
	//		g_speed = 175;
	//	g_speed = v_PIDCalc(&motorPID);         //���õ��PID

	//}

	



	//���ܼ���
	if (g_runFaster)
	{
		g_speed = 300;     //400
		g_runFasterTime++;
		if (ABS(g_angerror_temp)>3 || g_runFasterTime >120  )			//ƫ�Ǵ���3�����ʱ�䳬��500ms��ֹͣ����
			g_runFaster = 0;						//���̷���ֵfeedbackΪ0ʱ������Ϊ1

	}

	if (g_gameBegin == 0)
	{
		g_speed = 0;
	}
	//�����յ�ֹͣ
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
    //��ֵת��Ϊƫ���������������ת��
    g_angerror_temp = (middle - g_ccd_middle);

	//��������Ҳ��������أ��ò�ǵ����ϴεĽ�
	if (g_leftbreak_num > 50 && g_rightbreak_num > 50)
	{
		g_angerror_temp = last_g_angerror_temp;
	}

	last_g_angerror_temp = g_angerror_temp;

	//���ù�������ս�,ֱ����С�ս�

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
//ccd����
/*************************************************************************
*                           ������ӹ�����
*
*  �������ƣ�SendImageData
*  ����˵����
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
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
*                           ������ӹ�����
*
*  �������ƣ�SendHex
*  ����˵�����ɼ���������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
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