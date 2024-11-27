

#include "stm32f446xx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hall.h"
#include "font_ubuntu_mono_24.h"
#include "font_freemono_mono_bold_24.h"
#include "ILI9341.h"


	void hallEffect_pinInit(){
		RCC->AHB1ENR |= (1<<7);
		
		HALL_MODER(0);
		HALL2_MODER(0);
		
		SYSCFG->EXTICR[3] &= ~(0xF<<4);
		SYSCFG->EXTICR[3] |=  (0x1<<4);
		SYSCFG->EXTICR[2] &= ~(0xF<<(4*3));
		SYSCFG->EXTICR[2] |=  (0x1<<(4*3));
		
		EXTI->IMR  |=  (1<<HALL_PIN);
		EXTI->FTSR |=  (1<<HALL_PIN);
		EXTI->RTSR &=~ (1<<HALL_PIN);
		
		EXTI->IMR  |=  (1<<HALL2_PIN);
		EXTI->FTSR |=  (1<<HALL2_PIN);
		EXTI->RTSR &=~ (1<<HALL2_PIN);
		
		NVIC_EnableIRQ(EXTI15_10_IRQn);
	}
	

	
