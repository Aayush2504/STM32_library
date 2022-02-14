 #include <stm32f407xx.h>
#include "GPIO.h"

 //////handle variable for gpio//////
 Handle_Pin_t Handle_Pin;


void Clock_Config_t(GPIO_TypeDef *cGPIO)
{
	switch((int)cGPIO)
	{
		case (int)GPIOA:
		RCC->AHB1ENR|=(1<<0);//eneble PORTA clock 
		break;
		case (int)GPIOB:
		RCC->AHB1ENR|=(1<<1);//eneble PORTB clock 
		break;
		case (int)GPIOC:
		RCC->AHB1ENR|=(1<<2);//eneble PORTC clock 
		break;
		case (int)GPIOD:
		RCC->AHB1ENR|=(1<<3);//eneble PORTD clock 
		break;
		case (int)GPIOE:
		RCC->AHB1ENR|=(1<<4);//eneble PORTE clock 
		break;
		case (int)GPIOF:
		RCC->AHB1ENR|=(1<<5);//eneble PORTF clock 
    break;
		case (int)GPIOG:
		RCC->AHB1ENR|=(1<<6);//eneble PORTG clock 
    break;
		case (int)GPIOH:
		RCC->AHB1ENR|=(1<<7);//eneble PORTH clock 
    break;
		case (int)GPIOI:
		RCC->AHB1ENR|=(1<<8);//eneble PORTI clock 
		break;
		
	}
}
 void GPIO_Config(GPIO_TypeDef* xgpio,uint8_t m,uint8_t n)//to configute gpio pin//
 { 
	 Handle_Pin.xGPIO=xgpio;
	 Handle_Pin.Config_Pin.Pin_Mode=m;
	 Handle_Pin.Config_Pin.Pin_Number=n;
	 GPIO_Init(&Handle_Pin);
 }
void GPIO_Init(Handle_Pin_t *pinHandle)
{
  Clock_Config_t(pinHandle->xGPIO); //eneble clock//
	uint32_t temp=0;
	
	// configure  mode //
	if(pinHandle->Config_Pin.Pin_Mode<=3)
	{
		
	pinHandle->xGPIO->MODER|=(pinHandle->Config_Pin.Pin_Mode << (2*(pinHandle->Config_Pin.Pin_Number)));//sending data to moder register
	}
	else
	{
		if(pinHandle->Config_Pin.Pin_Mode==4)
		{
			EXTI->FTSR|=(1<<pinHandle->Config_Pin.Pin_Number);
			EXTI->RTSR&=~(1<<pinHandle->Config_Pin.Pin_Number);
		}
		else if(pinHandle->Config_Pin.Pin_Mode==5)
		{
			EXTI->FTSR&=~(1<<pinHandle->Config_Pin.Pin_Number);
			EXTI->RTSR|=(1<<pinHandle->Config_Pin.Pin_Number);
		}
		else if(pinHandle->Config_Pin.Pin_Mode==6)
		{
			EXTI->FTSR|=(1<<pinHandle->Config_Pin.Pin_Number);
			EXTI->RTSR|=(1<<pinHandle->Config_Pin.Pin_Number);
		}
		RCC->AHB2ENR|=(1<<14);
		SYSCFG->EXTICR[pinHandle->Config_Pin.Pin_Number/4]|=((GPIO_PORT(pinHandle->xGPIO))<<(pinHandle->Config_Pin.Pin_Number%4));
		//configer interrupt port and pin both//
		EXTI->IMR|=(1<<pinHandle->Config_Pin.Pin_Number);
	}
		temp=(pinHandle->Config_Pin.Pin_Resistor << (2*(pinHandle->Config_Pin.Pin_Number)));
	pinHandle->xGPIO->PUPDR|=temp;
	
	//congiger pin resistor pullup pulldown//
	pinHandle->xGPIO->OSPEEDR|= (pinHandle->Config_Pin.Pin_Speed << (2*(pinHandle->Config_Pin.Pin_Number)));
	//configer pin speed//
	
  if(pinHandle->Config_Pin.Pin_Mode==GPIO_MODE_ALTERFU)
	{
		int temp1;
		int temp2; 
		temp1=pinHandle->Config_Pin.Pin_Number/8;
		temp2=pinHandle->Config_Pin.Pin_Number%8;
		pinHandle->xGPIO->AFR[temp1]&=~((0xF) << (4*temp2));
		pinHandle->xGPIO->AFR[temp1]|=(pinHandle->Config_Pin.Pin_Alterfun << (4*temp2));
	}		
}
 void GPIO_Write(GPIO_TypeDef *xgpio,uint8_t n,uint8_t SETORRESET)
 {
	 if(SETORRESET==SET)
   xgpio->ODR|=1<<n;
	 else
	 xgpio->ODR&=~(1<<n);
 }	 
 
 int input(GPIO_TypeDef *xgpio,int N)
 {
	 return ((xgpio->IDR>>N)&0x01); 
 }
 
