/*********************************************************************************
NAME:
COURSE:
DATE:
DESCRIPTION:
*********************************************************************************/
 
 
 
/*********************************************************************************
																				LIBRARIES
*********************************************************************************/
#include "main.h"

/*********************************************************************************
																				Global Variables
*********************************************************************************/
uint8_t hall_FLAG = 1;
uint8_t hall2_FLAG = 1;
uint8_t swPress = 0; 
uint8_t foodCount = 0; 
int last = 0;
int current; 
double period; 
int pos = 0;
char value = 0;
char timeDate[14];

//inital screen 
int menu = startUpScreen; 
//init state
int state = content;

uint8_t tmp = 0; 
//temp value to create a blue highlight value

//RTC_data and point
char RTC_data;
char *RTC_Data_ptr = &RTC_data;

//RTC VALUES
uint8_t RTC_Hour;
uint8_t RTC_Minute;
uint8_t RTC_Second;

uint8_t RTC_Year;
uint8_t RTC_Month;
uint8_t RTC_Date;
uint8_t RTC_Day;

uint8_t menu_flag = 1;





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
		Encoder_init();
	  stepper_init();
	
	__enable_irq();
	
      while (1)
    {
			switch(state){
//----------------------------content------------------------------
				case(content):
				default:
					menu = ExpContent;
					if(hall_FLAG){
						state = feeding; 
					}
					
					break;
				
				
//------------------------------HAPPY--------------------------------
				case(happy):
					menu = ExpHappy;
				
					break;

				
//-----------------------------HUNGRY-----------------------------------
				case(hungry):
					menu = ExpHungry;
				
								
					break;
				
				
//-------------------------------SLEEPY---------------------------------
				case(sleepy):
					menu = ExpSleepy;
				
					break;
				
		
//-------------------------------DEAD---------------------------------
				case(dead):
					menu = ExpDead;
				
					break;
				
				
//-------------------------------FEEDING---------------------------------
				case(feeding):
					menu = ExpFeeding;
				
				while(hall_FLAG){
				MENU_SCREENS();
				}
					state = content;
					break;
			}
			
			
			MENU_SCREENS(); //displays the timer menu options, currently workin on this 
			//**NOTE** THIS HAS A LOT OF WHILE LOOPS SO IMMA NEED TO GO BACK AND 
			
			
		}
}











/*********************************************************************************
																				EXTI15_10_Handler
*********************************************************************************/
	void EXTI15_10_IRQHandler(void){
		//hall_flag = 1;

		if(EXTI->PR & 1<<HALL_PIN){
			foodCount ++;
			
				if((HALL_IN) && hall_FLAG == 1){
					hall_FLAG = 0; 
				}else if((HALL_IN) == 0 && hall_FLAG == 0){
					hall_FLAG = 1; 
				}
				
			}
		
			if(EXTI->PR & 1<<HALL2_PIN){
			
				if((HALL2_IN) && hall2_FLAG == 1){
					hall2_FLAG = 0; 
				}else if((HALL2_IN) == 0 && hall2_FLAG == 0){
					hall2_FLAG = 1; 
				}
				
			}
			
		if(EXTI->PR & 1<<BTN1_PIN){
			
		}
			
		EXTI->PR |= (1<<HALL_PIN)|(1<<BTN1_PIN)|(1<<HALL2_PIN);
}
	




