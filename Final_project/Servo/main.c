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
	Timer6_Init();
	
	while(1){
		    // Set duty cycle for 90 degrees (1.5 ms pulse width)
		//TIM1->CCR2 = i; // Adjust this value for different angles
for(int i = 0; i < 1000000; i ++){}
	
        Eye_Move_To(1000); // left
				Eyelid_Move_To(1500); // open
			  Tongue_Move_To(500); // Right
	
	
	for(int i = 0; i < 1000000; i ++){}
	
        Eye_Move_To(1800);
				Eyelid_Move_To(2570); //closed
				Tongue_Move_To(2500); // Left
		
	}
	
}

//100 ms period 
//8ms on 


