/*
(2^12)-1 = 4095
collect sample time and recorded voltage
1000 samples per second for 1 second
sample occurs upon button push
*/

#include "stm32f446xx.h"
#include "ILI9341.h"
#include "RccConfig.h"
#include "font_ubuntu_mono_24.h"
#include "font_freemono_mono_bold_24.h"
#include "spi.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "ADC.h"
#include <stdbool.h>

bool flag = false;

typedef struct{
	uint16_t x;
	uint16_t y;
		}point;

		
point Center = {(TFT_WIDTH/2),(TFT_HEIGHT/2)-25};


extern void SysTick_Handler(void);
void display_adc(point coord);
void SysTick_init(void);
void gpio_init(void);
void adc_init(void);
uint8_t value = 0;



////////////////////////////////////////////MAIN////////////////////////////////////////////////////	
int main (void) {
 __disable_irq();

	gpio_init();
	Display_Init(); // Initializes the LCD
	Fill_Screen(BLACK);
	adc_init();
  SysTick_init();
 __enable_irq();
	
 while (1) {
		value = Read_ADC();
	 	TIM5->CCR1 = ((TIM5->ARR+1)*((double)value/10.0));
	 
	 if(flag){
		 display_adc(Center);
		 flag=false;
	 }
	 
	}
}




//////////////////////////////// GPIO INIT ///////////////////////////////////////////////
 void gpio_init(void){
 RCC->AHB1ENR |= 1; /* enable GPIOA clock */
 RCC->AHB1ENR |= 4; /* enable GPIOC clock */
 GPIOA->MODER |= 0xC; /* PA1 analog */
 
 // configure PA0 as output to drive the LED AF2
GPIOA->MODER &= ~0x00000003; /* clear pin mode */
GPIOA->MODER |= 0x00000002; /* set pin to alternate function */
GPIOA->AFR[0] &=~0x0000000F; /* clear pin AF bits */
GPIOA->AFR[0] |= 0x2; /* set pin to AF1 for TIM5 CH1 */

RCC->APB1ENR |= 1<<3; /* enable TIM5 clock */
TIM5->PSC = 160 - 1; /* divided by 160 */
TIM5->ARR = 100 - 1; /* divided by 100 */
TIM5->CCMR1 = 0x60; /* set output to PWM mode */
TIM5->CCER |= 0x01; /* enable CH1 compare mode */
TIM5->CNT = 0; /* clear counter */
TIM5->CR1 = 1; /* enable TIM2 */
 }
 
 
 
 ///////////////////////////////// ENABLE SYSTICK INTERRUPT ////////////////////////////////////
 void SysTick_init(void){
	 //Setting SysTick_CTL to disable Systick during a step
	 SysTick -> CTRL	= 0;
	 
	 //Setting SysTick_LOAD ms
	 SysTick -> LOAD	= (160000000/2)-1; // 1 sec interrupt
	 
	 //Writing to SysTick_VAL  to clear it
	 SysTick -> VAL	= 0;
	 
	 //Enabling SysTick Interrupt
	 SysTick -> CTRL	= 7;	 
 }
 
//////////////////////////////////////////////////// WRITE VALUE TO ADC ////////////////////////////////////////////////////////////
 void display_adc(point coord)
 {
	 value = (value>=9)?9:value;
   Draw_Char_BG(coord.x,coord.y,'0'+value,WHITE,BLACK,&font_ubuntu_mono_24);
	}
/////////////////////////////////////////////////// SYSTICK HANDLER //////////////////////////////////////////////////////////////////
 void SysTick_Handler(void){
	flag = true;
}
