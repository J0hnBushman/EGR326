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

static uint8_t servo = 0;
////////////////TIM1///////////////////////////////////////////////////////
void TIM1_setup(void){
	TIM_GPIO();
	
 // configure TIM1 for the servo motor
 RCC->APB2ENR |= 0x01; /* enable TIM1 clock */
 TIM1->PSC = 16-1; /* divided by 1600 */
 TIM1->ARR = 20000-1; /* divided by 20000 */
 TIM1->CNT = 0; /* clear counter */
	
/****CHANNEL 1**********/
 TIM1->CCMR1 &= ~(0x7 << 4);       // Clear output compare mode (OC2M)
 TIM1->CCMR1 |= (0x6 << 4);        // Set mode 1 (OC2M = 110)
 TIM1->CCMR1 |= (1U << 3);         // Enable preload (OC2PE)
 TIM1->CCR1 = 1000; /* set match value 1000-2000 is 1 ms to 2 ms*/ 
 TIM1->CCER |= 1; /* enable CH1 compare mode */
	
	
 /****CHANNEL 2**********/
 TIM1->CCMR1 &= ~(0x7 << 12);       // Clear output compare mode (OC2M)
 TIM1->CCMR1 |= (0x6 << 12);        // Set mode 1 (OC2M = 110)
 TIM1->CCMR1 |= (1U << 11);         // Enable preload (OC2PE)
 TIM1->CCR2 = 1500; /* set match value 1000-2000 is 1 ms to 2 ms*/ 
 TIM1->CCER |= 1<<4; /* enable CH2 compare mode */
	
 /****CHANNEL 3**********/
 TIM1->CCMR2 &= ~(0x7 << 4);       // Clear output compare mode (OC2M)
 TIM1->CCMR2 |= (0x6 << 4);        // Set mode 1 (OC2M = 110)
 TIM1->CCMR2 |= (1U << 3);         // Enable preload (OC2PE)
 TIM1->CCR3 = 2000; /* set match value 1000-2000 is 1 ms to 2 ms*/ 
 TIM1->CCER |= 1<<8; /* enable CH3 compare mode */
 
 
 TIM1->BDTR |= 1<<15; //MOE enabled
 TIM1->CR1 = 1; /* enable TIM1 */
}

void Timer6_Init(void){
	RCC->APB1ENR |= (1<<5); // Enable TIM7 Clock
	TIM6->PSC		=   16000-1;
	TIM6->ARR		=   100-1;
	TIM6->CNT 		=   0;
	TIM6->DIER		|=   0x0001U;
	TIM6->SR		&= ~0x0001U;
	TIM6->CR1		=   0x0001U;
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
}


/////////////////////GPIO SETUP///////////////////////////////////////////////////
void TIM_GPIO(void){
  RCC->AHB1ENR |= 7;
	
 //gpio for timer 1 channel 2 on pa9
 T1C2_MODER &= ~ (0x03<<(2*9)); /* clear pin mode */
 T1C2_MODER |= 0x02<<(2*9); /* set pin to alternate function */
 T1C2_AFR  &=~ (0x0F<<(1*4)); /* clear pin AF bits */
 T1C2_AFR  |= (0x01<<(1*4)); /* clear pin AF bits */
	
	//gpio for timer 1 channel 1 on pa8
 T1C2_MODER &= ~ (0x03<<(2*8)); /* clear pin mode */
 T1C2_MODER |= 0x02<<(2*8); /* set pin to alternate function */
 T1C2_AFR  &=~ (0x0F); /* clear pin AF bits */
 T1C2_AFR  |= (0x01); /* clear pin AF bits */
	
	 //gpio for timer 1 channel 3 on pa10
 T1C2_MODER &= ~ (0x03<<(2*10)); /* clear pin mode */
 T1C2_MODER |= 0x02<<(2*10); /* set pin to alternate function */
 T1C2_AFR  &=~ (0x0F<<(2*4)); /* clear pin AF bits */
 T1C2_AFR  |= (0x01<<(2*4)); /* clear pin AF bits */
}

void Eye_Move_To(uint32_t position){
	TIM1->CCR1 = position;
}

void Eyelid_Move_To(uint32_t position){
	TIM1->CCR2 = position;
}

void Tongue_Move_To(uint32_t position){
	TIM1->CCR3 = position;
}


void TIM1_CH1_Enable(void){
	TIM1->CCER |= 1; /* enable CH1 compare mode */
}

void TIM1_CH2_Enable(void){
	TIM1->CCER |= 1<<4; /* enable CH2 compare mode */
}

void TIM1_CH3_Enable(void){
	TIM1->CCER |= 1<<8; /* enable CH3 compare mode */
}

void TIM1_CH1_Disable(void){
	TIM1->CCER &= ~ 0x01; /* enable CH1 compare mode */
}

void TIM1_CH2_Disable(void){
	TIM1->CCER &= ~(1<<4); /* enable CH2 compare mode */
}

void TIM1_CH3_Disable(void){
	TIM1->CCER &= ~(1<<8); /* enable CH3 compare mode */
}

void TIM6_DAC_IRQHandler(void)
{
	TIM6->SR		&= ~0x0001U;
	
	servo = (servo>=2)? 0 : servo+1;
	
	switch(servo){
		case(0):
			TIM1_CH1_Enable();
			TIM1_CH2_Disable();
			TIM1_CH3_Disable();
		break;
		
		case(1):
			TIM1_CH1_Disable();
			TIM1_CH2_Enable();
			TIM1_CH3_Disable();
		break;
		
		case(2):
			TIM1_CH1_Disable();
			TIM1_CH2_Disable();
			TIM1_CH3_Enable();
			
		break;
		
	}
}
