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
uint8_t petFlag = 0;
int last = 0;
int current; 
double period; 
int pos = 0;
int servo = 1000;
char value = 0;
char timeDate[14];


//PHOTO SENSOR STUFF
int lightLvl = 0;

//SEVEN SEGMENT STUFF
int count = 60;
int old_count = 0;

int num[] = {0x7E,  //0
							0x30,  //1
							0x6D,  //2
							0x79,  //3
							0x33,  //4
							0x5B,  //5
							0x5F,  //6
							0x70,  //7
							0x7F,  //8
							0x7B,  //9
							0x01}; //-


/***MENU STUFF***/
//inital screen 
int menu = startUpScreen; 
//init state
int state = MENU_STATE;
int prev_state;

//temp valu is for the 
uint8_t tmp = 0;

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

int distance = 0;





/*********************************************************************************
																				MAIN
*********************************************************************************/
int main(void)
{
	__disable_irq();
	
//=====initilaztion functions=====
	  hallEffect_pinInit();
    Display_Init(); 
		I2C_init();
		Encoder_init();
	  stepper_init();
	  sonar_gpio_init();
		TIM1_setup();
		timer_init();
		tim5_init();
		init_ShiftRegister();
		HealthCurrent();
		Init_seq();
		adc_init();
	
	__enable_irq();
	
	 
	menu = mainMenu;
	
      while (1)
    {
			switch(state){
//----------------------------content------------------------------
				case(content):
				default:
					menu = ExpContent;

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
					menu = ExpSleepy;
				
					break;
				
//--------------------------------MENU-------------------------------------
				case(MENU_STATE):
					
				
					break;
			}
			
				MENU_SCREENS(); //change LCD
			
			
			
			/*DISTANCE TAIL WAG*/
			distance = abs(dist());	//get the distance value
			//check servo position
			
			/*CHECK LIGHT LEVEL*/
			lightLvl = Read_ADC();
			
			if(count != old_count){
				old_count = count; 
				sevenSeg_write(0x05, num[count/10]);
				sevenSeg_write(0x04, num[count%10]);
			}

		}
}











