/******************************************************************************
Name: 				John Bushman & Charles Norton
Course:				EGR 326 
Project:			Digimon
File: 				servo.c
Description: 	Servo c file
***********************************************************************************/

//**********libraries******************
#include "stm32f446xx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "servo.h"


////////////////TIM2///////////////////////////////////////////////////////
void TIM2_setup(void){
 // configure TIM2 for the servo motor
 // and toggle CH1 output when the counter value is 0
 RCC->APB1ENR |= 0x01; /* enable TIM2 clock */
 TIM2->SR = 0; 
 TIM2->PSC = 16; /* divided by 1600 */
 TIM2->ARR = 20000; /* divided by 20000 */
 TIM2->CCMR1 = 0x60; /* set output to toggle on match */
 TIM2->CCR1 = 1000; /* set match value 1000-2000 is 1 ms to 2 ms*/ 
 TIM2->CCER |= 1; /* enable CH1 compare mode */
 TIM2->CNT = 0; /* clear counter */
 TIM2->CR1 = 1; /* enable TIM2 */
}



/////////////////////GPIO SETUP///////////////////////////////////////////////////
void TIM_GPIO(void){
  RCC->AHB1ENR |= 1<<0;
	
 //gpio for timer 2 channel 1 on pa5 
 T2C1_MODER &= ~ (0x03<<(2*T2C1_PIN)); /* clear pin mode */
 T2C1_MODER |= 0x02<<(2*T2C1_PIN); /* set pin to alternate function */
 T2C1_AFR  &=~ (0x0F<<T2C1_PIN*4); /* clear pin AF bits */
 T2C1_AFR  |= 0x01<<(T2C1_PIN*4); /* set pin to AF1 for TIM2 CH1 */
 //gpio for timer 3 channel 1 on pa6
}


