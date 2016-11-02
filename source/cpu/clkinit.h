/*
 * File:        clkinit.h
 * Purpose:     Kinetis Configuration
 *              Initializes processor to a default clock state
 *
 * Notes:
 *
 */

#ifndef __CLKINIT_H__
#define __CLKINIT_H__

/******************************************************************************/
//extern
extern int g_core_clk_khz;
extern int g_core_clk_mhz;
extern int g_periph_clk_khz;
extern int g_periph_clk_mhz;

/******************************************************************************/
// function prototypes
void clkinit(void);

/******************************************************************************/
#endif /* __CLKINIT_H__ */
