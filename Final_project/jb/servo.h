/******************************************************************************
Name: 				John Bushman & Charles Norton
Course:				EGR 326 
Project:			Digimon
File: 				servo.h
Description: 	Servo header file
***********************************************************************************/

#ifndef __servo_H__
#define __servo_H__

//librarys
#include "stm32f446xx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define T1C2_PIN on pa5
#define T1C2_AF				1
#define T1C2_PIN      9
#define T1C2_PORT     (GPIOA)
#define T1C2_ODR      (T1C2_PORT->ODR)
#define T1C2_MODER    (T1C2_PORT->MODER)
#define T1C2_IDR      (T1C2_PORT->IDR)
#define T1C2_PUPDR    (T1C2_PORT->PUPDR)
#define T1C2_AFR    	(T1C2_PORT->AFR[T1C2_AF])

#define upper_bound   2000
#define lower_bound   1000

void TIM_GPIO(void);
void TIM1_setup(void);

void Eye_Move_To(uint32_t position);
void Eyelid_Move_To(uint32_t position);
void Tongue_Move_To(uint32_t position);

void Timer6_Init(void);
void TIM6_DAC_IRQHandler(void);

void TIM1_CH1_Enable(void);
void TIM1_CH2_Enable(void);
void TIM1_CH3_Enable(void);

void TIM1_CH1_Disable(void);
void TIM1_CH2_Disable(void);
void TIM1_CH3_Disable(void);

#endif