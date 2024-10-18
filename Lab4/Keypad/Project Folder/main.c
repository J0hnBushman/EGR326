

#include "stm32f446xx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "KP.h" 

int main (void) {

	uint16_t  key;
	char carray[13];
	keypadInit();
	//SysTick_Init();
	
	while(1) {
		
		while(!(key = readKeypad()));  /*Get which keys pressed*/
		decodeKeypad(key, carray);  /*What are those keys*/
		
		printf("%s\n",carray);  /*Print those keys to screen*/
		while(readKeypad() == key); /*Wait for the keypad to change*/
		}
	}