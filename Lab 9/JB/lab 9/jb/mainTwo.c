/*=============================================================
Name: 				Bushman & Norton

Course:				EGR 326 - Embedded Systems

Project:			Communicating 2 stms using i2c

File: 				main.c

Description: 	
=============================================================*/

#include "stm32f446xx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "I2C.h"
#include "KP.h" 

#define S_ADDR      0x55
#define MEM_ADDR    0x0F

#define BP1 ((GPIOC->IDR)&(1<<13))	
#define BP2 ((GPIOC->IDR)&(1<<11))

void delayMs(int n);
void btn_init(void);


/////////////////////////////////////////////////////////////////////
int main (void){
	uint16_t  key;
	char carray[13];
	char value = 0;
	int position = 0; 
	
	
	
	printf("-- Init I2C1 -- \n");
  I2C_init();
	printf("-- Init Btns --\n");
	btn_init();
	printf("-- Init Keypad --\n");
	keypadInit();
	printf("-- Init Complete --\n\n");

	while(1){
			if((key = readKeypad())){
					decodeKeypad(key, carray); 
					value = carray[0];
					printf("Value Pressed: %c\n", value);	
			while(readKeypad() == key); 
			}	

		
		if(value == '#' || value == '*'){
			value = '0'; 
		}
		
		

			if(BP1 == 0){
				while(!BP1);
				if((position+(value-'0')) <= 160){
					position += (value-'0'); 
				}
				I2C1_byteWrite(S_ADDR,value);
				printf(" -- Data Transfer Complete -- \n\n");
				printf("Present Motor Count: %d\n", position);
				
			}
			if(BP2 == 0){
				while(!BP2);
				if((position-(value-'0')) >= 0){
					 position -= (value-'0');
				}		
				I2C1_byteWrite(S_ADDR,(value+10));
				printf(" -- Data Transfer Complete -- \n");
				printf("Present Motor Count: %d\n\n", position);
				
			}
	
	}

}

//
void delayMs(int n)
{
int i;
for(;n>0;n--)
for(i=0;i<3195;i++);
}


//
void btn_init(void){
	RCC->AHB1ENR |= 0x7;
	//PC13, 12, 11 for button presss
	GPIOC->MODER &= ~ 0x00FF00000UL;		//pc13 and pc12 button press
	GPIOC->PUPDR |=   1<<13*2;
	GPIOC->PUPDR |=   1<<11*2;
}