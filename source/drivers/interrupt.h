/*
 * File:		interrupt.h
 * Purpose:
 *
 * Notes:
 */

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__
/******************************************************************************/
/* ARM Cortex M4 implementation for interrupt priority shift */
#define ARM_INTERRUPT_LEVEL_BITS    4

/******************************************************************************/
// Define
#define INTERRUPT_PIT0_IRQ      (48) // PIT0

/******************************************************************************/
/* Set Interrupt Vector Table Function Pointers */
#undef  VECTOR_064    //INTERRUPT_PIT0_IRQ + 16   //取消之前的定义
#define VECTOR_064  pit0_isr    //重新定义中断向量表中的PIT Channel 0所对应的中断服务函数的地址

/******************************************************
作者：黄伟波
日期：2014年1月22日
使用说明：需要用到的GPIO中断，请更改中断函数名后，将该部分中断、
          粘贴到interrupt.h并取消注释，中断向量对应的含义查阅K66技术文档
//GPIO模块中断服务定义
#undef  VECTOR_103       //取消之前的定义
#define VECTOR_103  pit0_isr    //重新定义中断向量表中的PORTA所对应的中断服务函数的地址

#undef  VECTOR_104       //取消之前的定义
#define VECTOR_104  pit0_isr    //重新定义中断向量表中的PORTB所对应的中断服务函数的地址

#undef  VECTOR_105       //取消之前的定义
#define VECTOR_105  pit0_isr    //重新定义中断向量表中的PORTC所对应的中断服务函数的地址

#undef  VECTOR_106       //取消之前的定义
#define VECTOR_106  pit0_isr    //重新定义中断向量表中的PORTD所对应的中断服务函数的地址

#undef  VECTOR_107       //取消之前的定义
#define VECTOR_107  pit0_isr    //重新定义中断向量表中的PORTE所对应的中断服务函数的地址

......
......
******************************************************/
// Function prototypes
void Enable_irq(int);
void Disable_irq(int);
void Set_irq_Priority(int, int);
void Interrupt_Init(void);

/******************************************************************************/
#endif /* __INTERRUPT_H__ */