/*  Author: John Bushman
 *  Date: 10/9/23
 *  Description: This is the source file for spi transmission functions.
 *  Notes:
 */

#ifndef __MAIN_H__
#define __MAIN_H__

#include <stm32f446xx.h>

/*******************************************************************************/
//                          USER DEFINES
/*******************************************************************************/


//screen values
#define mainMenu 0
#define timMenu 1
#define helpMenu 2
#define infoMenu 3
#define startUpScreen 4
#define settings 5

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
/// @brief just some menu screens
void MENU_SCREENS(int screen);

/*******************************************************************************/
/*******************************************************************************/

#endif

/* EOF */