#ifndef __ADC_H_
#define __ADC_H_

#define VREF 3.3

double Read_ADC(void);
void adc_init(void);
int map(int Input, int In_Min, int In_Max, int Out_Min, int Out_Max);

#endif