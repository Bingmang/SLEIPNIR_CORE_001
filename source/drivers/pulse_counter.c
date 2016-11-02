/*
 * File:	pulse_counter.c
 * Purpose:	pulse counter initialization
 *
 * Notes:
 */
#include "common.h"
#include "pulse_counter.h"

/******************************************************************************/
void Pulse_Counter_Init(void)
{
    // open the clock gate to the FTM1 module
#if(0 == PULSE_COUNTER_FTM)
    SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;
#elif(1 == PULSE_COUNTER_FTM)
    SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;
#elif(2 == PULSE_COUNTER_FTM)
    SIM_SCGC6 |= SIM_SCGC6_FTM2_MASK;
#else
#error "Definition PULSE_COUNTER_FTM ERROR ! "
#endif

    // Write protection is disabled, FTM enabale
    FTM_MODE_REG(PULSE_COUNTER_PTR) = 0 | FTM_MODE_WPDIS_MASK | FTM_MODE_FTMEN_MASK;

    // counter initialization value is 0
    FTM_CNTIN_REG(PULSE_COUNTER_PTR) = 0UL;

    // clear counter£¬write any value to CNT register
    FTM_CNT_REG(PULSE_COUNTER_PTR) = 0UL;

    // max modulo value, 65535
    FTM_MOD_REG(PULSE_COUNTER_PTR) = FTM_MOD_MOD(0xffff);

    // External clock, Divide by 2
    FTM_SC_REG(PULSE_COUNTER_PTR) = 0 | FTM_SC_CLKS(3)|FTM_SC_PS(1);

    FTM_QDCTRL_REG(PULSE_COUNTER_PTR) = 0|FTM_QDCTRL_QUADEN_MASK|FTM_QDCTRL_PHAFLTREN_MASK|FTM_QDCTRL_PHBFLTREN_MASK;

    FTM_FILTER_REG(PULSE_COUNTER_PTR) = 0|FTM_FILTER_CH0FVAL(15)|FTM_FILTER_CH1FVAL(15);

        // PORT
    PULSE_COUNTER_QDA_PCR = 0 | PORT_PCR_MUX(PULSE_COUNTER_ALTn);
    PULSE_COUNTER_QDB_PCR = 0 | PORT_PCR_MUX(PULSE_COUNTER_ALTn);

}

/******************************************************************************/