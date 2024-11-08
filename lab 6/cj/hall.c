

#include "stm32f446xx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hall.h"
#include "font_ubuntu_mono_24.h"
#include "font_freemono_mono_bold_24.h"
#include "ILI9341.h"


	void hallEffect_pinInit(){
		RCC->AHB1ENR |= (1<<2);
		
		HALL_MODER(0);
		
		SYSCFG->EXTICR[3] &= ~(0xF<<4);
		SYSCFG->EXTICR[3] |=  (0x1<<4);
		
		EXTI->IMR  |=  (1<<HALL_PIN);
		EXTI->FTSR |=  (1<<HALL_PIN);
		EXTI->RTSR &=~ (1<<HALL_PIN);
		
		NVIC_EnableIRQ(EXTI15_10_IRQn);
	}
	

	
