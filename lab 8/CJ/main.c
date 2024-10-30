#include <stm32f446xx.h>
#include <stdlib.h>
#include <stdio.h>

void SPI1_init(void);
void SPI1_write(unsigned char data);
void write(uint8_t MSB, uint8_t LSB);
void init_sequence(void);
void SysTick_Init (void);
void SysTick_msdelay(uint16_t msdelay);
void timer_init(void);


//*********************************************************************************
//************************************MAIN*****************************************
//*********************************************************************************
int main(void)
{
	int num[] = { 0x7E,   //0
								0x30,   //1
								0x6D,   //2
								0x79,   //3
								0x33,   //4
								0x5B,   //5
								0x5F,   //6
								0x70,   //7
								0x7F,   //8
								0x7B,   //9
								0x01 }; //-
	
		__disable_irq();
		SPI1_init();
		SysTick_Init();
		init_sequence();
		timer_init();
		__enable_irq();

      while (1)
    {
			if(TIM3->SR & 1<<0){
					TIM3->SR &=~ (1<<0);
					printf("here\n");
			}
	
    }
}
void SPI1_init(void)
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

//GPIO 4 for the slave select
GPIOA->MODER &= ~0x00000300;
GPIOA->MODER |=  0x00000100;

//SPI1 set up
SPI1->CR1 = 0x31C;
SPI1->CR2 = 0;
SPI1->CR1 |= 0x40;

//PC13, 12, 11 for button presss
GPIOC->MODER &= ~ 0x00F000000UL; //pc13 and pc12 button press
GPIOC->PUPDR |=   1<<13*2;
GPIOC->PUPDR |=   1<<12*2;
GPIOC->PUPDR |=   1<<11*2;

//interupt set up for PC13
SYSCFG->EXTICR[3] &= ~0x00F0U;
SYSCFG->EXTICR[3] |=  0x0020U;
EXTI->IMR |=  1U<<13;
EXTI->RTSR &= ~1U<<13;
EXTI->FTSR |=  1U<<13;

//interupt set up for PC11
SYSCFG->EXTICR[2] &= ~0x00F000U;
SYSCFG->EXTICR[2] |=  0x002000U;
EXTI->IMR |=  1U<<11;
EXTI->RTSR &= ~1U<<11;
EXTI->FTSR |=  1U<<11;

//interupt set up for PC12
SYSCFG->EXTICR[3] &= ~0x00FU;
SYSCFG->EXTICR[3] |=  0x002U;
EXTI->IMR |=  1U<<12;
EXTI->RTSR &= ~1U<<12;
EXTI->FTSR |=  1U<<12;

NVIC_EnableIRQ(EXTI15_10_IRQn);

	
}

void SPI1_write(unsigned char data)
{
	while (!(SPI1->SR & 2)){}
	GPIOA->BSRR = 0x00100000;
	SPI1->DR = data;
	while (SPI1->SR & 0x80){}
	GPIOA->BSRR = 0x00000010;
}
void write(uint8_t MSB, uint8_t LSB)
{
	while (!(SPI1->SR & 2)){}
	GPIOA->BSRR = 0x00100000;
	SPI1->DR = MSB;
	while (SPI1->SR & 0x80){}
	SPI1->DR = LSB;
	while (SPI1->SR & 0x80){}
		
	GPIOA->BSRR = 0x00000010;
}
void init_sequence(void){
	write(0x09,0x00);
	write(0x0A,0X02);
	write(0X0B,0X07);
	write(0X0C,0X01);
	write(0X0F,0X0F);
	write(0X0F,0X00);
}

 void SysTick_Init (void){
	 
	 //Setting SysTick_CTL to disable Systick during a step
	 SysTick -> CTRL	= (unsigned long)0x00000000;
	 
	 //Setting SysTick_LOAD to max reload value
	 SysTick -> LOAD	= (unsigned long)0x00FFFFFF;
	 
	 //Writing SysTick_VAL to to clear it
	 SysTick -> VAL	= (unsigned long)0x00000000;
	 
	 //Enabling SysTick_CTL, 16MHz, No Interrupts
	 SysTick -> CTRL	= (unsigned long)0x00000005;
 }
 void SysTick_msdelay(uint16_t msdelay){
	 //delay for 1 ms delay * (some delay value) //SysTick_LOAD
	 SysTick -> LOAD = ((msdelay * 16000) - 1);
	 
	 //Clearing SysTick_VAL
	 SysTick -> VAL = 0;
	 
	 // Waiting for flag to be set //SysTick_CTL
	 while ( (SysTick -> CTRL & 0x00010000) == 0);
 }
 
 void timer_init(void)
 {
	 RCC->APB1ENR |=0x03;
	 TIM2->PSC = 16000;
	 TIM3->PSC = 16000;
	 TIM2->ARR = 1000;
	 TIM2->CCR1 = 0;
	 TIM3->ARR = 1000;
	 TIM3->CCR1 = 0;
	 TIM2->CNT = 0;
	 TIM3->CNT = 0;

	 TIM2->CR1 = 1;
	 TIM3->CR1 = 1;

	 
 }



