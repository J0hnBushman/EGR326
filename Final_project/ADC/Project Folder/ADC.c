#include "stm32f446xx.h"
#include "ADC.h"
#include <math.h>

uint8_t N=12;

 void adc_init(void){
	/* setup ADC1 */
 RCC->APB2ENR |= 0x00000100; /* enable ADC1 clock */
 ADC1->SMPR2 |= 0x8; /* sampling time: 15 cycles */
 ADC1->CR1 = 0; /* 12 bit resolution */
 ADC1->CR2 = 0; /* Data right-aligned */
 ADC1->SQR3 = 1; /* conversion sequence starts at ch 1 */
 ADC1->SQR1 = 0; /* conversion sequence length 1 */
 ADC1->CR2 |= 1; /* enable ADC1 */
 }
 
int Read_ADC(void){
	uint16_t raw;
	
	while(!(ADC1->SR & 2)) {} /* wait for conv complete */
	raw=ADC1->DR &0xFFF; /* read conversion result */
	//result = raw*VREF/pow(2,N); /* decode from binary to decimal ADC readout */	
	return raw;
	}

int map(int Input, double In_Min, double In_Max, double Out_Min, double Out_Max){
	double m = 0.0;
	int y = 0;
	
	m = (Out_Max-Out_Min)/(In_Max-In_Min);
	
	y = ((m*Input) - (m*In_Min)) + Out_Min;
	
	return y;
}