#ifndef __ADC_H_
#define __ADC_H_

#define VREF 3.3

int Read_ADC(void);
void adc_init(void);
int map(int Input, double In_Min, double In_Max, double Out_Min, double Out_Max);

#endif