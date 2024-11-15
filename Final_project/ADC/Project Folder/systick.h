#include "stm32f446xx.h"
#ifndef SYSTICK_H
#define SYSTICK_H

void SysTick_Init(void);
void delayMS(uint16_t n);
void delayMicroS(uint16_t n);

#endif