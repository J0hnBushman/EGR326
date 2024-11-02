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
    RCC->AHB1ENR |= 1 | 2 | 4; // Enable GPIOA, GPIOB, GPIOC clock

    SCK_GPIO->MODER &= ~(3 << (2 * SCK_PIN));
    SCK_GPIO->MODER |= (2 << (2 * SCK_PIN));

    MOSI_GPIO->MODER &= ~(3 << (2 * MOSI_PIN));
    MOSI_GPIO->MODER |= (2 << (2 * MOSI_PIN));

    MISO_GPIO->MODER &= ~(3 << (2 * MISO_PIN));
    MISO_GPIO->MODER |= (2 << (2 * MISO_PIN));

    CS_GPIO->MODER &= ~(3 << (2 * CS_PIN));
    CS_GPIO->MODER |= (1 << (2 * CS_PIN));

    if (SCK_PIN > 7)
    {
        SCK_GPIO->AFR[1] &= ~(0xF << (4 * SCK_PIN));
        SCK_GPIO->AFR[1] |= (0x5 << (4 * SCK_PIN));
    }
    else
    {
        SCK_GPIO->AFR[0] &= ~(0xF << (4 * SCK_PIN));
        SCK_GPIO->AFR[0] |= (0x5 << (4 * SCK_PIN));
    }

    if (MISO_PIN > 7)
    {
        MISO_GPIO->AFR[1] &= ~(0xF << (4 * MISO_PIN));
        MISO_GPIO->AFR[1] |= (0x5 << (4 * MISO_PIN));
    }
    else
    {
        MISO_GPIO->AFR[0] &= ~(0xF << (4 * MISO_PIN));
        MISO_GPIO->AFR[0] |= (0x5 << (4 * MISO_PIN));
    }

    if (MOSI_PIN > 7)
    {
        MOSI_GPIO->AFR[1] &= ~(0xF << (4 * MOSI_PIN));
        MOSI_GPIO->AFR[1] |= (0x5 << (4 * MOSI_PIN));
    }
    else
    {
        MOSI_GPIO->AFR[0] &= ~(0xF << (4 * MOSI_PIN));
        MOSI_GPIO->AFR[0] |= (0x5 << (4 * MOSI_PIN));
    }

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
