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
#include "I2C.h"`
#include "hall.h"
#include "TIMERS.h"
#include "stepper.h"
#include <stdlib.h>
#include <stm32f446xx.h>

#define mainMenu 0
#define timMenu 1
#define helpMenu 2
#define infoMenu 3

#define MSB(X)          (((X & 0x70)>>4)+'0')
#define Y_MSB(X)        (((X & 0xF0)>>4)+'0')
#define LSB(X)          ((X & 0x0F)+'0')
#define SLAVE_ADDR      0x68
#define SECONDS_ADDR    0x00
#define MINUTES_ADDR    0x01
#define HOURS_ADDR      0x02
#define DATE_ADDR       0x04
#define MONTH_ADDR      0x05
#define YEAR_ADDR       0x06
#define DAY_ADDR        0x0D

uint8_t flag_closed = 1;
int last = 0;
int current; 
double period; 

uint8_t RTC_Hour;
uint8_t RTC_Minute;
uint8_t RTC_Second;

uint8_t RTC_Year;
uint8_t RTC_Month;
uint8_t RTC_Date;
uint8_t RTC_Day;

uint8_t time_flag = 0;


void Set_Time(uint8_t RTC_Hour, uint8_t RTC_Minute, uint8_t RTC_Second);
void Set_Date(uint8_t RTC_Year, uint8_t RTC_Month, uint8_t RTC_Date);
void Set_TD(void);
void MENU_SCREENS(int screen);



