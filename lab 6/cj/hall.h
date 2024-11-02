
#ifndef __hall_H__
#define __hall_H__

#include "stm32f446xx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HALL_PIN						(13)
#define HALL_PORT 					(GPIOB)
#define HALL_MODER(X)				(HALL_PORT->MODER &= ~ (0x03UL<<(HALL_PIN))); (HALL_PORT->MODER |= (X<<(HALL_PIN)))
#define HALL_IN             (HALL_PORT->IDR & 1UL << HALL_PIN)

void hallEffect_pinInit(void);
extern void EXTI15_10_IRQHandler(void);

#endif 