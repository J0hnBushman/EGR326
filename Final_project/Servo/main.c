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
		
		for(i =1000; i < 2000; i ++){
			for(int j = 0; j < 1000; j ++){}
			TIM1->CCR2 = i; /* set match value 1000-2000 is 1 ms to 2 ms*/ 
		}
		for(i =2000; i > 1000; i --){
			for(int j = 0; j < 1000; j ++){}
			TIM1->CCR2 = i; /* set match value 1000-2000 is 1 ms to 2 ms*/ 
		}
		
	}
	
}




