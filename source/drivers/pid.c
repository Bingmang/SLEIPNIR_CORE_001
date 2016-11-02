/*
 * File:	pid.c
 * Purpose: 
 *
 * Notes:		
 */
#include "common.h"
#include "pid.h"

/*
function name:  PIDInit
parameters:     none
author:    
date:           2012-6-27
description:    initialize PID values
*/
PID sPID;
PID sPID_1;
PID sPID_2;

void PIDInit(void)          
{	
    sPID.vi_Ref = 0 ;	      	 
    sPID.vi_FeedBack = 0 ;		
            
    sPID.vi_PreError = 0 ;	  	
    sPID.vi_PreDerror = 0 ;	  	
    
    sPID.v_Kp = SPEED_KP;       
    sPID.v_Ki = SPEED_KI;    
    sPID.v_Kd = SPEED_KD;     													 
            
    sPID.vl_PreU = 0;		
  /*********************************************/ 
    sPID_1.vi_Ref = 0 ;	      	 
    sPID_1.vi_FeedBack = 0 ;		
            
    sPID_1.vi_PreError = 0 ;	  	
    sPID_1.vi_PreDerror = 0 ;	  	
    
    sPID_1.v_Kp = SPEED_KP_1;       
    sPID_1.v_Ki = SPEED_KI_1;    
    sPID_1.v_Kd = SPEED_KD_1;     													 
            
    sPID_1.vl_PreU = 0;		
   /*********************************************/   
    sPID_2.vi_Ref = 0 ;	      	 
    sPID_2.vi_FeedBack = 0 ;		
            
    sPID_2.vi_PreError = 0 ;	  	
    sPID_2.vi_PreDerror = 0 ;	  	
    
    sPID_2.v_Kp = SPEED_KP_2;       
    sPID_2.v_Ki = SPEED_KI_2;    
    sPID_2.v_Kd = SPEED_KD_2;     													 
            
    sPID_2.vl_PreU = 0;	
}

/*
function name:  V_PIDCalc
parameters:     none
author:    
date:           2012-6-27
description:    PID control
*/
int16 V_PIDCalc(PID *pp)                        
{    
    int16  error,d_error,dd_error; 
			 
    error = pp->vi_Ref - pp->vi_FeedBack;	        			
    d_error = error - pp->vi_PreError;             
    dd_error = d_error - pp->vi_PreDerror;          
        
    pp->vi_PreError = error;		                     
    pp->vi_PreDerror = d_error;
	
    if( ( error < VV_DEADLINE ) && ( error > -VV_DEADLINE ) )   
    {
        ;             
    }	                                                        
    else								
    { 
        pp->vl_PreU += (pp -> v_Kp * d_error + pp -> v_Ki * error + pp->v_Kd*dd_error); 
    } 
          
    if( pp->vl_PreU >= VV_MAX ) 		
        pp->vl_PreU = VV_MAX;
    else if( pp->vl_PreU <= VV_MIN )	
        pp->vl_PreU = VV_MIN; 	
                                             
     return (pp->vl_PreU);	          
} 

/******************************************************************************/
