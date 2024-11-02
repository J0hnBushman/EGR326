#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdint.h>
#include <string.h>
#include "stm32f4xx.h"



//Macro Functions
#define BIT(x) (uint32_t) (1<<x)
#define SHIFT(x,y) (uint32_t) (y<<x)

#define PC 2

#define C0 9
#define C1 10
#define C2 12

#define R0 0
#define R1 2
#define R2 4
#define R3 5


void SysTick_Delay(unsigned int delayTime);
void keypadInit(void); //Initiallized the GPIO to read the keypad.
uint16_t readKeypad(void); //Returns the state of all of the keypad buttons in the return value at the moment the function is called.
void decodeKeypad(uint16_t, char *); //Takes the state of the keypad and returns (by reference) an array of the key's pressed.
uint8_t readRow(void);

void USART_Init(void);
void USART2_write_char (int ch);
void USART2_write(char *line, uint16_t u16_size);