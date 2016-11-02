/*
 * File:	keyboard.h
 * Purpose:	keyboard ZLG7290
 *
 * Notes:
 */

#ifndef __ZLG7290_H__
#define __ZLG7290_H__

/******************************************************************************/
/* ----------------------------V A R I A B L E--------------------------------*/
extern unsigned int Stop_Mode;
extern unsigned int Stop_Time;
extern unsigned int Stop_Distance;
extern unsigned char keyboardsign;

/* ----------------------------F U N C T I O N--------------------------------*/
// Function prototypes
void ZLG7290DisplayData(unsigned int data, unsigned char bit);
void ZLG7290UpDisplayData(uint32 data,uint8 bit);
void ZLG7290DownDisplayData(uint32 data,uint8 bit);
float ZLG7290GetKeyAndDisplay(unsigned char bit);
uint16 ZLG7290GetKeyDisplay(void);
void ZLG7290ClearAll(void);
// ²ßÂÔ
extern void Choice(void);
// Definition

/******************************************************************************/

#endif /* __KEYBOARD_H__ */
