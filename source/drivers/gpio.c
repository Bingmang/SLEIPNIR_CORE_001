/******************************************************************************
** Module Name : gpio.c
** Author      : ����Խ
** Date        : 2016.9.19
** Version     : V3.0
** description :
** Notes       :
**-------------------------------------------------------------
** Reversion    :
** Modified By  :
** Modified Date:
** Notes: I/O��ʼ������Ҫ����K66�����ֲ��184ҳ�ĹܽŹ��ܱ��������Ӧ���ܣ�����
�ܽŵĵ�һ����ΪI/O���������ĳ�ʼ���л���PORT_PCR_MUX��Ĳ���Ϊ1����
���һ���ܡ�֮��Ҫ����ʵ����Ҫ������Ϊ����������״̬����Ϊ���ˣ���ͨ
��BIT_IS_HIGH����������ƽ�Ƿ�Ϊ�ߣ�����1Ϊ�ߣ��෴Ϊ�ͣ���Ϊ�������
ͨ��SET_BIT����CLR_BIT����������ߵ�ƽ���ߵ͵�ƽ
*****************************************************************************/

#include "common.h"
#include "gpio.h"

//���뿪��״̬����
uint8 JM_1;
uint8 JM_2;
uint8 JM_3;
uint8 JM_4;

void gpio_init(void)
{
  //���뿪�س�ʼ��������
  SWITCH1_PCR = (0 | PORT_PCR_MUX(1));
  SWITCH2_PCR = (0 | PORT_PCR_MUX(1));
  SWITCH3_PCR = (0 | PORT_PCR_MUX(1));
  SWITCH4_PCR = (0 | PORT_PCR_MUX(1));
  
  CLR_BIT(SWITCH1_PDDR, SWITCH1_PIN);
  CLR_BIT(SWITCH2_PDDR, SWITCH2_PIN);
  CLR_BIT(SWITCH3_PDDR, SWITCH3_PIN);
  CLR_BIT(SWITCH4_PDDR, SWITCH4_PIN);
  
  //����INT�ܽų�ʼ��������
  ZLG7290_INT_PCR = (0 | PORT_PCR_MUX(1));
  
  CLR_BIT(ZLG7290_INT_PDDR,ZLG7290_INT_PIN);
  
  //CCD���øÿ�ΪGPIO
  CCD_0_SI_PCR = (0 | PORT_PCR_MUX(1));
  CCD_0_CLK_PCR = (0 | PORT_PCR_MUX(1));
  
  //CCD��SI��CLK�����
  SET_BIT(CCD_0_SI_DDR, CCD_0_SI_PIN);        //CCD_0 ��SI�ܽţ����
  SET_BIT(CCD_0_CLK_DDR, CCD_0_CLK_PIN);      //CCD_0 ��CLK�ܽţ����
  
  //LEDָʾ�Ƴ�ʼ�������
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

