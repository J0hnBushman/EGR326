/*********************************************************************************
NAME:
COURSE:
DATE:
DESCRIPTION:
*********************************************************************************/
 
 
 
/*********************************************************************************
																				LIBRARIES
*********************************************************************************/
#include "ILI9341.h"
#include "RccConfig.h"
#include "font_ubuntu_mono_24.h"
#include "font_freemono_mono_bold_24.h"
#include "my_photos.h"
#include "spi.h"
#include "I2C.h"
#include "main.h"
#include "hall.h"
#include "TIMERS.h"
#include "stepper.h"
#include <stdlib.h>
#include <stm32f446xx.h>



/*********************************************************************************
																				Global Variables
*********************************************************************************/
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




/*********************************************************************************
																				MAIN
*********************************************************************************/
int main(void)
{
	__disable_irq();
	
//=====initilaztion functions=====
	  hallEffect_pinInit();
    Display_Init(); 
		timer_init();
		I2C_init();
	  stepper_init();
	
	__enable_irq();
	
		//Start up Screen
		MENU_SCREENS(startUpScreen);
	
      while (1)
    {
			MENU_SCREENS(settings); //displays the timer menu options, currently workin on this 
    }
}








/*********************************************************************************
																				EXTI15_10_Handler
*********************************************************************************/
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
	




/*********************************************************************************
																				TIM3_Handler
*********************************************************************************/
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










/*===========================================================================================
// Set Date and date

 * @brief: Prompts the user to set the registers of the RTC controlling the month, day, year and date
 * 
 * @param[in] NULL
 * 
 * @return: NULL
 ===========================================================================================*/
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






/*===========================================================================================
// Set Date and date

 * @brief: Prompts the user to set the registers of the RTC controlling the month, day, year and date
 * 
 * @param[in] NULL
 * 
 * @return: NULL
 ===========================================================================================*/
void MENU_SCREENS(int menu){
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
					menu = helpMenu;
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
				
				case startUpScreen:
					Rotate_Display(3); //landscape inverted
					Draw_Bitmap((TFT_WIDTH - testImage->width) / 2, (TFT_HEIGHT - testImage->height) / 2, testImage); // Displays a scaled image of an apple. (Small to maintain 32kB flash limit on Keil)
						delayMS(3000);
						Fill_Screen(BLACK);
						Fill_Rect(10, 50, 280, 140, WHITE); //Moves sp l to R, moves sp t to b /*NOTE THIS IS JUST TO CLEAR THE OLD TXT THERE, while keep the time at top*/
					break;
				
				case settings:
					Fill_Rect(10, 50, 280, 140, WHITE); //Moves sp l to R, moves sp t to b /*NOTE THIS IS JUST TO CLEAR THE OLD TXT THERE, while keep the time at top*/
					Draw_String_BG(20, 80, "Open Settings?", BLACK, WHITE, &font_ubuntu_mono_24);
					Draw_String_BG(20, 120, "Yes       No", BLACK, WHITE, &font_ubuntu_mono_24);
					for(int i = 0; i < 60000; i ++);
					break;
			}
}



// EOF



