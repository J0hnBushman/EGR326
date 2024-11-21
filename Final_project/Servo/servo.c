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


////////////////TIM1///////////////////////////////////////////////////////
void TIM1_setup(void){
 // configure TIM1 for the servo motor
 // and toggle CH1 output when the counter value is 0
 RCC->APB2ENR |= 0x01; /* enable TIM1 clock */
 TIM1->SR = 0; 
 TIM1->PSC = 16; /* divided by 1600 */
 TIM1->ARR = 20000; /* divided by 20000 */
 TIM1->CCMR1 = 0x6000; /* set output to toggle on match */
 TIM1->CCR2 = 1000; /* set match value 1000-2000 is 1 ms to 2 ms*/ 
 TIM1->CCER |= 10; /* enable CH2 compare mode */
 TIM1->CNT = 0; /* clear counter */
 TIM1->CR1 = 1; /* enable TIM1 */
}



/////////////////////GPIO SETUP///////////////////////////////////////////////////
void TIM_GPIO(void){
  RCC->AHB1ENR |= 1<<0;
	
 //gpio for timer 2 channel 1 on pa5 
 T1C2_MODER &= ~ (0x03<<(2*T1C2_PIN)); /* clear pin mode */
 T1C2_MODER |= 0x02<<(2*T1C2_PIN); /* set pin to alternate function */
 T1C2_AFR  &=~ (0x0F<<T1C2_PIN*4); /* clear pin AF bits */
 T1C2_AFR  |= 0x01<<(T1C2_PIN*4); /* set pin to AF1 for TIM1 CH1 */
 //gpio for timer 3 channel 1 on pa6
}


