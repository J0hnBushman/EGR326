#include "stm32f446xx.h"
#include "health_bar.h"

int main(void){
	tim5_init();
	init_ShiftRegister();
	//HealthPlusPlus();
	HealthCurrent();
	while(1){
		
	}
	
	return 0;
}