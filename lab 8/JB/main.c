
/*******************************************************************************
* Name:             Charles Norton & John Bushman
* Course:           EGR 326 - Embedded Systems
* Project:          7-segment
* File:             lab8_main
* Description:   		
********************************************************************************/

#include <stm32f446xx.h>
#include <stdio.h>
#include "sevenSeg.h"

#define BP1 ((GPIOC->IDR)&(1<<13))	
#define BP2 ((GPIOC->IDR)&(1<<12))
#define BP3 ((GPIOC->IDR)&(1<<11))


void sevenSeg_init(void);
void sevenSeg_write(uint8_t adder, uint8_t dater);
void delayMs(int n);
void Init_seq(void);
void systick_init(void);
void SysTick_Handler(void);

int count = 0;

//EXTI
extern void EXTI15_10IRQHandler(void);

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

							
//*********************************************************************************
//************************************MAIN*****************************************
//*********************************************************************************
int main(void)
{
	int start_flag = 0;
	int p1 = 0;
	int p2 = 0;
	
	__disable_irq();
	sevenSeg_init();
	Init_seq();
	__enable_irq();
	
	
      while (1)
    {
			if(BP1 == 0){
				start_flag = 1; 
				systick_init();
			}
			
			if((start_flag==1)){
				if(BP2 == 0){
					p1 = 1;
				}
				if(BP3 == 0){
					p2 = 1;
				}
				if(p1 == 0){
					sevenSeg_write(1, num[count%10]);
					sevenSeg_write(2, num[(count%100)/10]);
				}
				if(p2 == 0){
					sevenSeg_write(4, num[count%10]);
					sevenSeg_write(5, num[(count%100)/10]);
				}
					if(count<160){
					sevenSeg_write(7, num[(count/10)%10]);
					sevenSeg_write(8, num[(count/100)%10]);
				}

			}
			
	}
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




//
void delayMs(int n)
{
int i;
for(;n>0;n--)
for(i=0;i<3195;i++);
}



///
void Init_seq(void){
	sevenSeg_write(0x09, 0x00);
	sevenSeg_write(0x0A, 0x02);
	sevenSeg_write(0x0B, 0x07);
	sevenSeg_write(0x0C, 0x01);
	sevenSeg_write(0x0F, 0x0F);
	sevenSeg_write(0x0F, 0x00);
	//setup screen
	sevenSeg_write(0x08, num[0]);
	sevenSeg_write(0x07, num[0]);
	sevenSeg_write(0x06, num[10]); //dash
	sevenSeg_write(0x05, num[0]);
	sevenSeg_write(0x04, num[0]);
	sevenSeg_write(0x03, num[10]); //dash
	sevenSeg_write(0x02, num[0]);
	sevenSeg_write(0x01, num[0]);
}



/////
void systick_init(void)
{
	SysTick->CTRL = 0; //disables systick
	SysTick->LOAD = 1600000 - 1; //Loads value at 16MHz clock
	SysTick->VAL = 0;	//Clears VAL
	SysTick->CTRL = 0x0000007; //Enables systick
}


void SysTick_Handler(void) {
	count ++;
}


