#ifndef __TIMERS_H__
#define __TIMERS_H__

#include "stm32f446xx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TIMER_PIN						(13)
#define TIMER_PORT 					(GPIOB)
#define TIMER_MODER(X)				(HALL_PORT->MODER &= ~ (0x03UL<<(HALL_PIN))); (HALL_PORT->MODER |= (X<<(HALL_PIN)))


void timer_init(void);


void TIM3_IRQHandler(void);


#endif 