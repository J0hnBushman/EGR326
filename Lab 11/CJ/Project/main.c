#include "stm32f446xx.h"
#include <stdio.h>
#include <stdlib.h>
#include "UART.h"
#include "I2C.h"
#include "systick.h"
/*=============================================================
Name: 				Bushman & Norton

Course:				EGR 326 - Embedded Systems

Project:			RTC and an EEPROM using an I2C Bus

File: 				main.c

Description: 	
=============================================================*/



#define BP1 ((GPIOC->IDR)&(1<<13))	
#define BP2 ((GPIOC->IDR)&(1<<11))

#define MSB(X)          (((X & 0x70)>>4)+'0')
#define Y_MSB(X)        (((X & 0xF0)>>4)+'0')
#define LSB(X)          ((X & 0x0F)+'0')
#define RTC_SLAVE_ADDR      0x68
#define EEPROM_SLAVE_ADDR 0x50
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

// EEPROM MEM addresses for different Times
#define TIME1_HR		0x00
#define TIME1_MIN		0x08
#define TIME1_SEC		0x10

#define TIME2_HR		0x18
#define TIME2_MIN		0x20
#define TIME2_SEC		0x28

#define TIME3_HR		0x30
#define TIME3_MIN		0x38
#define TIME3_SEC	  0x40

#define TIME4_HR		0x48
#define TIME4_MIN		0x50
#define TIME4_SEC		0x58

#define TIME5_HR		0x60
#define TIME5_MIN		0x68		
#define TIME5_SEC		0x70

void Read_Time(void);
void Store_Time(void);
void Read_Date(void);
void btn_init(void);


uint8_t entry = 0;
char RTC_data;
char *RTC_Data_ptr = &RTC_data;

    uint8_t time[5][3] = {
        {TIME1_HR, TIME1_MIN, TIME1_SEC},  // TIME1
        {TIME2_HR, TIME2_MIN, TIME2_SEC},  // TIME2
        {TIME3_HR, TIME3_MIN, TIME3_SEC},  // TIME3
        {TIME4_HR, TIME4_MIN, TIME4_SEC},  // TIME4
        {TIME5_HR, TIME5_MIN, TIME5_SEC}   // TIME5
    };

/////////////////////////////////////////////////////////////////////

int main (void){
	SysTick_Init();
	I2C_init();
	USART2_init();
	btn_init();
	
	while(1){
		
		if(BP1==0){//store time in EEPROM
			while(!BP1);
			Store_Time();
		}
		
		if(BP2==0){//read time from EEPROM
			while(!BP2);
			Read_Time();
		}
		
	}
	return 0;
}
/*===========================================================================================
// Store_Time

 * @brief: Stores the time from the RTC on to EEPROM
 * 
 * @param[in] NULL
 * 
 * @return: NULL
 ===========================================================================================*/
void Store_Time(void){
	volatile int i = 0;
	
	delayMS(1);
    // Read the current hour from the RTC and store in RTC_Data_ptr
	I2C1_byteRead(RTC_SLAVE_ADDR, HOURS_ADDR, RTC_Data_ptr);
	delayMS(1);
		// Write the data from the RTC to a memory address in the EEPROM
	I2C1_byteWrite(EEPROM_SLAVE_ADDR, time[entry][i++], RTC_data);
   delayMS(1);
	
    // Read the current minutes from the RTC
	I2C1_byteRead(RTC_SLAVE_ADDR, MINUTES_ADDR, RTC_Data_ptr);
	delayMS(1);
		// Write the data from the RTC to a memory address in the EEPROM
	I2C1_byteWrite(EEPROM_SLAVE_ADDR, time[entry][i++], RTC_data);
   delayMS(1);
	
    // Read the current seconds from the RTC
	I2C1_byteRead(RTC_SLAVE_ADDR, SECONDS_ADDR, RTC_Data_ptr);
	delayMS(1);
		// Write the data from the RTC to a memory address in the EEPROM
	I2C1_byteWrite(EEPROM_SLAVE_ADDR, time[entry][i], RTC_data);
	delayMS(1);
    
	
	entry = (entry>=4)? 0 : entry+1;
}

void Read_Time(void){
	volatile int i = 0;
	
	USART2_print("Entry: ");
	USART2_write((entry+1)+'0');
	USART2_print("\n\r");
	delayMS(1);
    // Read the current hour from the current entry in EEPROM and store in RTC_Data_ptr
	I2C1_byteRead(EEPROM_SLAVE_ADDR, time[entry][i++], RTC_Data_ptr);
	
	delayMS(1);
    
    // Send the hour to USART2 (most significant byte and least significant byte)
	USART2_write(MSB(RTC_data));
	USART2_write(LSB(RTC_data));
	USART2_write(':');  // Add colon between hours and minutes
	
	delayMS(1);
		// Read the current minute from the current entry in EEPROM and store in RTC_Data_ptr
	I2C1_byteRead(EEPROM_SLAVE_ADDR, time[entry][i++], RTC_Data_ptr);
  
	delayMS(1);
	
    // Send the minutes to USART2
	USART2_write(MSB(RTC_data));
	USART2_write(LSB(RTC_data));
	USART2_write(':');  // Add colon between minutes and seconds
	
	delayMS(1);
	
	// Read the current second from the current entry in EEPROM and store in RTC_Data_ptr
	I2C1_byteRead(EEPROM_SLAVE_ADDR, time[entry][i++], RTC_Data_ptr);
   
	delayMS(1);
	
    // Send the seconds to USART2
	USART2_write(MSB(RTC_data));
	USART2_write(LSB(RTC_data));
    
    // Print a newline to finish the time output
	USART2_print("\n\r\n");
	
	delayMS(1);
	entry = (entry>=4)? 0 : entry+1;
}

/*===========================================================================================
// button_init

 * @brief: Prints the current date stored on the RTC
 * 
 * @param[in] NULL
 * 
 * @return: NULL
 ===========================================================================================*/
void btn_init(void){
	RCC->AHB1ENR |= 0x7;
	//PC13, 11 for button press
	GPIOC->MODER &= ~ (0x03<<(2*13));
	GPIOC->MODER &= ~ (0x03<<(2*11));
	GPIOC->PUPDR |=   0x01<<(13*2);
	GPIOC->PUPDR |=   0x01<<(11*2);
}
