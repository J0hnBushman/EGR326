#include "stm32f446xx.h"
#include "Piezo.h"


int main(void){
	int i = 0;
	
	
	while(1){
		
		
		Buzzer_PlayTone(NOTE_A7, 500);
		Buzzer_PlayTone(NOTE_E7, 500);
		Buzzer_PlayTone(NOTE_E7, 500);
		
		
	}
	
	
	
	return 0;
}