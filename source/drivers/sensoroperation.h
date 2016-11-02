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
  int x_simple;    //x�����ֵ
  int y_simple;    //y�����ֵ
  int z_simple;    //z�����ֵ
}Acc_data,*pAcc_data;

typedef struct gyo_data
{
  int g_simple;   //���ٶȲ���ֵ
  int g_angle;    //�����ǽǶ�ֵ
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