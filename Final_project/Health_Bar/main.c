#include "stm32f446xx.h"
#include "health_bar.h"
#include "sevenSeg.h"

int main(void){
	tim5_init();
	init_ShiftRegister();
	sevenSeg_init();
	Init_seq();
	//HealthPlusPlus();
	while(1){
		HealthCurrent();
	}
	
	return 0;
}