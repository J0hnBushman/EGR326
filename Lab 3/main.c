/*******************************************************************************
* Name:             Charles Norton & John Bushman
* Course:           EGR 326 - Embedded Systems
* Project:          Input Interfacing with the STM using interrupts
* File:             EGR326_Lab2_Part1main.c
* Description:   		This program set up the ultra sonic sensor
********************************************************************************/
#include "stm32f446xx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Sonar.h"


//global variables
double distance; 

//*********************MAIN*********************************************
int main(void)
{
	//init functions
	sonar_gpio_init();
	timer_init();
	
	while(1){
		distance = dist();
	}
}


