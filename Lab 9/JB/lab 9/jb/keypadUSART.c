#include "keypadUSART.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**************************************************************** 
Brief: This function sets up the GPIOC pins and puts pullup resistors on the row pins
param: void
return: void
****************************************************************/

void keypadInit(void){
	
	RCC->AHB1ENR |= BIT(PC);
	GPIOC->MODER &=~(uint32_t) (SHIFT(2*R0,3)|SHIFT(2*R1,3)|SHIFT(2*R2,3)|SHIFT(2*R3,3)|SHIFT(2*C0,3)|SHIFT(2*C1,3)|SHIFT(2*C2,3));  //Clears row and column pins
	GPIOC->PUPDR &=~(uint32_t) (SHIFT(2*R0,3)|SHIFT(2*R1,3)|SHIFT(2*R2,3)|SHIFT(2*R3,3));	//Clears all bits in PUPDR
	GPIOC->PUPDR |= (uint32_t) (SHIFT(2*R0,1)|SHIFT(2*R1,1)|SHIFT(2*R2,1)|SHIFT(2*R3,1));	//Sets specific bits to put pull up resistors on row pins
	// R0-R3: pull up, C0-C2: High Z (no pull up/down)
}

/**************************************************************** 
Brief: This function reads inputs from keyapd and returns a int that holds the bit locations that have been pressed in key
param: Void
return: The 16 bit int key
****************************************************************/
uint16_t readKeypad(void){
	
	uint16_t key = 0;
	
		GPIOC->MODER |= (uint32_t) (0x01<<(2*C0));// Set Column 0 to an Output
		GPIOC->ODR &=~(uint32_t) (1<<(C0));// Set Column 1 to GND
		key |= (readRow() & 0xFFFF ) << 0x00;//Set readRow to Key and shift it 0 bits to the left
		GPIOC->MODER &=~ (uint32_t) (0x03<<(2*C0));// Set Column 0 back to an input
		
		
		GPIOC->MODER |= (uint32_t) (0x01<<(2*C1));// Set Column 1 to an Output
		GPIOC->ODR &=~(uint32_t) (1<<(C1));// Set Column 1 to GND
		key |= (readRow() & 0xFFFF ) << 0x04;//Set readRow to Key and shift it 4 bits to the left
		GPIOC->MODER &=~ (uint32_t) (0x03<<(2*C1));// Set Column 1 back to an input
	
	
		GPIOC->MODER |= (uint32_t) (0x01<<(2*C2));// Set Column 2 to Output
		GPIOC->ODR &=~(uint32_t) (1<<(C2));// Set Column 2 to GND
		key |= (readRow() & 0xFFFF ) << 0x08;//Set readRow to Key and shift it 8 bits to the left
		GPIOC->MODER &=~ (uint32_t) (0x03<<(2*C2));// Set Column 2 back to an input
		
	
		return key;
}


/**************************************************************** 
Brief: This function determines what rows have been pressed in a column (active low)
param: void
return: returns a int that holds certain bits based off whether a button in the row has been pressed
****************************************************************/
uint8_t readRow(void){
	uint8_t rowsPressed = 0x00;
	SysTick_Delay(10);
	rowsPressed |=  (!(GPIOC->IDR & (BIT(R0))) ? 1<<0x00: 0);//Checks if specific row is pressed if pressed it will shift that 1 to the desired row bit (left shift 0 bits)
	rowsPressed |=  (!(GPIOC->IDR & (BIT(R1))) ? 1<<0x01: 0);//Checks if specific row is pressed if pressed it will shift that 1 to the desired row bit (left shift 1 bits)
	rowsPressed |=  (!(GPIOC->IDR & (BIT(R2))) ? 1<<0x02: 0);//Checks if specific row is pressed if pressed it will shift that 1 to the desired row bit (left shift 2 bits)
	rowsPressed |=  (!(GPIOC->IDR & (BIT(R3))) ? 1<<0x03: 0);//Checks if specific row is pressed if pressed it will shift that 1 to the desired row bit (left shift 3 bits)
	
	return rowsPressed;
}


/**************************************************************** 
Brief: This function aissgns characters to the array based from inputs from keyapd
param: Takes in 16 bit int Key and the the pointer of carray
return: void
****************************************************************/

