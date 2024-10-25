/*******************************************************************************
* Name:             Charles Norton & John Bushman
* Course:           EGR 326 - Embedded Systems
* Project:          Input Interfacing with the STM using interrupts
* File:             EGR326_Lab2_Part1main.c
* Description:   		This code makes blinky lights 
********************************************************************************/

#include "stm32f446xx.h"
#include <stdio.h>

//ODR pins for LEDs (GPIOA)
#define G (1<<5)
#define R (1<<4)
#define B (1<<6)

double button_count; /////////////////
volatile uint8_t button_flag;
volatile uint8_t btn1_press;
volatile uint8_t btn2_press;

//IDR Reading, returns 0 if pressed and 1 if not
#define BP1 ((GPIOC->IDR)&(1<<13))	
#define BP2 ((GPIOC->IDR)&(1<<12))

//Function Prototypes
void gpio_init(void);
void timer_init(void);
void systick_init(void);
void delay_msDelay(uint16_t msDelay);

//debounce and button functions
uint8_t debounce_btn1(void);
uint8_t debounce_btn2(void);

//EXI
extern void EXTI15_10IRQHandler(void);



//*******************MAIN*********************************************
int main(void)
{
	button_count = 2000;
	btn1_press = 0;
	btn2_press = 0;
	__disable_irq();
	gpio_init();
	systick_init();
	timer_init();
	__enable_irq();
  
	while(1)
	{
			if(TIM3->SR & 1<<0){
				TIM3->SR &=~ (1<<0);
				GPIOA->ODR ^= (G|B|R);
			}
			
			TIM3->ARR = (button_count)-1;
		
		if(btn1_press){
			NVIC_DisableIRQ(EXTI15_10_IRQn);
			if(debounce_btn1()){
				btn1_press = 0; 
				button_count = button_count*2;
				TIM3->CNT = 0; /* clear counter */
				button_flag = 1; 
				EXTI->PR |= (1<<13)|(1<<12);
				NVIC_EnableIRQ(EXTI15_10_IRQn);
			}
		}
		
		if(btn2_press){
			NVIC_DisableIRQ(EXTI15_10_IRQn);
			if(debounce_btn2()){
				btn2_press = 0;
				button_count = button_count/2;
				TIM3->CNT = 0; /* clear counter */
				EXTI->PR |= (1<<13)|(1<<12);
				NVIC_EnableIRQ(EXTI15_10_IRQn);
			}
		}
		
	}
	
}




//****************GPIO INIT****************************
//Description: this function inits GPIOA pins 4, 5,6, and PC13 PC12
void gpio_init(void)
{
	RCC->AHB1ENR |= (unsigned long)0x0000007;	//enable GPIO port A and C
	RCC->APB2ENR		|=  1<<14;
	
	GPIOA->MODER &= ~(unsigned long)0x00003F00; //Clear MODER
	GPIOA->MODER |= (unsigned long)0x0001500; //set MODER pins 0,1 to input and 4,5,6
	
	//setting up TIM3_ch1 on GPIO B pin 4
	GPIOB->MODER &=~ (0x03<<(2*4)); //clears mode r
	GPIOB->MODER |= 0x02<<(2*4); //set MODER as alternate funciton
	//Setting the pin to AF2
	GPIOB->AFR[0] &=~ (0x0F<<(4*4));
	GPIOB->AFR[0] &=~ (0x02<<(4*4));
	
	GPIOC->MODER &= ~ 0x00F000000UL;		//pc13 and pc12 button press
	GPIOC->PUPDR |=   1<<13*2;
	GPIOC->PUPDR |=   1<<12*2;
	
	//interupt set up for PC13
	SYSCFG->EXTICR[3]	&= ~0x00F0U;
	SYSCFG->EXTICR[3]	|=  0x0020U;
		EXTI->IMR		|=  1U<<13;
	EXTI->RTSR		&= ~1U<<13;
	EXTI->FTSR		|=  1U<<13;

	//interupt set up for PC12
	SYSCFG->EXTICR[3]	&= ~0x00FU;
	SYSCFG->EXTICR[3]	|=  0x002U;
		EXTI->IMR		|=  1U<<12;
	EXTI->RTSR		&= ~1U<<12;
	EXTI->FTSR		|=  1U<<12;
	
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}



/////////***************TIMER init***************************
void timer_init(void){
	RCC->APB1ENR |= 2;
	TIM3->PSC = 16000 - 1; 
	TIM3->ARR = 1000 - 1;
	TIM3->CCMR1 = 0x60; /* set PWM mode1 */
	TIM3->CCR1 = (TIM3->ARR+1)*50.f/100;
	//TIM3->CCR1 = 0;
	TIM3->CCER |= 1; /* enable CH1 compare mode */
	TIM3->CNT = 0; /* clear counter */
	TIM3->CR1 = 1; /* enable TIM5 */
}


//*****************SYSTICK INIT***************************
//Description: This funciton inits the systick timer
void systick_init(void)
{
	SysTick->CTRL = 0; //disables systick
	SysTick->LOAD = 0x00FFFFFF; //Loads value at 16MHz clock
	SysTick->VAL = 0;	//Clears VAL
	SysTick->CTRL = 0x0000005; //Enables systick
}


//*****************SysTick millisecond Delay************************
//Description: this fucntion uses the systick timer to create a delay
//
void delay_msDelay(uint16_t msDelay){
	SysTick->LOAD = ((msDelay*16000)-1);	//init Max value of timer
	SysTick->VAL = 0; 	//clears val
	while((SysTick->CTRL&(1<<16))==0); //wait for bit 16 to set
}



////***************DEBOUNCE*******************************
//GPIOC pin 13 is button one, uses a gansell debounce
//
uint8_t debounce_btn1(void){
	unsigned char pinValue = 0; 
	
	if(!BP1){
		delay_msDelay(5);
		if(!BP1){
			pinValue = 1; 
		}
	}
	return pinValue; 
}

////***************DEBOUNCE*******************************
//GPIOC pin 12 is button one, uses a gansell debounce
//
uint8_t debounce_btn2(void){
	unsigned char pinValue = 0; 
	
	if(!BP2){
		delay_msDelay(5);
		if(!BP2){
			pinValue = 1; 
		}
	}
	return pinValue; 
}


///////////////////////////////////////////////////////
void EXTI15_10_IRQHandler(void)
{
	if (EXTI->PR & (1<<13)){ 
			btn1_press = 1; 
			button_flag = 1;
	}
	if (EXTI->PR & (1<<12)){ 
			if(button_count == 2000){
				button_flag = 0; 
			}else{
				btn2_press = 1; 	
			}
	}
	  EXTI->PR |= (1<<13)|(1<<12);
}
