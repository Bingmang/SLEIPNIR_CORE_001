/*
 * File:	pwm.h
 * Purpose:	pwm to contrl motor and servo
 *
 * Notes:
 */

#ifndef __PWM_H__
#define __PWM_H__

/*--------------M A C R O S -----------------*/
//#define RUDDER_MIDDLE_TURN 3200
//#define TURN_MAX 800

/*---------- V A R I A B L E S --------------*/
extern unsigned int PWM_turn_value;
extern signed int PWM_motor_value;

/******************************************************************************/
// 电机
#define PWM_MOT_PCR     PORTB_PCR1      // FTM1_CH1
#define PWM_MOT_ALTn    (3)             // 0-7
#define PWM_MOT_PTR     FTM1_BASE_PTR   // FTM0_BASE_PTR - FTM2_BASE_PTR
#define PWM_MOT_FTM     (1)             // 0-2
#define PWM_MOT_CHANNEL (1)             // when PWM_MOT_FTM=0 0-7, else 0-1
#define MOTOR_FULL_DUTY 1000          //电机PWM频率16KHz

//转向舵机
#define PWM_SVO_PCR     PORTD_PCR4      //FTM0_CH4
#define PWM_SVO_ALTn    (4)             // 0-7
#define PWM_SVO_PTR     FTM0_BASE_PTR   // FTM0_BASE_PTR - FTM2_BASE_PTR
#define PWM_SVO_FTM     (0)             // 0-2
#define PWM_SVO_CHANNEL (4)             // when PWM_SVO_FTM=0 0-7, else 0-1
#define TURN_SVO_FULL_DUTY 12500        //产生160Hz的PWM波

//改变PWM占空比
//注意，在此版最简主板中，所有PWM输出均经过了74LVC14反向器，占空比为x/MOTOR_FULL_DUTY

#define SET_PWM_MOT(x) \
       {FTM_CnV_REG(PWM_MOT_PTR,PWM_MOT_CHANNEL) = (ABS(x)) & 0xffff;\
         FTM_PWMLOAD_REG(PWM_MOT_PTR) |= FTM_PWMLOAD_LDOK_MASK;}

        //0<x<10000
#define SET_PWM_SVO(x) \
       {FTM_CnV_REG(PWM_SVO_PTR,PWM_SVO_CHANNEL) = (TURN_SVO_FULL_DUTY - MAX(PWM_SVO_MIN,MIN(x,PWM_SVO_MAX))) & 0xffff;\
        FTM_PWMLOAD_REG(PWM_SVO_PTR) |= FTM_PWMLOAD_LDOK_MASK;}


// Function prototypes
void pwm_init(void);
void pwm_motor_init(void);
void pwm_servo_init(void);

/******************************************************************************/
#endif /* __PWM_H__ */
