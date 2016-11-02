 /*
 * File:        common.h
 * Purpose:     File to be included by all project files
 *
 * Notes:
 */

#ifndef __COMMON_H__
#define __COMMON_H__

/******************************************************************************/
#define DEBUG
#define DEBUG_PRINT

/*
 * Conditional compilation config
 */
#define PRINT_EN    0   // function printf()

/*
 * Config Defines
 */
#define CORE_CLK_MHZ    PLL128      // 50,100,160,180,200,48,96,ÄÚºËÊ±ÖÓ
#define UART_BAUD       (115200/2)      // UART baud rate

#define   SetBit(reg,bit)		    reg |= (1 << bit)
#define   ClrBit(reg,bit)		    reg &= ~(1 << bit)

/*
 * Defines used as function
 */
#define Delay_T3_uS(n)  {TIME3_RESET();while(TIME3_GET_uS()<=n);}
#define Delay_T3_mS(n)  {TIME3_RESET();while(TIME3_GET_uS()<=n*1000);}

#define  Delay_ms(n)    Delay_T3_mS(n)
#define  Delay_us(n)    Delay_T3_uS(n)

/*
 * Include the cpu specific header file
 */

#include<freescale/MK66F18.h>
#include<c/intrinsics.h>

/*
 * Include the generic CPU header file
 */
#include "clkinit.h"
#include "core.h"
#include "start.h"
#include "vectors.h"

/*
 * Include drivers utilities
 */
#include "gpio.h"
#include "interrupt.h"
#include "mcg.h"
#include "pulse_counter.h"
#include "pwm.h"
#include "timer.h"
#include "wdog.h"
#include "adc.h"
#include "spi.h"
#include "sd.h"
#include "i2c.h"
#include "uart.h"

#if(1==PRINT_EN)
    #include "print.h"
#endif // #if(1==PRINT_EN)

#include "../schedule/schedule.h"
#include "../systeminit/systeminit.h"
#include "../pid/pid.h"
#include "../ccdcollect/ccdcollect.h"
#include "../ccdidentify/ccdidentify.h"
#include "../keyboard/keyboard.h"
#include "../math/math.h"

extern uint8 g_switch1;
extern uint8 g_switch2;
extern uint8 g_switch3;
extern uint8 g_switch4;

/******************************************************************************/

#endif /* __COMMON_H__ */
