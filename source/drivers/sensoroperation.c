#include "common.h"

int AD[8];
Acc_data acc;
Gyo_data gyo;

void sensor_init(void)
{
  int i;
  for(i=0;i<8;i++)
    AD[i] = 0;
  
  acc.x_simple = 0;
  acc.y_simple = 0;
  acc.z_simple = 0;  
  
  gyo.g_simple = 0;
  gyo.g_angle = 0;
}

void mag_ad_simple(void)
{
   AD[0] = adc_once(1,15,16,0);
   AD[1] = adc_once(1,14,16,0);
   AD[2] = adc_once(0,13,16,0);
   AD[3] = adc_once(0,12,16,0);
   AD[4] = adc_once(1,5,16,1);
   AD[5] = adc_once(1,4,16,1);
   AD[6] = adc_once(1,7,16,1);
   AD[7] = adc_once(1,6,16,1);
}

void acc_ad_simple(void)
{
  acc.x_simple = adc_once(1,4,16,0);
  acc.y_simple = adc_once(0,7,16,1);
  acc.z_simple = adc_once(0,6,16,1);
}

void gyo_ad_simple(void)
{
  gyo.g_simple = adc_once(1,1,16,0); 
  gyo.g_angle += gyo.g_simple;
}