/*
 * Author: Jacob Clarey
 * Date: 9/21/2024
 * Description: This main file incorporates a ClockConfig setup for the STM32F446RE IC with a SPI ILI9341 Driver code.
 * It shows off a the font and image functions as well as a rectangle screensaver loop.
 * Notes: The included headers and
 * sources are used to drive the LCD, provide images/fonts, and modify the system clock frequency.
 *
 * The wiring used for the ILI9341 module was as follows in the format MCU Pin->Display Pin, GPIOXX->SCK, GPIOXX->MOSI,
 * GPIOXX->CS, GPIOXX->RST, GPIOXX->DCX, 5V->VCC, GND->GND, 3.3V->LED
 *
 * In the ILI9341.h header file, CS, RST, and DCX are modifiable through simply changing the #define values.
 */
 
 
 

#include "ILI9341.h"
#include "RccConfig.h"
#include "font_ubuntu_mono_24.h"
#include "font_freemono_mono_bold_24.h"
#include "my_photos.h"
#include "spi.h"
#include "KP.h"
#include "hall.h"
#include "TIMERS.h"
#include "stepper.h"
#include <stdlib.h>
#include <stm32f446xx.h>

int flag_closed = 1;
int last = 0;
int current; 
double period; 


//*********************************************************************************
//************************************MAIN*****************************************
//*********************************************************************************
int main(void)
{
	//variables for the keypad funciton
		uint16_t key;
		char carray[13];
	
	__disable_irq();
	
	//initilaztion functions
	  hallEffect_pinInit();
		keypadInit();
    Display_Init(); 
		timer_init();
	  stepper_init();

		//Draws a back splash
		Draw_Bitmap((TFT_WIDTH - testImage->width) / 2, (TFT_HEIGHT - testImage->height) / 2, testImage); // Displays a scaled image of an apple. (Small to maintain 32kB flash limit on Keil)
	  delayMS(3000);
	  Fill_Screen(BLACK);
	  Draw_String_BG(20, 150, "Enter a Speed 0-5:", WHITE, BLACK, &font_ubuntu_mono_24);
	
	__enable_irq();
	
      while (1)
    {
			
			
			//IDK THIS IS NOT REALLY WORKING HOW IT IS SUPPOSED TO 
			if(TIM3->SR & 1<<0){
					TIM3->SR &=~ (1<<0);
					stepper_full_step();
			}
			
				
			
			if((TIM4->SR & 2)){
				current = TIM4->CCR1;
				TIM4->CCR1 = 0;
				period = (current - last);
				last = current;
			}
			
			
			if((key = readKeypad())){
				decodeKeypad(key, carray); 
				
				
				Draw_String_BG(70, 180, "    ", WHITE, BLACK, &font_ubuntu_mono_24);
				if((carray[0] == 0x31)||(carray[0] == 0x32)||(carray[0] == 0x33)||(carray[0] == 0x34)||(carray[0] == 0x35)||(carray[0] == 0x30)){
					Draw_String_BG(70, 180, carray, WHITE, BLACK, &font_ubuntu_mono_24);
				}
				
				while(readKeypad() == key); 
			}	
			
    }
}




//***************************EXTI15_10********************************************
	void EXTI15_10_IRQHandler(void){
		//hall_flag = 1;

		if(EXTI->PR & 1<<HALL_PIN){
				if((HALL_IN) && flag_closed == 1){
					flag_closed = 0; 
				}else if((HALL_IN) == 0 && flag_closed == 0){
					flag_closed = 1; 
				}
			}
		EXTI->PR |= (1<<HALL_PIN);
}
	



//*********************TIM3***************************************
void TIM3_IRQHandler(void)
{
	TIM3->SR &= ~0xFFFFU;
}



// EOF
