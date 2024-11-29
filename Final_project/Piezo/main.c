#include "stm32f446xx.h"
#include "Piezo.h"


int main(void){
	int i = 0;
	
	
	while(1){
		
		Buzzer_PlayTone(NOTE_B2, 500);
		Buzzer_PlayTone(NOTE_D2, 500);
		Buzzer_PlayTone(NOTE_E2, 500);
		
		
	}
	
	
	
	return 0;
}