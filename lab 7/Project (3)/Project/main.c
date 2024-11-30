#include "stm32f446xx.h"
#include "stepper.h"
void msdelay(uint16_t msdelay);
void usdelay(uint16_t usdelay);
void SysTick_Init (void);

int main(void)
{
	stepper_init();
	SysTick_Init();
	while(1)
	{
		stepper_half_step();
		usdelay(2500);
	}
	return 0;
}

void SysTick_Init (void){
	 
	 //Setting SysTick_CTL to disable Systick during a step
	 SysTick -> CTRL	= (unsigned long)0x00000000;
	 
	 //Setting SysTick_LOAD to max reload value
	 SysTick -> LOAD	= (unsigned long)0x00FFFFFF;
	 
	 //Writing SysTick_VAL to to clear it
	 SysTick -> VAL	= (unsigned long)0x00000000;
	 
	 //Enabling SysTick_CTL, 16MHz, No Interrupts
	 SysTick -> CTRL	= (unsigned long)0x00000005;
 }
void msdelay(uint16_t msdelay){
	 //delay for 1 ms delay * (some delay value) //SysTick_LOAD
	 SysTick -> LOAD = ((msdelay * 16000) - 1);
	 
	 //Clearing SysTick_VAL
	 SysTick -> VAL = 0;
	 
	 // Waiting for flag to be set //SysTick_CTL
	 while ( (SysTick -> CTRL & 0x00010000) == 0);
 }
void usdelay(uint16_t usdelay){
	 //delay for 1 ms delay * (some delay value) //SysTick_LOAD
	 SysTick -> LOAD = ((usdelay * 16) - 1);
	 
	 //Clearing SysTick_VAL
	 SysTick -> VAL = 0;
	 
	 // Waiting for flag to be set //SysTick_CTL
	 while ( (SysTick -> CTRL & 0x00010000) == 0);
 }