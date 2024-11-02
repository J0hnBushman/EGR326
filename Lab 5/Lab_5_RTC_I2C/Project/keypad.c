/*******************************************************************************
* Name:             Charles Norton
* Course:           EGR 226 - Microcontroller Programming and Applications Lab
* Project:          Keypad Lab Prep
* File:            

*Description: 	
**************************************************************************************************/

#include "stm32f4xx.h"
#include "keypad.h"
#include <stdio.h>
#include <string.h>
#include "UART.h"
#include "I2C.h"

/****************************************
*Brief: 
*
****************************************/
uint8_t Hex2Bit (uint32_t hex_num){
	uint8_t bit_count = 0; 
	while(hex_num>>1)
	{
		bit_count++;
		hex_num=hex_num>>1;
	}
	return bit_count;
}



/****************************************
*Brief: Port Initialization
*
****************************************/
void Keypad_Init(void){
	RCC->AHB1ENR |= gpioC;
	GPIOC->MODER &= ~(uint32_t)((0x03<<(2*Hex2Bit(R0)))|(0x03<<(2*Hex2Bit(R1)))|(0x03<<(2*Hex2Bit(R2)))|(0x03<<(2*Hex2Bit(R3)))|(0x03<<(2*Hex2Bit(C0)))|(0x03<<(2*Hex2Bit(C1)))|(0x03<<(2*Hex2Bit(C2))));
	GPIOC->PUPDR &= ~(uint32_t)((0x03<<(2*Hex2Bit(R0)))|(0x03<<(2*Hex2Bit(R1)))|(0x03<<(2*Hex2Bit(R2)))|(0x03<<(2*Hex2Bit(R3)))|(0x03<<(2*Hex2Bit(C0)))|(0x03<<(2*Hex2Bit(C1)))|(0x03<<(2*Hex2Bit(C2))));
	GPIOC->PUPDR |= (uint32_t)((0x01<<(2*Hex2Bit(R0)))|(0x01<<(2*Hex2Bit(R1)))|(0x01<<(2*Hex2Bit(R2)))|(0x01<<(2*Hex2Bit(R3))));

}//Rows: Pull Up, Col: High Z (no PUPDR)


/****************************************
*Brief: 
*This function Initilizes the systick funciton
****************************************/
void SysTick_Init(void){
 SysTick->CTRL = 0; //disable SysTick during step
 SysTick->LOAD = 0x00FFFFFF; // max reload value
 SysTick->VAL = 0; // any write to current clears it
 SysTick->CTRL = 0x00000005; // enable SysTick, 16MHz, No Interrupts,
}


/***| Systick_msdelay() |****************************
*Brief: Systick Millisecond Delay Function, gets 16MHz clock
*Brief: 62.5ns is one period. 1 ms=(62.5*16000)ns, Max load is 2^24
*Params:
* (uint16) delay: delay in the units of milliseconds
********************************************************/
void SysTick_Delay(uint16_t delay){
 SysTick->LOAD = ((delay * 16000) - 1); // delay for 1 ms* delay value SYSTICK LOAD = 16000*n-1
 SysTick->VAL = 0; // any write to CVR clears it
 while ( (SysTick->CTRL & 0x00010000) == 0); // wait for flag to be SET/counts down to 0
}
void SysTick_Delay_us(uint16_t delay){
 SysTick->LOAD = ((delay * 16) - 1); // delay for 1 ms* delay value SYSTICK LOAD = 16000*n-1
 SysTick->VAL = 0; // any write to CVR clears it
 while ( (SysTick->CTRL & 0x00010000) == 0); // wait for flag to be SET/counts down to 0
}


