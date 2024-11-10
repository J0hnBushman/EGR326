#include "stm32f446xx.h"
#include "EEPROM.h"
/*=============================================================
Name: 				Bushman & Norton

Course:				EGR 326 - Embedded Systems

Project:			Integration with an RTC using an I2C Bus

File: 				main.c

Description: 	When the user enters a ?*? followed by a ?1? on the keypad, 
							the current day, month, and year are displayed on the serial 
							monitor.  
							When the user enters a ?*? followed by a ?2? on the 
							keypad, the hour, minute, and second are displayed.
							If the user enters a ?*? followed by a ?3? on the keypad, the 
							temperature is displayed in Celsius
=============================================================*/

#include "stm32f446xx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "UART.h"
#include "I2C.h"

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
#define POUND           12
#define TEMP_ADDR_WHOLE 0x11
#define TEMP_ADDR_FRAC  0x12

void delayMs(int n);
void Read_Time(void);
void Read_Date(void);
void Set_Time(void);
void Set_Date(void);
void Read_Temperature(void);
void menu_choice(void);

uint8_t num = 0;
uint8_t choice = 0;
uint16_t pressed;
uint8_t *numptr = &num;
bool flag = 0;
char S_address = 0x68;
char RTC_data;
char *RTC_Data_ptr = &RTC_data;

uint8_t RTC_Hour;
uint8_t RTC_Minute;
uint8_t RTC_Second;

uint8_t RTC_Year;
uint8_t RTC_Month;
uint8_t RTC_Date;
uint8_t RTC_Day;

/////////////////////////////////////////////////////////////////////

int main (void){
	I2C_init();
	USART2_init();
	

	
	USART2_print("Thank you for purchasing Bushman and Nortons Real Time Clock!\n\r\n");
	USART2_print("Press '#' key to change time and date.\n\r\n");
	while(1){
//			I2C1_byteWrite(SLAVE_ADDR,HOURS_ADDR,RTC_Hour);
//		I2C1_byteWrite(SLAVE_ADDR,MINUTES_ADDR,RTC_Minute);
//		I2C1_byteWrite(SLAVE_ADDR,SECONDS_ADDR,RTC_Second);
		
		
	}

	return 0;
}

void Read_Time(void){
    // Read the current hour from the RTC and store in RTC_Data_ptr
	I2C1_byteRead(SLAVE_ADDR, HOURS_ADDR, RTC_Data_ptr);
    
    // Send the hour to USART2 (most significant byte and least significant byte)
	USART2_write(MSB(RTC_data));
	USART2_write(LSB(RTC_data));
	USART2_write(':');  // Add colon between hours and minutes
	
    // Read the current minutes from the RTC
	I2C1_byteRead(SLAVE_ADDR, MINUTES_ADDR, RTC_Data_ptr);
    
    // Send the minutes to USART2
	USART2_write(MSB(RTC_data));
	USART2_write(LSB(RTC_data));
	USART2_write(':');  // Add colon between minutes and seconds
	
    // Read the current seconds from the RTC
	I2C1_byteRead(SLAVE_ADDR, SECONDS_ADDR, RTC_Data_ptr);
    
    // Send the seconds to USART2
	USART2_write(MSB(RTC_data));
	USART2_write(LSB(RTC_data));
    
    // Print a newline to finish the time output
	USART2_print("\n\r\n");
}

/*===========================================================================================
// Read_Date

 * @brief: Prints the current date stored on the RTC
 * 
 * @param[in] NULL
 * 
 * @return: NULL
 ===========================================================================================*/
void Read_Date(void){
    // Read the day of the week from the RTC
	I2C1_byteRead(SLAVE_ADDR, DAY_ADDR, RTC_Data_ptr);
    
    // Print the day of the week based on the value of RTC_data
	if (RTC_data == 1) USART2_print("Sunday ");
	if (RTC_data == 2) USART2_print("Monday ");
	if (RTC_data == 3) USART2_print("Tuesday ");
	if (RTC_data == 4) USART2_print("Wednesday ");
	if (RTC_data == 5) USART2_print("Thursday ");
	if (RTC_data == 6) USART2_print("Friday ");
	if (RTC_data == 7) USART2_print("Saturday ");
	
    // Read the current month from the RTC and display it
	I2C1_byteRead(SLAVE_ADDR, MONTH_ADDR, RTC_Data_ptr);
	USART2_write(MSB(RTC_data));  // Print the most significant byte (MSB)
	USART2_write(LSB(RTC_data));  // Print the least significant byte (LSB)
	USART2_write('/');  // Separator between month and date
	
    // Read the current date (day of the month) from the RTC and display it
	I2C1_byteRead(SLAVE_ADDR, DATE_ADDR, RTC_Data_ptr);
	USART2_write(MSB(RTC_data));
	USART2_write(LSB(RTC_data));
	USART2_write('/');  // Separator between date and year
	
    // Read the year from the RTC and display it
	I2C1_byteRead(SLAVE_ADDR, YEAR_ADDR, RTC_Data_ptr);
	USART2_write(Y_MSB(RTC_data));  // Print the most significant byte of the year
	USART2_write(LSB(RTC_data));    // Print the least significant byte of the year
	
    // Print a newline to finish the date output
	USART2_print("\n\r\n");
}

