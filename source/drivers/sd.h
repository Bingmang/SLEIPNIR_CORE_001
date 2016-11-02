
#ifndef __SDHC_H__
#define __SDHC_H__

/********************************************************************/
#include "common.h"

/********************************************************************/
// Function prototypes
extern void SD_Send(void);
extern void SD_Send_Lcd(void);
extern void Data_Send_To_Buffer(void);

/********************************************************************/
extern unsigned char send_flag;
extern uint16 data_send[2048];

/********************************************************************/
//SD Registers Related.
#define BLOCK_SIZE      (512)
#define SECTORS_PER_PICTURE 5
#define MAX_NUM SECTORS_PER_PICTURE*BLOCK_SIZE*2	//»º³åÊý×é

#define SEND_DATA data_send
#define SEND_LENGTH 2048
#define SEND_DATA_LCD data_lcd
#define SEND_LENGTH_LCD 512

#define START 0
#define STOP  1
/********************************************************************/
#endif /* __SDHC_H__ */
