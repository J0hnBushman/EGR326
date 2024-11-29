#include "Piezo.h"
#include "stm32f446xx.h"

// Buzzer on PC6, TIM3 Channel 1

// Simple delay function (busy-wait loop) for millisecond delays
static void Delay_ms(uint32_t delay) {
    volatile uint32_t i;
    while (delay--) {
                                       for (i = 0; i < 4000; i++) {  // Adjust the loop count based on your clock
            __NOP();  // No Operation, just a delay
        }
    }
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
void Buzzer_PlayTone(uint32_t frequency, uint32_t duration) {
    Timer3_Init(frequency);  // Reconfigure Timer 3 for the specified frequency

    // Wait for the specified duration (in milliseconds)
    Delay_ms(duration);

    // Stop the buzzer after the duration
    Buzzer_Stop();
}

// Stop the buzzer (set PWM to 0)
void Buzzer_Stop(void) {
    TIM3->CR1 &= ~0x01;  // Disable Timer 3 to stop the buzzer
		GPIOC->MODER &= ~(0x3 << 2*6);
}