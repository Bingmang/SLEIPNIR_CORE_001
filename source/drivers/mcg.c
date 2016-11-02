/*
* File:    mcg.c
* Purpose: Driver for enabling the PLL in 1 of 6 options
*
* Notes:
* Assumes the MCG mode is in the default FEI mode out of reset
* One of 6 clocking oprions can be selected.
*/
#include "common.h"
#include "mcg.h"

int pll_init(uint8 clk)
{
  int pll_freq;
  
  if (clk!=PLL50 && clk!=PLL100 && clk!=PLL160 && clk!=PLL180 && clk!=PLL200
      && clk!=PLL48 && clk!=PLL96 && clk!=PLL128)
  {return 0;} //return 0 if one of the available options is not selected
  
  //This assumes that the MCG is in default FEI mode out of reset.
  
  // First move to FBE mode
  //    MCG_C2 = 0;
  
  // after initialization of oscillator release latched state of oscillator and GPIO
  //    SIM_SCGC4 |= SIM_SCGC4_LLWU_MASK;
  //    LLWU_CS |= LLWU_CS_ACKISO_MASK;
  
  // Select external oscilator and Reference Divider and clear IREFS to start ext osc
  // CLKS=2, FRDIV=3, IREFS=0, IRCLKEN=0, IREFSTEN=0
  MCG_C2 = MCG_C2_RANGE(1) | MCG_C2_HGO_MASK | MCG_C2_EREFS_MASK; 
  
  MCG_C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(3);
  while (!(MCG_S & MCG_S_OSCINIT0_MASK)){};	//等待锁相环初始化结束  
  
  while (MCG_S & MCG_S_IREFST_MASK){}; // wait for Reference clock Status bit to clear
  
  while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x2){}; // Wait for clock status bits to show clock source is ext ref clk
  
  // Now in FBE
//  if(clk==PLL128 || clk == PLL160 || clk == PLL180 || clk == PLL200)
//    MCG_C5 = MCG_C5_PRDIV(0x01);
//  else
//    MCG_C5 = MCG_C5_PRDIV(0x03);	
  	MCG_C5 = MCG_C5_PRDIV(0);					//分频在8~16MHz之间

  // Ensure MCG_C6 is at the reset default of 0. LOLIE disabled, PLL disabled, clk monitor disabled, PLL VCO divider is clear
//  MCG_C6 = 0x0;
  
  // Select the PLL VCO divider and system clock dividers depending on clocking option
  switch (clk)
  {
  case PLL50:
    // Set system options dividers
    //MCG=PLL, core = MCG, bus = MCG, FlexBus = MCG, Flash clock= MCG/2
    set_sys_dividers(0,0,0,1);
    // Set the VCO divider and enable the PLL for 50MHz, LOLIE=0, PLLS=1, CME=0, VDIV=1
    MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(1); //VDIV = 1 (8x25/4)
    pll_freq = 50;
    break;
  case PLL100:
    // Set system options dividers
    //MCG=PLL, core = MCG, bus = MCG/2, FlexBus = MCG/2, Flash clock= MCG/4
    set_sys_dividers(0,1,1,3);
    // Set the VCO divider and enable the PLL for 100MHz, LOLIE=0, PLLS=1, CME=0, VDIV=26
    MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(26); //VDIV = 26 (8x50/4)
    pll_freq = 100;
    break;
  case PLL160:
    // Set system options dividers
    //MCG=PLL, core = MCG, bus = MCG/2, FlexBus = MCG/2, Flash clock= MCG/5
    set_sys_dividers(0,1,1,4);
    // Set the VCO divider and enable the PLL for 96MHz, LOLIE=0, PLLS=1, CME=0, VDIV=24
    MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(16); //VDIV = 16 (8x40/2)
    pll_freq = 160;
    break;
  case PLL180:
    // Set system options dividers
    //MCG=PLL, core = MCG, bus = MCG/2, FlexBus = MCG/2, Flash clock= MCG/6
    set_sys_dividers(0,1,1,5);
    // Set the VCO divider and enable the PLL for 96MHz, LOLIE=0, PLLS=1, CME=0, VDIV=24
    MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(21); //VDIV = 21 (8x45/2)
    pll_freq = 180;
    break;
  case PLL200:
    // Set system options dividers
    //MCG=PLL, core = MCG, bus = MCG/2, FlexBus = MCG/2, Flash clock= MCG/6
    set_sys_dividers(0,1,1,5);
    // Set the VCO divider and enable the PLL for 96MHz, LOLIE=0, PLLS=1, CME=0, VDIV=24
    MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(26); //VDIV = 26 (8x50/2)
    pll_freq = 200;
    break;
  case PLL48:
    // Set system options dividers
    //MCG=PLL, core = MCG, bus = MCG, FlexBus = MCG, Flash clock= MCG/2
    set_sys_dividers(0,0,0,1);
    // Set the VCO divider and enable the PLL for 48MHz, LOLIE=0, PLLS=1, CME=0, VDIV=0
    MCG_C6 = MCG_C6_PLLS_MASK; //VDIV = 0 (8x24/4)
    pll_freq = 48;
    break;
  case PLL96:
    // Set system options dividers
    //MCG=PLL, core = MCG, bus = MCG/2, FlexBus = MCG/2, Flash clock= MCG/4
    set_sys_dividers(0,1,1,3);
    // Set the VCO divider and enable the PLL for 96MHz, LOLIE=0, PLLS=1, CME=0, VDIV=24
    MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(24); //VDIV = 24 (8x48/4)
    pll_freq = 96;
    break;
  case PLL128:
    // Set system options dividers
    //MCG = PLL, core = MCG, bus = MCG/2, FlexBus = MCG/2, Flash clock= MCG/5
    set_sys_dividers(0,1,1,4);
    // Set the VCO divider and enable the PLL for 96MHz, LOLIE=0, PLLS=1, CME=0, VDIV=24
    MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(0); //VDIV = 0 (8x16/1 = 128)
    pll_freq = 128;
    break;
  }
  while (!(MCG_S & MCG_S_PLLST_MASK)){}; // wait for PLL status bit to set
  
  while (!(MCG_S & MCG_S_LOCK0_MASK)){}; // Wait for LOCK bit to set
  
  // Now running PBE Mode
  
  // Transition into PEE by setting CLKS to 0
  // CLKS=0, FRDIV=3, IREFS=0, IRCLKEN=0, IREFSTEN=0
  MCG_C1 &= ~MCG_C1_CLKS_MASK;
  
  // Wait for clock status bits to update
  while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x3){};
  
  // Now running PEE Mode
  
  return pll_freq;
  
} //pll_init

