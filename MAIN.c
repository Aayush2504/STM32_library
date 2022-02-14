#include <stdint.h>
#include <stm32f407xx.h>  
#include "common.h"
#include "UART.h"
 //////handle variable for gpio//////
 Handle_Pin_t Handle;
 SPI_Handle_t SPI_Handle;
 UART_Handle_t UART_Handle; 
/*int main()
{
	RCC->AHB1ENR|=(1<<4);   
	LCD_Init();
  cmd(0x0E) ;
	LCD_Int(100);
	while(1);
}*/

void LCD_command(unsigned char h,GPIO_TypeDef* GPIOx)
{
	Handle.xGPIO->ODR = 0xff;
	//or else get value in function from lcd gpio config//
	GPIOx->ODR = 0xff;
}