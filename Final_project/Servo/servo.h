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

//#define T2C1_PIN on pa5
#define T2C1_AF 0
#define T2C1_PIN      5
#define T2C1_PORT     (GPIOA)
#define T2C1_ODR      (T2C1_PORT->ODR)
#define T2C1_MODER    (T2C1_PORT->MODER)
#define T2C1_IDR      (T2C1_PORT->IDR)
#define T2C1_PUPDR    (T2C1_PORT->PUPDR)
#define T2C1_AFR    	(T2C1_PORT->AFR[T2C1_AF])

void TIM_GPIO(void);
void TIM2_setup(void);

#endif