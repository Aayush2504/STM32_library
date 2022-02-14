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
	switch( (int)(pUARTx))
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
	UARTHandle->pUARTx->CR1&=~(0xFFFF);
	
	UARTHandle->pUARTx->CR1|=(1<<13);
	
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
	UARTHandle->pUARTx->CR1&=~(1<<10);
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
	uint16_t X,I,Y;
	 
	float CLKDIV;
	CLKDIV= CLKS/(16*UARTHandle->UART_Config.UART_Baud);
	Y=CLKDIV;
	X=Y;
	(I)=(CLKDIV*100);
	(X)=(X*100);
	X=(I-X);
	X=(X*16);
	X=X+50;
	X=X/100;
	UARTHandle->pUARTx->BRR|=((Y)<<4)|X<<0;
}

uint8_t UART_Communicate(USART_TypeDef *pUARTx,uint8_t pTxBuffer)
{
	//for(int i=0;i<1000000;i++);
	while(!(pUARTx->SR & (1<<7)));
	pUARTx->DR=pTxBuffer;
	while(!(pUARTx->SR & (1<<6)));
	//while(!(pUARTx->SR & (1<<5)));
	return pUARTx->DR;
	
}