/**************************************************************
** Copyright(c) 2016 Smartcar Lab of USTB
** All Rights Reserve
**-------------------------------------------------------------
** MCU         : K66(Freescale)
** Crystal     :
** Module Name : system_init.c
Author         : QI
Date           : 2012.09.11
** Version     : V1.0
** description :
** Notes       :
**-------------------------------------------------------------
** Reversion    :
** Modified By  :
** Modified Date:
** Notes        :
**************************************************************/

#include "common.h"
#include "systeminit.h"

/******************************************************************************/
void system_init(void)
{
    gpio_init();              //I/O��ʼ��
    timer_init();             //��ʱ�жϳ�ʼ��
    Pulse_Counter_Init();  //�����ۼ�ģ���ʼ�����ӱջ���ʹ��
    pwm_init();
    Interrupt_Init();
    uart_init();              //���ڳ�ʼ��
    ADC_Init();
    v_PIDInit();
    CCD_Init();
}
/******************************************************************************/
