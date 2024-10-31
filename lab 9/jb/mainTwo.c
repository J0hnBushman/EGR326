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

#define S_ADDR      0x0F
#define MEM_ADDR    0x0F


/////////////////////////////////////////////////////////////////////
int main (void){
  I2C_init();
	//I2C_init_slave();
	
	char data[8];
	
	while(1){
		/*
		listen(data);
		for(int i = 0; i < 8; i++){
			if(data[i]){
				GPIOA->ODR ^= (1<<5);
			}
		}
		*/
		I2C1_byteWrite(S_ADDR,MEM_ADDR,(1<<5));
		
		for(int i = 0; i< 3000; i++);
		
	}

}



