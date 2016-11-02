/*
 * File:	timer.c
 * Purpose:
 *
 * Notes:
 */

#include "common.h"
#include "timer.h"
/******************************************************************************/
void timer_init(void)
{
    //open the clock gate to make the PIT work
    SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;

    //turn on PIT
    PIT_MCR = 0x00;

    // Timer 0
    PIT_LDVAL0 = interrupt_time * g_periph_clk_khz; //  T=5ms
                               // g_periph_clk_mhz is calculated in the start.c
    PIT_TCTRL0 = 0x00;
    PIT_TCTRL0 = 0x03; // enable Timer 0 interrupts
    PIT_TFLG0 |= PIT_TFLG_TIF_MASK;
    
    // Timer 2
    PIT_LDVAL2 = 0xFFFFFFE0; // setup timer 2 for the maximum cycles
    PIT_TCTRL2 = 0x00; // disable Timer 2 interrupts

    // Timer 3
    PIT_LDVAL3 = 0xFFFFFFE0; // setup timer 3 for the maximum cycles
    PIT_TCTRL3 = 0x00; // disable Timer 3 interrupts

}

/******************************************************************************/
