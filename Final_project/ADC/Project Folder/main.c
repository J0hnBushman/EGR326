/*
(2^12)-1 = 4095
collect sample time and recorded voltage
1000 samples per second for 1 second
sample occurs upon button push
*/

#include "stm32f446xx.h"
#include <stdint.h>
#include <stdio.h>
#include "ADC.h"
#include "systick.h"

#define ARRAY 1000
#define LIGHT_MIN 50
#define LIGHT_MAX 4025

#define OUT_MIN 1
#define OUTMAX  10

void gpio_init(void);

int main (void) {
	gpio_init();
	adc_init();
	SysTick_Init();
	
 while (1) {
	 
	 delayMS(500);
	 
 }
}

//////////////////////////////// GPIO INIT ///////////////////////////////////////////////

 void gpio_init(void){
 RCC->AHB1ENR |= 1; /* enable GPIOA clock */
 GPIOA->MODER |= 0xC; /* PA1 analog */
 }