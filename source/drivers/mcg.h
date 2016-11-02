/*
 * File:    pll_init.h
 * Purpose: pll_driver specific declarations
 *
 * Notes:
 */
#ifndef __MCG_H__
#define __MCG_H__
/********************************************************************/

/* For some reason CW needs to have cw.h explicitly included here for
 * the code relocation of set_sys_dividers() to work correctly even
 * though common.h should pull in cw.h.
 */

int pll_init(uint8 clk);
__ramfunc void set_sys_dividers(uint32 outdiv1, uint32 outdiv2, uint32 outdiv3, uint32 outdiv4);
void trace_clk_init(void);
void fb_clk_init(void);

enum clk_option
{
    PLL50 =0,
    PLL100=1,
    PLL160=2,
    PLL180=3,
    PLL200=4,
    
    PLL48 =5,
    PLL96 =6,
    PLL128=7
};

/********************************************************************/
#endif /* __MCG_H__ */
