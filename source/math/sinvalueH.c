/*
** ===================================================================
**  Copyright (c)  Smartcar Lab of USTB
**--------------------------------------------------------------------
**	Module Name: sin_value.c
**	Module Date: 06/27/2008
**	Module Auth: AiN
**  Description: caculation of sin(x) or cos(x) (MC9S08AW60)
 0:1/100:15 sin_10000拟合的函数y=1757*x/1000-196*x*x/10000000
15:1/100:30 sin_10000拟合的函数y=187*x/100-58*x*x/1000000-88
30:1/100:45 sin_10000拟合的函数y=2078*x/1000-93*x*x/1000000-397
45:1/100:60 sin_10000拟合的函数y=232*x/100-12*x*x/100000-940
60:1/100:90 sin_10000拟合的函数y=2637*x/1000-146*(x/3)*(x/3)/111115-1909
**--------------------------------------------------------------------
**  Revision History:
**  Date:		month/day/year
**  Notes:
** ===================================================================
*/

/*--------------- I N C L U D E S ----------------------------------*/
#include "sinvalueH.h"


/*--------------- D E F I N I T I O N ------------------------------*/

/*--------------- M A C R O S --------------------------------------*/

/*--------------- D E C L A R A T I O N ----------------------------*/

/*******************高精度的正弦************************/
signed int sin_value_10000(unsigned long Angle)
{
    long Angle_value = 0;
    if(Angle < 1500)
    {
        Angle_value = 1757 * Angle / 1000 - 196 * Angle * Angle / 10000000;
    }
    else if(Angle < 3000)
    {
        Angle_value = 187 * Angle / 100 - 58 * Angle * Angle / 1000000 - 88;
    }
    else if(Angle < 4500)
    {
        Angle_value = 2078 * Angle / 1000 - 93 * Angle * Angle / 1000000 - 397;
    }
    else if(Angle < 6000)
    {
        Angle_value = 232 * Angle / 100 - 12 * Angle * Angle / 100000 - 940;
    }
    else
    {
        Angle = 9000 - Angle;
        Angle_value = 10000 - 944 * Angle / 100000 - 146 * Angle * Angle / 1000000;
    }
    return Angle_value;
}
signed int sin_10000(signed long Angle)
{
    signed int SinValue = 0;
    while(Angle > 36000)
    {
        Angle = Angle - 36000;
    }
    while(Angle < 0)
    {
        Angle = Angle + 36000;
    }
    if(Angle <= 9000)
    {
        SinValue = sin_value_10000(Angle);
    }
    else if(Angle <= 18000)
    {
        SinValue = 18000 - Angle;
        SinValue = sin_value_10000(SinValue);
    }
    else if(Angle <= 27000)
    {
        SinValue = Angle - 18000;
        SinValue = 0 - sin_value_10000(SinValue);
    }
    else
    {
        SinValue = 36000 - Angle;
        SinValue = 0 - sin_value_10000(SinValue);
    }
    return SinValue;
}
/*******************高精度余弦*********************/
signed int cos_10000(signed long Angle)
{
    signed int CosValue = 0;
    while(Angle > 36000)
    {
        Angle = Angle - 36000;
    }
    while(Angle < 0)
    {
        Angle = Angle + 36000;
    }
    if(Angle <= 9000)
    {
        CosValue = sin_value_10000(9000 - Angle);
    }
    else if(Angle <= 18000)
    {
        CosValue = Angle - 9000;
        CosValue = 0 - sin_value_10000(CosValue);
    }
    else if(Angle <= 27000)
    {
        CosValue = 27000 - Angle;
        CosValue = 0 - sin_value_10000(CosValue);
    }
    else
    {
        CosValue = sin_value_10000(Angle - 27000);
    }
    return CosValue;
}

signed int tan_10000(signed long Angle)
{
    long TanValue;
    if(Angle > 6500) Angle = 6500;
    if(Angle < -6500) Angle = -6500;
    if(Angle == 0)
    {
        TanValue = 0;
    }
    else
    {
        TanValue = 10000L * sin_10000(Angle) / cos_10000(Angle);
    }
    return TanValue;
}
//arccos()函数
//输入（0,10000）
//输出（0,18000）
signed long arccos_10000(signed int value)
{
  int vax,r;
  int down,up,mid;
  
  if(value < cos_10000(17999))
  {
    return 17999;
  }
  else if(value > cos_10000(1))
  {
    return 1;
  }
  
  vax = ABS(value);
  down = 0;
  mid = 9000;
  up = 17999;
  
  while(up >= down)
  {
    if(vax < cos_10000(mid))
    {
      down = mid + 1;
    }
    else
    {
      up = mid - 1;
    }
    mid = (up + down)>>1;
  }
  
  r = (vax - cos_10000(up)) / (cos_10000(down) - cos_10000(up)) + up;
    
  return r;
}

//arcsin()函数
//输入（0,10000）
//输出（-9000,9000）
signed long arcsin_10000(signed int value)
{
  int vax,r;
  int down,up,mid;
  
  if(value < sin_10000(-8999))
  {
    return -8999;
  }
  else if(value > sin_10000(8999))
  {
    return 8999;
  }
  
  vax = ABS(value);
  down = -8999;
  mid = 0;
  up = 8999;
  
  while(up >= down)
  {
    if(vax > sin_10000(mid))
    {
      down = mid + 1;
    }
    else
    {
      up = mid - 1;
    }
    mid = (up + down)>>1;
  }
  
  r = (vax - sin_10000(up)) / (sin_10000(down) - sin_10000(up)) + up;
    
  if(value < 0)
    r = -r;
  
  return r;
}


//cos_f()函数
//输入float
//输出float
float cos_f(float Angle_f)
{
    int Angle =(int)(Angle_f*100);
    float CosValue_f;
    signed int CosValue = 0;
    while(Angle > 36000)
    {
        Angle = Angle - 36000;
    }
    while(Angle < 0)
    {
        Angle = Angle + 36000;
    }
    if(Angle <= 9000)
    {
        CosValue = sin_value_10000(9000 - Angle);
    }
    else if(Angle <= 18000)
    {
        CosValue = Angle - 9000;
        CosValue = 0 - sin_value_10000(CosValue);
    }
    else if(Angle <= 27000)
    {
        CosValue = 27000 - Angle;
        CosValue = 0 - sin_value_10000(CosValue);
    }
    else
    {
        CosValue = sin_value_10000(Angle - 27000);
    }
    CosValue_f =(float) CosValue/10000;
    return CosValue_f;
}


float sin_f(float Angle_f)
{
    int Angle =(int) (Angle_f*100);
    float SinValue_f;
    signed int SinValue = 0;
    while(Angle > 36000)
    {
        Angle = Angle - 36000;
    }
    while(Angle < 0)
    {
        Angle = Angle + 36000;
    }
    if(Angle <= 9000)
    {
        SinValue = sin_value_10000(Angle);
    }
    else if(Angle <= 18000)
    {
        SinValue = 18000 - Angle;
        SinValue = sin_value_10000(SinValue);
    }
    else if(Angle <= 27000)
    {
        SinValue = Angle - 18000;
        SinValue = 0 - sin_value_10000(SinValue);
    }
    else
    {
        SinValue = 36000 - Angle;
        SinValue = 0 - sin_value_10000(SinValue);
    }
    SinValue_f = (float)SinValue/10000;
    return SinValue_f;
}
