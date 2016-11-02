/******************************************************************************
** Module Name : gpio.c
** Author      : 吴子越
** Date        : 2016.9.19
** Version     : V3.0
** description :
** Notes       :
**-------------------------------------------------------------
** Reversion    :
** Modified By  :
** Modified Date:
** Notes: I/O初始化首先要根据K66技术手册第184页的管脚功能表格配置相应功能，例如
管脚的第一功能为I/O，因此下面的初始化中会有PORT_PCR_MUX里的参数为1，代
表第一功能。之后要根据实际需要配置其为输入或者输出状态，若为输人，则通
过BIT_IS_HIGH检测其输入电平是否为高，返回1为高，相反为低；若为输出，则
通过SET_BIT或者CLR_BIT控制其输入高电平或者低电平
*****************************************************************************/

#include "common.h"
#include "gpio.h"

//拨码开关状态变量
uint8 JM_1;
uint8 JM_2;
uint8 JM_3;
uint8 JM_4;

void gpio_init(void)
{
  //拨码开关初始化，输入
  SWITCH1_PCR = (0 | PORT_PCR_MUX(1));
  SWITCH2_PCR = (0 | PORT_PCR_MUX(1));
  SWITCH3_PCR = (0 | PORT_PCR_MUX(1));
  SWITCH4_PCR = (0 | PORT_PCR_MUX(1));
  
  CLR_BIT(SWITCH1_PDDR, SWITCH1_PIN);
  CLR_BIT(SWITCH2_PDDR, SWITCH2_PIN);
  CLR_BIT(SWITCH3_PDDR, SWITCH3_PIN);
  CLR_BIT(SWITCH4_PDDR, SWITCH4_PIN);
  
  //键盘INT管脚初始化，输入
  ZLG7290_INT_PCR = (0 | PORT_PCR_MUX(1));
  
  CLR_BIT(ZLG7290_INT_PDDR,ZLG7290_INT_PIN);
  
  //CCD设置该口为GPIO
  CCD_0_SI_PCR = (0 | PORT_PCR_MUX(1));
  CCD_0_CLK_PCR = (0 | PORT_PCR_MUX(1));
  
  //CCD的SI和CLK，输出
  SET_BIT(CCD_0_SI_DDR, CCD_0_SI_PIN);        //CCD_0 的SI管脚，输出
  SET_BIT(CCD_0_CLK_DDR, CCD_0_CLK_PIN);      //CCD_0 的CLK管脚，输出
  
  //LED指示灯初始化，输出
  LED0_PCR = (0 | PORT_PCR_MUX(1));
  LED1_PCR = (0 | PORT_PCR_MUX(1));
  LED2_PCR = (0 | PORT_PCR_MUX(1));
  LED3_PCR = (0 | PORT_PCR_MUX(1));
  
  SET_BIT(LED0_PDDR, LED0_PIN);
  SET_BIT(LED1_PDDR, LED1_PIN);
  SET_BIT(LED2_PDDR, LED2_PIN);
  SET_BIT(LED3_PDDR, LED3_PIN);
}


/******************************************************************************/