/*********************************************************************************
																				EXTI4_Handler
*********************************************************************************/
	void EXTI4_IRQHandler(void){
		swPress ++;
		
		
		//***TIME SET MENU ****
		if(menu == timMenu){
				//used to display the correct value when moving cursor in menu
			if(swPress%4 == 0){
					TIM2->CNT = pos*2; //keeps the current position value 
			}else{
					TIM2->CNT = value*2; //keeps current value 
			}
		
			if(pos == 13){
				menu_flag = 0;
			}
		
			if(pos == 12){
				menu_flag = 0;
				RTC_Second = 0; //these should probably be the current value, not zero but I'll have to change it afer more testing
				RTC_Minute = 0;
				RTC_Hour = 0;
				RTC_Date = 0;
				RTC_Month = 0;
				RTC_Year = 0;
			}
	}
		
		//****MAIN MENU*****
	if(menu == mainMenu){
		menu_flag = 0;
		if(pos == 0){
			menu = timMenu;
		}else if(pos == 1){
			menu = helpMenu;
		}else{
			menu = infoMenu;
		}
	}
	
	//****HELP MENU******
	if(menu == helpMenu){
		menu_flag = 0;
	}
	
	//****INFO MENU******
	if(menu == infoMenu){
		menu_flag = 0;
	}
	
	if(menu == startUpScreen){
		menu_flag = 0;
	}
	
	if(menu == settings){
		menu_flag = 0; 
	}
	
	
		EXTI->PR |= (1<<4);
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
// READ Date

 * @brief: Prompts the user to set the registers of the RTC controlling the month, day, year and date
 * 
 * @param[in] NULL
 * 
 * @return: NULL
 ===========================================================================================*/
void Read_Date(void){
	//read the current hour from the RTC, stores value in the RTC_data pointer
	I2C1_byteRead(SLAVE_ADDR, HOURS_ADDR, RTC_Data_ptr);
	Draw_Char_BG(10, 5, MSB(RTC_data), WHITE, BLACK, &font_ubuntu_mono_24);
	Draw_Char_BG(20, 5, LSB(RTC_data), WHITE, BLACK, &font_ubuntu_mono_24);
	Draw_Char_BG(30, 5, ':', WHITE, BLACK, &font_ubuntu_mono_24);
	//read the current min from the RTC, stores value in the RTC_data pointer
	I2C1_byteRead(SLAVE_ADDR, MINUTES_ADDR, RTC_Data_ptr);
	Draw_Char_BG(40, 5, MSB(RTC_data), WHITE, BLACK, &font_ubuntu_mono_24);
	Draw_Char_BG(50, 5, LSB(RTC_data), WHITE, BLACK, &font_ubuntu_mono_24);
	Draw_Char_BG(60, 5, ':', WHITE, BLACK, &font_ubuntu_mono_24);
	//read the current second from the RTC, stores value in the RTC_data pointer
	I2C1_byteRead(SLAVE_ADDR, SECONDS_ADDR, RTC_Data_ptr);
	Draw_Char_BG(70, 5, MSB(RTC_data), WHITE, BLACK, &font_ubuntu_mono_24);
	Draw_Char_BG(80, 5, LSB(RTC_data), WHITE, BLACK, &font_ubuntu_mono_24);
		//read the current hour from the RTC, stores value in the RTC_data pointer
	I2C1_byteRead(SLAVE_ADDR, HOURS_ADDR, RTC_Data_ptr);
	Draw_Char_BG(190, 5, MSB(RTC_data), WHITE, BLACK, &font_ubuntu_mono_24);
	Draw_Char_BG(200, 5, LSB(RTC_data), WHITE, BLACK, &font_ubuntu_mono_24);
	Draw_Char_BG(210, 5, '/', WHITE, BLACK, &font_ubuntu_mono_24);
	//read the current min from the RTC, stores value in the RTC_data pointer
	I2C1_byteRead(SLAVE_ADDR, MINUTES_ADDR, RTC_Data_ptr);
	Draw_Char_BG(220, 5, MSB(RTC_data), WHITE, BLACK, &font_ubuntu_mono_24);
	Draw_Char_BG(230, 5, LSB(RTC_data), WHITE, BLACK, &font_ubuntu_mono_24);
	Draw_Char_BG(240, 5, '/', WHITE, BLACK, &font_ubuntu_mono_24);
	//read the current second from the RTC, stores value in the RTC_data pointer
	I2C1_byteRead(SLAVE_ADDR, SECONDS_ADDR, RTC_Data_ptr);
	Draw_Char_BG(250, 5, MSB(RTC_data), WHITE, BLACK, &font_ubuntu_mono_24);
	Draw_Char_BG(260, 5, LSB(RTC_data), WHITE, BLACK, &font_ubuntu_mono_24);
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
	TIM2->ARR = 27;
	
	while(menu_flag){
		//set up position to change based on the interupt from the rotary encoder
		//I want to set this such that when the btn on Rotary is pressed the interupt no longer changes position but changes value
		//this should be the math to cahnge this, I have to do this instead of using a flag due to the inturrtp counting twice
		
		if(swPress%4 == 0){
				tmp = pos;
				pos = TIM2->CNT/2;
				value = timeDate[pos];
			if(pos != tmp){
				if(tmp<=11){
					Draw_Char_BG(180+((tmp%2)*20), 30+((tmp/2)*30), (timeDate[tmp] + '0'), BLACK, WHITE, &font_ubuntu_mono_24);
				}else if(tmp == 12){
					Draw_String_BG(20, 210, "Cancel", BLACK, WHITE, &font_ubuntu_mono_24);
				}else{
					Draw_String_BG(180, 210, "Enter", BLACK, WHITE, &font_ubuntu_mono_24);
				}
				
			}
		}else{
				value = TIM2->CNT/2;
				timeDate[pos] = value;
		}
		
		//PRINTS THE CURRENT POSITION AND VALUE 
		if(pos<=11){
			Draw_Char_BG(180+((pos%2)*20), 30+((pos/2)*30), (value + '0'), BLACK, BLUE, &font_ubuntu_mono_24);
		}else if(pos == 12){
			Draw_String_BG(20, 210, "Cancel", BLACK, BLUE, &font_ubuntu_mono_24);
		}else{
			Draw_String_BG(180, 210, "Enter", BLACK, BLUE, &font_ubuntu_mono_24);
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
// MENU SCREENS

 * @brief: DISPLAYS DIFFERENT MENU OPTIONS AND SCREEN FOR DIFFERENT STATES IN THE PROGRAM
 * 
 * @param[in] NULL
 * 
 * @return: NULL
 ===========================================================================================*/
void MENU_SCREENS(void){
	
				switch(menu){

//--------------------------MAIN MENU-----------------------------
				case mainMenu:
					default:
							menu_flag = 1;
							Fill_Rect(12, 30, 288, 226, WHITE); //Moves sp l to R, moves sp t to b /*NOTE THIS IS JUST TO CLEAR THE OLD TXT THERE, while keep the time at top*/
								TIM2->CNT = 0; 
								pos = 0;
						TIM2->ARR = 5;
							while(menu_flag){
								Read_Date();
								pos = TIM2->CNT/2; //set position
								
								if(pos == 0){
							Draw_String_BG(40, 80, "Time Set:", BLACK, BLUE, &font_ubuntu_mono_24);
							Draw_String_BG(40, 120, "Help:", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(40, 160, "More Info:", BLACK, WHITE, &font_ubuntu_mono_24);
								}else if(pos == 1){
							Draw_String_BG(40, 80, "Time Set:", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(40, 120, "Help:", BLACK, BLUE, &font_ubuntu_mono_24);
							Draw_String_BG(40, 160, "More Info:", BLACK, WHITE, &font_ubuntu_mono_24);
								}else{
							Draw_String_BG(40, 80, "Time Set:", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(40, 120, "Help:", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(40, 160, "More Info:", BLACK, BLUE, &font_ubuntu_mono_24);
								}
							}
				break;
					
							
//--------------------TIME SET MENU-------------------------------
				case timMenu:	
					menu_flag = 1; 
							Fill_Rect(12, 30, 288, 226, WHITE);
							Draw_String_BG(20, 30, "Set Second:", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(20, 60, "Set Minute:", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(20, 90, "Set Hour:", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(20, 120, "Set date:", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(20, 150, "Set Month:", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(20, 180, "Set Year:", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(20, 210, "Cancel", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(180, 210, "Enter", BLACK, WHITE, &font_ubuntu_mono_24);
				
				
				
							Draw_String_BG(180, 30, "0", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(180, 60, "0", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(180, 90, "0", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(180, 120, "0", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(180, 150, "0", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(180, 180, "0", BLACK, WHITE, &font_ubuntu_mono_24);
				
							Draw_String_BG(200, 30, "0", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(200, 60, "0", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(200, 90, "0", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(200, 120, "0", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(200, 150, "0", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(200, 180, "0", BLACK, WHITE, &font_ubuntu_mono_24);
				
							Set_TD();
				menu = mainMenu;
				menu_flag = 1;
					break;
				
//--------------------------------HELP MENU------------------------------------------
				case helpMenu:
					Read_Date();
					menu_flag = 1;
					TIM2->ARR = 3;
						Fill_Rect(12, 30, 288, 226, WHITE);//Moves sp l to R, moves sp t to b /*NOTE THIS IS JUST TO CLEAR THE OLD TXT THERE, while keep the time at top*/
						while(menu_flag){
							Draw_String_BG(20, 120, "HELP MENU SCREEN", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(20, 160, "Press to contiune", BLACK, WHITE, &font_ubuntu_mono_24);
						}
						menu = mainMenu;
				break;
				
				
//------------------------------------INFO MENU---------------------------------------
				case infoMenu:
					Read_Date();
					menu_flag = 1; 
						Fill_Rect(12, 30, 288, 226, WHITE);  //Moves sp l to R, moves sp t to b /*NOTE THIS IS JUST TO CLEAR THE OLD TXT THERE, while keep the time at top*/
						while(menu_flag){
							Draw_String_BG(20, 120, "INFO MENU SCREEN:", BLACK, WHITE, &font_ubuntu_mono_24);
							Draw_String_BG(20, 160, "Press to contiune", BLACK, WHITE, &font_ubuntu_mono_24);
						}
						menu = mainMenu;
				break;
				
				
//-------------------------------------START UP SCREEN------------------------------------
				case startUpScreen:
					menu_flag = 1;
					Fill_Rect(12, 30, 288, 226, WHITE); //Moves sp L to R, moves sp t to b /*NOTE THIS IS JUST TO CLEAR THE OLD TXT THERE, while keep the time at top*
					Rotate_Display(1); //landscape inverted
					//Draw_Bitmap((TFT_WIDTH - testImage->width) / 2, (TFT_HEIGHT - testImage->height) / 2, testImage); // Displays a scaled image of an apple. (Small to maintain 32kB flash limit on Keil)
						//delayMS(3000);
						Fill_Screen(BLACK);
				while(menu_flag){}
				menu = mainMenu;
				break;
				
				
//-----------------------------------------SETTINGS-----------------------------------------
				case settings:
					menu_flag = 1;
					TIM2->ARR = 3;
								TIM2->CNT = 0; 
								pos = 0;
					Fill_Rect(12, 30, 288, 226, WHITE); //Moves sp L to R, moves sp t to b /*NOTE THIS IS JUST TO CLEAR THE OLD TXT THERE, while keep the time at top*/
					Draw_String_BG(20, 80, "Open Settings?", BLACK, WHITE, &font_ubuntu_mono_24);
					while(menu_flag){
						
						Draw_String_BG(20, 120, "Yes", BLACK, WHITE, &font_ubuntu_mono_24);
					}
					break;
					
					
//-----------------------------------------CONTENT-----------------------------------------
				case ExpContent:
					Rotate_Display(0);
					Draw_Bitmap((TFT_WIDTH - testImage->width) / 2, (TFT_HEIGHT - testImage->height) / 2, testImage); // Displays a scaled image of an apple. (Small to maintain 32kB flash limit on Keil)
					Fill_Rect(10, 10, 30, 30, WHITE); //Moves sp L to R, moves sp t to b /*NOTE THIS IS JUST TO CLEAR THE OLD TXT THERE, while keep the time at top*/
				break;
				
				
//-----------------------------------------HAPPY-----------------------------------------
				case ExpHappy:
					Fill_Rect(12, 30, 288, 226, GREEN);
					break;
				
				
//-----------------------------------------HUNGRY-----------------------------------------
				case ExpHungry:
					Fill_Rect(12, 30, 288, 226, BRIGHT_TEAL);
					break;
				
				
//-----------------------------------------SLEEPY-----------------------------------------
				case ExpSleepy:
					Fill_Rect(12, 30, 288, 226, SKY_BLUE);
					break;
				
				
//-----------------------------------------DEAD-----------------------------------------
				case ExpDead:
					Fill_Rect(12, 30, 288, 226, GRAY);
					break;
				
//-----------------------------------------feeding----------------------------------------
				case ExpFeeding:
					Fill_Rect(12, 30, 288, 226, PURPLE);
					break;
				
			}
				
}



// EOF



