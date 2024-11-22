

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
	
	
	//PB6 - TIM4_CH1 - AF2
	GPIOB->MODER &=~ (0x03<<(2*6)); //clears mode r
	GPIOB->MODER |= 0x02<<(2*6); //set MODER as alternate funciton
	GPIOB->AFR[0] &=~ (0x0F<<(4*6));
	GPIOB->AFR[0] |= (0x02<<(4*6));
	
	RCC->APB1ENR |= 4;
	TIM4->PSC = 16000 - 1; 
	TIM4->ARR = 10000 - 1;
	TIM4->CCMR1 = 0x01; /* set to toggle on match */
	TIM4->CCR1 = 0;
	TIM4->CCER |= 0x03; /* enable CH1 compare mode and sets to caputre as an input on both edges */
	TIM4->CNT = 0; /* clear counter */
	TIM4->CR1 = 1; /* enable TIM5 */



	//Trigger Needs to be set High for 10 us to send out a pulse
	//PB5 - TIM3_CH2 - AF2
	RCC->APB1ENR |= 0x02;
	TIM3->PSC = 16 - 1; 
	TIM3->ARR = 40000 - 1;
	TIM3->CCMR1 = 0x06000; /* set PWM mode1 */
	TIM3->CCR2 = 39990; //((TIM3->ARR+1)*90.f/100);
	TIM3->CCER |= 0x10; /* enable CH2 compare mode */
	TIM3->CNT = 0; /* clear counter */
	TIM3->CR1 = 1; /* enable TIM5 */
	
	//ECHO pin Needs capture the edge 
	//PB6 - TIM4_CH1 - AF2
	RCC->APB1ENR |= 4;
	TIM4->PSC = 16 - 1; 
	TIM4->ARR = 10000000 - 1;
	TIM4->CCMR1 = 0x01; /* set to toggle on match */
	TIM4->CCR1 = 0;
	TIM4->CCER |= 0x0B; /* enable CH1 compare mode and sets to caputre as an input on both edges */
	TIM4->CNT = 0; /* clear counter */
	TIM4->CR1 = 1; /* enable TIM5 */
}
