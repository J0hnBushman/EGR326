
#include "sevenSeg.h"

int num[] = {0x7E,  //0
							0x30,  //1
							0x6D,  //2
							0x79,  //3
							0x33,  //4
							0x5B,  //5
							0x5F,  //6
							0x70,  //7
							0x7F,  //8
							0x7B,  //9
							0x01}; //-

void Init_seq(void){
	sevenSeg_write(0x09, 0x00);
	sevenSeg_write(0x0A, 0x02);
	sevenSeg_write(0x0B, 0x07);
	sevenSeg_write(0x0C, 0x01);
	sevenSeg_write(0x0F, 0x0F);
	sevenSeg_write(0x0F, 0x00);
	//setup screen
	sevenSeg_write(0x08, num[10]);
	sevenSeg_write(0x07, num[10]);
	sevenSeg_write(0x06, num[00]); //dash
	sevenSeg_write(0x05, num[0]);
	sevenSeg_write(0x04, num[0]);
	sevenSeg_write(0x03, num[0]); //dash
	sevenSeg_write(0x02, num[10]);
	sevenSeg_write(0x01, num[10]);
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
	
	//PC13, 12, 11 for button presss
	GPIOC->MODER &= ~ 0x00FF00000UL;		//pc13 and pc12 button press
	GPIOC->PUPDR |=   1<<13*2;
	GPIOC->PUPDR |=   1<<12*2;
	GPIOC->PUPDR |=   1<<11*2;
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

