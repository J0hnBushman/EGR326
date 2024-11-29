/******************************************************************************
Name: 				John Bushman & Charles Norton
Course:				EGR 326 
Project:			Digimon
File: 				testmain.c
Description: 	This is for the testing of the servo library
***********************************************************************************/
//**********libraries******************
#include "stm32f446xx.h"
#include <stdio.h>
#include <string.h>
#include "servo.h"
#include <stdlib.h>


int i;

int main(void) {
	TIM_GPIO();
	TIM1_setup();
	
	while(1){
		    // Set duty cycle for 90 degrees (1.5 ms pulse width)
		//TIM1->CCR2 = i; // Adjust this value for different angles
for(int i = 0; i < 1000000; i ++){}
	
        TIM1->CCR2 = 1000;
				TIM1->CCR1 = 1000;
			  TIM1->CCR3 = 1000;
	
	
	for(int i = 0; i < 1000000; i ++){}
	
        TIM1->CCR2 = 2000;
				TIM1->CCR1 = 2000;
				TIM1->CCR3 = 2000;
		
	}
	
}

//100 ms period 
//8ms on 


