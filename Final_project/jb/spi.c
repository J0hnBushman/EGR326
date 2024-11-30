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

    RCC->APB2ENR |= 1 << 12;

    SPI1->CR1 |= (1 << 2); // Master mode
    SPI1->CR1 |= (7 << 0); // Baud rate psc

    SPI1->CR1 &= ~(1 << 7);           // Ensuring MSB transmit first
    SPI1->CR1 |= (1 << 8) | (1 << 9); // Allows any pin to be Chip Sel

    SPI1->CR1 &= ~((1 << 10) | (1 << 11)); // Full duplex, 8-bit data

    SPI1->CR2 = 0; // Not using anything here (DMA and Interrupts)

    SPI_Enable();
}

void SPI_GPIO(void)
{
	//define PIN setup for SCK, MOSI, MISO, CS_GPIO
	RCC->AHB1ENR |= 1; //GPIOA
	
	// enable MODER for SCK, MOSI, MISO, CS_GPIO  (Note CS- is just an output)
	// setup AF fo SCK, MOSI, MISO  (SPI1 remember!)
	SCK_GPIO->MODER &= ~(0x03<<(2*SCK_PIN));	
	SCK_GPIO->MODER |=  (0x02<<(2*SCK_PIN));
	SCK_GPIO->AFR[0] &= ~(0x0F<<(SCK_PIN*4));
	SCK_GPIO->AFR[0] |=  (0x05<<(SCK_PIN*4)); //set for AF5
	
	MISO_GPIO->MODER &= ~(0x03<<(2*MISO_PIN));
	MISO_GPIO->MODER |=  (0x02<<(2*MISO_PIN));
	MISO_GPIO->AFR[0] &= ~(0x0F<<(MISO_PIN*4));
	MISO_GPIO->AFR[0] |=  (0x05<<(MISO_PIN*4)); //set for AF5
	
	MOSI_GPIO->MODER &= ~(0x03<<(2*MOSI_PIN));
	MOSI_GPIO->MODER |=  (0x02<<(2*MOSI_PIN));
	MOSI_GPIO->AFR[0] &= ~(0x0F<<(MOSI_PIN*4));
	MOSI_GPIO->AFR[0] |=  (0x05<<(MOSI_PIN*4)); //set for AF5
	
	CS_GPIO->MODER &= ~(0x03<<(2*CS_PIN));
	CS_GPIO->MODER |=  (0x01<<(2*CS_PIN));
	
  GPIOB->MODER &= ~(0x3<<(2*12));
  GPIOB->MODER |=  0x1<<(2*12);
	
	
	RCC->APB2ENR |= 1 << 12;	// enable SPI1 Clock

    CS_Low();
		
}

void SPI_Disable(void)
{
   SPI1->CR1 &= ~(1 << 6);
}



void SPI_Enable(void)
{
   SPI1->CR1 |= 1 << 6;
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
