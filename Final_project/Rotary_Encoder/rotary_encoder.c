#include "stm32f446xx.h"
#include "rotary_encoder.h"

// ARR must always equal (MENU_OPTIONS * 2)-1 

// When reading position of counter: POS = (TIMx->CNT)/2

void Encoder_TIM_init(void)
{
	//Using Timer 2
	RCC->APB1ENR |= 0x00000001UL;
	TIM2->CCER |= (1<<1) | (1<<5); //catch falling edge of inputs/////////////////////////////////////////////////
	TIM2->SMCR |= (0x50)|(0x02);
	TIM2->PSC  = 1;
	TIM2->ARR = 12+1;
	TIM2->CCMR1 |= (1<<0) | (1<<8); // Set inputs to TI1 and TI2
	TIM2->CCMR1 |= (1<<4) | (1<<12); // adjust sampling frequency of TI1 and TI2
	TIM2->CNT  = 6;
	
	TIM2->CR1 = 0x03; // turns on the timer, The Update events are not generated
	
	
}

void Encoder_init(void)
{
	RCC->AHB1ENR |= (unsigned long)0x0000007; //enable GPIO port C
	ENC_CLK_MODER(ALT_F);
	ENC_DT_MODER(ALT_F);
	GPIOA->AFR[0]		&= ~0x000000FFUL;
	GPIOA->AFR[0]		|=	0x00000011UL;
	Encoder_TIM_init();
}