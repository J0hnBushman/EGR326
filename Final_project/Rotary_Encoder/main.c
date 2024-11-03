#include "stm32f446xx.h"
#include "rotary_encoder.h"



int main(void){
	ONBOARD_LED_MODER(OUTPUT);
	Encoder_init();
	unsigned int MENU_OPTIONS=0;

	
	
	
	while(1){
		MENU_OPTIONS = (TIM2->CNT)/2;
		
		
		
	}
return 0;
}
