

#include "stm32f446xx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TIMERS.h"


void timer_init(void){
	/////setting up TIM3_ch1 on GPIO B pin 4 as a timer interupt 
	RCC->AHB1ENR |= 2;
	
	GPIOB->MODER &=~ (0x03<<(2*4)); //clears mode r
	GPIOB->MODER |= 0x02<<(2*4); //set MODER as alternate funciton
	//Setting the pin to AF2
	GPIOB->AFR[0] &=~ (0x0F<<(4*4));
	GPIOB->AFR[0] &=~ (0x02<<(4*4));
	
	RCC->APB1ENR |= 2;
	TIM3->PSC = 1600 - 1; 
	TIM3->ARR = 1000 - 1;
	TIM3->CCMR1 = 0x60; /* set PWM mode1 */
	TIM3->CCR1 = (TIM3->ARR+1)*50.f/100;
	//TIM3->CCR1 = 0;
	TIM3->CCER |= 1; /* enable CH1 compare mode */
	TIM3->CNT = 0; /* clear counter */
	TIM3->CR1 = 1; /* enable TIM5 */
	
	//Timer interupt
	//TIM3->SR		&= ~0xFFFFU;
	//TIM3->DIER		=   0x001;
	//NVIC_EnableIRQ(TIM3_IRQn);
}
