/*
 * File:	uart.h
 * Purpose: Universal Asynchronous Receiver/Transmitter
 *
 * Notes:
 */

#ifndef __UART_H__
#define __UART_H__

/******************************************************************************/
// Function prototypes
void uart_init(void);
uint8 uart_getchar(void);
void uart_putchar(uint8 ch);
void uart_putstr(char str[]);
void uart_putvec(uint8 *ptr, int len);
int uart_getchar_present(void);

/******************************************************************************/
// Definition
#define UART_CHAN_PTR   UART1_BASE_PTR
#define UART_CHANNEL    (1)              // pin144: 0-5 is available pin100: 0-4

#define UART_TX_PCR     PORTC_PCR4  // uart port
#define UART_TX_ATLn    (3) // 0-7
#define UART_RX_PCR     PORTC_PCR3
#define UART_RX_ATLn    (3) // 0-7

/******************************************************************************/
#endif /* __UART_H__ */