void decodeKeypad(uint16_t key, char *carray){
	uint8_t place = 0;
	key & 1<<0x07 ? carray[place++] = 0 : 0;//prints 0 if Bit 7 is set in uint16_t key 
	key & 1<<0x00 ? carray[place++] = 1 : 0;//prints 0 if Bit 0 is set in uint16_t key 
	key & 1<<0x04 ? carray[place++] = 2 : 0;//prints 0 if Bit 4 is set in uint16_t key
	key & 1<<0x08 ? carray[place++] = 3 : 0;//prints 0 if Bit 8 is set in uint16_t key
	key & 1<<0x01 ? carray[place++] = 4 : 0;//prints 0 if Bit 1 is set in uint16_t key
	key & 1<<0x05 ? carray[place++] = 5 : 0;//prints 0 if Bit 5 is set in uint16_t key
	key & 1<<0x09 ? carray[place++] = 6 : 0;//prints 0 if Bit 9 is set in uint16_t key
	key & 1<<0x02 ? carray[place++] = 7 : 0;//prints 0 if Bit 2 is set in uint16_t key
	key & 1<<0x06 ? carray[place++] = 8 : 0;//prints 0 if Bit 6 is set in uint16_t key
	key & 1<<0x0A ? carray[place++] = 9 : 0;//prints 0 if Bit 10 is set in uint16_t key
	key & 1<<0x0B ? carray[place++] = 10 : 0;//prints 0 if Bit 11 is set in uint16_t key
	key & 1<<0x03 ? carray[place++] = 11 : 0;//prints 0 if Bit 3 is set in uint16_t key
	
	carray[place] = '\0';
	
}

	
/**************************************************************** 
Brief: This function delays the code for a certain amount of time based from the input delayTime
param: delayTime (usigned int)
return: void
****************************************************************/
	
void SysTick_Delay(unsigned int delayTime){
// Systick delay function
	SysTick->CTRL = 0; // disable SysTick During CTRL
	SysTick->LOAD = ((delayTime * 16000) - 1); //delay for 1 usecond per delay value
	SysTick->VAL = (unsigned long)0x00000000; // any write to CVR clears it
	SysTick->CTRL = (unsigned long)0x00000005; // enable systic, 16MHz, No Interrupts
	
		while(((SysTick->CTRL) & 0x00010000) == 0); // wait for flag to be SET	
		
	}

	
	/***************************************************************
* Brief:  Sets up the USART2 for TX on pin PA2 and Rx on Pin PA3
* param:  None
* return: None
****************************************************************/

void USART_Init(void){

RCC->AHB1ENR  |= 1;             //Set the GPIO clock on Port A
RCC->APB1ENR  |= 0x20000;       //Set the clock for the UART
/** USART Rx **/
GPIOA->AFR[0] |= 0x7000;
GPIOA->MODER  |= 0x0080;
/** USART Tx **/
GPIOA->AFR[0] |= 0x0700;
GPIOA->MODER  |= 0x0020;

USART2->BRR    = 0x0683;        //set 9600 baud rate
USART2->CR1    = 0x000C;        //set TX and RX 8 bits
USART2->CR2    = 0x0000;        //1 stop bit
USART2->CR3    = 0x0000;        //no flow control
USART2->CR1   |= 0x2000;        //enable USART2

}

/***************************************************************
* Brief:  waits for Tx to be open then sends one character
* param:  one character
* return: None
****************************************************************/
void USART2_write_char (int ch){
	while(!(USART2->SR & 0x0080)) {}    //wait until Tx buffer is empty
	USART2->DR = (ch & 0xFF);
}

/***************************************************************
* Brief:  Loops through the characters in the string and sends
* each one through USART.
* param:  string line
* return: None
****************************************************************/
void USART2_write(char *line, uint16_t u16_size){
	for(uint16_t u16_string_inc = 0; u16_string_inc < u16_size; u16_string_inc++)
		USART2_write_char(line[u16_string_inc]);
}

/***************************************************************
* Brief:  Waits for the character and then returns the data
* from the data register
* param:  none
* return: Character from the USART data register
****************************************************************/
char USART2_read_char(void){
	while (!(USART2->SR & 0x0020)) {;}   //wait until char arrives
	return USART2->DR;
}





