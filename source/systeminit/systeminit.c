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
    gpio_init();              //I/O初始化
    timer_init();             //定时中断初始化
    Pulse_Counter_Init();  //脉冲累加模块初始化，加闭环后使用
    pwm_init();
    Interrupt_Init();
    uart_init();              //串口初始化
    ADC_Init();
    v_PIDInit();
    CCD_Init();
}
/******************************************************************************/
