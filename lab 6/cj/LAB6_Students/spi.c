/*  Author: Jacob Clarey
 *  Date: 10/9/23
 *  Description: This is the header file for spi transmission functions.
 *  Notes:
 */

#include "spi.h"

/*******************************************************************************/
//                          USER FUNCTION DEFINITIONS
/*******************************************************************************/
void SPI_Init(void)
{
    SPI_GPIO();

   //    NEEDS CR1 and CR2 defined
   //    CR1->  Master mode, MSB transmit first, Bit8,9=1
   //    CR1-> Full Duplex, 8-bit data
   // CR2= 0 
   

    SPI_Enable();
}

void SPI_GPIO(void)
{
	//define PIN setup for SCK, MOSI, MISO, CS_GPIO
	
	// enable SPI1 Clock
	// enable MODER for SCK, MOSI, MISO, CS_GPIO  (Note CS- is just an output)
	// setup AF fo SCK, MOSI, MISO  (SPI1 remember!)
	
  
    CS_Low();
}

void SPI_Disable(void)
{
   disable SPI in CR1 register
}

void SPI_Enable(void)
{
   // enable SPI in CR1 register
}

void SPI_Transmit(uint8_t *data, uint8_t size)
{
    uint8_t i = 0;
    while (i < size)
    {
        while (!(SPI1->SR & 0x2))
        {
        }
        SPI1->DR = data[i];
        i++;
    }

    while (!(SPI1->SR & 0x2))
    {
    }
    while (SPI1->SR & 0x80)
    {
    }

    uint8_t temp = SPI1->DR;
    temp = SPI1->SR;
}

void CS_Low(void)
{
    CS_GPIO->ODR &= ~(1 << CS_PIN);
}

void CS_High(void)
{
    CS_GPIO->ODR |= 1 << CS_PIN;
}
/*******************************************************************************/
/*******************************************************************************/

/* EOF */
