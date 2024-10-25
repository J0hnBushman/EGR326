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

#define Trig_pin 5
#define Echo_pin 6


//Function Prototypes
void gpio_init(void);
void timer_init(void);
void light_intensity(double distance);
void systick_init(void);
void SysTick_Handler(void);

//global variables
int last = 0;
int current; 
double period; 
double distance; 
int flag = 0;


//*********************MAIN*********************************************
int main(void)
{
	//init functions
	__disable_irq();
	gpio_init();
	timer_init();
	systick_init();
	__enable_irq();
	
	
	while(1){
		
		while((TIM4->SR & 2) == 0); //waits for a catpure on channel 1
		//once you capture the value set the count back to 0, count value restart
		current = TIM4->CCR1;
		//period = last- current;
		period = current - last;
		last = current; 
		distance = ((period/2.0)*343.0/(10000.0*2.54)); //distance calculation
		if((GPIOB->IDR & (1<<6))==0){ 	//make sure to check it when the signal is low
			if(distance>=0){							//no negative distances
				if(flag){
						printf("%0.2lf\n", distance);
					flag = 0;
				}
			light_intensity(distance);
			}
		}
	}
	
	
}





//*************************GPIO INIT*********************************
//Description: this function inits GPIOB Pin 5 and 6
//						 And PA5 for the LED.
//Returns: Void
//Parameters: None
//*******************************************************************
void gpio_init(void)
{
	RCC->AHB1ENR |= (unsigned long)0x0000007;	//enable GPIO port A and C
	
	//setting up TIM3_ch1 on GPIO B pin 5 and 6
	GPIOB->MODER &=~ (0x03<<(2*Trig_pin)); //clears mode r
	GPIOB->MODER |= (0x02 << (2*Trig_pin)); //set MODER as alternate funciton
	GPIOB->MODER &=~ (0x03<<(2*Echo_pin)); //clears mode r
	GPIOB->MODER |= 0x02<<(2*Echo_pin); //set MODER as alternate funciton
	//setting up PA5 for timer 2 cahnnel 1
	GPIOA->MODER &=~ (0x03<<(2*5));
	GPIOA->MODER |=  (0x02<<(2*5));

	//clear the AF2
	GPIOB->AFR[0] &=~ (0x0F<<(4*Trig_pin));
	GPIOB->AFR[0] &=~ (0x0F<<(4*Echo_pin));
	GPIOA->AFR[0] &=~ (0x0F<<(4*5));
	
	//asign the AFR
	GPIOB->AFR[0] |= (0x02<<(4*Trig_pin));
	GPIOB->AFR[0] |= (0x02<<(4*Echo_pin));
	GPIOA->AFR[0] |= (0x01<<(4*5));
}





//************************TIMER init***************************
//Description: This Function sets up timer 3 channel 2 for the trigger
//						 pulse. Timer 4 channel 1 for the echo capture. And 
//						 Timer 2 channel 1 for the LED connected to the 
//						 Proximity sensor. 
//Returns: Void
//Parameters: None
//********************************************************************
void timer_init(void){
	//Trigger Needs to be set High for 10 us to send out a pulse
	//PB5 - TIM3_CH2 - AF2
	RCC->APB1ENR |= 0x02;
	TIM3->PSC = 16 - 1; 
	TIM3->ARR = 100 - 1;										//60 ms period 
	TIM3->CCMR1 = 0x06000; /* set PWM mode1 */
	TIM3->CCR2 = ((TIM3->ARR+1)*90.f/100);
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
	
	//PA5 TIM2_Ch1 for the LED
	RCC->APB1ENR |= 1;
	TIM2->PSC = 160-1;
	TIM2->ARR = 100 - 1;
	TIM2->CCMR1 = 0x60;
	TIM2->CCER |= 0x01;
	TIM2->CNT = 0;
	TIM2->CR1 = 1;
}





////////////////LIGHT INTENSITY///////////////////////
//Description: Changes the intensity of the LED based on the distance 
//						 intensity is changed via the duty cycle. 
//Returns: Void
//Parameters: Double Distance value from the Prox sensor
//********************************************************
void light_intensity(double distance){
	if(distance <= 1){ //one inch or closer
		TIM2->PSC = 8000-1;
		TIM2->ARR = 1000-1;
		TIM2->CCR1 = ((TIM2->ARR+1)*50.f/100);
	}else {
		TIM2->PSC = 160-1;
		if(distance <= 2){ //two inches
		TIM2->CCR1 = ((TIM2->ARR+1)*20.f/100);
	}else if(distance <= 3){		//3 in
		TIM2->CCR1 = ((TIM2->ARR+1)*30.f/100);
	}else if(distance <= 4){//4 in
		TIM2->CCR1 = ((TIM2->ARR+1)*40.f/100);
	}else if(distance <= 5){//5 in
		TIM2->CCR1 = ((TIM2->ARR+1)*50.f/100);
	}else if(distance <= 6){//6 in
		TIM2->CCR1 = ((TIM2->ARR+1)*60.f/100);
	}else if(distance <= 7){// 7 in
		TIM2->CCR1 = ((TIM2->ARR+1)*70.f/100);
	}else if(distance <= 8){//8 in
		TIM2->CCR1 = ((TIM2->ARR+1)*80.f/100);
	}else if(distance <= 9){//9 in
		TIM2->CCR1 = ((TIM2->ARR+1)*90.f/100);
	}else{
		TIM2->CCR1 = 0;
	}
}
	
}


//*****************SYSTICK INIT***************************
//Description: This funciton inits the systick timer
void systick_init(void)
{
	SysTick->CTRL = 0; //disables systick
	SysTick->LOAD = 0x32000000-1; //Loads value at 16MHz clock
	SysTick->VAL = 0;	//Clears VAL
	SysTick->CTRL = 0x0000007; //Enables systick
}

//**************SYSTICK HANDLER******************
//
void SysTick_Handler(void)
{
	flag = 1;
}
