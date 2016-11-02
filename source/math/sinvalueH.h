/***********************************************************************
**  Copyright (c)  Smartcar Lab of USTB
**----------------------------------------------------------------------
**	Module Name: sin_value.h
**	Module Date: April 30,2009                         
**	Module Auth: AiN
**  Description: System_Init 
**							 
**----------------------------------------------------------------------
**  Revision History:
**  Date:		month/day/year    
**  Notes:
***********************************************************************/
#ifndef __SINVALUEH_H__
#define __SINVALUEH_H__

/*--------------- I N C L U D E S ----------------------------------*/
#include "common.h"
/*--------------- D E F I N I T I O N ------------------------------*/

/*--------------- M A C R O S --------------------------------------*/

/*--------------- D E C L A R A T I O N ----------------------------*/

signed int tan_10000(signed long Angle);
signed int sin_10000(signed long Angle);
signed int cos_10000(signed long Angle);
signed long arccos_10000(signed int value);
signed long arcsin_10000(signed int value);
float cos_f(float);
float sin_f(float);
#endif