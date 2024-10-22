/*******************************************************************************
* Name:             Charles Norton & John Bushman
* Course:           EGR 326 - Embedded Systems
* Project:          Inerfacing the STM and the rotary controler
* File:             EGR326_Lab4.c
* Description:   		This program is for the encoder
********************************************************************************/
#include "stm32f446xx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "keypad.h"

//Function Prototypes
void EXTI1_IRQHandler(void);
void EXTI9_5_IRQHandler(void);

int btn_flag;
int spin_flag;
int counterR;
int counterL;


//*********************MAIN*********************************************
int main(void)
{
	btn_flag = 0;
	counterR = 0;
	counterL = 0;
	spin_flag = 0;
	__disable_irq();
	gpio_init();
	Keypad_Init();
	SysTick_Init();
	uint16_t num, pressed, digit;
	num = 0;
	digit = 100;
	uint16_t *digitptr = &digit;
	uint16_t *numptr = &num;
	__enable_irq();
	
	printf("Please enter your 2 digit Value.\n");
	printf("Press enter with the # key.\n");	
	while(1){
		
		if((abs(counterL-counterR)/2)==digit){
			GPIOC->ODR &= ~ (1<<R);
			GPIOC->ODR |= (1<<B);
		}else{
			if(digit != 100){
				GPIOC->ODR |= (1<<R);
				GPIOC->ODR &= ~(1<<B);
			}
		}
		if(btn_flag){
			btn_flag = 0;
			counterL = 0;
			counterR = 0;
			spin_flag = 0;
			GPIOC->ODR &= ~ (1<<R|B);
			digit = 100;
		}
		
		pressed = Read_Keypad(numptr);
					if(pressed){
						Print_Keys(numptr, digitptr);
						SysTick_Delay(10);
					}
		
	}
}



//**********CLK*INTRUPT*ON*FALLING EDGE*************
void EXTI1_IRQHandler(void){
	spin_flag =1;
	if((GPIOC->IDR & (1<<DT))){
				counterR ++;
			}else{
				counterL ++;
			}
	EXTI->PR |= (1<<CLK);
}



//*************SW*BTN*INTERUPT******************
void EXTI9_5_IRQHandler(void){
	btn_flag = 1;
	EXTI->PR |= (1<<SW);
}