/*
* This routine must be placed in RAM. It is a workaround for errata e2448.
* Flash prefetch must be disabled when the flash clock divider is changed.
* This cannot be performed while executing out of flash.
* There must be a short delay after the clock dividers are changed before prefetch
* can be re-enabled.
*/
__ramfunc void set_sys_dividers(uint32 outdiv1, uint32 outdiv2, uint32 outdiv3, uint32 outdiv4)
{
  uint32 temp_reg;
  uint8 i;
  
  // store present value of FMC_PFAPR
  temp_reg = FMC_PFAPR; 
  
  // set M0PFD through M7PFD to 1 to disable prefetch
  FMC_PFAPR |= FMC_PFAPR_M7PFD_MASK | FMC_PFAPR_M6PFD_MASK | FMC_PFAPR_M5PFD_MASK
    | FMC_PFAPR_M4PFD_MASK | FMC_PFAPR_M3PFD_MASK | FMC_PFAPR_M2PFD_MASK
      | FMC_PFAPR_M1PFD_MASK | FMC_PFAPR_M0PFD_MASK;
  
  // set clock dividers to desired value
  SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(outdiv1) | SIM_CLKDIV1_OUTDIV2(outdiv2)
    | SIM_CLKDIV1_OUTDIV3(outdiv3) | SIM_CLKDIV1_OUTDIV4(outdiv4);
  
  // wait for dividers to change
  for (i = 0 ; i < outdiv4 ; i++)
  { ; }
  
  // re-store original value of FMC_PFAPR
  FMC_PFAPR = temp_reg;
  
  return;
  
} // set_sys_dividers

/********************************************************************/
void trace_clk_init(void)
{
  /* Set the trace clock to the core clock frequency */
  SIM_SOPT2 |= SIM_SOPT2_TRACECLKSEL_MASK;
  
  /* Enable the TRACE_CLKOUT pin function on PTA6 (alt7 function) */
  PORTA_PCR6 = ( PORT_PCR_MUX(0x7));
}

/********************************************************************/
void fb_clk_init(void)
{
  /* Enable the clock to the FlexBus module */
  SIM_SCGC7 |= SIM_SCGC7_FLEXBUS_MASK;
  
  /* Enable the FB_CLKOUT function on PTC3 (alt5 function) */
  PORTC_PCR3 = ( PORT_PCR_MUX(0x5));
}
/********************************************************************/