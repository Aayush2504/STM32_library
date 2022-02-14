#include <stm32f407xx.h>
#include "SPI.h"
#
/*
 * @ SPI CR1 BITS Macros
 */

#define MASTER_SELECT_BIT      2
#define CLOCK_PHASE_BIT        0
#define CLOCK_POLARITY_BIT     1
#define BAUDRATE_BIT           3
#define PERIPHERAL_EN_BIT      6
#define SSM_BIT                9
#define RXONLY_SIMPLEX_BIT     10
#define DFF_BIT                11
#define BIDIMODE_BIT           15
#define SSI_BIT                8
/*
 *@SPI CR2 BITS Macros
 */
 #define CR2_BIT_RXDMAEN       0
 #define CR2_BIT_TXDMAE        1
 #define CR2_BIT_SSOE          2
 #define CR2_BIT_FRF           3
 #define CR2_BIT_ERRIE         4
 #define CR2_BIT_RXNEIE        5
 #define CR2_BIT_TXIE          6
 
  /*
   *@SPI CLOCK Configuration
   */ 
void SPI_CLCK_Config(SPI_TypeDef *pSPIx)
	
{
	 switch((int)pSPIx)
	 {
		 case (int)SPI1:RCC->APB2ENR|=(1<<12);
		 // eneble spi1 clock//
		 break;
		 case (int)SPI2:RCC->APB1ENR|=(1<<14);
		 // eneble spi2 clock //
		 break;
		 case (int)SPI3:RCC->APB1ENR|=(1<<15);
		 // eneble spi3 clock //
		 break;
	 }
}

void SPI_Init(SPI_Handle_t* SPI_Handle)
{
	 
	 SPI_CLCK_Config(SPI_Handle->pSPIx);//eneble spi clock//
	 // device bus configuration//
   switch(SPI_Handle->SPI_Config.BUS_CONFIG)
   {
		 case 1: SPI_Handle->pSPIx->CR1&=~(1<<BIDIMODE_BIT);
	 // clear bidi bit to configure FD mode //
		 break;
		 case 2: SPI_Handle->pSPIx->CR1|=(1<<BIDIMODE_BIT);
	 // set bidi bit to configure HD mode //
		 break;
		 case 3: SPI_Handle->pSPIx->CR1&=~(1<<BIDIMODE_BIT);
	 // reset bidi //
		         SPI_Handle->pSPIx->CR1|=(1<<RXONLY_SIMPLEX_BIT);
	 //set rx only pin to configure simplex rx bus config//
	 }
	 
	 //configure clock speed//
	 SPI_Handle->pSPIx->CR1|=(SPI_Handle->SPI_Config.CLK_SPEED<<BAUDRATE_BIT);
   
   //configure DFF mode //
	 SPI_Handle->pSPIx->CR1|=(SPI_Handle->SPI_Config.DFF<<DFF_BIT);
	 
	 //configure CPOL //
	 SPI_Handle->pSPIx->CR1|=(SPI_Handle->SPI_Config.CPOL<<CLOCK_POLARITY_BIT);
	 
	 //configure CPHA //
	 SPI_Handle->pSPIx->CR1|=(SPI_Handle->SPI_Config.CPHA<<CLOCK_PHASE_BIT);
	 
	 //configure SSM bit//
	 SPI_Handle->pSPIx->CR1|=(SPI_Handle->SPI_Config.SSM<<SSM_BIT);
	 if((SPI_Handle->pSPIx->CR1 & 0x0200)>0)
	 {
		 SPI_Handle->pSPIx->CR1|=(1<<SSI_BIT);
	 }
	 SPI_Handle->pSPIx->CR1|=(SPI_Handle->SPI_Config.DEVICE_MODE<<MASTER_SELECT_BIT);
	 SPI_Handle->pSPIx->CR1|=1<<6;
	 
   	 
  }

uint16_t SPI_Communicate(SPI_TypeDef *pSPIx,uint8_t pTxBuffer)
	{	
		 
			pSPIx->DR = pTxBuffer; 
		  //wait until RXNE flag is set
		  while(!(pSPIx->SR & (1<<SR_RXNE)));
		  return pSPIx->DR;
 }