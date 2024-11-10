#include "UART.h"
#include "stm32f4xx.h"
#include <string.h>

void USART2_init(void){
	RCC->AHB1ENR |= 1;
	RCC->APB1ENR |= 0x20000;

	GPIOA->AFR[0] &= ~ 0x0F00;
	GPIOA->AFR[0] |=   0x0700;

	GPIOA->MODER &= ~0x0030;
	GPIOA->MODER |= 0x0020;

	USART2->BRR = 0x0683;
	USART2->CR1 = 0x0008;
	USART2->CR2 = 0x0000;
	USART2->CR3 = 0x0000;
	USART2->CR1 |= 0x2000;
}

void USART2_write(char c){
	while(!(USART2->SR & 0x0080)){}
	USART2->DR = (c);
}

void USART2_print(char string[]){
	unsigned int i;
	
	for (i=0;i<=strlen(string);i++){
		USART2_write(string[i]);
	}
}