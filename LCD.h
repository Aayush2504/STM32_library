#include <stdint.h>
#include <stm32f407xx.h>
#include "GPIO.h"
#include <stdio.h>
#include <math.h>

#ifndef LCD_H
#define LCD_H

#define EN PE9
#define RS PE7
#define D4 PE11
#define D5 PE13
#define D6 PE14
#define D7 PE12

/*
 * @mecros for basic commands in LCD
 */
 #define CURSOR_BLINK 0x0E
 #define NEW_LINE     0xC0
 #define CLEAR_SCREEN 0x01
  
void cmd(unsigned char cmnd);//command function//
//////////////////////////////////////////
void LCD_data(unsigned char data);//data sending function//
//////////////////////////////////////////
void LCD_Init();//lcd initialisation function//
//////////////////////////////////////////
void LCD_String(char*);//string sending function//
//////////////////////////////////////////
void LCD_Char(char);//charactor sending function//
//////////////////////////////////////////
void LCD_Int(long int);//intiger sending function//
//////////////////////////////////////////
void LCD_Float(float);//float sending function//
//////////////////////////////////////////
#endif