
#include <stm32f407xx.h>
//all addresses are predifined but if we are declaring any mecros for register than typecasting required according to that structure//

#ifndef GPIO_H
#define GPIO_H
//mecros for output type
#define GPIO_MODE_INPUT     0
#define GPIO_MODE_OUTPUT    1
#define GPIO_MODE_ALTERFU	  2
#define GPIO_MODE_ANALOG    3
#define GPIO_IT_FT          4
#define GPIO_IT_RT          5
#define GPIO_IT_FTRT        6  
//mecros for pushpul and open drain output//
#define GPIO_OUT_PUSHPULL  0
#define GPIO_OUT_OPENDRAIN 1
//mecros for output speed register//
#define GPIO_SPEED_LOW     0
#define GPIO_SPEED_MEDIUM  1
#define GPIO_SPEED_HIGH    2
#define GPIO_SPEED_UHIGH   3
//mecros for config pullup or pulldown or none of them//
#define REGISTER_NO_PULLUP_PULLDOWN 0
#define REGISTER_PULL_UP            1
#define REGISTER_PULL_DOWN          2
//mecros for high low//
#define HIGH   1
#define LOW    0
#define SET    1
#define RESET  0
//mecros for alternate function//
#define AF0  0
#define AF1  1
#define AF2  2
#define AF3  3
#define AF4  4
#define AF5  5
#define AF6  6
#define AF7  7
#define AF8  8
#define AF9  9
#define AF10 10
#define AF11 11
#define AF12 12
#define AF13 13
#define AF14 14
#define AF15 15
#define AF16 16
//mecros for interrupt port//
#define PA 0
#define PB 0
#define PC 0
#define PD 0
#define PE 0
#define PF 0
#define PG 0
#define PG 0
#define PH 0
#define PI 0
//mecro to confine interrupt port//
#define GPIO_PORT(x) ((x==GPIOA) ? 0 : \
                          (x==GPIOB) ? 1 : \
													(x==GPIOC) ? 2 : \
													(x==GPIOD) ? 3 : \
													(x==GPIOE) ? 4 : \
													(x==GPIOF) ? 5 : \
													(x==GPIOG) ? 6 : \
													(x==GPIOH) ? 7 : \
													(x==GPIOI) ? 8 : 0)
//mecros for congigure pin and port//
#define PA0   0
#define PA1   1
#define PA2   2
#define PA3   3
#define PA4   4
#define PA5   5
#define PA6   6
#define PA7   7
#define PA8   8
#define PA9   9
#define PA10  10
#define PA11  11
#define PA12  12
#define PA13  13
#define PA14  14
#define PA15  15
#define PA16  16
#define PB0   20
#define PB1   21
#define PB2   22
#define PB3   23
#define PB4   24
#define PB5   25
#define PB6   26
#define PB7   27
#define PB8   28
#define PB9   29
#define PB10  30
#define PB11  31
#define PB12  32
#define PB13  33
#define PB14  34
#define PB15  35
#define PB16  36
#define PC0   40
#define PC1   41
#define PC2   42
#define PC3   43
#define PC4   44
#define PC5   45
#define PC6   46
#define PC7   47
#define PC8   48
#define PC9   49
#define PC10  50
#define PC11  51
#define PC12  52
#define PC13  53
#define PC14  54
#define PC15  55
#define PC16  56
#define PD0   60
#define PD1   61
#define PD2   62
#define PD3   63
#define PD4   64
#define PD5   65
#define PD6   66
#define PD7   67
#define PD8   68
#define PD9   69
#define PD10  70
#define PD11  71
#define PD12  72
#define PD13  73
#define PD14  74
#define PD15  75
#define PD16  76
#define PE0   80
#define PE1   81
#define PE2   82
#define PE3   83
#define PE4   84
#define PE5   85
#define PE6   86
#define PE7   87
#define PE8   88
#define PE9   89
#define PE10  90
#define PE11  91
#define PE12  92
#define PE13  93
#define PE14  94
#define PE15  95
#define PE16  96
typedef struct 
{
	uint8_t Pin_Number;//pin number
	uint8_t Pin_Mode ;//@output type
	uint8_t Pin_Type ;//@pushpull drain
	uint8_t Pin_Speed;//@speed register
	uint8_t Pin_Resistor;//@pull and pull down
	uint8_t Pin_Alterfun;//@configer alternate function
	uint8_t Pin_InterPort;//@configer Interrupt port
	
}Config_Pin_t;




typedef struct 
{
	GPIO_TypeDef *xGPIO;    //connecting to gpio//
	Config_Pin_t Config_Pin;//connecting to configration//
}Handle_Pin_t;
void GPIO_Init(Handle_Pin_t *pinHandle);//configering pin//
//////////////////////////////////////////////////////
void __NVIC_EnableIRQ(IRQn_Type IRQn);//eneble interrupt//
//////////////////////////////////////////////////////
void __NVIC_DisableIRQ(IRQn_Type IRQn);//disable interrupt request//
//////////////////////////////////////////////////////
void __NVIC_ClearPendingIRQ(IRQn_Type IRQn);//clear pending irq(interuupt) request//
//////////////////////////////////////////////////////
void GPIO_Write(GPIO_TypeDef *xgpio,uint8_t,uint8_t);//set gpio bit(set or reset)
//////////////////////////////////////////////////////
int input(GPIO_TypeDef *xgpio,int N);//read input from gpio pin//
//////////////////////////////////////////////////////
void GPIO_Config(GPIO_TypeDef* xgpio,uint8_t m,uint8_t n);//configure gpio port//
//syntax GPIO_Config(GPIOA,GPIO_MODE_OUTPUT,12(pin number))//
//////////////////////////////////////////////////////





#endif