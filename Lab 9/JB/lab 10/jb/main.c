
/*=============================================================
Name: 				Bushman & Norton

Course:				EGR 326 - Embedded Systems

Project:			WatchDog Timer

File: 				main.c

Description: 	
=============================================================*/

#include "stm32f446xx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


void delayMs(int n);
void GPIO_init(void);
void WDT_init(void);
void systick_init(void);
void SysTick_Handler(void);

int count = 0;


/////////////////////////////////////////////////////////////////////
int main (void){
	GPIO_init();
	WDT_init();
	systick_init();
	
	while(1){

	}

}


///////////////////////////////////////////////////////////////////////
void delayMs(int n)
{
int i;
for(;n>0;n--)
for(i=0;i<3195;i++);
}



//////////////////////////////////////////////////////////////////////////
void GPIO_init(void){
	RCC->AHB1ENR |= 0x7;
	
	//PA5 as a output for an LED
	GPIOA->MODER &=~ (0x3<<(5*2));
	GPIOA->MODER |=  (0x1<<(5*2));
	
	//FLASH the LED to indicate init
	GPIOA->ODR |= 1<<5;
	delayMs(100);
	GPIOA->ODR &=~ (1<<5);
	
	//PC13 for a button 
	GPIOC->MODER &=~ (0x3<<(2*13));
	GPIOC->PUPDR &=~ (0x3<<(2*13));
	GPIOC->PUPDR |=  (0x1<<(2*13));
	
}



////////////////////////////////////////////////////////////////////////////
void WDT_init(void){
	IWDG->KR |= 0xCCCC;		//Starts the WDT
	IWDG->KR |= 0x5555;		// enables access to the IWDG_PR and IWDG_RLR registers 
	 
	IWDG->PR |= 0x3;		//division by 32
	IWDG->RLR |= 0xFFF; //MAX RELOAD VALUE
	
	//while(!(IWDG->SR & ));
}



/////////////////////////////////////////////////////////////////
void systick_init(void)
{
	SysTick->CTRL = 0; //disables systick
	SysTick->LOAD = 1600000 - 1; //Loads value at 16MHz clock
	SysTick->VAL = 0;	//Clears VAL
	SysTick->CTRL = 0x0000007; //Enables systick
}



//////////////////////////////////////////////////////////////////
void SysTick_Handler(void) {
	count ++;
}
