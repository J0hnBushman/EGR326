/*  Author: Jacob Clarey
 *  Date: 10/9/23
 *  Description: This is the source file for spi transmission functions.
 *  Notes:
 */

#ifndef __sevenSeg_H__
#define __sevenSeg_H__

#include <stm32f446xx.h>

/*******************************************************************************/
//                          USER DEFINES
/*******************************************************************************/



/*******************************************************************************/
/*******************************************************************************/

/*******************************************************************************/
//                           USER STRUCT DEFINITIONS
/*******************************************************************************/

/*******************************************************************************/
/*******************************************************************************/

/*******************************************************************************/
//                          USER FUNCTION PROTOTYPE
/*******************************************************************************/
/// @brief Initialize SPI1 registers for STM32F446RE Nucleo board
void SPI_Init(void);

/// @brief Enable GPIO for SPI1 on STM32F446RE Nucleo board
void SPI_GPIO(void);

/// @brief Disable SPI1 for idle
void SPI_Disable(void);

/// @brief Enable SPI1 for use
void SPI_Enable(void);

/// @brief Transmits data over SPI1 line
/// @param data is data byte array to transmit
/// @param size is length of data byte array
void SPI_Transmit(uint8_t *data, uint8_t size);

/*******************************************************************************/
/*******************************************************************************/

#endif

/* EOF */