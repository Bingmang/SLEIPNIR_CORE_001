/*
 * File:	uart.c
 * Purpose: Universal Asynchronous Receiver/Transmitter
 *
 * Notes:		
 */
#include "common.h"
#include "uart.h"

/******************************************************************************/
void uart_init(void)
{
    int sbr, brfa;  
    
    // open the clock gate of UART
#if(0==UART_CHANNEL)
    SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
#elif(1==UART_CHANNEL)
    SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;
#elif(2==UART_CHANNEL)
    SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;
#elif(3==UART_CHANNEL)
    SIM_SCGC4 |= SIM_SCGC4_UART3_MASK;
#elif(4==UART_CHANNEL)
    SIM_SCGC1 |= SIM_SCGC1_UART4_MASK;
#elif(5==UART_CHANNEL)
    SIM_SCGC1 |= SIM_SCGC1_UART5_MASK;
#else
#error "Definition UART_CHANNEL ERROR ! "
#endif
    
    /* Make sure that the transmitter and receiver are disabled while we 
     * change settings.
     */
    UART_C2_REG(UART_CHAN_PTR) &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);

    /* Configure the UART for 8-bit mode, no parity,
     * We need all default settings, so entire register is cleared
     */
    UART_C1_REG(UART_CHAN_PTR) = 0x00;
    
    /* Calculate baud settings, UART baud rate = UART module clock / (16 * (sbr + brfa/32)) */
    sbr = (int)(((int64)g_periph_clk_khz*1000) / (UART_BAUD*16));
    brfa = (int)(((int64)g_periph_clk_khz*1000*32) / (UART_BAUD*16) - sbr * 32);
    if(ABS((int64)g_periph_clk_khz*1000*10 / (32*sbr+brfa+1) - UART_BAUD*5)
       < ABS((int64)g_periph_clk_khz*1000*10 / (32*sbr+brfa) - UART_BAUD*5))
        brfa = brfa + 1;

    UART_BDH_REG(UART_CHAN_PTR) = UART_BDH_SBR((sbr & 0x1F00) >> 8);
    UART_BDL_REG(UART_CHAN_PTR) = (uint8)(sbr & UART_BDL_SBR_MASK);
    UART_C4_REG(UART_CHAN_PTR) = UART_C4_BRFA(brfa); 
    
    // set port to uart function,TX Internal pull-down resistor is enabled
    UART_TX_PCR = PORT_PCR_MUX(UART_TX_ATLn);
    UART_RX_PCR = PORT_PCR_MUX(UART_RX_ATLn);

    /* Enable receiver and transmitter */
    UART_C2_REG(UART_CHAN_PTR) |= UART_C2_TE_MASK | UART_C2_RE_MASK;
}

/******************************************************************************/
/*
 * Wait for a character to be received on the specified UART
 *
 * Parameters:
 *  channel      UART channel to read from
 *
 * Return Values:
 *  the received character
 */
uint8 uart_getchar(void)
{
    /* Wait until character has been received */
    while (!(UART_S1_REG(UART_CHAN_PTR) & UART_S1_RDRF_MASK));
    
    /* Return the 8-bit data from the receiver */
    return UART_D_REG(UART_CHAN_PTR);
}

/******************************************************************************/
/*
 * Wait for space in the UART Tx FIFO and then send a character
 *
 * Parameters:
 *  channel      UART channel to send to
 *  ch			 character to send
 */ 
void uart_putchar(uint8 ch)
{
    /* Wait until space is available in the FIFO */
    while(!(UART_S1_REG(UART_CHAN_PTR) & UART_S1_TDRE_MASK));
    
    /* Send the character */
    UART_D_REG(UART_CHAN_PTR) = ch;
}

/******************************************************************************/
void uart_putstr(char str[])
{   
    while(*str)
    {
        /* Wait until space is available in the FIFO */
        while(!(UART_S1_REG(UART_CHAN_PTR) & UART_S1_TDRE_MASK));
        /* Send the character */
        UART_D_REG(UART_CHAN_PTR) = *str;
        str ++;
    }
}

/******************************************************************************/
void uart_putvec(uint8 *ptr, int len)
{
    while(len--)
    {
        /* Wait until space is available in the FIFO */
        while(!(UART_S1_REG(UART_CHAN_PTR) & UART_S1_TDRE_MASK));
        /* Send the character */
        UART_D_REG(UART_CHAN_PTR) = *ptr;
        ptr ++;
    }
}

/******************************************************************************/
/*
 * Check to see if a character has been received
 *
 * Parameters:
 *  channel      UART channel to check for a character
 *
 * Return values:
 *  0       No character received
 *  1       Character has been received
 */
int uart_getchar_present(void)
{
    return (UART_S1_REG(UART_CHAN_PTR) & UART_S1_RDRF_MASK);
}
/******************************************************************************/
