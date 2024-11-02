
/***********************************************************************************************
Name: 				Charles Norton
Course:				
Project:			
File: 				227_lab5.c
Description: 	
**************************************************************************************************/
#include "stm32f4xx.h"

#ifndef UART_H_
#define UART_H_
//function initializations
void USART2_init(void);
void USART2_write(char c);
void USART2_print(char string[]);
#endif
