/***********************************************************************
**  Copyright (c)  Smartcar Lab of USTB
**----------------------------------------------------------------------
**	Module Name: SD.c
**	Module Date: 11/21/2012                         
**	Module Auth: QI
**  Description: SD 
**							 
**----------------------------------------------------------------------
**  Revision History:
**  Date:		month/day/year    
**  Notes:
***********************************************************************/
#include "spi.h"

/***********************************************************************
Function Name:SD_Init                   
Author:  QI                                                                          
NOTES:   SPI0 Initialized used as SD communication.                                                       
***********************************************************************/
void SD_Init(void)
{
    // port init
    SPI0_SOUT_PCR = PORT_PCR_MUX(SPI0_SOUT_ALTn);
    SPI0_SCK_PCR = PORT_PCR_MUX(SPI0_SCK_ALTn);
    SPI0_SIN_PCR = PORT_PCR_MUX(SPI0_SIN_ALTn);
    
    SD_SEND_PCR = (0 | PORT_PCR_MUX(1));
    SET_BIT(SD_SEND_PDDR,SD_SEND_PIN);
        
    SD_RECEIVE_PCR = (0 | PORT_PCR_MUX(1));
    CLR_BIT(SD_RECEIVE_PDDR,SD_RECEIVE_PIN);
 
    // open the clock gate of SPI
    SIM_SCGC6 |= SIM_SCGC6_DSPI0_MASK;

    // Module Configuration Register
    SPI_MCR_REG(SPI0_PTR) = SPI_MCR_MSTR_MASK        //Initiated as master mode.
                         | SPI_MCR_DCONF(0x00)      //SPI mode.
                         | SPI_MCR_PCSIS(0x01)      //PCx high is inactive.
                         | SPI_MCR_HALT_MASK        //Stop for the time being.
                         | SPI_MCR_SMPL_PT(2);      //two system clocks between SCK and SIN.
    
    // Flushes the TX FIFO, Flushes the RX FIFO
    SPI_MCR_REG(SPI0_PTR) |= SPI_MCR_CLR_TXF_MASK   
                          | SPI_MCR_CLR_RXF_MASK;  
    
    //COUNT REGISTER
    SPI_TCR_REG(SPI0_PTR) = 0;
    
    // Frame Size and baud rate
    SPI_CTAR_REG(SPI0_PTR,0) = SPI_CTAR_FMSZ(SPI0_FRAME_SIZE)        //16 bits per frame.
                            | SPI_CTAR_DBR_MASK|SPI_CTAR_CSSCK(7)   //delay between SCK and PCS.
                            | SPI_CTAR_CPOL_MASK|SPI_CTAR_PBR(3)    //Baud rate dividor is 7.
                            | SPI_CTAR_CPHA_MASK                    //inactive level is high.
                            | SPI_CTAR_PASC(3);                     //SCK Duty cycle is 66/33.
    
    
    SPI_CTAR_REG(SPI0_PTR,1) =  SPI_CTAR_FMSZ(SPI0_FRAME_SIZE) \
                            | SPI_CTAR_DBR_MASK|SPI_CTAR_CSSCK(7) \
                            | SPI_CTAR_CPOL_MASK |SPI_CTAR_PBR(3) \
                            | SPI_CTAR_CPHA_MASK \
                            | SPI_CTAR_PASC(3);
    
    SPI_PUSHR_REG(SPI0_PTR) |=SPI_PUSHR_CONT_MASK;
      
    // clear all flag
    SPI_SR_REG(SPI0_PTR) = 0xffff0000UL;
    
    // close all interrupt
    SPI_RSER_REG(SPI0_PTR) = 0x00UL;\
    
    // start DSPI transfers
    SPI_MCR_REG(SPI0_PTR) &= ~SPI_MCR_HALT_MASK;
    
    //SD_SELECT;
}

/******************************************************************************/
/*****按数组发送****/
void SD_Send_array(SPI0_TYPE *p,int length)
{   
    static uint32 command = SPI_PUSHR_CTAS(0)|SPI_PUSHR_PCS(SPI0_PCS_NUM);
    
    // Flushes the TX FIFO, Flushes the RX FIFO
    SPI_MCR_REG(SPI0_PTR) |= SPI_MCR_CLR_TXF_MASK
                          | SPI_MCR_CLR_RXF_MASK;
    
    SPI_SR_REG(SPI0_PTR) = 0xffff0000UL;// clear all flag

    while(length-->0)
    {
         while(!(SPI_SR_REG(SPI0_PTR)&SPI_SR_TFFF_MASK));//SPI_SR_TFFF_MASK
         if(length>0)
           SPI_PUSHR_REG(SPI0_PTR) = command | *p++;
         else
           SPI_PUSHR_REG(SPI0_PTR) = command | *p++ | SPI_PUSHR_EOQ_MASK;
         SPI_SR_REG(SPI0_PTR) |= SPI_SR_TFFF_MASK;
    }
}

/******************************************************************************/
void Spi_Init(void)
{
    // port init
    SPI0_PCS_PCR = PORT_PCR_MUX(SPI0_PCS_ALTn);
    SPI0_SOUT_PCR = PORT_PCR_MUX(SPI0_SOUT_ALTn);
    SPI0_SCK_PCR = PORT_PCR_MUX(SPI0_SCK_ALTn);
    SPI0_SIN_PCR = PORT_PCR_MUX(SPI0_SIN_ALTn);
    
    //spi初始化
    SD_SEND_PCR = (0 | PORT_PCR_MUX(1)); 
    SET_BIT(SD_SEND_PDDR,SD_SEND_PIN);
    SD_RECEIVE_PCR = (0 | PORT_PCR_MUX(1));
    CLR_BIT(SD_RECEIVE_PDDR,SD_RECEIVE_PIN);
    
    // open the clock gate of spi
#if(0==SPI0_CHANNEL)
    SIM_SCGC6 |= SIM_SCGC6_DSPI0_MASK;
#elif(1==SPI0_CHANNEL)
    SIM_SCGC6 |= SIM_SCGC6_SPI1_MASK;
#elif(2==SPI0_CHANNEL)
    SIM_SCGC3 |= SIM_SCGC3_SPI2_MASK;
#else
#error "Definition of SPI_CHANNEL ERROR ! "
#endif
    
    // Module Configuration Register
    SPI_MCR_REG(SPI0_PTR) = SPI_MCR_MSTR_MASK
                         | SPI_MCR_DCONF(0x0)
                         | SPI_MCR_PCSIS(0x0)
                         | SPI_MCR_HALT_MASK;
    // Flushes the TX FIFO, Flushes the RX FIFO
    SPI_MCR_REG(SPI0_PTR) |= SPI_MCR_CLR_TXF_MASK
                          | SPI_MCR_CLR_RXF_MASK;
    // Frame Size and baud rate
    SPI_CTAR_REG(SPI0_PTR,0) = SPI_CTAR_FMSZ(SPI0_FRAME_SIZE)
                            | SPI_CTAR_DBR_MASK;
    
    SPI_CTAR_REG(SPI0_PTR,1) = SPI_CTAR_FMSZ(SPI0_FRAME_SIZE)
                            | SPI_CTAR_DBR_MASK;
  
    // clear all flag
    SPI_SR_REG(SPI0_PTR) = 0xffff0000UL;
    // close all interrupt
    SPI_RSER_REG(SPI0_PTR) = 0x00UL;
    // start DSPI transfers
    SPI_MCR_REG(SPI0_PTR) &= ~SPI_MCR_HALT_MASK;
}


