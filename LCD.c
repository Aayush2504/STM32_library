#include <stm32f407xx.h>
#include "LCD.h"
#include "common.h"



/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


 GPIO_TypeDef* LCD_Port(uint8_t n)//configure LCD port//
 {
	 n=n/20;
	 switch(n)
	 {
		 case 0:return GPIOA;break;
		 case 1:return GPIOB;break;
		 case 2:return GPIOC;break;
		 case 3:return GPIOD;break;
		 case 4:return GPIOE;break;
	 }
 }
Handle_Pin_t Handle_x;

void cmd(unsigned char cmnd)
{
	
	GPIO_Write(LCD_Port(RS),RS%20,RESET);
	((cmnd>>4) & 0x01) ?  GPIO_Write(LCD_Port(D4),D4%20,SET) : GPIO_Write(LCD_Port(D4),D4%20,RESET);
	((cmnd>>5) & 0x01) ?  GPIO_Write(LCD_Port(D5),D5%20,SET) : GPIO_Write(LCD_Port(D5),D5%20,RESET);
	((cmnd>>6) & 0x01) ?  GPIO_Write(LCD_Port(D6),D6%20,SET) : GPIO_Write(LCD_Port(D6),D6%20,RESET);
	((cmnd>>7) & 0x01) ?  GPIO_Write(LCD_Port(D7),D7%20,SET) : GPIO_Write(LCD_Port(D7),D7%20,RESET);
  GPIO_Write(LCD_Port(EN),EN%20,SET);
	delay_ms(10);
  GPIO_Write(LCD_Port(EN),EN%20,RESET);
	delay_ms(20);
	((cmnd   ) & 0x01) ?  GPIO_Write(LCD_Port(D4),D4%20,SET) : GPIO_Write(LCD_Port(D4),D4%20,RESET);
	((cmnd>>1) & 0x01) ?  GPIO_Write(LCD_Port(D5),D5%20,SET) : GPIO_Write(LCD_Port(D5),D5%20,RESET);
	((cmnd>>2) & 0x01) ?  GPIO_Write(LCD_Port(D6),D6%20,SET) : GPIO_Write(LCD_Port(D6),D6%20,RESET);
	((cmnd>>3) & 0x01) ?  GPIO_Write(LCD_Port(D7),D7%20,SET) : GPIO_Write(LCD_Port(D7),D7%20,RESET);
	GPIO_Write(LCD_Port(EN),EN%20,SET);
	delay_ms(10);	
  GPIO_Write(LCD_Port(EN),EN%20,RESET);
	delay_ms(20);
}
void LCD_Init()
{ 
	GPIO_Config(LCD_Port(D4),GPIO_MODE_OUTPUT,(D4%20));
	GPIO_Config(LCD_Port(D5),GPIO_MODE_OUTPUT,(D5%20));
	GPIO_Config(LCD_Port(D6),GPIO_MODE_OUTPUT,(D6%20));
	GPIO_Config(LCD_Port(D7),GPIO_MODE_OUTPUT,(D7%20));
	GPIO_Config(LCD_Port(EN),GPIO_MODE_OUTPUT,(EN%20));
	GPIO_Config(LCD_Port(RS),GPIO_MODE_OUTPUT,(RS%20));
	delay_ms(20);
	cmd(0x33);
	cmd(0x32);
	cmd(0x28);
	cmd(0x0C);
	cmd(0x06);
	cmd(0x01);
	delay_ms(2);
	cmd(0x08);
	delay_ms(2); 
}

void Lcd_Data(unsigned char data)
{
   GPIO_Write(LCD_Port(RS),RS%20,SET);
	((data>>4) & 0x01) ?  GPIO_Write(LCD_Port(D4),D4%20,SET) : GPIO_Write(LCD_Port(D4),D4%20,RESET);
	((data>>5) & 0x01) ?  GPIO_Write(LCD_Port(D5),D5%20,SET) : GPIO_Write(LCD_Port(D5),D5%20,RESET);
	((data>>6) & 0x01) ?  GPIO_Write(LCD_Port(D6),D6%20,SET) : GPIO_Write(LCD_Port(D6),D6%20,RESET);
	((data>>7) & 0x01) ?  GPIO_Write(LCD_Port(D7),D7%20,SET) : GPIO_Write(LCD_Port(D7),D7%20,RESET);
  GPIO_Write(LCD_Port(EN),EN%20,SET);
	delay_ms(10);	
  GPIO_Write(LCD_Port(EN),EN%20,RESET);
 	delay_ms(20);
	((data>>0) & 0x01) ?  GPIO_Write(LCD_Port(D4),D4%20,SET) : GPIO_Write(LCD_Port(D4),D4%20,RESET);
	((data>>1) & 0x01) ?  GPIO_Write(LCD_Port(D5),D5%20,SET) : GPIO_Write(LCD_Port(D5),D5%20,RESET);
	((data>>2) & 0x01) ?  GPIO_Write(LCD_Port(D6),D6%20,SET) : GPIO_Write(LCD_Port(D6),D6%20,RESET);
	((data>>3) & 0x01) ?  GPIO_Write(LCD_Port(D7),D7%20,SET) : GPIO_Write(LCD_Port(D7),D7%20,RESET);
	GPIO_Write(LCD_Port(EN),EN%20,SET);
	delay_ms(10);	
  GPIO_Write(LCD_Port(EN),EN%20,RESET);
 	delay_ms(20);
	
	
}
void LCD_String(char *str)
{
 int i; 
 for(i=0;str[i]!='\0';i++)
	{
		Lcd_Data(str[i]);
	}
}
void LCD_Char(char n)
{
		Lcd_Data(n);
}
void LCD_Int(long int n)
{
	char a;
	int d,i=0;
	unsigned int ans=0;
	if(n<0)
	{
		Lcd_Data(45);
		n=(-(n));
	}
	while(n!=0)                                          
	{
	i++;
	d=n%10;
	if(ans==0&&d==0)
	{
	ans=10;
	}
	else
	{
	ans=ans*10+d;
	}
	n=n/10;
	}
	while(i!=0)
	{
	i--;
	a=ans%10;
	ans=ans/10;
	Lcd_Data(a+48);
	}
}
void LCD_Float(float n)
{
  int x,j;
	int num=n;
	if(num==0)
	Lcd_Data(48);
	char a;
	int d,i=0;
	unsigned int ans=0;
	if(num<0)
	{
		Lcd_Data(45);
		num=(-(num));
		x=(-n);
	}
	else
	x=n;	
	while(num!=0)
	{
	i++;
	j++;
	d=num%10;
	if(ans==0&&d==0)
	{
	ans=10;
	}
	else
	{
	ans=ans*10+d;
	}
	num=num/10;
	}
	while(i!=0)
	{
	i--;
	a=ans%10;
	ans=ans/10;
	Lcd_Data(a+48);
	}
  //x=x*100000;
	LCD_String(".");
	ans=0;
	i=0;
	n=(n-x);
	
  	
	
	
}
