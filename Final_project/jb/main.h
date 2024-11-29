/*  Author: John Bushman
 *  Date: 10/9/23
 *  Description: This is the source file for spi transmission functions.
 *  Notes:
 */

#ifndef __MAIN_H__
#define __MAIN_H__

#include <stm32f446xx.h>
#include "ILI9341.h"
#include "RccConfig.h"
#include "font_ubuntu_mono_24.h"
#include "font_freemono_mono_bold_24.h"
#include "my_photos.h"
#include "spi.h"
#include "I2C.h"
#include "rotary_encoder.h"
#include "hall.h"
#include "TIMERS.h"
#include "stepper.h"
#include "btn.h"
#include <stdlib.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include "Sonar.h"
#include "servo.h"
#include "ADC.h"
#include "health_bar.h"
#include "Flash_Access.h"

/*******************************************************************************/
//                          USER DEFINES
/*******************************************************************************/


//screen values
#define mainMenu 			0
#define timMenu  			1
#define helpMenu 			2
#define infoMenu 			3
#define startUpScreen 4
#define settings 			5
#define ExpContent		6
#define ExpHappy			7
#define ExpHungry			8
#define ExpSleepy			9
#define ExpDead				10
#define ExpFeeding		11

//EXPRESSION
#define content 	 0
#define happy 	 	 1
#define hungry     2
#define sleepy 		 3
#define dead			 4
#define feeding		 5
#define MENU_STATE 6

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

/*******************************************************************************/
//                           USER STRUCT DEFINITIONS
/*******************************************************************************/




/*******************************************************************************/
//                          USER FUNCTION PROTOTYPE
/*******************************************************************************/
/// @brief Set the time 
void Set_Time(uint8_t RTC_Hour, uint8_t RTC_Minute, uint8_t RTC_Second);
/// @brief Set the Date
void Set_Date(uint8_t RTC_Year, uint8_t RTC_Month, uint8_t RTC_Date);
/// @brief Set the time and Date
void Set_TD(void);
/// @brief READ the Date
void Read_Date(void);
void Read_Time(void);
/// @brief just some menu screens
void MENU_SCREENS(void);

/*******************************************************************************/
/*******************************************************************************/

#endif

/* EOF */