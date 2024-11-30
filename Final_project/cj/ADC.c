#include "stm32f446xx.h"
#include "ADC.h"
#include <math.h>
#include <stdio.h>

#define In_Min 50.0
#define In_Max 2500.0
#define Out_Min 0.0
#define Out_Max 9.0

uint8_t N=12;



 void adc_init(void){
	RCC->AHB1ENR |= 7; /* enable GPIOA clock */
	GPIOC->MODER |= 0x3<<(2*2); /* PC2 analog */
		/* setup ADC1 */
	RCC->APB2ENR |= (1<<9); 				/* enable ADC2 clock */
	ADC2->SMPR1 |= (5<<6); 					/* sampling time: 112 cycles */
	ADC2->CR1 |= (1<<24); 					/* 10 bit resolution */
	ADC2->CR2 |= (1<<11);						/* Data left-aligned */
	ADC2->SQR3 |= (12<<0); 					/* conversion sequence starts at ch 1 */
	ADC2->SQR1 = 0; 								/* conversion sequence length 1 */
	ADC2->CR2 |= 1; 	
 }
 
 
 
uint8_t Read_ADC(void){
	double m = (Out_Max-Out_Min)/(In_Max-In_Min);
	uint16_t raw;
	int result = 0;
	ADC2->CR2 |= 0x40000000; /* start a conversion */
	while(!(ADC2->SR & 2)) {} /* wait for conv complete */
	raw=ADC2->DR &0xFFC0; /* read conversion result */
	
	raw = (raw >> 6);
		printf("Raw: %d\t\t", raw);
	//result = raw*VREF/pow(2,N); /* decode from binary to decimal ADC readout */	
	result = ((m*raw)-(m*In_Min))+Out_Min;
		
   printf("Value: %d\n", result);
	return result;
	}