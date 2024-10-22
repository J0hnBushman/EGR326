/*******************************************************************************
* Name:             Charles Norton & John Bushman
* Course:           EGR 326 - Embedded Systems
* Project:          I/O Interfacing with the STM32F446
* File:             EGR326_Lab1_main.c
* Description:   		First Part of the Lab: This program on reset turns all current LEDs OFF
										Then if the first button is pressed then the RED LED will turn on while
										Button is held. one the second push of the first button the LED turns green 
										until the button is released, and on a third push the LED turns Blue until released
										The cycle contiues as more buttons are pressed.
********************************************************************************/

#include "stm32f446xx.h"
#include <stdio.h>

//ODR pins for LEDs (GPIOA)
#define G (1<<5)
#define R (1<<4)
#define B (1<<6)

//IDR Reading, returns 0 if pressed and 1 if not
#define BP1 ((GPIOA->IDR)&(1<<0))	
#define BP2 ((GPIOA->IDR)&(1<<1))

#define DEBOUNCE 10 //debounce value


//Function Prototypes
void gpio_init(void);
void systick_init(void);
void delay_msDelay(uint16_t msDelay);
unsigned char btn1_pressed(uint16_t debounce);
unsigned char btn2_pressed(uint16_t debounce);
int btn_press(void);
void turnOnLED(uint8_t color);
void turnOFFLED(uint8_t color, int lock);
void G_led (void);
void R_led (void);
void B_led (void);
void OFF (void);




//*******************MAIN*********************************************
int main(void)
{
	//variables
	int forward;
	uint8_t color = 0; //init color value
	int lock = 0x08;
	
	//init for systick and GPIO pins 
	gpio_init();
	systick_init();
	
	//BTN1 PRESS/LED light cycle
	while(1){
		forward = 0; 
		while(!btn1_pressed(DEBOUNCE)){
			forward = 1;
			if(btn2_pressed(DEBOUNCE)){
				turnOnLED(color);					//turn on color
			}else{ //RESET
				OFF();
				forward = 1;
				lock = 0x08;
				delay_msDelay(1);
				break;
			}
	}
		
		//TURN OFF LED after btn1 press
	if(forward == 1){
		turnOFFLED(color, lock);
	}
	
	
	//**LOCKING METHOD**
	while(!btn2_pressed(DEBOUNCE)){ //Checks if btn1 is pressed
		if(btn1_pressed(DEBOUNCE)){   //checks if btn2 is not pressed
				switch(color){
				case 2:
						G_led();	//turn on Green LED 
						lock |= 1<<0; 
				break;
				case 1: 
						R_led();	//turn on Red LED
						lock |= 1<<1; 
				break;
				case 0:
						B_led();	//turn on Blue LED
						lock |= 1<<2; 
					break;
				default:
						OFF();
					break;
			}
		}else{  //REST ALL LEDS
				OFF();
				forward = 1;
			lock = 0x08;
			delay_msDelay(1);
				break;
		}
	}
		

		if(forward ==1){	//determines which color is to be displayed
			color = color + 1; 
			if(color>=3){color = 0;}
			
		}
	}
}



//****************GPIO INIT****************************
//Description:
//
void gpio_init(void)
{
	RCC->AHB1ENR |= (unsigned long)0x0000001;	//enable GPIO port A
	GPIOA->MODER &= ~(unsigned long)0x0003F0F; //Clear MODER
	GPIOA->MODER |= (unsigned long)0x0001500; //set MODER pins 0,1 to input and 4,5,6
	GPIOA->PUPDR |= (unsigned long)0x0000005; //set pins 0,1 to pull up
}



//*****************SYSTICK INIT***************************
//Description: This funciton inits the systick timer
//
void systick_init(void)
{
	SysTick->CTRL = 0; //disables systick
	SysTick->LOAD = 0x00FFFFFF; //Loads value at 16MHz clock
	SysTick->VAL = 0;	//Clears VAL
	SysTick->CTRL = 0x0000005; //Enables systick
}



//*****************SysTick millisecond Delay************************
//Description: this fucntion uses the systick timer to create a delay
//
void delay_msDelay(uint16_t msDelay){
	SysTick->LOAD = ((msDelay*16000)-1);	//init Max value of timer
	SysTick->VAL = 0; 	//clears val
	while((SysTick->CTRL&(1<<16))==0); //wait for bit 16 to set
}


//***********************GREEN LED ON************************
//Descriptino: This funciton turns the green LED on
void G_led (void){
		GPIOA->ODR |= (unsigned long)G; //Turns Green LED on
}


//***********************RED LED ON************************
//Descriptino: This funciton turns the red LED on
void R_led (void){
		GPIOA->ODR |= (unsigned long)R; //Turns Red LED on
}


//***********************BLUE LED ON************************
//Descriptino: This funciton turns the blue LED on
void B_led (void){
		GPIOA->ODR |= (unsigned long)B; //turns on Blue LED
}


//***********************Button 1 pressed************************
//Description:
//Debounce for Button 1, 
//returns a unsiged Char value
//arguments a uint16_t debounce value
unsigned char btn1_pressed(uint16_t debounce){
	unsigned char pin_value = 1; 
	
	if(!BP1){ //checks if button is pressed
		delay_msDelay(debounce); //waits Debounce ms
		if(!BP1){ //checks if button is pressed
			pin_value = 0; 
		}
	}
	return pin_value;
}


//****************GANSSE DEBOUNCE******************************
//Description: A gansse type debounce read about in the prelab
int btn_press(){
		static uint64_t State = 0;             	//current debounce status
	
		State=(State<<1) | (GPIOA->IDR & 0x2)>>1 | 0x8000000000000000;    //checks pin 1
	
		if(State==0x8000000000000000)  {
			return 1;               
		}		
     return 0;

}


//***********************Button 2 pressed************************
//Description:
//Debounce for Button 2, 
//returns a unsiged Char value
//arguments a uint16_t debounce value
unsigned char btn2_pressed(uint16_t debounce){
	unsigned char pin_value = 1; 
	
	if(!BP2){ //checks if button is pressed
		delay_msDelay(debounce); //waits for Debounce ms
		if(!BP2){ //checks if button is pressed
			pin_value = 0; 
		}
	}
	return pin_value;
}

//********************COLOR ON***********************************************
//Description: Turns on a color based on how many times the first button was pressed
void turnOnLED(uint8_t color){
	switch(color){
				case 1:
						G_led();	//turn on Green LED
				break;
				case 0: 
						R_led();	//turn on Red LED
				break;
				case 2:
						B_led();	//turn on Blue LED
					break;
				default:
						OFF();
					break;
			}
}


//********************COLOR ON***********************************************
//Description: Turns on a color based on how many times the first button was pressed
void turnOFFLED(uint8_t color, int lock){
	switch(color){
				case 1:
					if(!(lock & 1<<0)){				//checks if the color was locked on
						GPIOA->ODR &= ~(unsigned long)(G); 
					}
				break;
				case 0: 
						if(!(lock & 1<<1)){     	//checks if the color was locked on
						GPIOA->ODR &= ~(unsigned long)(R); 
						}
				break;
				case 2:
						if(!(lock & 1<<2)){      	//checks if the color was locked on
					  GPIOA->ODR &= ~(unsigned long)(B); 
						}
					break;
				default:
						OFF();
					break;
			}
}


//*******************Turns all LEDS off************8
void OFF (void){
	GPIOA->ODR &= ~(unsigned long)(R|G|B); //Clears pins for all LEDs
}

