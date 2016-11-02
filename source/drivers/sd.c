
#include "sd.h"

uint16 data_send[2048] = {1};
uint16 data_lcd[512]={1};
unsigned char send_flag = STOP;
int sdcount = 0;
/***********************************************************************
Function Name:SD_Send                   
Author:  cxd                                                                         
NOTES:   SPI0 Initialized used as SD communication.                                                       
***********************************************************************/
void  SD_Send(void)
{
     if((SD_RECEIVE_STATUS==0)&&(send_flag == START))
    {
        SD_SELECT; 
       // Delay_T3_uS(20);
          SD_Send_array(SEND_DATA,SEND_LENGTH);
          send_flag = STOP;
        SD_DESELECT; 
    }
    else
    {
        SD_DESELECT;
    }
}

void  SD_Send_Lcd(void)
{
     if((SD_RECEIVE_STATUS==0)&&(send_flag == START))
    {
        SD_SELECT; 
        Delay_T3_uS(20);
          SD_Send_array(SEND_DATA_LCD,SEND_LENGTH_LCD);
          send_flag = STOP;
        SD_DESELECT; 
    }
    else
    {
        SD_DESELECT;
    }
}

/******************************************************************************/
void Data_Send_To_Buffer(void)
{
    int i = 0;
    
    //起始位
    data_send[0+512*sdcount] = 0xAA;
    data_send[1+512*sdcount] = 0xBB;
    data_send[2+512*sdcount] = 0xCC;
    data_send[3+512*sdcount] = 0xDD;

//    data_send[9+512*sdcount] = 0x10;
//    data_send[13+512*sdcount] = 0x14;
    //CCD
    for(i=4; i<132; i++)
    {
      data_send[i+512*sdcount] = ccd0.graph[i-4];
    }  
  
    data_send[132+512*sdcount] = (char) left_toggle_point;
    data_send[133+512*sdcount] = (char) right_toggle_point;
    data_send[134+512*sdcount] = (char) middle;
    //data_send[135+512*sdcount] = (char) white_point_counter;
    
    //MOTOR
    data_send[136+512*sdcount] = i;
    data_send[137+512*sdcount] = i >> 8;
    data_send[138+512*sdcount] = i >> 16;
    data_send[139+512*sdcount] = i >> 24;

//    data_send[140+512*sdcount] = motorPID.vi_FeedBack;
//    data_send[141+512*sdcount] = motorPID.vi_FeedBack >> 8;
//    data_send[142+512*sdcount] = motorPID.vi_FeedBack >> 16;
//    data_send[143+512*sdcount] = motorPID.vi_FeedBack >> 24;
//
//    data_send[144+512*sdcount] = motorPID.vi_PreError;
//    data_send[145+512*sdcount] = motorPID.vi_PreError >> 8;
//    data_send[146+512*sdcount] = motorPID.vi_PreError >> 16;
//    data_send[147+512*sdcount] = motorPID.vi_PreError >> 24;
//
//    data_send[148+512*sdcount] = motorPID.vi_PreDerror;
//    data_send[149+512*sdcount] = motorPID.vi_PreDerror >> 8;
//    data_send[150+512*sdcount] = motorPID.vi_PreDerror >> 16;
//    data_send[151+512*sdcount] = motorPID.vi_PreDerror >> 24;

    //data_send[152+512*sdcount] = motorPID.v_Kp;
    //data_send[153+512*sdcount] = motorPID.v_Kp >> 8;
    
    //data_send[154+512*sdcount] = motorPID.v_Ki;
    //data_send[155+512*sdcount] = motorPID.v_Ki >> 8;
    
    //data_send[156+512*sdcount] = motorPID.v_Kd;
    //data_send[157+512*sdcount] = motorPID.v_Kd >> 8;
    
  
    //SPEED
//    data_send[158+512*sdcount] = (char) g_speed_counter;
//
    data_send[159+512*sdcount] = g_speedvalue_temp;
    data_send[160+512*sdcount] = g_speedvalue_temp >> 8;
//    
//    data_send[161+512*sdcount] = g_speed_feedback;
//    data_send[162+512*sdcount] = g_speed_feedback >> 8;
// 
//    data_send[163+512*sdcount] = g_angerror_temp;
//    data_send[164+512*sdcount] = g_angerror_temp >> 8;
//
//    data_send[165+512*sdcount] = g_motor_set;
//    data_send[166+512*sdcount] = g_motor_set >> 8;
//
//    data_send[167+512*sdcount] = slow_down_rate;
//    data_send[168+512*sdcount] = slow_down_rate >> 8;
//
    data_send[169+512*sdcount] = PWM_motor_value;
    data_send[170+512*sdcount] = PWM_motor_value >> 8;
    
    
    //TURN
    //data_send[171+512*sdcount] = (char) turn_p;

    data_send[172+512*sdcount] = PWM_turn_value;
    data_send[173+512*sdcount] = PWM_turn_value >> 8;
    
    //POSITION
//    data_send[174+512*sdcount] = Position_X;
//    data_send[175+512*sdcount] = Position_X >> 8;
//    data_send[176+512*sdcount] = Position_X >> 16;
//    data_send[177+512*sdcount] = Position_X >> 24;
//    
//    data_send[178+512*sdcount] = Position_Y;
//    data_send[179+512*sdcount] = Position_Y >> 8;
//    data_send[180+512*sdcount] = Position_X >> 16;
//    data_send[181+512*sdcount] = Position_X >> 24;


    //中止位    
    data_send[511+512*sdcount] = 0xFF;
    
    sdcount++;
    if(sdcount>=4)
    {
        sdcount=0;
        send_flag = START;
    }
    
}