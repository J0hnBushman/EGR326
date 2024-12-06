/*********************************************************************************
NAME:
COURSE:
DATE:
DESCRIPTION:
*********************************************************************************/
/* NOTES TO SELF

- servos all on timer1
- TIM1->CCR1/2/3 -> 1000=LEFT, 1500=CENTER, 2000=RIGHT

	NEXT UP
	
- [x] EEPROM
- [x] WATCHDOG TIMER
- [ ] Only want one servo on at a time
- [x] Add sound to states
- [ ] Want to fix the light sensor to be more precise

- MAYBE Reset the 7-seg timer when fed.
	b/c rn it'll complete the time cycle without losing health, then
	it will lose health on the subsequent cycles like normal.

*/
 
 
/*********************************************************************************
																				LIBRARIES
*********************************************************************************/
#include "main.h"

/*********************************************************************************
																				Global Variables
*********************************************************************************/
typedef struct{
	uint32_t eye;
	uint32_t eyelid;
	uint32_t tongue;
	bool is_close;
}Servo;

Servo Mimic_Servo = {1000,1000,1000,false};
bool test = 0;
bool tongue_wag = 0;

uint8_t random_seconds = 1;
uint32_t random_seconds_counter = 0;

uint8_t swPress = 0; 
uint8_t foodCount = 0; // IN CASE OF ADDING OVERFEEDING
uint8_t petFlag = 0;

bool Expression_Transition = true;

unsigned long long Time_New;
unsigned long long Time_Old;

int last = 0; // FOR MENU SYSTEM
int current;  // FOR MENU SYSTEM
double period; // FOR MENU SYSTEM
int pos = 0; // FOR ROTARY ENCODER
int servo = 1000;
char value = 0; // FOR MENU SYSTEM
char timeDate[14]; // FOR RTC

char* health_ptr;


//PHOTO SENSOR STUFF
int lightLvl = 0;

///////////////// SEVEN SEGMENT STUFF //////////////////////////////
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


///////////////////////// MENU STUFF ////////////////////////////
//inital screen 
int menu = startUpScreen; 
//init state
int state = MENU_STATE;
int prev_state;

//temp valu is for the 
uint8_t tmp = 0;
							
uint8_t CNT_Old;
uint8_t CNT_New;



////////////////////////// RTC VALUES //////////////////////////////
//RTC_data and pointER
char RTC_data;
char *RTC_Data_ptr = &RTC_data;
							
