/*  Author: John Bushman
 *  Date: 10/21/23
 *  Description: This is the header file for spi transmission functions.
 *  Notes:
 */

#ifndef __SPI_H__
#define __SPI_H__

#include <stm32f446xx.h>

/*******************************************************************************/
//                          USER DEFINES
/*******************************************************************************/

//clk
#define SCK_GPIO GPIOA
#define SCK_PIN 5

//MISO
#define MISO_GPIO GPIOA
#define MISO_PIN 6

//MOSI
#define MOSI_GPIO GPIOA
#define MOSI_PIN 7

//Slave Select
#define SS_GPIO GPIOA
#define SS_PIN 9

//Detect Micro SD
#define DET_GPIO GPIOA
#define DET_PIN 8



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
void SPI_Transmit(uint16_t *data, uint8_t size);

/// @brief recives data over SPI1 line
/// @param data is data byte array to recive
/// @param size is length of data byte array
void SPI_recive(uint8_t *data, uint8_t size);

/// @brief Pulls slave select I/O line low
void SS_Low(void);

/// @brief Pulls slave select I/O line high
void SS_High(void);

#endif

/* EOF */
