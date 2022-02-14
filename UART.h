

// maximum baudrate should be 115200 //

#include <stm32f407xx.h>
#include "GPIO.h"

#ifndef UART_H
#define UART_H


/*
 * UART peripheral clock eneble mecros
 */
#define UART1_CLOCK_EN  if(1){RCC->APB2ENR|=(1<<4);}
#define UART2_CLOCK_EN  if(1){RCC->APB1ENR|=(1<<17);}
#define UART3_CLOCK_EN  if(1){RCC->APB1ENR|=(1<<18);}
#define UART4_CLOCK_EN  if(1){RCC->APB1ENR|=(1<<19);}
#define UART5_CLOCK_EN  if(1){RCC->APB1ENR|=(1<<20);}
#define UART6_CLOCK_EN  if(1){RCC->APB2ENR|=(1<<5);}

/*
 * UART_Mode mecros
 */
#define UART_MODE_RX    1
#define UART_MODE_TX    2
#define UART_MODE_TXRX  3

/*
 * UART_Parity mecros
 */
#define UART_PARITY_DISABLE 2
#define UART_PARITY_EVEN    0
#define UART_PARITY_ODD     1

/*
 * UART_StopBit mecros
 */
#define UART_STOPBIT_HALF        1
#define UART_STOPBIT_ONE         0
#define UART_STOPBIT_ONEANDHALF  3
#define UART_STOPBIT_TWO         2

/*
 * HW_Flow_Control
 */
#define UART_HFLOW_CONTROL_NONE      0    
#define UART_HFLOW_CONTROL_CTS       2
#define UART_HFLOW_CONTROL_RTS       1
#define UART_HFLOW_CONTROL_CTS_RTS   3
 typedef struct
 {
	 uint8_t   UART_Mode;
	 uint32_t  UART_Baud;
	 uint8_t   UART_StopBits;
	 uint8_t   UART_WordLength;
	 uint8_t   UART_Parity;
	 uint8_t   UART_HWFlow;
 }UART_Config_t;

typedef struct
{
	UART_Config_t UART_Config;
	USART_TypeDef *pUARTx; 
}UART_Handle_t;	
 


void UART_Init(UART_Handle_t *UARTHandle);


uint8_t UART_Communicate(USART_TypeDef *pUARTx,uint8_t pTxBuffer);

#endif