
/*******************************************************************************
* Name:             Charles Norton & John Bushman
* Course:           EGR 326 - Embedded Systems
* Project:          7-segment
* File:             lab8_main
* Description:   		
********************************************************************************/

#include <stm32f446xx.h>
#include <stdio.h>
#include "stepper.h"
#include "I2C.h"

#define BP1 ((GPIOC->IDR)&(1<<13))	
#define BP2 ((GPIOC->IDR)&(1<<12))
#define BP3 ((GPIOC->IDR)&(1<<11))


void GPIO_init(void);
void systick_init(void);
void SysTick_Handler(void);

int flag = 0;

//*********************************************************************************
//************************************MAIN*****************************************
//*********************************************************************************
int main(void)
{
	GPIO_init();
	stepper_init();
	systick_init();
	I2C_init();
	
  while (1){
		if(flag == 1){
			stepper_full_step();
			flag = 0;
		}
			
	}
}





/////////GPIO///////
void GPIO_init(void)
{
	//GPIOA
	RCC->AHB1ENR |= 1;
	
	//PC13, 12, 11 for button presss
	GPIOC->MODER &= ~ 0x00FF00000UL;		//pc13 and pc12 button press
	GPIOC->PUPDR |=   1<<11*2;
}






/////////SYSTICK//////
void systick_init(void)
{
	SysTick->CTRL = 0; //disables systick
	SysTick->LOAD = 160000 - 1; //Loads value at 16MHz clock
	SysTick->VAL = 0;	//Clears VAL
	SysTick->CTRL = 0x0000007; //Enables systick
}



///////SYSTICK HANDLER/////
void SysTick_Handler(void) {
	flag = 1;
}


