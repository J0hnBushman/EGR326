#include "stm32f446xx.h"
#include "health_bar.h"

int main(void){
	SysTick_Init();
	init_ShiftRegister();
	HealthPlusPlus();
	while(1){
		
	}
	
	return 0;
}