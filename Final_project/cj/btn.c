/*  Author: John Bushman
 *  Date: 10/9/23
 *  Description: BTN stuff i guess
 *  Notes:
 */


#include "stm32f446xx.h"
#include "btn.h"


void BTN_init(void){
	RCC->AHB1ENR  |=  0x00000007;
	RCC->APB2ENR		|=  1U<<14;
	
	BTN1_PORT->MODER &= ~ (0x3<<BTN1_PIN);
	BTN1_PORT->PUPDR |= (PULLUP<<BTN1_PIN*2);
	
	SYSCFG->EXTICR[2] &= ~(0xF<<(4*3));
	SYSCFG->EXTICR[2] |=  (0x2<<(4*3));
	
	EXTI->IMR |= 1<<BTN1_PIN;
	EXTI->RTSR &= ~ (1<<BTN1_PIN);
	EXTI->FTSR |= 1<<BTN1_PIN;
}
