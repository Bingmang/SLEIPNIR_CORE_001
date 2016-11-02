/*
 * File:	sensoroperation.h
 * Purpose:	sensoroperation 
 *
 * Notes:		
 */

#ifndef __SENSOROPERATION_H__
#define __SENSOROPERATION_H__

/******************************************************************************/

typedef struct acc_data
{
  int x_simple;    //x轴采样值
  int y_simple;    //y轴采样值
  int z_simple;    //z轴采样值
}Acc_data,*pAcc_data;

typedef struct gyo_data
{
  int g_simple;   //角速度采样值
  int g_angle;    //陀螺仪角度值
}Gyo_data,*pGyo_data;
// Function prototypes

void sensor_init(void);
void mag_ad_simple(void);
void acc_ad_simple(void);
void gyo_ad_simple(void);

extern int AD[8];
extern Acc_data acc;
extern Gyo_data gyo;

/******************************************************************************/
#endif /* __SENSOROPERATION_H__ */