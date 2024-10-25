



#include "stm32f446xx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "KP.h" 

/********************************************
*Brief: This function Initilizes the systick
********************************************/
/*
void SysTick_Init(void){
 SysTick->CTRL = 0; //disable SysTick during step
 SysTick->LOAD = 0x00FFFFFF; // max reload value
 SysTick->VAL = 0; // any write to current clears it
 SysTick->CTRL = 0x00000005; // enable SysTick, 16MHz, No Interrupts,
}
*/

/********************************************************************
*Brief: Systick Millisecond Delay Function, gets 16MHz clock
*       62.5ns is one period. 1 ms=(62.5*16000)ns, Max load is 2^24
*Params:
* (uint16) delay: delay in the units of milliseconds
********************************************************************/
void SysTick_Delay(uint16_t delay){
 SysTick->LOAD = ((delay * 16000) - 1); // delay for 1 ms* delay value SYSTICK LOAD = 16000*n-1
 SysTick->VAL = 0; // any write to CVR clears it
 while ( (SysTick->CTRL & 0x00010000) == 0); // wait for flag to be SET/counts down to 0
}


/******************************************
*Brief: Initialize the GPIO for the Keypad
******************************************/
void keypadInit(void){
	RCC->AHB1ENR |= (1<<2);
	
	//Initialize R0
	R0_MODER &= ~(0x03UL << (2*R0_PIN)); //Set R0 as input
	R0_PUPDR &= ~(0x03UL << (2*R0_PIN)); //Clearing PUPDR for R0
	R0_PUPDR |=  (0x01UL << (2*R0_PIN)); //Assign R0 a pullup resistor
	
	//Initialize R1
	R1_MODER &= ~(0x03UL << (2*R1_PIN)); //Set R1 as input
	R1_PUPDR &= ~(0x03UL << (2*R1_PIN)); //Clearing PUPDR for R1
	R1_PUPDR |=  (0x01UL << (2*R1_PIN)); //Assign R1 a pullup resistor	
	
	//Initialize R2
	R2_MODER &= ~(0x03UL << (2*R2_PIN)); //Set R2 as input
	R2_PUPDR &= ~(0x03UL << (2*R2_PIN)); //Clearing PUPDR for R2
	R2_PUPDR |=  (0x01UL << (2*R2_PIN)); //Assign R2 a pullup resistor	
	
	//Initialize R3
	R3_MODER &= ~(0x03UL << (2*R3_PIN)); //Set R3 as input
	R3_PUPDR &= ~(0x03UL << (2*R3_PIN)); //Clearing PUPDR for R3
	R3_PUPDR |=  (0x01UL << (2*R3_PIN)); //Assign R3 a pullup resistor	
	
	//Initialize C0
	C0_MODER &= ~(0x03UL << (2*C0_PIN)); //Set C0 as input
	C0_PUPDR &= ~(0x03UL << (2*C0_PIN)); //Clear PUPDR for C0
	C0_OUT   &= ~(0x03UL << (2*C0_PIN)); //Set C0 ODR as output low
	
	//Initialize C1
	C1_MODER &= ~(0x03UL << (2*C1_PIN)); //Set C1 as input
	C1_PUPDR &= ~(0x03UL << (2*C1_PIN)); //Clear PUPDR for C1
	C1_OUT   &= ~(0x03UL << (2*C1_PIN)); //Set C1 ODR as output low	
	
	//Initialize C2
	C2_MODER &= ~(0x03UL << (2*C2_PIN)); //Set C2 as input
	C2_PUPDR &= ~(0x03UL << (2*C2_PIN)); //Clear PUPDR for C2
	C2_OUT   &= ~(0x03UL << (2*C2_PIN)); //Set C2 ODR as output low	
	
	SysTick->CTRL = 0; //disable SysTick during step
  SysTick->LOAD = 0x00FFFFFF; // max reload value
  SysTick->VAL = 0; // any write to current clears it
  SysTick->CTRL = 0x00000005; // enable SysTick, 16MHz, No Interrupts,
}
/********************************************************
*Brief: Sequentially changes column pin to output low,
* 			checks of a button was pressed in any of the
*				rows, then changes column pin to input high z.
*				
*				If any button is pressed, the keyPress variable
*				gets masked with bits.
*******************************************************/
uint16_t readKeypad(void){
	uint16_t keyPress = 0;
	
	COL0(ON);
	keyPress |= (readColumn() & 0x000F); 
	COL0(OFF);
	
	COL1(ON);
	keyPress |= (readColumn() & 0x000F)<<4;
	COL1(OFF);

	COL2(ON);
	keyPress |= (readColumn() & 0x000F)<<8;
	COL2(OFF);

  return keyPress;	
}
/********************************************
*Brief: checks each row for a low value
*       (key press) and returns 4 bits
*       that will get masked with a 16 bit 
*       integer and decoded
*********************************************/
uint16_t readColumn(void){
	uint16_t columnRead = 0x0000; 
	SysTick_Delay(DELAY); // debounce button
	
	if(!(R0_IN&(1<<R0_PIN))) columnRead |= 1<<0; // is row 0 pressed?
  if(!(R1_IN&(1<<R1_PIN))) columnRead |= 1<<1; // is row 1 pressed?
	if(!(R2_IN&(1<<R2_PIN))) columnRead |= 1<<2; // is row 2 pressed?
	if(!(R3_IN&(1<<R3_PIN))) columnRead |= 1<<3; // is row 3 pressed?
	
	return columnRead;
}
/********************************************
*Brief: decodes a 16-bit integer into keypad
*       values that are appended to an array
********************************************* 
* | bit  0 | bit  4 | bit  8 |
* |    1   |    2   |    3   |
* ----------------------------
* | bit  1 | bit  5 | bit  9 |
* |    4   |    5   |    6   |
* ----------------------------
* | bit  2 | bit  6 | bit 10 |
* |    7   |    8   |    9   |
* ----------------------------
* | bit  3 | bit  7 | bit 11 |
* |    *   |    0   |    #   |
*
******************************************/
void decodeKeypad(uint16_t key, char * carray){
	uint8_t n = 0;
	if(key & (1<<7))  carray[n++] = '0';
	if(key & (1<<0))  carray[n++] = '1';
	if(key & (1<<4))  carray[n++] = '2';
	if(key & (1<<8))  carray[n++] = '3';
	if(key & (1<<1))  carray[n++] = '4';
	if(key & (1<<5))  carray[n++] = '5';
	if(key & (1<<9))  carray[n++] = '6';
	if(key & (1<<2))  carray[n++] = '7';
	if(key & (1<<6))  carray[n++] = '8';
	if(key & (1<<10)) carray[n++] = '9';
	if(key & (1<<3))  carray[n++] = '*';
	if(key & (1<<11)) carray[n++] = '#';
	
	carray[n] = '\0';

}