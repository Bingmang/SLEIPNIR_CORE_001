/**************************************************************
** Copyright(c) 2016 Smartcar Lab of USTB
** All Rights Reserve
**-------------------------------------------------------------
** MCU         : K66(Freescale)
** Crystal     :
** Module Name : main
Author         : Haoyu Tang
Date           : 2014.09.22
** Version     : V1.0
** description : �ƺ�������
** Notes       :
**-------------------------------------------------------------
** Reversion    : V2.0
** Modified By  : ����Խ
** Modified Date: 2016.09.19
** Notes        :
**************************************************************/

#include "common.h"

/*--------------------M A C R O S--------------------*/

/*-----------------V A R I A B L E S-----------------*/
void main(void)
{
    DisableInterrupts;  //����һ��ʼ��Ҫ�ر������жϣ���ֹ��Ƭ����ʼ�������б�ĳ���жϴ��
    
    system_init();      //ϵͳ��ʼ��
    Delay_ms(60);

    EnableInterrupts;   //���жϣ���ʱ���жϿ�ʼ����


    /*-----------------���������ȷѭ���׶�-----------------*/

    for( ; ; )
    {
      //SET_PWM_MOT(300);       //TEST
      
      //�˴�Ϊ���뿪�غ�LED��IO���Գ��򣬿��Ը����Լ�����Ҫ�����޸ĺ͵���      
      JM_1 = SWITCH1_STATUS;
      JM_2 = SWITCH2_STATUS;
      JM_3 = SWITCH3_STATUS;
      JM_4 = SWITCH4_STATUS;
      if(JM_1==0)
      {        
        LED0_OFF();
      }
      else
      {
        LED0_ON();
      }
      if(JM_2==0)
      {        
        LED1_OFF();
      }
      else
      {
        LED1_ON();
      }
      if(JM_3==0)
      {        
        LED2_OFF();
      }
      else
      {
        LED2_ON();
      }
      if(JM_4==0)
      {        
        LED3_OFF();
      }
      else
      {
        LED3_ON();
      }
      //IO test end
      
      if(g_ccd_sendflag==1)
      {
        g_ccd_sendflag = 0;
        SendImageData(ccd0.graph);
      }
    }
}