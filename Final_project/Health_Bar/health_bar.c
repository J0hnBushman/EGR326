#include "health_bar.h"

/*
3 pins control the operation of the 74HC595 Shift Register:

'SER'   - Data pin
'RCLK'  - Latch Pin
'SRCLK' - Clock Pin

The 8 parallel data output pins are the pins that we are
loading our output data on.

To get the desired data on the parallel data output pins,
perform the following steps:

1) Set the 'Latch' Pin low so that data can be received

2) Load the desired output data for QH on to the data pin.

3) Pulse the Clock pin to accept the desired data for QH.

4) Load the desired output data for QG on to the data pin.

5) Pulse the Clock pin to accept the desired data for QG.

6) Repeat steps 2 and 3 for pins QF ? QA

7) Set the 'Latch' Pin high to accept the data


_______________________________
                               |
Colors for Shift Register Bits |
                               |
Q0	Q1	Q2	Q3	Q4	Q5	Q6	Q7 |
R		R		O		O		Y		Y		G		G  |
_______________________________|

*/

static uint8_t health = 5;

void init_ShiftRegister(void){
	
	RCC->AHB1ENR |= (1<<2);
	
	DATA_MODER(OUTPUT);
	LATCH_MODER(OUTPUT);
	CLOCK_MODER(OUTPUT);
	
	DATA_OUT(LOW);
	LATCH_OUT(HIGH);
	CLOCK_OUT(HIGH);
	
}

void init_Health_Timer(void){
	
	
	
}

uint8_t HealthMinusMinus(void){
	if(health==0){
	return 0;
	}
	health--;
	uint8_t i;
	HealthClear();
	
	CLOCK_OUT(LOW);
	LATCH_OUT(LOW);
	CLOCK_OUT(HIGH);
	
	
	for(i=0;i<health;i++)
	{
		CLOCK_OUT(LOW);
		
		DATA_OUT(HIGH);
		
		CLOCK_OUT(HIGH);
		

	}
	
	CLOCK_OUT(LOW);
	LATCH_OUT(HIGH);
	CLOCK_OUT(HIGH);
	
	return 1;
	
}

uint8_t HealthPlusPlus(void){
	
	if(health==8){
	return 0;
	}
	
	health++;
	uint8_t i;
	HealthClear();
	
	CLOCK_OUT(LOW);
	LATCH_OUT(LOW);
	CLOCK_OUT(HIGH);
	
	
	for(i=0;i<health;i++)
	{
		CLOCK_OUT(LOW);
		
		DATA_OUT(HIGH);
		
		CLOCK_OUT(HIGH);
		

	}
	
	CLOCK_OUT(LOW);
	LATCH_OUT(HIGH);
	CLOCK_OUT(HIGH);
	
	return 1;

}

void HealthMax(void){
	health = 8;
	uint8_t i;
	CLOCK_OUT(LOW);
	LATCH_OUT(LOW);
	CLOCK_OUT(HIGH);
	
	for(i=0;i<8;i++)
	{
		CLOCK_OUT(LOW);
		
		DATA_OUT(HIGH);
		
		CLOCK_OUT(HIGH);
		

	}
	
	CLOCK_OUT(LOW);
	LATCH_OUT(HIGH);
	CLOCK_OUT(HIGH);

}

void HealthClear(void){
		uint8_t i;
	CLOCK_OUT(LOW);
	LATCH_OUT(LOW);
	CLOCK_OUT(HIGH);
	
	for(i=0;i<8;i++)
	{
		CLOCK_OUT(LOW);
		
		DATA_OUT(LOW);
		
		CLOCK_OUT(HIGH);
		

	}
	
	CLOCK_OUT(LOW);
	LATCH_OUT(HIGH);
	CLOCK_OUT(HIGH);

}

void SysTick_Init(void)
{
    SysTick->CTRL = 0;
    SysTick->LOAD = 0x00FFFFFF;
    SysTick->VAL = 0;
    SysTick->CTRL |= 5;
}

void delayMS(uint16_t n)
{
    SysTick->LOAD = ((n * 16000) - 1);
    SysTick->VAL = 0;
    while ((SysTick->CTRL & 0x00010000) == 0)
    {
    }
}

void delayMicroS(uint16_t n)
{
    SysTick->LOAD = ((n * 16) - 1);
    SysTick->VAL = 0;
    while ((SysTick->CTRL & 0x00010000) == 0)
    {
    }
}