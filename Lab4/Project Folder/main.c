/***********************************************************************************************
Name: 				John Bushman
Course:				EGR 227 - Microcontroller Programming And Applications
Project:			STM32 with and without Libraries
File: 				227_lab5.c
Description: 	
**************************************************************************************************/

//libraries 
#include <stdio.h>
#include "stm32f4xx.h"
#include "keypad.h"


//********************MAIN FUNCTION***********************
int main (void){
	SysTick_Init();
	Keypad_Init();
	uint16_t num, pressed;
	//char pinCode[100];
	num = 0;
	uint16_t *numptr=&num;
	
	printf("Please enter your 4 digit PIN.\n");
	printf("Press enter with the # key.\n");
	while (1){
		pressed = Read_Keypad(numptr);
					if(pressed){
						Print_Keys(numptr);
					}
				SysTick_Delay(10);
	}
}