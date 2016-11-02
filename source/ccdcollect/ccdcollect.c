/**************************************************************
** Copyright(c) 2016 Smartcar Lab of USTB
** All Rights Reserve
**-------------------------------------------------------------
** MCU         : K66
** Crystal     : 16MHz
** Module Name : ccdcollect.c
** Author      : ���Ʒ�
** Date        : 2013.01.25
** Version     : V1.0
** description :
** Notes       :
**-------------------------------------------------------------
** Reversion    : V1.1
** Modified By  : ����Խ
** Modified Date: 2016.09.19
** Notes        :
**************************************************************/

#include "common.h"
#include "ccdcollect.h"

/******************************************************************************/

/*--------------- V A R I A B L E S ------------------*/
CCD_data ccd0;

/*--------------- F U N C T I O N S ----------------------------------*/

/**************************************************************
Function Name  : CCD_collect
Date           : 2013.01.25
Description    :
Input	       : None
Output         : None
Notes	       :
˵��           :��Ҫ�� SI �����ߵ�ƽ 20ns ������� 1 �� CLK �źţ�����ÿ
                �� CLK �źŵ��½���ʱ�ɼ� AO ���ŵ�����ĵ�ѹֵ���ڲɼ�
                �� 128 �����غ󣬻��������ɵ� 129 ��CLK�źŽ������βɼ���
**************************************************************/
void CCD_Collect(CCD_data *ccd)
{
  asm("nop");
  
  CCD_SI_LOW(ccd->id);
  asm("nop");
  
  CCD_SI_HIGH(ccd->id);            /* SI �ߵ�ƽ */
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  
  CCD_CLK_HIGH(ccd->id);           /* CLK �ߵ�ƽ */
  asm("nop");
  
  CCD_SI_LOW(ccd->id);            /* SI  �͵�ƽ */
  asm("nop");
  
  ccd->graph[0]=Get_AD_Channel(ccd->id);
  
  CCD_CLK_LOW(ccd->id);           /* CLK = 0 */
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");
  asm("nop");

  for(int i=1; i<19; i++)
  {
    asm("nop");
    asm("nop");
    CCD_CLK_HIGH(ccd->id);
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    ccd->graph[i] =  Get_AD_Channel(ccd->id);
    CCD_CLK_LOW(ccd->id);
  }
  
  asm("nop");
  
  for(int i=19; i<GRAPH_WIDTH; i++)
  {
    asm("nop");
    asm("nop");
    CCD_CLK_HIGH(ccd->id);       /* CLK �ߵ�ƽ */
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    ccd->graph[i] =  Get_AD_Channel(ccd->id);
    CCD_CLK_LOW(ccd->id);        /* CLK �͵�ƽ */
  }

    asm("nop");
    asm("nop");
    CCD_CLK_HIGH(ccd->id);           /* CLK �ߵ�ƽ */
    asm("nop");
    asm("nop");
    CCD_CLK_LOW(ccd->id);           /* CLK �͵�ƽ */
    asm("nop");
}

//CCDֵ��ʼ��
void CCD_Init(void)
{
  ccd0.id = 0;
}


