#ifndef __ADC_H_
#define __ADC_H_

#include "stm32f446xx.h"

#define VREF 3.3


uint8_t Read_ADC(void);
void adc_init(void);

#endif