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

#define ARRAY 1000

volatile uint8_t flag;
volatile uint8_t ms;
int milliseconds[ARRAY];
float voltage[ARRAY];

extern void EXTI15_10_IRQHandler(void);
void SysTick_msdelay(uint16_t msdelay);
extern void SysTick_Handler(void);
void SysTick_init(void);
void SysTick_ii_init(void);
void gpio_init(void);
void adc_init(void);




int main (void) {
 __disable_irq();
 volatile int i;



	gpio_init();
	SysTick_init();
	adc_init();
  
 __enable_irq();
	
	
//////////////////////////////////////////// WHILE ONE /////////////////////////////////////////////////////	
	
 while (1) {
	 i=0;
	 if(flag){
		 SysTick_ii_init();
		 do{
			 
				if(ms){
				ms=0;	

				voltage[i] = result;
				milliseconds[i] = i+1;
					i++;
					}
				
				}while(i<ARRAY);
		 SysTick_init(); //Turn off SysTick interrupt
				
		 for(i=0;i<ARRAY;i++){
			 printf("%.3f\t%d\n", voltage[i], milliseconds[i]);  // PRINT VALUES
			 SysTick_msdelay(5);
		 }
		 flag = 0;
	 }
	 
	 
 }
}

//////////////////////////////// GPIO INIT ///////////////////////////////////////////////

 void gpio_init(void){
 RCC->AHB1ENR |= 1; /* enable GPIOA clock */
 RCC->AHB1ENR |= 4; /* enable GPIOC clock */
 GPIOA->MODER |= 0xC; /* PA1 analog */
	 
/*Configure PC13 for push button Interrupt*/	 
 GPIOC->MODER &= ~0x0C000000UL; /* clear pin mode to input mode */
 RCC->APB2ENR |= 0x4000; /*Enable SYSCFG clock*/
 SYSCFG->EXTICR[3] &= ~0x00F0UL; /* clear port selection for EXTI13 */
 SYSCFG->EXTICR[3] |= 0x0020UL; /* select port C for EXTI13 */
 EXTI->IMR |= 0x2000UL; /* unmask EXTI13 */
 EXTI->FTSR |= 0x2000UL; /* select falling edge trigger */
 NVIC_EnableIRQ(EXTI15_10_IRQn);
 
 }
 
//////////////////////////////// ADC INIT ///////////////////////////////////////////////
 

//////////////////////////////// SYSTICK INIT ///////////////////////////////////////////////
 
 void SysTick_init (void){
	 
	 //Setting SysTick_CTL to disable Systick during a step
	 SysTick -> CTRL	= 0;
	 
	 //Setting SysTick_LOAD to max reload value
	 //SysTick -> LOAD	= (unsigned long)0x00FFFFFF;
	 SysTick -> LOAD	= 16000-1;
	 
	 //Writing to SysTick_VAL  to clear it
	 SysTick -> VAL	= 0;
	 
	 //Enabling SysTick_CTL, 16MHz, No Interrupts
	 SysTick -> CTRL	= 5;
 }
 
 ///////////////////////////////// ENABLE SYSTICK INTERRUPT ////////////////////////////////////
 
 void SysTick_ii_init(void){
	 //Setting SysTick_CTL to disable Systick during a step
	 SysTick -> CTRL	= 0;
	 
	 //Setting SysTick_LOAD ms
	 SysTick -> LOAD	= 16000-1;
	 
	 //Writing to SysTick_VAL  to clear it
	 SysTick -> VAL	= 0;
	 
	 //Enabling SysTick Interrupt
	 SysTick -> CTRL	= 7;	 
 }

/////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx////////////////////////// SYSTICK MS DELAY ///////////////////////////////////////////////
 
void SysTick_msdelay(uint16_t msdelay){
	 //delay for 1 ms delay * (some delay value) //SysTick_LOAD
	 SysTick -> LOAD = ((msdelay * 16000) - 1);
	 
	 //Clearing SysTick_VAL
	 SysTick -> VAL = 0;
	 
	 // Waiting for flag to be set //SysTick_CTL
	 while ( (SysTick -> CTRL & 0x00010000) == 0);
}

/////////////////////////////////////////////////// BUTTON HANDLER ////////////////////////////////////////////////////////////////////

 void EXTI15_10_IRQHandler(void){
	 
 if(EXTI->PR & (0x2000)){	
	 flag++;
 }
	EXTI->PR = 0x2000; /* clear interrupt pending flag */
}
 
/////////////////////////////////////////////////// SYSTICK HANDLER //////////////////////////////////////////////////////////////////

 void SysTick_Handler(void){
	ADC1->CR2 |= 0x40000000; /* start a conversion */
	ms++;
}