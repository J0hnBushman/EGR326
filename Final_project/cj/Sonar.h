/* Author: John Buhamn
*	Date: nov 1, 2024
* Description: Functions to set up and 
* call a distance using the HC-SR05 sonar sensor 
*/

#ifndef __Sonar__
#define __Sonar__

#include <stm32f446xx.h>


/*******************************************************************************/
//                          USER DEFINES
/*******************************************************************************/
#define Trig_pin 5
#define Echo_pin 6

/*******************************************************************************/
//                           USER STRUCT DEFINITIONS
/*******************************************************************************/


/*******************************************************************************/
//                          USER FUNCTION PROTOTYPE
/*******************************************************************************/
/// @brief Inits the GPIO pins used for the trigger and echo of the sonar
void sonar_gpio_init(void);
/// @brief Calculates the period between relected signal and sending time
double dist(void);
/// @brief Sets up timers of the trigger and echo pins
//void timer_init(void);
/*******************************************************************************/
/*******************************************************************************/

#endif

/* EOF */