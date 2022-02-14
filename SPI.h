 /* when SSM is set to software slave select SSI bit is configured 
  *By default NSS is set to 0 which pull the NSS bit to ground
	*this cause the mode fault error
	*configure SSI bit in SOFTWARE SLAVE SELECT mode
	*/

/*when we want to some data we first have to send data length
 *ex.in string first send strlen() and its size should be 1 or 2 byte
 */
 
/*to close the communication or to send other data first cheak busy flag in SR register
 */
 
 ///////////////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////////////////////////////////////////


#include <stm32f407xx.h>
#include "GPIO.h"
#ifndef SPI_H
#define SPI_H
////// SPI1 32 MHz // SPI2 && SPI3 16 MHz by default prescaller //////

// @SPI Device mode//
#define SPI_DEVICE_MODE_MASTER  1
#define SPI_DEVICE_MODE_SLAVE   0
// @SPI Bus config//
#define SPI_BUS_FD              1
#define SPI_BUS_HD              2
#define SPI_BUS_SIMPLEX_TX      3
#define SPI_BUS_SIMPLEX_RX      4
// @SPI ClkSpeed //
#define SPI_CLK_SPEED_DIV2      0
#define SPI_CLK_SPEED_DIV4      1
#define SPI_CLK_SPEED_DIV8      2
#define SPI_CLK_SPEED_DIV16     3
#define SPI_CLK_SPEED_DIV32     4
#define SPI_CLK_SPEED_DIV64     5
#define SPI_CLK_SPEED_DIV128    6
#define SPI_CLK_SPEED_DIV256    7
// @SPI DFF MODE //
#define SPI_DFF_8BIT            0
#define SPI_DFF_16BIT           1
// @SPI CPOL //
#define SPI_CPOL_HIGH           1
#define SPI_CPOL_LOW            0
// @SPI CPHA //
#define SPI_CPHA_HIGH           1
#define SPI_CPHA_LOW            0
// @SPI SSM //
#define SPI_SSM_HW              0
#define SPI_SSM_SW              1

/*
 *@SPI STATUS Register Mecros
 */
#define SR_RXNE                0
#define SR_TXE                 1
#define SR_CHSIDE              2
#define SR_UDR                 3
#define SR_CRCERR              4
#define SR_MODF                5
#define SR_OVR                 6
#define SR_BSY                 7
#define SR_FRE                 8
typedef struct
{
	uint8_t DEVICE_MODE;
	uint8_t BUS_CONFIG;
	uint8_t CLK_SPEED;
	uint8_t DFF;
  uint8_t CPOL;
  uint8_t CPHA; 
  uint8_t SSM;	
}SPI_Config_t;
typedef struct
{
	SPI_TypeDef   *pSPIx;
	SPI_Config_t  SPI_Config;
}SPI_Handle_t;

uint16_t SPI_Communicate(SPI_TypeDef *pSPIx,uint8_t pTxBuffer);//SPI communicate  (transmit and recieve)//
//////////////////////////////////////////////////////////////////////////////////////////////////////
void SPI_Init(SPI_Handle_t *SPI_Handle);//SPI initialisation //
//////////////////////////////////////////////////////////////////////////////////////////////////////
#endif