//*********************************************************************************
//************************************MAIN*****************************************
//*********************************************************************************
int main(void)
{
		int menu = timMenu; 
	__disable_irq();
	
	  //initilaztion functions
	  //hallEffect_pinInit();
    Display_Init(); 
		timer_init();
		I2C_init();
	  stepper_init();

		//Draws a back splash
		Draw_Bitmap((TFT_WIDTH - testImage->width) / 2, (TFT_HEIGHT - testImage->height) / 2, testImage); // Displays a scaled image of an apple. (Small to maintain 32kB flash limit on Keil)
	  delayMS(3000);
		Rotate_Display(3); //landscape inverted
		Fill_Screen(BLACK);
		Fill_Rect(10, 50, 280, 140, WHITE); //Moves sp l to R, moves sp t to b /*NOTE THIS IS JUST TO CLEAR THE OLD TXT THERE, while keep the time at top*/

		
	
	__enable_irq();
	
      while (1)
    {
			
			switch(menu){
				case mainMenu:
					default:
							Draw_String_BG(20, 120, "Time Set:", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(20, 140, "Help:", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(20, 160, "More Info:", BLACK, WHITE, &font_ubuntu_mono_24);
					for(int i = 0; i < 60000; i ++);
					menu = timMenu;
					Fill_Rect(10, 50, 280, 140, WHITE); //Moves sp l to R, moves sp t to b /*NOTE THIS IS JUST TO CLEAR THE OLD TXT THERE, while keep the time at top*/
					break;
					
				case timMenu:
					
				
				
				
				
							Draw_String_BG(20, 80, "Set Day:", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(20, 100, "Set Month:", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(20, 120, "Set Year:", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(20, 140, "Set Min:", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(20, 160, "Set hour:", BLACK, WHITE, &font_ubuntu_mono_24);
					for(int i = 0; i < 60000; i ++);
					//menu = helpMenu;
				Fill_Rect(10, 50, 280, 140, WHITE); //Moves sp l to R, moves sp t to b /*NOTE THIS IS JUST TO CLEAR THE OLD TXT THERE, while keep the time at top*/
				
					break;
				
				
				case helpMenu:
						Fill_Rect(10, 50, 280, 140, WHITE); //Moves sp l to R, moves sp t to b /*NOTE THIS IS JUST TO CLEAR THE OLD TXT THERE, while keep the time at top*/
							Draw_String_BG(20, 120, "HELP MENU SCREEN", BLACK, WHITE, &font_ubuntu_mono_24);
					for(int i = 0; i < 60000; i ++);
					menu = infoMenu;
				Fill_Rect(10, 50, 280, 140, WHITE); //Moves sp l to R, moves sp t to b /*NOTE THIS IS JUST TO CLEAR THE OLD TXT THERE, while keep the time at top*/
				break;
				
				
				case infoMenu:
						Fill_Rect(10, 50, 280, 140, WHITE); //Moves sp l to R, moves sp t to b /*NOTE THIS IS JUST TO CLEAR THE OLD TXT THERE, while keep the time at top*/
							Draw_String_BG(20, 120, "INFO MENU SCREEN:", BLACK, WHITE, &font_ubuntu_mono_24);
					for(int i = 0; i < 60000; i ++);
					menu = mainMenu;
				Fill_Rect(10, 50, 280, 140, WHITE); //Moves sp l to R, moves sp t to b /*NOTE THIS IS JUST TO CLEAR THE OLD TXT THERE, while keep the time at top*/
				break;
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




/*===========================================================================================
// Set_Time

 * @brief: Prompts the user to set the registers of the RTC controlling the hours, minutes and seconds
 * 
 * @param[in] NULL
 * 
 * @return: NULL
 ===========================================================================================*/
void Set_Time(uint8_t RTC_Hour, uint8_t RTC_Minute, uint8_t RTC_Second){
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
	I2C1_byteWrite(SLAVE_ADDR,HOURS_ADDR,RTC_Hour);
	I2C1_byteWrite(SLAVE_ADDR,MINUTES_ADDR,RTC_Minute);
	I2C1_byteWrite(SLAVE_ADDR,SECONDS_ADDR,RTC_Second);
}





/*===========================================================================================
// Set Date

 * @brief: Prompts the user to set the registers of the RTC controlling the month, day, year and date
 * 
 * @param[in] NULL
 * 
 * @return: NULL
 ===========================================================================================*/
void Set_Date(uint8_t RTC_Year, uint8_t RTC_Month, uint8_t RTC_Date){
	/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
	I2C1_byteWrite(SLAVE_ADDR,YEAR_ADDR,RTC_Year);
	I2C1_byteWrite(SLAVE_ADDR,MONTH_ADDR,RTC_Month);
	I2C1_byteWrite(SLAVE_ADDR,DATE_ADDR,RTC_Date);
}


void Set_TD(void){
	char timeDate[14];
	int pos = 0;
	uint8_t btn = 0;
	int value = 0; 
	/*FOR REFERENCE:
		-Sec 		0,1
		-Min 		2,3
		-hr	 		4,5
		-date		6,7
		-month	8,9
		-Year		10,11
		-Canel	12,
		-Enter	13
	
	*/
	
	while(time_flag){
		//set up position to change based on the interupt from the rotary encoder
		//I want to set this such that when the btn on Rotary is pressed the interupt no longer changes position but changes value
		
		timeDate[pos] = value; //this assigns the current postion of the array to the value, both the value and postion are change via rotatry encoder 
		
		
		if(pos == 13 && btn){
			time_flag = 0;
		}
		if(pos == 12 && btn){
			time_flag = 0;
				RTC_Second = 0; //these should probably be the current value, not zero but I'll have to change it afer more testing
				RTC_Minute = 0;
				RTC_Hour = 0;
				RTC_Date = 0;
				RTC_Month = 0;
				RTC_Year = 0;
		}
	}
	
	RTC_Second = timeDate[0]<<4 | timeDate[1];
	RTC_Minute = timeDate[2]<<4 | timeDate[3];
	RTC_Hour = timeDate[4]<<4 | timeDate[5];
	RTC_Date = timeDate[6]<<4 | timeDate[7];
	RTC_Month = timeDate[8]<<4 | timeDate[9];
	RTC_Year = timeDate[10]<<4 | timeDate[11];
	
	Set_Time(RTC_Hour, RTC_Minute, RTC_Second);
	Set_Date(RTC_Year, RTC_Month, RTC_Date);
}

// EOF




///I WANNA PUT ALL OF THe differnt screens into this function and have a switch case for whcih one gets displayed idk
void MENU_SCREENS(int screen){
	
}