/*********************************************************************************
																				EXTI15_10_Handler
*********************************************************************************/
	void EXTI15_10_IRQHandler(void){

		if(EXTI->PR & 1<<HALL_PIN){
			HealthPlusPlus();
			}
		
			
		if(EXTI->PR & 1<<HALL2_PIN){
				petFlag = 1; 
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
		//confirm selected times
			if(pos == 13){
				menu_flag = 0;
			}
		//cancel menu select
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
		}else if(pos == 2){
			menu = infoMenu;
		}else{
			//THIS SET YOU BACK TO THE EXPRESSIONS, 
			//it needs to be adjusted such that you go back to the 
			//previous state not just the content state
			state = content;
			menu_flag = 0;
			menu = ExpContent;
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
	
	//**START UP SCREEN***   //not set up yet
	if(menu == startUpScreen){
		menu_flag = 0;
	}
	//**SETTINGS SCREEN***	//not set up yet
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
	I2C1_byteRead(SLAVE_ADDR, MONTH_ADDR, RTC_Data_ptr);
	Draw_Char_BG(140, 5, MSB(RTC_data), BROWN, WHITE, &font_ubuntu_mono_24);
	Draw_Char_BG(150, 5, LSB(RTC_data), BROWN, WHITE, &font_ubuntu_mono_24);
	Draw_Char_BG(160, 5, '/', BROWN, WHITE, &font_ubuntu_mono_24);
	//read the current min from the RTC, stores value in the RTC_data pointer
	I2C1_byteRead(SLAVE_ADDR, DATE_ADDR, RTC_Data_ptr);
	Draw_Char_BG(170, 5, MSB(RTC_data), BROWN, WHITE, &font_ubuntu_mono_24);
	Draw_Char_BG(180, 5, LSB(RTC_data), BROWN, WHITE, &font_ubuntu_mono_24);
	Draw_Char_BG(190, 5, '/', BROWN, WHITE, &font_ubuntu_mono_24);
	//read the current second from the RTC, stores value in the RTC_data pointer
	I2C1_byteRead(SLAVE_ADDR, YEAR_ADDR, RTC_Data_ptr);
	Draw_Char_BG(200, 5, MSB(RTC_data), BROWN, WHITE, &font_ubuntu_mono_24);
	Draw_Char_BG(210, 5, LSB(RTC_data), BROWN, WHITE, &font_ubuntu_mono_24);
}





/*===========================================================================================
// READ Date

 * @brief: Prompts the user to set the registers of the RTC controlling the month, day, year and date
 * 
 * @param[in] NULL
 * 
 * @return: NULL
 ===========================================================================================*/
void Read_Time(void){
	//read the current hour from the RTC, stores value in the RTC_data pointer
	I2C1_byteRead(SLAVE_ADDR, HOURS_ADDR, RTC_Data_ptr);
	Draw_Char_BG(10, 5, MSB(RTC_data), BROWN, WHITE, &font_ubuntu_mono_24);
	Draw_Char_BG(20, 5, LSB(RTC_data), BROWN, WHITE, &font_ubuntu_mono_24);
	Draw_Char_BG(30, 5, ':', BROWN, WHITE, &font_ubuntu_mono_24);
	//read the current min from the RTC, stores value in the RTC_data pointer
	I2C1_byteRead(SLAVE_ADDR, MINUTES_ADDR, RTC_Data_ptr);
	Draw_Char_BG(40, 5, MSB(RTC_data), BROWN, WHITE, &font_ubuntu_mono_24);
	Draw_Char_BG(50, 5, LSB(RTC_data), BROWN, WHITE, &font_ubuntu_mono_24);
	Draw_Char_BG(60, 5, ':', BROWN, WHITE, &font_ubuntu_mono_24);
	//read the current second from the RTC, stores value in the RTC_data pointer
	I2C1_byteRead(SLAVE_ADDR, SECONDS_ADDR, RTC_Data_ptr);
	Draw_Char_BG(70, 5, MSB(RTC_data), BROWN, WHITE, &font_ubuntu_mono_24);
	Draw_Char_BG(80, 5, LSB(RTC_data), BROWN, WHITE, &font_ubuntu_mono_24);
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
					Draw_Char_BG(180+((tmp%2)*20), 30+((tmp/2)*30), (timeDate[tmp] + '0'), WHITE, BROWN, &font_ubuntu_mono_24);
				}else if(tmp == 12){
					Draw_String_BG(30, 210, "Cancel", WHITE, BROWN, &font_ubuntu_mono_24);
				}else{
					Draw_String_BG(160, 210, "Enter", WHITE, BROWN, &font_ubuntu_mono_24);
				}
				
			}
		}else{
				value = TIM2->CNT/2;
				timeDate[pos] = value;
		}
		
		//PRINTS THE CURRENT POSITION AND VALUE 
		if(pos<=11){
			Draw_Char_BG(180+((pos%2)*20), 30+((pos/2)*30), (value + '0'), WHITE, GRAY, &font_ubuntu_mono_24);
		}else if(pos == 12){
			Draw_String_BG(20, 210, "Cancel", WHITE, GRAY, &font_ubuntu_mono_24);
		}else{
			Draw_String_BG(180, 210, "Enter", WHITE, GRAY, &font_ubuntu_mono_24);
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
	int temp = 0; 
	/*
	HOW THE MENU SYSTEM WORKS:
	NOTE: the order is not always consistant
	Enter a menu screen,
	Menu flag is set, This keeps the user in the menu loop until an option is picked
	A white rectangle clears all old text, 
	The count value and position (which corrisponds to the position of the encoder) is restart (0)
	
	The TIM2->ARR gets addjusted to the amount of menu options that are in the state
	Example:
	main Menu has 5 options
	TIM2->ARR = (5*2)-1;
	
	While Loop()
	Displays the current poisiton of the rotary encoder
	When the switch is pressed an interupt is entered that sets menu flag 
	kicking the user out of the screen and into another one
	*/
	
				switch(menu){

//--------------------------MAIN MENU-----------------------------
				case mainMenu:
					default:
						//RESET VARIABLES
							menu_flag = 1;
							TIM2->CNT = 0; 
							pos = 0;
							TIM2->ARR = 7; //set the number of options
					
							//clear screen then read the date
							Fill_Rect(12, 30, 288, 226, BROWN); //Moves sp l to R, moves sp t to b /*NOTE THIS IS JUST TO CLEAR THE OLD TXT THERE, while keep the time at top*/
							Read_Date();
					
						//display options
							Draw_String_BG(50, 80, "Time Set:", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(50, 120, "Help:", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(50, 160, "More Info:", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(50, 200, "Cancel", WHITE, BROWN, &font_ubuntu_mono_24);
					
							while(menu_flag){
								Read_Time();
								temp = pos; 
								pos = TIM2->CNT/2; //set position
								
								if(temp == pos){
									Draw_String_BG(30, 80+(pos*40), " ", GRAY, GRAY, &font_ubuntu_mono_24);
								}else{
									Draw_String_BG(30, 80+(temp*40), " ", BROWN, BROWN, &font_ubuntu_mono_24);
								}
								
								
							}
				break;
					
							
//--------------------TIME SET MENU-------------------------------
				case timMenu:	
					menu_flag = 1; 
							Fill_Rect(12, 30, 288, 226, BROWN);
							Draw_String_BG(20, 30, "Set Second:", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(20, 60, "Set Minute:", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(20, 90, "Set Hour:", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(20, 120, "Set date:", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(20, 150, "Set Month:", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(20, 180, "Set Year:", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(20, 210, "Cancel", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(180, 210, "Enter", WHITE, BROWN, &font_ubuntu_mono_24);
				
				
				
							Draw_String_BG(180, 30, "0", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(180, 60, "0", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(180, 90, "0", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(180, 120, "0", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(180, 150, "0", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(180, 180, "0", WHITE, BROWN, &font_ubuntu_mono_24);
				
							Draw_String_BG(200, 30, "0", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(200, 60, "0", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(200, 90, "0", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(200, 120, "0", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(200, 150, "0", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(200, 180, "0", WHITE, BROWN, &font_ubuntu_mono_24);
				
							Set_TD();
				menu = mainMenu;
				menu_flag = 1;
					break;
				
//--------------------------------HELP MENU------------------------------------------
				case helpMenu:
					Read_Date();
					menu_flag = 1;
					TIM2->ARR = 3;
					Fill_Screen(BROWN);
							Draw_String_BG(20, 120, "HELP MENU SCREEN", WHITE, BROWN, &font_ubuntu_mono_24);
							Draw_String_BG(20, 160, "Press to contiune", WHITE, BROWN, &font_ubuntu_mono_24);
						while(menu_flag){
							Read_Time();
						}
						menu = mainMenu;
				break;
				
				
//------------------------------------INFO MENU---------------------------------------
				case infoMenu:
					Read_Date();
					menu_flag = 1; 
						Fill_Screen(BROWN);
						Draw_String_BG(20, 120, "INFO MENU SCREEN:", WHITE, BROWN, &font_ubuntu_mono_24);
						Draw_String_BG(20, 160, "Press to contiune", WHITE, BROWN, &font_ubuntu_mono_24);
					while(menu_flag){
							Read_Time();
						}
						menu = mainMenu;
				break;
				
				
//-------------------------------------START UP SCREEN------------------------------------
				case startUpScreen:
					menu_flag = 1;
					Fill_Screen(BROWN);
				while(menu_flag){}
				menu = mainMenu;
				break;
				
				
//-----------------------------------------SETTINGS-----------------------------------------
				case settings:
					menu_flag = 1;
					TIM2->ARR = 3;
								TIM2->CNT = 0; 
								pos = 0;
					Fill_Screen(BROWN);
					Draw_String_BG(20, 80, "Open Settings?", WHITE, BROWN, &font_ubuntu_mono_24);
					while(menu_flag){
						
						Draw_String_BG(20, 120, "Yes", WHITE, BROWN, &font_ubuntu_mono_24);
					}
					break;
					
					
//-----------------------------------------CONTENT-----------------------------------------
				case ExpContent:
					Rotate_Display(2);
					Fill_Screen(BROWN);
					Draw_Bitmap((TFT_WIDTH - contentImage->width) / 2, (TFT_HEIGHT - contentImage->height) / 2, contentImage); // Displays a scaled image of an apple. (Small to maintain 32kB flash limit on Keil)
				break;
				
				
//-----------------------------------------HAPPY-----------------------------------------
				case ExpHappy:
					Rotate_Display(2);
					Fill_Screen(BROWN);
					Draw_Bitmap((TFT_WIDTH - HappyImage->width) / 2, (TFT_HEIGHT - HappyImage->height) / 2, HappyImage); // Displays a scaled image of an apple. (Small to maintain 32kB flash limit on Keil)
					break;
				
				
//-----------------------------------------HUNGRY-----------------------------------------
				case ExpHungry:
					Rotate_Display(2);
					Fill_Screen(BROWN);
					Draw_Bitmap((TFT_WIDTH - HungryImage->width) / 2, (TFT_HEIGHT - HungryImage->height) / 2, HungryImage); // Displays a scaled image of an apple. (Small to maintain 32kB flash limit on Keil)
					break;
				
				
//-----------------------------------------SLEEPY-----------------------------------------
				case ExpSleepy:
					Rotate_Display(2);
					Fill_Screen(BROWN);
					Draw_Bitmap((TFT_WIDTH - SleepyImage->width) / 2, (TFT_HEIGHT - SleepyImage->height) / 2, SleepyImage); // Displays a scaled image of an apple. (Small to maintain 32kB flash limit on Keil)

					break;
				
			}
				
}



void TIM5_IRQHandler(void)
{
	if(state != MENU_STATE){
		count --; 
	if(count <= 0){
		count = 60; 
		HealthMinusMinus();
		}
	}
	
	TIM5->SR &= ~0x0001U;
}


// EOF



