/*

Some sorta header thang


*/


#include "stm32f4xx.h"

void delayMs(int n);
void SPI_init(void);
void SPI1_write(uint8_t address, uint8_t memory);
void SPI_init_startup(void);

int main(void){
	SPI_init();
	SPI_init_startup();
	while(1){
			for(int i = 0; i< 8; i++){
				SPI1_write(i, 0x7E);
				delayMs(10);
			}
		}
	}



void SPI_init(void){
	RCC->AHB1ENR |= 1;
	RCC->APB2ENR |= 0x1000;
	
	GPIOA->MODER &= ~ 0xCC00;
	GPIOA->MODER |= 0x8800;
	GPIOA->AFR[0] &= ~0xF0F00000;
	GPIOA->AFR[0] |= 0x50500000;
	
	GPIOA->MODER &=~ 0x300;
	GPIOA->MODER |= 0x100;
	
	SPI1->CR1 = 0x31C;
	SPI1->CR2 = 0;
	SPI1->CR1 |= 0x40;
}

void SPI1_write(uint8_t address, uint8_t dater){
	while(!(SPI1->SR & 2)){}
	GPIOA->BSRR = 0x1000000;
	SPI1->DR = address;
	while(SPI1->SR & 0x80){}
	SPI1->DR = dater;
	while(SPI1->SR & 0x80){}
	GPIOA->BSRR = 0x010;
}


void SPI_init_startup(void){
	SPI1_write(0x09, 0x00);
	SPI1_write(0x0A, 0x02);
	SPI1_write(0x0B, 0x07);
	SPI1_write(0x0C, 0x01);
	SPI1_write(0x0F, 0x0F);
	SPI1_write(0x0F, 0x00);
}


void delayMs(int n){
	int i;
	for(;n>0;n--)
		for(i =0; i < 3195; i++);
}




