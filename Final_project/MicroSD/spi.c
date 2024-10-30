/*  Author: John Bushman
 *  Date: 10/21/23
 *  Description: This is the header file for spi transmission functions.
 *  Notes:
 */

#include "spi.h"


//initilizes SPI1
void SPI_Init(void)
{
    SPI_GPIO();

    RCC->APB2ENR |= 1 << 12;
	
		SPI1->CR1 |= (3 << 0); // CPOL = 1, CPHA = 1 !!!!CHECK IF YOU NEED THE POLARITY OR PHASE TO BE ANYTHIGN
    //SPI1->CR1 |= (1 << 2); // Master mode
    //SPI1->CR1 |= (7<<3); // BR[2:0] = 011: fPCLK/16, PCLK2 = 80MHz, SPI clk = 5MHz !!!CHECK THE DATA SHEET FOR THE BAUD RAT
		SPI1->CR1 &= ~(1 << 7);    // Ensuring MSB transmit first
    //SPI1->CR1 |= (1<<8)|(1<<9);  // SSM=1, SSi=1,
		SPI1->CR1 |= (1<<11) | (1<<14)|(1<<15); //sets to a 16 bit set, and enables bidirection to 1-line transmit mode
		//SPI1->CR1 &= ~((1 << 10)); // Full duplex
		
		SPI1->CR1 |= 0x33C;
		SPI1->CR2 = 0; // Not using anything here (DMA and Interrupts)
	
    SPI_Enable();
}



//SETS up the GPIO pins for SPI
void SPI_GPIO(void)
{
	//define PIN setup for SCK, MOSI, MISO, SS_GPIO
	RCC->AHB1ENR |= 1; //GPIOA
	
	// enable MODER for SCK, MOSI, MISO, SS_GPIO  (Note SS- is just an output)
	// setup AF of SCK, MOSI, MISO  (SPI1)
	SCK_GPIO->MODER &= ~(0x03<<(2*SCK_PIN));	
	SCK_GPIO->MODER |=  (0x02<<(2*SCK_PIN));
	SCK_GPIO->OSPEEDR |= (0x03<<2*SCK_PIN);
	SCK_GPIO->AFR[0] &= ~(0x0F<<(SCK_PIN*4));
	SCK_GPIO->AFR[0] |=  (0x05<<(SCK_PIN*4)); //set for AF5
	
	MISO_GPIO->MODER &= ~(0x03<<(2*MISO_PIN));
	MISO_GPIO->MODER |=  (0x02<<(2*MISO_PIN));
	MISO_GPIO->OSPEEDR |= (0x03<<2*MISO_PIN);
	MISO_GPIO->AFR[0] &= ~(0x0F<<(MISO_PIN*4));
	MISO_GPIO->AFR[0] |=  (0x05<<(MISO_PIN*4)); //set for AF5
	
	MOSI_GPIO->MODER &= ~(0x03<<(2*MOSI_PIN));
	MOSI_GPIO->MODER |=  (0x02<<(2*MOSI_PIN));
	MOSI_GPIO->OSPEEDR |= (0x03<<2*MOSI_PIN);
	MOSI_GPIO->AFR[0] &= ~(0x0F<<(MOSI_PIN*4));
	MOSI_GPIO->AFR[0] |=  (0x05<<(MOSI_PIN*4)); //set for AF5
	
	SS_GPIO->MODER &= ~(0x03<<(2*SS_PIN));	//sets the SS to an output
	SS_GPIO->MODER |=  (0x01<<(2*SS_PIN));
	
	DET_GPIO->MODER &= ~(0x03<<(2*DET_PIN)); //set the detect microSD card pin as an input
	
	RCC->APB2ENR |= 1 << 12;	// enable SPI1 Clock

   SS_High();
}


//SPI disable
void SPI_Disable(void)
{
   SPI1->CR1 &= ~(1 << 6);
}



//SPI enable
void SPI_Enable(void)
{
   SPI1->CR1 |= 1 << 6;
}



//******SPI_Transmition*****
/*		STEPS to transmit data
	1. Wait for the TXE bit to set in the Status Register
	2. Write the data to the Data Register
	3. After the data has been transmitted, wait for the BSY bit to reset in Status Register
	4. Clear the Overrun flag by reading DR and SR
*/
void SPI_Transmit(uint16_t *data, uint8_t size)
{
    uint16_t i = 0;
    while (i < size)
    {
        while (!(SPI1->SR & 0x2)){}; //check if the buffer is empty, wait for the TXE bit to set
        SPI1->DR = data[i]; //put data into the data register
        i++;
    }

    while (!(SPI1->SR & 0x02)){}; //wait for buffer empty, wait for TXE bit to set
    while (SPI1->SR & 0x80){};	//check if SPI is busy, wait for the BSY bit to reset

			//This clears the overrun flag by reading DR and SR
    uint16_t temp = SPI1->DR;
			temp = SPI1->SR;
}




//***********SPI_Recive***********
/*
	1. Wait for the TXE bit to set in the Status Register
	2. Write the data to the Data Register
	3. After the data has been transmitted, wait for the BSY bit to reset in Status Register
	4. Clear the Overrun flag by reading DR and SR
*/
void SPI_recive(uint8_t *data, uint8_t size){
	//SS_Low(); I think that the data has to pulled low to revice data!!!!!!!!!! but i should double check
	
		while (size){
		while (((SPI1->SR)&(0x80))) {};  // wait for BSY bit to Reset
		SPI1->DR = 0;  	// send some sorat dummy data
		while (!((SPI1->SR) &(0x01))){};  // Wait for RXNE to set
	  *data++ = (SPI1->DR);
		size--;
			
	}	
}



//sets the SS to low
void SS_Low(void)
{
    SS_GPIO->ODR &= ~(1 << SS_PIN);
}



//sets the SS to high
void SS_High(void)
{
    SS_GPIO->ODR |= 1 << SS_PIN;
	
}


/* EOF */
