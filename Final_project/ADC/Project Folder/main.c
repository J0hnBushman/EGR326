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
#include "systick.h"

#define ARRAY 1000

volatile uint8_t flag;
volatile uint8_t ms;
int milliseconds[ARRAY];
float voltage[ARRAY];

extern void EXTI15_10_IRQHandler(void);
void SysTick_msdelay(uint16_t msdelay);
extern void SysTick_Handler(void);
void gpio_init(void);




int main (void) {
 __disable_irq();
 volatile int i;



	gpio_init();
	adc_init();
	SysTick_Init();
  
 __enable_irq();
	
	
//////////////////////////////////////////// WHILE ONE /////////////////////////////////////////////////////	
	
 while (1) {
	 
	 
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
 
/////////////////////////////////////////////////// BUTTON HANDLER ////////////////////////////////////////////////////////////////////

 void EXTI15_10_IRQHandler(void){
	 
 if(EXTI->PR & (0x2000)){	
	 flag++;
 }
	EXTI->PR = 0x2000; /* clear interrupt pending flag */
}
 