bool refresh_WDT = false;

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
	  
		TIM1_setup();
		tim5_init();
		Timer6_Init();
		Timer7_Init();
		init_ShiftRegister();
		HealthCurrent();
		Init_seq();
		adc_init();
		WDT_init();
		sonar_gpio_init();
	
	__enable_irq();
	
	 
	menu = mainMenu;
	health_ptr = &health;
	
	
	//I2C1_byteWrite(EEPROM_SLAVE_ADDR, MEMORY_1 , health); // Store Current Health on EEPROM
	
	delayMS(5);
	
	//Retrieve_Health(); // Retrieve Current Health from EEPROM
	
	//delayMS(1);
	
	//HealthCurrent(); // Display Current Health on the Health Bar
	
	
      while (1)
    {
			CNT_Old = TIM2->CNT;
			
			if(CNT_New != CNT_Old) IWDG->KR |= 0xAAAA; // If the rotary encoder is used, refresh the WDT
			
			if((menu == An_Expression_State) || (refresh_WDT == true)) {
				WDT_reset();
				refresh_WDT = false;
			}
			
			switch(state){
//----------------------------content------------------------------
				case(content):
					IWDG->KR |= 0xAAAA;
					
					if(lightLvl <=2 ){ // check sleepy
						petFlag = 0;
						state = sleepy;
						Play_Tone_2();
						menu = ExpSleepy;
						Eyelid_Move_To(2570);
						Expression_Transition = true;
						break;
					}
					
					if(health>=5){     // check happy via food
						state = happy;
						menu = ExpHappy;
						Play_Tone_1();
						Eyelid_Move_To(1500); // open
						Expression_Transition = true;
						
						break;
					}
					
					if(petFlag){        // check happy via petting
						Time_Old = millis(); 
						state = happy;
						menu = ExpHappy;
						Play_Tone_1();
						Eyelid_Move_To(1500); // open
						Expression_Transition = true;
						break;
					}
					
					if(health <= 2){ // check hungry
						state = hungry;
						Play_Tone_3();
						menu = ExpHungry;
						Eyelid_Move_To(2200); //closed
						Expression_Transition = true;
						break;
					}
					
					
					break;
				
				
//------------------------------HAPPY--------------------------------
				case(happy):
					IWDG->KR |= 0xAAAA;
					if(lightLvl <=2 ){ // check sleepy
						petFlag = 0;
						state = sleepy;
						Play_Tone_2();
						menu = ExpSleepy;
						Eyelid_Move_To(2570);
						Expression_Transition = true;
						break;
					}
				
					if(petFlag){            // begin pet flag cool down
						Time_New = millis();
						if(Time_New-Time_Old > 3000){
							petFlag = 0;
							state = content;
							Play_Tone_2();
							menu = ExpContent; 
							Eyelid_Move_To(1900); // open (HappY)
							Expression_Transition = true;
							break;
						}
						break;
					}
				
					if(health<5 && health >2){
						state = content;
						menu = ExpContent;
						Play_Tone_2();
						Eyelid_Move_To(1900); // open (HappY)
						Expression_Transition = true;
						break;
					}
					

					
					
					//menu = ExpHappy;
					
					break;

				
//-----------------------------HUNGRY-----------------------------------
				case(hungry):
					IWDG->KR |= 0xAAAA;
					
					if(lightLvl <=2 ){ // check sleepy
						petFlag = 0;
						state = sleepy;
						Play_Tone_4();
						menu = ExpSleepy;
						Eyelid_Move_To(2570);
						Expression_Transition = true;
						break;
					}
				
					if(health>2){
						state = happy;
						menu = ExpHappy;
						Play_Tone_1();
						Eyelid_Move_To(1500); // open (HappY)
						Expression_Transition = true;
						break;
					}
					
					if(petFlag){        // check happy via petting
						Time_Old = millis(); 
						state = happy;
						menu = ExpHappy;
						Play_Tone_1();
						Eyelid_Move_To(1500); // open
						Expression_Transition = true;
						break;
					}
					
				
					break;
				
				
//-------------------------------SLEEPY---------------------------------
				case(sleepy):
					IWDG->KR |= 0xAAAA;
					
					if((lightLvl > 2) && (health < 5) && (health > 2)){ // Lights on -> Sleepy to Content
						state = content;
						Play_Tone_2();
						menu = ExpContent;
						Eyelid_Move_To(1900); // open (content)
						Expression_Transition = true;
						break;
					}
					
					if((lightLvl > 2) && (health >= 5)){ // Lights on -> Sleepy to Happy
						state = happy;
						menu = ExpHappy;
						Play_Tone_1();
						Eyelid_Move_To(1500); // open
						Expression_Transition = true;
						break;
					}
					
					if((lightLvl > 2) && (health <= 2)){ // Lights on -> Sleepy to Hungry
						state = hungry;
						menu = ExpHungry;
						Play_Tone_3();
						Eyelid_Move_To(2200); //closed
						Expression_Transition = true;
						break;
					}
					
					
					break;
				
		
//-------------------------------DEAD---------------------------------
				case(dead):
					IWDG->KR |= 0xAAAA;
					menu = ExpSleepy;
				
					break;
				
//--------------------------------MENU-------------------------------------
				case(MENU_STATE):
					
				
					break;
			}
				
				MENU_SCREENS(); //change LCD
			
			
			
			/*DISTANCE TAIL WAG*/
			//sonar_gpio_init();
			
			distance = abs(dist());	//get the distance value
			
			if(distance < 400) {Mimic_Servo.is_close = true;}
			else{Mimic_Servo.is_close = false;}
			
			//check servo position
			
			/*CHECK LIGHT LEVEL*/
			lightLvl = Read_ADC();
			
			if(count != old_count){
				old_count = count; 
				sevenSeg_write(0x05, num[count/10]);
				sevenSeg_write(0x04, num[count%10]);
			}
		CNT_New = CNT_Old;
		
		}
}


