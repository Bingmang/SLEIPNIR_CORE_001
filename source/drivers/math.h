/*
 * File:	math.h
 * Purpose:	mathematica function 
 *
 * Notes:		
 */

#ifndef __MATH_H__
#define __MATH_H__

/******************************************************************************/

#undef PI 
#define PI      (3.14159265359)
/******************************************************************************/
int32 Triangle_C(int32 a,int32 b);
uint16 Sqrt32(uint32 x);
uint8 Sqrt16(uint16 x);
float Arctan(float x);
float Sin(float x);
float Pow_Double(float x,uint16 n);
uint32 Pow_Uint32(uint32 x,uint16 n);
float Tan(float x);
/******************************************************************************/
#endif /* __MATH_H__ */