/****************************************
*Brief: 
****************************************/
void Print_Keys (uint8_t *numptr,uint16_t *spin_num_ptr){
	volatile unsigned int i;
	static char pinCode [3];
	static char year[4];
	
	if(*numptr ==12) { //the pound key
		
		if(strlen(pinCode)<2){
			printf("\nERROR!\n");
		  printf("Please enter a 2 digit number.\n");
	    printf("Press enter with the # key.\n");			
			for(i = 0; i<sizeof(pinCode); i++){     // clear array
			  pinCode[i] = '\0';
		  }
		}		
		else{
		printf("#\n\n");
		printf("Number:\t%s\n\n", pinCode);
		*spin_num_ptr = char_to_int(pinCode);
		printf("\n\n spin num is %d \n\n",*spin_num_ptr);
		for(i = 0; i<sizeof(pinCode); i++){     // clear array
			  pinCode[i] = '\0';
		  }
		}
	}
	if(*numptr ==11) {
		printf("0");
	  fflush(stdout);
		if(strlen(pinCode)<2){
			strcat(pinCode,"0");
		}
		else{
			arrayLeftShift(pinCode, '0');
		}
		
	}
	if(*numptr ==10) {  //'*' key
		printf("\nERROR!\n\n");
		printf("Please enter your 4 digit PIN.\n");
	  printf("Press enter with the # key.\n");
		for(i = 0; i<sizeof(pinCode); i++){
			pinCode[i] = '\0';
		}
		
	}
	if(*numptr == 9) {
		printf("9");
	  fflush(stdout);
		if(strlen(pinCode)<2){ 
			strcat(pinCode,"9");
		}
		else{
			arrayLeftShift(pinCode, '9');
		}		
		
	}
	
	if(*numptr == 8) {
		printf("8");
	  fflush(stdout);
		if(strlen(pinCode)<2){
			strcat(pinCode,"8");
		}
		else{
			arrayLeftShift(pinCode, '8');
		}		
		
	}	
	
	if(*numptr == 7) {
		printf("7");
	  fflush(stdout);
		if(strlen(pinCode)<2){
			strcat(pinCode,"7");
		}
		else{
			arrayLeftShift(pinCode, '7');
		}		
		
	}		
	
	if(*numptr == 6) {
		printf("6");
	  fflush(stdout);
		if(strlen(pinCode)<2){
			strcat(pinCode,"6");
		}
		else{
			arrayLeftShift(pinCode, '6');
		}		
		
	}		
	
	if(*numptr == 5) {
		printf("5");
	  fflush(stdout);
		if(strlen(pinCode)<2){
			strcat(pinCode,"5");
		}
		else{
			arrayLeftShift(pinCode, '5');
		}		
		
	}		
	
	if(*numptr == 4) {
		printf("4");
	  fflush(stdout);
		if(strlen(pinCode)<2){
			strcat(pinCode,"4");
		}
		else{
			arrayLeftShift(pinCode, '4');
		}		
		
	}		
	
	if(*numptr == 3) {
		printf("3");
	  fflush(stdout);
		if(strlen(pinCode)<2){
			strcat(pinCode,"3");
		}
		else{
			arrayLeftShift(pinCode, '3');
		}
				
	}		
	
	if(*numptr == 2) {
		printf("2");
		fflush(stdout);
		if(strlen(pinCode)<2){
			strcat(pinCode,"2");
		}
		else{
			arrayLeftShift(pinCode, '2');
		}
				
		
	}		
	
	if(*numptr == 1) {
		printf("1");
	  fflush(stdout);
		if(strlen(pinCode)<2){
			strcat(pinCode,"1");
		}
		else{
			arrayLeftShift(pinCode, '1');
		}
		
	}		
	
	
}


/****************************************
*Brief: 
*
****************************************/
void arrayLeftShift(char pinCode[],char key){
	volatile int i;
	for (i=0;i<2;i++){
		pinCode[i] = (i<1)? pinCode[i+1] : key;
	}
	
}
/****************************************
*Brief: 
*
****************************************/
uint16_t char_to_int(char pinCode[]){
	uint16_t tens;
	uint16_t ones;
	uint16_t num;
	
	tens = pinCode[0]-'0';
	ones = pinCode[1]-'0';
	
	num = (tens*10)+ones;
	
	return num;
}
/****************************************
*Brief: 
*
****************************************/
uint8_t Read_Keypad(uint8_t *numptr){
	uint8_t col, row = 0;
	for(col=0; col<3; col++){
		GPIOC->MODER &= ~(uint32_t)((0x03<<(2*Hex2Bit(C0)))|(0x03<<(2*Hex2Bit(C1)))|(0x03<<(2*Hex2Bit(C2)))); //clear MODER for columns
		
		GPIOC->MODER |= (uint32_t)(1<<((col*4)+16)); // set column as output
		GPIOC->ODR &=~(uint32_t)(1<<((col*2)+8)); //write odr to make column output LOW
		
		SysTick_Delay(10);
		
		row = GPIOC -> IDR & (1<<(R0)|R1|R2|R3);
		
		while(!(GPIOC->IDR & 1<<(R0))|!(GPIOC->IDR & R1)|!(GPIOC->IDR & R2)|!(GPIOC->IDR & R3));
		
		if(row != (1<<R0 | R1 | R2 | R3)){ // If one of the key pad buttos is pressed, break out of the for loop, so decoding can begin
			break;
		}
		
	}
		GPIOC->MODER &= ~(uint32_t)((0x03<<(2*Hex2Bit(C0)))|(0x03<<(2*Hex2Bit(C1)))|(0x03<<(2*Hex2Bit(C2)))); //clear MODER for columns
		if(col == 3) return 0;
		if(row == (        R1|R2|R3)) *numptr =     col + 1; 
	  if(row == (1<<(R0)   |R2|R3)) *numptr = 3 + col + 1; 
	  if(row == (1<<(R0)|R1   |R3)) *numptr = 6 + col + 1; 
	  if(row == (1<<(R0)|R1|R2   )) *numptr = 9 + col + 1; 
	
	  return 1;
}