/*********************************************************************************
																				EXTI15_10_Handler
*********************************************************************************/
	void EXTI15_10_IRQHandler(void){

		if(EXTI->PR & 1<<HALL_PIN){
			test = 1;
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
		
//		if(state == An_Expression_State){
//			IWDG->KR |= 0x5555;
//			 IWDG->RLR |= 0x0; // max reload Value
//		}
		
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
		//set up position to change based on the interrupt from the rotary encoder
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
							Rotate_Display(0);
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
					if(Expression_Transition == true){
						Rotate_Display(0);
						Fill_Screen(BROWN);
						Draw_Bitmap((TFT_WIDTH - contentImage->width) / 2, (TFT_HEIGHT - contentImage->height) / 2, contentImage); // Displays a scaled image of an apple. (Small to maintain 32kB flash limit on Keil)
						Expression_Transition = false;
					}
				break;
				
				
//-----------------------------------------HAPPY-----------------------------------------
				case ExpHappy:
					if(Expression_Transition == true){
						Rotate_Display(0);
						Fill_Screen(BROWN);
						Draw_Bitmap((TFT_WIDTH - HappyImage->width) / 2, (TFT_HEIGHT - HappyImage->height) / 2, HappyImage); // Displays a scaled image of an apple. (Small to maintain 32kB flash limit on Keil)
						Expression_Transition = false;
					}
					break;
				
				
//-----------------------------------------HUNGRY-----------------------------------------
				case ExpHungry:
					if(Expression_Transition == true){
						Rotate_Display(0);
						Fill_Screen(BROWN);
						Draw_Bitmap((TFT_WIDTH - HungryImage->width) / 2, (TFT_HEIGHT - HungryImage->height) / 2, HungryImage); // Displays a scaled image of an apple. (Small to maintain 32kB flash limit on Keil)
						Expression_Transition = false;
					}
					break;
				
				
//-----------------------------------------SLEEPY-----------------------------------------
				case ExpSleepy:
					if(Expression_Transition == true){
						Rotate_Display(0);
						Fill_Screen(BROWN);
						Draw_Bitmap((TFT_WIDTH - SleepyImage->width) / 2, (TFT_HEIGHT - SleepyImage->height) / 2, SleepyImage); // Displays a scaled image of an apple. (Small to maintain 32kB flash limit on Keil)
						Expression_Transition = false;
					}
					break;
				
			}
				
}


void TIM5_IRQHandler(void)
{
	random_seconds_counter++;
	if(state != MENU_STATE){
		count --; 
	if(count <= 0){
		count = 60; 
		HealthMinusMinus();
		

		//Store_Current_Health();
		
		}
	}
	
	tongue_wag = (tongue_wag)? 0:1;
		
		if(Mimic_Servo.is_close || petFlag){
			Tongue_Move_To((tongue_wag)? 1000:2000);
		}
		
	if(random_seconds_counter == random_seconds){
		random_seconds_counter = 0;
		Eye_Move_To(rand()%((1800-1000)+1)+1000 );
		random_seconds = rand()%(8)+1;
	}
	
	TIM5->SR &= ~0x0001U;
}

/// @brief function just to store health in the EEPROM
void Store_Current_Health(void){
	I2C1_byteWrite(EEPROM_SLAVE_ADDR, MEMORY_1 , health);
}

/// @brief fucntion just to retrieve health from the EEPROM
void Retrieve_Health(void){
	I2C1_byteRead(EEPROM_SLAVE_ADDR, MEMORY_1 , health_ptr);
}

/// @brief Initialize Watchdog Timer
void WDT_init(void){
	IWDG->KR |= 0x5555; // Write to Access PR and RLR
	IWDG->PR |= 0x6; // Prescalar max timeout 32768ms
	IWDG->RLR |= 0xFFF; // max reload Value
	IWDG->KR |= 0xCCCC; // Write to Start Watchdog Timer
}

/// @brief Reset Watchdog Timer
void WDT_reset(void){
	IWDG->KR |= 0xAAAA; // Write to Reset Counter
}

// EOF



