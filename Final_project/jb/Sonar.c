/* Author: John Buhamn
*	Date: nov 1, 2024
* Description: Functions to set up and 
* call a distance using the HC-SR05 sonar sensor 
*/

#include <stm32f446xx.h>
#include <stdio.h>
#include "Sonar.h"

//
static int last = 0;
static int current; 
static double period; 

//*************************GPIO INIT*********************************
//Description: this function inits GPIOB Pin 5 and 6
//						 And PA5 for the LED.
//Returns: Void
//Parameters: None
//*******************************************************************
void sonar_gpio_init(void)
{
	RCC->AHB1ENR |= (unsigned long)0x0000007;	//enable GPIO port A and C
	
	//setting up TIM3_ch1 on GPIO B pin 5 and 6
	GPIOB->MODER &=~ (0x03<<(2*Trig_pin)); //clears mode r
	GPIOB->MODER |= (0x02 << (2*Trig_pin)); //set MODER as alternate funciton
	GPIOB->MODER &=~ (0x03<<(2*Echo_pin)); //clears mode r
	GPIOB->MODER |= 0x02<<(2*Echo_pin); //set MODER as alternate funciton

	//clear the AF2
	GPIOB->AFR[0] &=~ (0x0F<<(4*Trig_pin));
	GPIOB->AFR[0] &=~ (0x0F<<(4*Echo_pin));
	
	//asign the AFR
	GPIOB->AFR[0] |= (0x02<<(4*Trig_pin));
	GPIOB->AFR[0] |= (0x02<<(4*Echo_pin));
	
	
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



double dist(void){
		while((TIM4->SR & 2) == 0); //waits for a catpure on channel 1
		//once you capture the value set the count back to 0, count value restart
		current = TIM4->CCR1;
		//period = last- current;
		period = current - last;
		last = current; 
	
		return period;
}



//************************TIMER init***************************
//Description: This Function sets up timer 3 channel 2 for the trigger
//						 pulse. Timer 4 channel 1 for the echo capture. And 
//						 Timer 2 channel 1 for the LED connected to the 
//						 Proximity sensor. 
//Returns: Void
//Parameters: None
//********************************************************************


/*
void timer_init(void){
	//Trigger Needs to be set High for 10 us to send out a pulse
	//PB5 - TIM3_CH2 - AF2
	
	RCC->APB1ENR |= 0x02;
	TIM3->PSC = 16 - 1; 
	TIM3->ARR = 40000 - 1;
	TIM3->CCMR1 = 0x06000;  set PWM mode1 
	TIM3->CCR2 = 39990; //((TIM3->ARR+1)*90.f/100);
	TIM3->CCER |= 0x10;  enable CH2 compare mode 
	TIM3->CNT = 0;  clear counter 
	TIM3->CR1 = 1;  enable TIM5 
	 
	//ECHO pin Needs capture the edge 
	//PB6 - TIM4_CH1 - AF2
	RCC->APB1ENR |= 4;
	TIM4->PSC = 16 - 1; 
	TIM4->ARR = 10000000 - 1;
	TIM4->CCMR1 = 0x01; set to toggle on match 
	
	TIM4->CCR1 = 0;
	TIM4->CCER |= 0x0B;  enable CH1 compare mode and sets to caputre as an input on both edges 
	
	TIM4->CNT = 0;  clear counter */
	/*
	TIM4->CR1 = 1;  enable TIM5 
}

*/
