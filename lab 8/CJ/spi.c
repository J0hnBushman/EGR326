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

		SPI1->CR1 |=0x31C;

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
	
	
	MOSI_GPIO->MODER &= ~(0x03<<(2*MOSI_PIN));
	MOSI_GPIO->MODER |=  (0x02<<(2*MOSI_PIN));
	MOSI_GPIO->AFR[0] &= ~(0x0F<<(MOSI_PIN*4));
	MOSI_GPIO->AFR[0] |=  (0x05<<(MOSI_PIN*4)); //set for AF5
	
	CS_GPIO->MODER &= ~(0x03<<(2*CS_PIN));
	CS_GPIO->MODER |=  (0x02<<(2*CS_PIN));
	CS_GPIO->AFR[0] &= ~(0x0F<<(CS_PIN*4));
	CS_GPIO->AFR[0] |=  (0x05<<(CS_PIN*4)); //set for AF5
	
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

void SPI1_write(unsigned char data)
{
	while(!(SPI1->SR & 2)){}
	GPIOA->BSRR = 0x00100000;
	SPI1->DR = data;
	while (SPI1->SR & 0x80){} //wait for transmission complete
	GPIOA->BSRR = 0x00000010; //deassert slave select
	
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


