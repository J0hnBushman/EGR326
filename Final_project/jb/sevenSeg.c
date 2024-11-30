
#include "sevenSeg.h"


void Init_seq(void){
	sevenSeg_write(0x09, 0x00);
	sevenSeg_write(0x0A, 0x02);
	sevenSeg_write(0x0B, 0x07);
	sevenSeg_write(0x0C, 0x01);
	sevenSeg_write(0x0F, 0x0F);
	sevenSeg_write(0x0F, 0x00);
	//setup screen
	sevenSeg_write(0x08, 0x01);
	sevenSeg_write(0x07, 0x01);
	sevenSeg_write(0x06, 0x01); //dash
	sevenSeg_write(0x05, 0x7E);
	sevenSeg_write(0x04, 0x7E);
	sevenSeg_write(0x03, 0x01); //dash
	sevenSeg_write(0x02, 0x01);
	sevenSeg_write(0x01, 0x01);
}


///
void sevenSeg_init(void)
{
//GPIO A and B
RCC->AHB1ENR |= 1;
RCC->AHB1ENR |= 4;
	
//PORTA 5, 7 for SPI1 MOSI and SCLK
RCC->APB2ENR |= 0x1000;
GPIOA->MODER &= ~0x0000CC00;
GPIOA->MODER |=  0x00008800;
GPIOA->AFR[0] &=~0xF0F00000;
GPIOA->AFR[0] |= 0x50500000;

	//GPIOB 12 for the slave select
GPIOB->MODER &= ~(0x3<<(2*12));
GPIOB->MODER |=  0x1<<(2*12);

	//SPI1 set up 
SPI1->CR1 = 0x31C;
SPI1->CR2 = 0;
SPI1->CR1 |= 0x40;
}


//
void sevenSeg_write(uint8_t adder, uint8_t dater){
while (!(SPI1->SR & 2)){}
	GPIOB->ODR &= ~ (1<<12);
	SPI1->DR = adder;
	while (SPI1->SR & 0x80){}
	SPI1->DR = dater;
	while (SPI1->SR & 0x80){}
	GPIOB->ODR |= (1<<12);
}

