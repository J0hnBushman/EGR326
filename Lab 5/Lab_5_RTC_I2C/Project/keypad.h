
/***********************************************************************************************
Name: 				John Bushman
Course:				EGR 227 - Microcontroller Programming And Applications
Project:			STM32 with and without Libraries
File: 				227_lab5.c
Description: 	
**************************************************************************************************/
#include "stm32f4xx.h"

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define gpioC	 (uint32_t) 0x04		//port C
#define R0	 (uint32_t) 0x00  	    //Row PC0 
#define R1	(uint32_t)  0x04		//Row PC2 
#define R2   (uint32_t) 0x10		//Row PC4 
#define R3   (uint32_t) 0x40		//Row PC6 
#define C0	 (uint32_t) 0x100		//Col PC8 
#define C1   (uint32_t) 0x400	    //Col PC10
#define C2	 (uint32_t) 0x1000		//Col PC12

//pin is the about of 0's its basiclly a 1<<pin number

//function initializations
uint8_t Hex2Bit (uint32_t hex_num);
uint16_t char_to_int(char pinCode[]);
void Keypad_Init (void);
void SysTick_Init (void);
void SysTick_Delay_us(uint16_t delay);
void SysTick_Delay(uint16_t delay);
void Print_Keys (uint8_t *numptr,uint16_t *spin_num_ptr);
void arrayLeftShift(char pinCode[],char key);
uint8_t Read_Keypad(uint8_t *numptr);


#endif //KEYPAD_H_
