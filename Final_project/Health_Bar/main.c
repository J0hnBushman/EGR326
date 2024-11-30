#include "stm32f446xx.h"
#include "health_bar.h"

int main(void){
	//SysTick_Init();
	tim5_init();
	init_ShiftRegister();
	//HealthPlusPlus();
	while(1){
		HealthCurrent();
	}
	
	return 0;
}