/***********************************************************************
**  Copyright (c)  Smartcar Lab of USTB
**----------------------------------------------------------------------
**	Module Name: SD.h
**	Module Date: 11/21/2012                         
**	Module Auth: QI
**  Description: SD 
**							 
**----------------------------------------------------------------------
**  Revision History:
**  Date:		month/day/year    
**  Notes:
***********************************************************************/

#ifndef __SPI_H__
#define __SPI_H__

/************************ I N C L U D E *******************************/
#include "common.h"

/************************** M A C R O S *********************************/
//SPI Registers Related
#define SPI0_CHANNEL     (0) // 0-2
#define SPI0_PTR         SPI0_BASE_PTR  //SPI0_BASE_PTR - SPI2_BASE_PTR

#define SPI0_PCS_PCR     PORTA_PCR14
#define SPI0_PCS_ALTn    (2)
#define SPI0_PCS_NUM     (0) // 0-4

#define SPI0_SIN_PCR     PORTA_PCR17
#define SPI0_SIN_ALTn    (2)
#define SPI0_SOUT_PCR    PORTA_PCR16
#define SPI0_SOUT_ALTn   (2)
#define SPI0_SCK_PCR     PORTA_PCR15
#define SPI0_SCK_ALTn    (2)

#define SPI0_FRAME_SIZE  (15) // SPI_FRAME_SIZE+1 is equal to the number of bits transferred per frame
#define SPI0_TYPE        uint16

//SD Select Related
#define SD_SEND_PIN      (12)
#define SD_SEND_PDOR     GPIOA_PDOR
#define SD_SEND_PDDR     GPIOA_PDDR
#define SD_SEND_PCR      PORTA_PCR12

#define SD_RECEIVE_PIN   (13)
#define SD_RECEIVE_PDIR  GPIOA_PDOR
#define SD_RECEIVE_PDDR  GPIOA_PDDR
#define SD_RECEIVE_PCR   PORTA_PCR13

#define SD_SELECT_HIGH      SET_BIT(SD_SEND_PDOR,SD_SEND_PIN)
#define SD_SELECT_LOW       CLR_BIT(SD_SEND_PDOR,SD_SEND_PIN)
#define SD_RECEIVE_STATUS   BIT_IS_HIGH(SD_RECEIVE_PDIR,SD_RECEIVE_PIN)

#define SD_SELECT        SD_SELECT_HIGH
#define SD_DESELECT      SD_SELECT_LOW

/********************* F U C T I O N S ****************************/
extern void SD_Init(void);
extern void SD_Send_array(SPI0_TYPE *p,int length);
extern void Spi_Init();
#endif