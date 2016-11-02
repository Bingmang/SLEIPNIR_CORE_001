/*
* File:	adc.c
* Purpose:	collect ad simple value
*
* Notes:
*/
#include "common.h"
#include "adc.h"

//============================================================================
//�������ƣ�adc_init
//�������أ�
//����˵����
//���ܸ�Ҫ��AD��ʼ��
//============================================================================
void ADC_Init(void)
{
  // open the clock gate
#if(0==ADC_CHANNEL)
  SIM_SCGC6 |= (SIM_SCGC6_ADC0_MASK );
  //#elif(1==SPI_CHANNEL)
#elif(1==ADC_CHANNEL)
  SIM_SCGC3 |= (SIM_SCGC3_ADC1_MASK );
#elif(2==ADC_CHANNEL)
  SIM_SCGC6 |= (SIM_SCGC6_ADC0_MASK );
  SIM_SCGC3 |= (SIM_SCGC3_ADC1_MASK );
#else
#error "Definition of ADC_CHANNEL ERROR ! "
#endif
  
}

//============================================================================
//�������ƣ�ad_once
//�������أ�16λ�޷��ŵ�ADֵ
//����˵����MoudelNumber��ģ���
//               Channel��ͨ����
//              accuracy������
//               ab: 0Ϊaͨ����1Ϊbͨ��
//���ܸ�Ҫ���ɼ�һ��һ·ģ������ADֵ
//============================================================================
uint16 ADC_Once(int MoudelNumber,int Channel,uint8 accuracy,uint8 ab)   //�ɼ�ĳ·ģ������ADֵ
{
  uint16 result = 0;
  uint8 ADCCfg1Mode = 0;
  ADC_MemMapPtr ADCMoudel;    //����ADCģ���ַָ��
  
  switch(accuracy)
  {
  case 8:
    ADCCfg1Mode = 0x00;
    break;
  case 12:
    ADCCfg1Mode = 0x01;
    break;
  case 10:
    ADCCfg1Mode = 0x02;
    break;
  case 16:
    ADCCfg1Mode = 0x03;
    break;
  default:
    ADCCfg1Mode = 0x00;
  }
  if(MoudelNumber==0)         //ѡ��ADCģ��0
  {
    ADCMoudel = ADC0_BASE_PTR;
  }
  else                       //ѡ��ADCģ��1
  {
    ADCMoudel = ADC1_BASE_PTR;
  }
  
  //����������Դģʽ������ʱ�ӣ�����ʱ��4��Ƶ��������ʱ��ʹ�ܣ����þ���
  ADC_CFG1_REG(ADCMoudel) = ADLPC_NORMAL
    | ADC_CFG1_ADIV(ADIV_4)
      | ADLSMP_LONG
        | ADC_CFG1_MODE(ADCCfg1Mode)
          | ADC_CFG1_ADICLK(ADICLK_BUS);
  
  //���ý�ֹ�첽ʱ��ʹ�������ADxxatͨ��ѡ�񣬸������ã�������ʱ��
  if(ab==0)
  {
    ADC_CFG2_REG(ADCMoudel)  =    MUXSEL_ADCA
      | ADACKEN_DISABLED
        | ADHSC_HISPEED
          | ADC_CFG2_ADLSTS(ADLSTS_2) ;
  }
  else
  {
    ADC_CFG2_REG(ADCMoudel)  =    MUXSEL_ADCB
      | ADACKEN_DISABLED
        | ADHSC_HISPEED
          | ADC_CFG2_ADLSTS(ADLSTS_2) ;
  }
  
  //����ͨ����
  //ADC_SC1_REG(ADCMoudel,A) = AIEN_ON |DIFF_DIFFERENTIAL | ADC_SC1_ADCH(Channel);
  ADC_SC1_REG(ADCMoudel,A) = AIEN_ON |DIFF_SINGLE | ADC_SC1_ADCH(Channel);
  //�ȴ�ת�����
  while (( ADC_SC1_REG(ADCMoudel,A) & ADC_SC1_COCO_MASK ) != ADC_SC1_COCO_MASK)
  {
    
  }
  //��ȡת�����
  result = ADC_R_REG(ADCMoudel,A);
  //��ADCת����ɱ�־
  ADC_SC1_REG(ADCMoudel,A) &= ~ADC_SC1_COCO_MASK;
  
  return result;
}
/******************************************************************************/
uint16 Get_AD_Channel(int16 i)
{
  uint16 result=0;
  switch(i)
  {
  case 0:
    result = ADC_Once(1,7,8,0);     //ccd,PTE3,ADC1_SE7a
    break;
    
  default:
    result = 0;
    break;
  }
  return result;
}
