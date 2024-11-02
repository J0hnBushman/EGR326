/*  Author: Jacob Clarey
 *  Date: 10/9/23
 *  Description: This is the source file for spi transmission functions.
 *  Notes:
 */

#ifndef __SPI_H__
#define __SPI_H__

#include <stm32f446xx.h>

/*******************************************************************************/
//                          USER DEFINES
/*******************************************************************************/

#define SCK_GPIO GPIOxxx
#define SCK_PIN xxx

#define MISO_GPIO GPIOxxx
#define MISO_PIN xxx

#define MOSI_GPIO GPIOxxx
#define MOSI_PIN xxx

#define CS_GPIO GPIOxxx
#define CS_PIN xxx

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

/// @brief Pulls chip select I/O line low
void CS_Low(void);

/// @brief Pulls chip select I/O line high
void CS_High(void);
/*******************************************************************************/
/*******************************************************************************/

#endif

/* EOF */