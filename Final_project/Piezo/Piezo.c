#include "Piezo.h"
#include "stm32f446xx.h"

// Buzzer on PC6, TIM3 Channel 1

int tone_state = -1;

// Public function to keep track of milliseconds
void Timer7_Init(void){
	RCC->APB1ENR |= (1<<5); // Enable TIM7 Clock
	TIM7->PSC		=   16000-1;
	TIM7->ARR		=   100-1;
	TIM7->CNT 		=   0;
	TIM7->DIER		|=   0x0001U;
	TIM7->SR		&= ~0x0001U;
	TIM7->CR1		=   0x0001U;
	NVIC_EnableIRQ(TIM7_IRQn);
}



// Private function to configure Timer 3 for PWM output
static void Timer3_Init(uint32_t frequency) {
    // Enable clock for Timer 3 and GPIO port C
    RCC->APB1ENR |= 1<<1;  // Enable Timer 3 clock
    RCC->AHB1ENR |= 1<<2;  // Enable GPIOC clock

    // Configure PC6 as alternate function (AF2) for TIM3 Channel 1 (PWM)
		GPIOC->MODER &= ~(0x3 << 2*6);
    GPIOC->MODER |= 0x2 << 2*6;   // Set PC6 to alternate function mode
    GPIOC->AFR[0] |= (0x2 << 4*6);         // Set PC6 to TIM3_CH1 (AF1)

		TIM3->CNT=0;
    TIM3->PSC = TIMER_PRESCALER;  // Set the prescaler
    TIM3->ARR = ((SYSTEM_CLOCK_HZ/TIMER_PRESCALER)/frequency)-1;          
		TIM3->CCR1 = ( ((SYSTEM_CLOCK_HZ/TIMER_PRESCALER)/frequency)/2 );

    // Set PWM mode for TIM3 Channel 1
    TIM3->CCMR1 |= 0x60;  // PWM mode 1
    TIM3->CCER |= 0x01;   // Enable capture/compare output on channel 1
    TIM3->CR1 |= 0x01;    // Enable Timer 3
}

// Initialize the buzzer by setting up the GPIO and Timer
void Buzzer_Init(void) {
    // Set up GPIO pin and Timer for PWM generation
    Timer3_Init(1000);  // Default frequency (e.g., 1 kHz tone)
}

// Generate a tone on the buzzer for a specific duration (in milliseconds)
void Play_Tone_1(void) {
		TIM7->CNT = 0;
		tone_state = TONE1_0;
}
void Play_Tone_2(void) {
		TIM7->CNT = 0;
		tone_state = TONE2_0;
}
void Play_Tone_3(void) {
		TIM7->CNT = 0;
		tone_state = TONE3_0;
}
void Play_Tone_4(void) {
		TIM7->CNT = 0;
		tone_state = TONE4_0;
}

// Stop the buzzer (set PWM to 0)
void Buzzer_Stop(void) {
    TIM3->CR1 &= ~0x01;  // Disable Timer 3 to stop the buzzer
		GPIOC->MODER &= ~(0x3 << 2*6);
}

void TIM7_IRQHandler(void)
{
	TIM7->SR		&= ~0x0001U;
	
	switch(tone_state){
/////////////////////////// TONE 1 ///////////////////////////
		case (TONE1_0):
			Timer3_Init(NOTE_C3);
			tone_state = TONE1_1;
		break;
		
		case (TONE1_1):
			Timer3_Init(NOTE_E3);
			tone_state = TONE1_2;
		break;
		
		case (TONE1_2):
			Timer3_Init(NOTE_B3);
			tone_state = TONE1_3;
		break;
		
		case (TONE1_3):
			Timer3_Init(NOTE_E3);
			tone_state = TONE1_END;
		break;
		
		case (TONE1_END):
			tone_state=-1;
			Buzzer_Stop();
		break;
/////////////////////////// TONE 2 ///////////////////////////
		case (TONE2_0):
			Timer3_Init(NOTE_A5);
			tone_state = TONE2_1;
			
		break;
		
		case (TONE2_1):
			Timer3_Init(NOTE_B5);
			tone_state = TONE2_2;
			
		break;
		
		case (TONE2_2):
			Timer3_Init(NOTE_E3);
			tone_state = TONE2_3;	
		
		break;
		
		case (TONE2_3):
			Timer3_Init(NOTE_C3);
			tone_state = TONE2_END;	
		
		break;
		
		case (TONE2_END):
			tone_state=-1;
			Buzzer_Stop();
		break;
/////////////////////////// TONE 3 ///////////////////////////
		case (TONE3_0):
			Timer3_Init(NOTE_AS3);
			tone_state = TONE3_1;	
		
		break;
		
		case (TONE3_1):
			Timer3_Init(NOTE_B3);
			tone_state = TONE3_2;
			
		break;
		
		case (TONE3_2):
			Timer3_Init(NOTE_B2);
			tone_state = TONE3_3;	
		
		break;
		
		case (TONE3_3):
			Timer3_Init(NOTE_AS2);
			tone_state = TONE3_END;	
		
		break;
		
		case (TONE3_END):
			tone_state=-1;
			Buzzer_Stop();
		break;
/////////////////////////// TONE 4 ///////////////////////////
		case (TONE4_0):
			Timer3_Init(NOTE_B2);
			tone_state = TONE4_1;	
		
		break;
		
		case (TONE4_1):
			Timer3_Init(NOTE_DS3);
			tone_state = TONE4_2;	
		
		break;
		
		case (TONE4_2):
			Timer3_Init(NOTE_B2);
			tone_state = TONE4_3;	
		
		break;
		
		case (TONE4_3):
			Timer3_Init(NOTE_DS3);
			tone_state = TONE4_END;	
		
		break;
		
		case (TONE4_END):
			tone_state=-1;
			Buzzer_Stop();
		break;
		
	}
	
}