/*===========================================================================================
// Read_Temperature

 * @brief: Reads and prints the temperature from the RTC
 * 
 * @param[in] NULL
 * 
 * @return: NULL
 ===========================================================================================*/
void Read_Temperature(void){
    // Declare variables to hold temperature data in different formats
	int8_t temperature = 0;
	int8_t temp_hundreds = 0;
	int8_t temp_tens = 0;
	int8_t temp_ones = 0;
	
    // Print the initial "Temperature: " string
	USART2_print("Temperature: ");
	
    // Read the whole temperature value (whole part of the temperature)
	I2C1_byteRead(SLAVE_ADDR, TEMP_ADDR_WHOLE, RTC_Data_ptr);

    // Assign the temperature value to the variable
	temperature = (int8_t)RTC_data;
	
    // Check if the temperature is negative (bit 7 indicates sign)
	if (((RTC_data & 0x80) >> 7) == 0x01) {  // Temperature is negative
        USART2_write('-');  // Print negative sign
        
        // Extract the hundreds, tens, and ones digits
		temp_hundreds = temperature / (-100);
		if (temp_hundreds != 0) USART2_write(((char)temp_hundreds + '0'));  // Print hundreds digit
		temp_tens = temperature / (-10);
		if (temp_tens != 0 || temp_hundreds != 0) USART2_write(((char)temp_tens + '0'));  // Print tens digit
		temp_ones = temperature % (-10);
		USART2_write(((char)temp_ones + '0'));  // Print ones digit
	}
	else {  // Temperature is positive
        temp_hundreds = temperature / 100;
		if (temp_hundreds != 0) USART2_write(((char)temp_hundreds + '0'));  // Print hundreds digit
		temp_tens = temperature / 10;
		if (temp_tens != 0 || temp_hundreds != 0) USART2_write(((char)temp_tens + '0'));  // Print tens digit
		temp_ones = temperature % 10;
		USART2_write(((char)temp_ones + '0'));  // Print ones digit
	}
	
    // Print the decimal point
	USART2_write(RTC_data);
	USART2_write('.');

    // Read the fractional part of the temperature
	I2C1_byteRead(SLAVE_ADDR, TEMP_ADDR_FRAC, RTC_Data_ptr);
	
    // Convert the fractional value to human-readable format and print
	RTC_data = (RTC_data & 0x0C) >> 6;  // Extract the two most significant bits (for fractions)
	if (RTC_data == 0x00) USART2_print("00");
	if (RTC_data == 0x01) USART2_print("25");
	if (RTC_data == 0x02) USART2_print("50");
	if (RTC_data == 0x03) USART2_print("75");
	
    // Print the unit (Degrees Celsius)
	USART2_print(" Degrees Celsius\n\r\n");
}

/*===========================================================================================
// menu_choice

 * @brief: Prompts the user to navigate through a menu
 * 
 * @param[in] NULL
 * 
 * @return: NULL
 ===========================================================================================*/
void menu_choice(void){
    // Initialize pressed flag to zero (user hasn't pressed a key yet)
	pressed = 0;
	
    // Display menu options on the terminal
	USART2_print("Press 1 for ................ Date\n\r");
	USART2_print("Press 2 for ................ Time\n\r");
	USART2_print("Press 3 for ................ Temperature\n\r\n");

    // Wait until the user presses a key (keypad input)
	while (pressed == 0) {
        pressed = Read_Keypad(numptr);  // Check if a key is pressed
        
        // Depending on the key pressed, call the appropriate function
		if (num == 1) { Read_Date(); }
		if (num == 2) { Read_Time(); }
		if (num == 3) { Read_Temperature(); }
	}
}