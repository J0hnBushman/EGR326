

#ifndef __KP_H__
#define __KP_H__

#include "stm32f446xx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**************************************************
Problem 1: Write a library that works with the following pin assignments
  
R0 -> PC0
   
R1 -> PC2
   
R2-> PC4
   
R3 -> PC6
   
C0-> PC8

C1->PC10

C2->PC12

Problem 2: Write a library that works with the following pin assignments

R0 -> PC1
  
R1 -> PC3
   
R2-> PC5 

R3 -> PC7
 
C0-> PC9

C1->PC11
 
C2->PC13
**************************************************/

#define R0_PIN      (1)
//#define R0_PIN      (0)
#define R0_PORT     (GPIOC)
#define R0_OUT      (R0_PORT->ODR)
#define R0_MODER    (R0_PORT->MODER)
#define R0_IN       (R0_PORT->IDR)
#define R0_PUPDR    (R0_PORT->PUPDR)


#define R1_PIN      (3)
//#define R1_PIN      (2)
#define R1_PORT     (GPIOC)
#define R1_OUT      (R1_PORT->ODR)
#define R1_MODER    (R1_PORT->MODER)
#define R1_IN       (R1_PORT->IDR)
#define R1_PUPDR    (R1_PORT->PUPDR)


#define R2_PIN      (5)
//#define R2_PIN      (4)
#define R2_PORT     (GPIOC)
#define R2_OUT      (R2_PORT->ODR)
#define R2_MODER    (R2_PORT->MODER)
#define R2_IN       (R2_PORT->IDR)
#define R2_PUPDR    (R2_PORT->PUPDR)


#define R3_PIN      (7)
//#define R3_PIN      (6)
#define R3_PORT     (GPIOC)
#define R3_OUT      (R3_PORT->ODR)
#define R3_MODER    (R3_PORT->MODER)
#define R3_IN       (R3_PORT->IDR)
#define R3_PUPDR    (R3_PORT->PUPDR)


#define C0_PIN      (9)
//#define C0_PIN      (8)
#define C0_PORT     (GPIOC)
#define C0_OUT      (C0_PORT->ODR)
#define C0_MODER    (C0_PORT->MODER)
#define C0_IN       (C0_PORT->IDR)
#define C0_PUPDR    (C0_PORT->PUPDR)


#define C1_PIN      (11)
//#define C1_PIN      (10)
#define C1_PORT     (GPIOC)
#define C1_OUT      (C1_PORT->ODR)
#define C1_MODER    (C1_PORT->MODER)
#define C1_IN       (C1_PORT->IDR)
#define C1_PUPDR    (C1_PORT->PUPDR)


#define C2_PIN      (13)
//#define C2_PIN      (12)
#define C2_PORT     (GPIOC)
#define C2_OUT      (C2_PORT->ODR)
#define C2_MODER    (C2_PORT->MODER)
#define C2_IN       (C2_PORT->IDR)
#define C2_PUPDR    (C2_PORT->PUPDR)


#define DELAY       1
#define ON          1
#define OFF         0

/*
* MACROS
* COLx(ON) - for output low
* COLx(OFF - for input high Z
*/
#define COL0(X)     ( (X)? (C0_MODER |= (0x01UL<<(2*C0_PIN))) : (C0_MODER &= ~(0x03UL<<(2*C0_PIN))) )
#define COL1(X)     ( (X)? (C1_MODER |= (0x01UL<<(2*C1_PIN))) : (C1_MODER &= ~(0x03UL<<(2*C1_PIN))) )
#define COL2(X)     ( (X)? (C2_MODER |= (0x01UL<<(2*C2_PIN))) : (C2_MODER &= ~(0x03UL<<(2*C2_PIN))) )

void SysTick_Delay(uint16_t delay);

void SysTick_Init(void);

void keypadInit(void); //Initiallized the GPIO to read the keypad.`

uint16_t readKeypad(void); //Returns the state of all of the keypad buttons in the return value at the moment the function is called.

uint16_t readColumn(void); //Returns bits that get assigned to a key and then decoded.

void decodeKeypad(uint16_t key, char *carray); //Takes the state of the keypad and returns (by reference) an array of the key's pressed.`

#endif 