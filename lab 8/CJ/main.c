#include <stm32f446xx.h>

void SPI1_init(void);
void SPI1_write(unsigned char data);
void delayMs(int n);


//*********************************************************************************
//************************************MAIN*****************************************
//*********************************************************************************
int main(void)
{
		char c;
		SPI1_init();

      while (1)
    {
			for(c = 'A';c<='Z';c++){
				SPI1_write(c);
				delayMs(100);
			}

    }
}
void SPI1_init(void)
{
	//PORTA 5, 7 for SPI1 MOSI and SCLK
	RCC->AHB1ENR |= 1;
	RCC->APB2ENR |= 0x1000;
	GPIOA->MODER &= ~0x0000CC00;
	GPIOA->MODER |=  0x00008800;
	GPIOA->AFR[0] &=~0xF0F00000;
	GPIOA->AFR[0] |= 0x50500000;
	
	GPIOA->MODER &= ~0x00000300;
	GPIOA->MODER |=  0x00000100;
	
	SPI1->CR1 = 0x31C;
	SPI1->CR2 = 0;
	SPI1->CR1 |= 0x40;
	
}

void SPI1_write(unsigned char data)
{
	while (!(SPI1->SR & 2)){}
	GPIOA->BSRR = 0x00100000;
	SPI1->DR = data;
	while (SPI1->SR & 0x80){}
	GPIOA->BSRR = 0x00000010;
}

void delayMs(int n)
{
	int i;
	for(;n>0;n--)
	for(i=0;i<3195;i++);
}




