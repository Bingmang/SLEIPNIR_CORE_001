/*
 * File:	pulse_counter.h
 * Purpose:	pulse counter
 *
 * Notes:
 */

#ifndef __PULSE_COUNTER_H__
#define __PULSE_COUNTER_H__

/********************************************************************/
//Definition

//±àÂëÆ÷½Ó¿Ú
#define PULSE_COUNTER_FTM       (2)
#define PULSE_COUNTER_PTR       FTM2_BASE_PTR

#define PULSE_COUNTER_QDA_PCR   PORTB_PCR18
#define PULSE_COUNTER_QDB_PCR   PORTB_PCR19
#define PULSE_COUNTER_ALTn      (6)


/********************************************************************/
// interface
#define PULSE_COUNTER_GET(x) \
       {x = (int16)FTM_CNT_REG(PULSE_COUNTER_PTR); \
        FTM_CNT_REG(PULSE_COUNTER_PTR) = 0;}            // Any write to CNT resets the FTM counter to the value in the CNTIN register.

/********************************************************************/
// Function prototypes
void Pulse_Counter_Init(void);


/********************************************************************/
#endif /* __PULSE_COUNTER_H__ */
