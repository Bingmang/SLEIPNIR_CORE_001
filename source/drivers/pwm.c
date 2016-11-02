/*******************************************************************************
* File:	pwm.c
* Purpose: PWM initialization
*
* Notes: 注意，在此版最简主板中，所有PWM输出均经过了74HC14反向器，即配置输
         出PWM占空比为20%，实际上作用到器件上的占空比为80%，使用时注意换算。
*******************************************************************************/
#include "common.h"
#include "pwm.h"

void pwm_init(void)
{
  pwm_servo_init();
  pwm_motor_init();
}

/******************************************************************************/
void pwm_motor_init(void)       // motor
{
  // FTM1_CH1
#if(0 == PWM_MOT_FTM)
  SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;
#elif(1 == PWM_MOT_FTM)
  SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;           // open the clock gate to the FTM1 module
#elif(2 == PWM_MOT_FTM)
  SIM_SCGC3 |= SIM_SCGC3_FTM2_MASK;
#else
#error "Definition PWM_MOT_FTM ERROR ! "
#endif
  
  FTM_CnSC_REG(PWM_MOT_PTR,0) = 0UL;                  // disable the channel
  FTM_CnSC_REG(PWM_MOT_PTR,1) = 0UL;
  
  FTM_MODE_REG(PWM_MOT_PTR) = 0|FTM_MODE_WPDIS_MASK;  // Write protection is disabled
  FTM_SC_REG(PWM_MOT_PTR) = 0UL;                      // clear first
  FTM_CNTIN_REG(PWM_MOT_PTR) = 0UL;                   // counter initialization value is 0
  FTM_CNT_REG(PWM_MOT_PTR) = 0UL;
     
  FTM_MOD_REG(PWM_MOT_PTR) = FTM_MOD_MOD(MOTOR_FULL_DUTY);            // Modulo value is 1000 to make the frequency 16kHz
  FTM_CnSC_REG(PWM_MOT_PTR,PWM_MOT_CHANNEL) = FTM_CnSC_ELSB_MASK|FTM_CnSC_MSB_MASK;           // Edge-aligned PWM
  FTM_CnV_REG(PWM_MOT_PTR,PWM_MOT_CHANNEL) = 0UL;          // Set up channel value register
  
  PWM_MOT_PCR = 0 | PORT_PCR_MUX(PWM_MOT_ALTn);       // set PTB1 to ALT3, route the desired signal to the pin
  
  FTM_SC_REG(PWM_MOT_PTR) = FTM_SC_CLKS(1)|FTM_SC_PS(2);      // System/bus clock, Divide by ___   = ____KHz
  
  // set initialization of PWM to the motor
  SET_PWM_MOT(0);
} // pwm_motor_init

void pwm_servo_init(void)       //servo
{
  //FTM0_CH4
#if(0 == PWM_SVO_FTM)
  SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;   // open the clock gate to the FTM0 module
#elif(1 == PWM_SVO_FTM)
  SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;
#elif(2 == PWM_SVO_FTM)
  SIM_SCGC3 |= SIM_SCGC3_FTM2_MASK;
#else
#error "Definition PWM_SVO_FTM ERROR ! "
#endif
  
  FTM_MODE_REG(PWM_SVO_PTR) = 0|FTM_MODE_WPDIS_MASK; // Write protection is disabled
  FTM_SC_REG(PWM_SVO_PTR) = 0UL;
  FTM_CNTIN_REG(PWM_SVO_PTR) = 0UL;  // counter initialization value is 0
  FTM_CNT_REG(PWM_SVO_PTR) = 0UL;     //  write any value to CNT register
  
  FTM_CnSC_REG(PWM_SVO_PTR,0) = 0UL;  // disable the channel
  FTM_CnSC_REG(PWM_SVO_PTR,1) = 0UL;
  
  FTM_MOD_REG(PWM_SVO_PTR) = FTM_MOD_MOD(TURN_SVO_FULL_DUTY);         // Modulo value is 12500 to make the frequency 160Hz

  FTM_CnSC_REG(PWM_SVO_PTR,PWM_SVO_CHANNEL) = FTM_CnSC_ELSB_MASK|FTM_CnSC_MSB_MASK;   // Edge-aligned PWM
  FTM_CnV_REG(PWM_SVO_PTR,PWM_SVO_CHANNEL) = 0UL;  // Set up channel value register
  
  PWM_SVO_PCR = 0 | PORT_PCR_MUX(PWM_SVO_ALTn);       // set PTD4 to ALT4, route the desired signal to the pin
  
  FTM_SC_REG(PWM_SVO_PTR) = FTM_SC_CLKS(1)|FTM_SC_PS(5);      // System/bus clock, Divide by ___ = ____MHz 
  
  SET_PWM_SVO(PWM_SVO_MIDDLE); // set initialization of PWM to the servo
} // pwm_servo_init

/******************************************************************************/