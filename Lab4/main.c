#include "stm32f446xx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "KP.h" 


void USART2_init(void);
void USART2_write(int c);
void delayMs(int n);



//************MAIN********************************
int main(void) {

	uint16_t  key;
	char carray[13];
	keypadInit();
	SysTick_Init();
	USART2_init();
	
	while(1) {
		
		while(!(key = readKeypad()));  /*Get which keys pressed*/
		decodeKeypad(key, carray);  /*What are those keys*/
		
		//printf("%s\n",carray);  /*Print those keys to screen*/
		while(readKeypad() == key); /*Wait for the keypad to change*/
		
		USART2_write(carray[0]);
		//USART2_write('e');
		//USART2_write('s');
		//delayMs(10);
		
		}
	}

	
	
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



void USART2_write(int c){
	while(!(USART2->SR & 0x0080)){}
		USART2->DR = (c & 0xFF);
}



void delayMs(int n){
	int i; 
	for(; n > 0 ; n --)
		for(i = 0; i < 2000; i++);
}
	





	
	