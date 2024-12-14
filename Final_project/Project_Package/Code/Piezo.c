#include "Piezo.h"
#include "stm32f446xx.h"

// Buzzer on PC6, TIM8 Channel 1
int tone_state = -1;

unsigned long long milliseconds = 0;

// Public function to keep track of milliseconds
void Timer7_Init(void){
    RCC->APB1ENR |= (1<<5); // Enable TIM7 Clock
    TIM7->PSC = 16000 - 1;
    TIM7->ARR = 300 - 1;
    TIM7->CNT = 0;
    TIM7->DIER |= 0x0001U;
    TIM7->SR &= ~0x0001U;
    TIM7->CR1 = 0x0001U;
    NVIC_EnableIRQ(TIM7_IRQn);
}

// Private function to configure Timer 8 for PWM output on TIM8 CH1 (PC6)
static void Timer8_Init(uint32_t frequency) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;     // Enable GPIOC clock
    RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;      // Enable TIM8 clock

    // 2. Configure PC6 as alternate function (AF3 for TIM8_CH1)
    GPIOC->MODER &= ~(0x03 << (2 * 6));      // Clear mode for PC6
    GPIOC->MODER |= (0x02 << (2 * 6));       // Set PC6 to alternate function (AF)
    GPIOC->AFR[0] &= ~(0x0F << (4 * 6));     // Clear alternate function for PC6
    GPIOC->AFR[0] |= (0x03 << (4 * 6));      // Set AF3 (TIM8_CH1)

    // 3. Configure TIM8 for PWM output on Channel 1
    TIM8->PSC = 1599;                        // Prescaler value (for 1 MHz timer frequency)
    TIM8->ARR = ((168000000 / (1599 + 1)) / frequency) - 1;  // Set the ARR for the given PWM frequency
    TIM8->CNT = 0;                           // Clear the timer counter

    // 4. Set PWM mode for TIM8 Channel 1 (PWM Mode 1)
    TIM8->CCMR1 &= ~(0x7 << 4);              // Clear OC1M bits (reset mode)
    TIM8->CCMR1 |= (0x6 << 4);               // Set PWM mode 1 for OC1 (OC1M = 110)

    // 5. Set the duty cycle (50% for this example)
    TIM8->CCR1 = (TIM8->ARR + 1) / 2;        // Set CCR1 for 50% duty cycle

    // 6. Enable the output compare for Channel 1 (CC1E)
    TIM8->CCER |= TIM_CCER_CC1E;             // Enable output compare on channel 1 (CC1E)

    // 7. Enable the main output (MOE) in the BDTR register to allow PWM signal generation
    TIM8->BDTR |= TIM_BDTR_MOE;              // Main Output Enable (MOE)

    // 8. Enable the timer
    TIM8->CR1 |= TIM_CR1_CEN;                // Enable TIM8 (CEN bit)
}

// Initialize the buzzer by setting up the GPIO and Timer
void Buzzer_Init(void) {
    // Set up GPIO pin and Timer for PWM generation
    Timer8_Init(1000);  // Default frequency (e.g., 1 kHz tone)
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
    TIM8->CR1 &= ~0x01;  // Disable Timer 8 to stop the buzzer
    GPIOC->MODER &= ~(0x03 << (2 * 6));   // Reset PC6 mode to input
}

void TIM7_IRQHandler(void)
{
    TIM7->SR &= ~0x0001U;  // Clear the interrupt flag
    milliseconds+=300;
    switch(tone_state){
        /////////////////////////// TONE 1 ///////////////////////////
        case (TONE1_0):
            Timer8_Init(NOTE_C3);
            tone_state = TONE1_1;
        break;
        
        case (TONE1_1):
            Timer8_Init(NOTE_E3);
            tone_state = TONE1_2;
        break;
        
        case (TONE1_2):
            Timer8_Init(NOTE_B3);
            tone_state = TONE1_3;
        break;
        
        case (TONE1_3):
            Timer8_Init(NOTE_E3);
            tone_state = TONE1_END;
        break;
        
        case (TONE1_END):
            tone_state = -1;
            Buzzer_Stop();
        break;
        /////////////////////////// TONE 2 ///////////////////////////
        case (TONE2_0):
            Timer8_Init(NOTE_A5);
            tone_state = TONE2_1;
        break;
        
        case (TONE2_1):
            Timer8_Init(NOTE_B5);
            tone_state = TONE2_2;
        break;
        
        case (TONE2_2):
            Timer8_Init(NOTE_E3);
            tone_state = TONE2_3;  
        break;
        
        case (TONE2_3):
            Timer8_Init(NOTE_C3);
            tone_state = TONE2_END;  
        break;
        
        case (TONE2_END):
            tone_state = -1;
            Buzzer_Stop();
        break;
        /////////////////////////// TONE 3 ///////////////////////////
        case (TONE3_0):
            Timer8_Init(NOTE_AS3);
            tone_state = TONE3_1;  
        break;
        
        case (TONE3_1):
            Timer8_Init(NOTE_B3);
            tone_state = TONE3_2;
        break;
        
        case (TONE3_2):
            Timer8_Init(NOTE_B2);
            tone_state = TONE3_3;  
        break;
        
        case (TONE3_3):
            Timer8_Init(NOTE_AS2);
            tone_state = TONE3_END;  
        break;
        
        case (TONE3_END):
            tone_state = -1;
            Buzzer_Stop();
        break;
        /////////////////////////// TONE 4 ///////////////////////////
        case (TONE4_0):
            Timer8_Init(NOTE_B2);
            tone_state = TONE4_1;  
        break;
        
        case (TONE4_1):
            Timer8_Init(NOTE_DS3);
            tone_state = TONE4_2;  
        break;
        
        case (TONE4_2):
            Timer8_Init(NOTE_B2);
            tone_state = TONE4_3;  
        break;
        
        case (TONE4_3):
            Timer8_Init(NOTE_DS3);
            tone_state = TONE4_END;  
        break;
        
        case (TONE4_END):
            tone_state = -1;
            Buzzer_Stop();
        break;
    }
}

unsigned long long millis(void){
	return milliseconds;
}
