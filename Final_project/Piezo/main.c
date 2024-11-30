#include "stm32f446xx.h"
#include "Piezo.h"


int main(void){
	__disable_irq();
	Timer7_Init();
	__enable_irq();
	
	Play_Tone_4();
	
	while(1){
		
	}
	
	
	
	return 0;
}