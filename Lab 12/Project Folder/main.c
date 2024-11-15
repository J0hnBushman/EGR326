/*
(2^12)-1 = 4095
collect sample time and recorded voltage
1000 samples per second for 1 second
sample occurs upon button push
*/

#include "stm32f446xx.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "ADC.h"


extern void SysTick_Handler(void);
void SysTick_init(void);
void gpio_init(void);
void adc_init(void);
double value = 0;



////////////////////////////////////////////MAIN////////////////////////////////////////////////////	
int main (void) {
 __disable_irq();

	gpio_init();
	adc_init();
  SysTick_init();
 __enable_irq();
	
 while (1) {
		value = Read_ADC();
	}
}




//////////////////////////////// GPIO INIT ///////////////////////////////////////////////
 void gpio_init(void){
 RCC->AHB1ENR |= 1; /* enable GPIOA clock */
 RCC->AHB1ENR |= 4; /* enable GPIOC clock */
 GPIOA->MODER |= 0xC; /* PA1 analog */
 
 }
 
 
 
 ///////////////////////////////// ENABLE SYSTICK INTERRUPT ////////////////////////////////////
 void SysTick_init(void){
	 //Setting SysTick_CTL to disable Systick during a step
	 SysTick -> CTRL	= 0;
	 
	 //Setting SysTick_LOAD ms
	 SysTick -> LOAD	= 16000-1;
	 
	 //Writing to SysTick_VAL  to clear it
	 SysTick -> VAL	= 0;
	 
	 //Enabling SysTick Interrupt
	 SysTick -> CTRL	= 7;	 
 }

 

 
/////////////////////////////////////////////////// SYSTICK HANDLER //////////////////////////////////////////////////////////////////
 void SysTick_Handler(void){
	ADC1->CR2 |= 0x40000000; /* start a conversion */
}