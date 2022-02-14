#include <stm32f407xx.h>
#include "UART.h"

void UART_ClockConfig(USART_TypeDef *pUARTc)
{
	switch((int)pUARTc)
	{
		case (int)USART1:UART1_CLOCK_EN;break;
		case (int)USART2:UART2_CLOCK_EN;break;
		case (int)USART3:UART3_CLOCK_EN;break;
		case (int)UART4 :UART4_CLOCK_EN;break;
		case (int)UART5 :UART5_CLOCK_EN;break;
		case (int)USART6:UART6_CLOCK_EN;break;
	}		
}

uint32_t UART_Clock_Speed(USART_TypeDef *pUARTx)
{ 
	switch(int(pUARTx))
	{
		case (int)USART1:
		case (int)USART6:return 84000000;break;
		case (int)USART2:
			case (int)USART3:
				case (int)UART4:
					case (int)UART5:return 42000000;break;
	}
}

void UART_Init(UART_Handle_t *UARTHandle)
{
	UART_ClockConfig(UARTHandle->pUARTx);
	
	if(UARTHandle->UART_Config.UART_Mode==UART_MODE_TX)
	{
		UARTHandle->pUARTx->CR1|=(UART_MODE_TX<<2);
	}
	else if(UARTHandle->UART_Config.UART_Mode==UART_MODE_RX)
	{
		UARTHandle->pUARTx->CR1|=(UART_MODE_RX<<2);
	}
	else if(UARTHandle->UART_Config.UART_Mode==UART_MODE_TXRX)
	{
		UARTHandle->pUARTx->CR1|=(UART_MODE_TXRX<<2);
	}
	//parity bit configuration
	if(UARTHandle->UART_Config.UART_Parity==UART_PARITY_DISABLE)
	UARTHandle->pUARTx->CR1|=(1<<10);
  else
	{	  
	UARTHandle->pUARTx->CR1|=(1<<10);
	if(UARTHandle->UART_Config.UART_Parity==UART_PARITY_ODD)
	{
	  UARTHandle->pUARTx->CR1|=(1<<10); 
	}
  }
	//configure stop bit//
	  UARTHandle->pUARTx->CR2|=(UARTHandle->UART_Config.UART_StopBits<<12);
	
	//configure hardware flow control//
	  UARTHandle->pUARTx->CR3|=(UARTHandle->UART_Config.UART_HWFlow<<8);
	
	uint32_t CLKS=UART_Clock_Speed(UARTHandle->pUARTx);
	uint16_t X,I;
	 
	float CLKDIV;
	CLKDIV= CLKS/(16*UARTHandle->UART_Config.UART_Baud);
	X=CLKDIV;
	UARTHandle->pUARTx->BRR|=(X<<4);
	I=CLKDIV*100;
	UARTHandle->pUARTx->BRR|=(((I-(X*100)*16)+50)/100) & (0X0F);
}

uint8_t UART_Communicate(USART_TypeDef *pUARTx,uint8_t pTxBuffer)
{
	while(!(pUARTx->SR & (1<<7)));
	pUARTx->DR=pTxBuffer;
	while(!(pUARTx->SR & (1<<5)));
	return pUARTx->DR;
	
}

