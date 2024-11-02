#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "I2C.h"

void I2C_init(void)
{
	RCC->AHB1ENR |= 0x2; //enable gpioB clock
	RCC->APB1ENR |= 1<<21;//Enable I2C clk
	//configuring PB8 abd PB9 for I2C1
	GPIOB->MODER &=~ 0x00F0000U; //set to afr as open-drain output with pullups
	GPIOB->MODER |= 0x000A0000U;
	GPIOB->AFR[1] &=~ 0x000000FFU;
	GPIOB->AFR[1] |= 0x00000044U;
	GPIOB->OTYPER |= 0x00000300U;
	//GPIOB->PUPDR &=~ 0x000F0000U;
	//GPIOB->PUPDR |= 0x00050000U;
	
	//i2c
	I2C1->CR1 = 0x8000; //software reset I2C1
	I2C1->CR1 &=~ 0x8000U; //out of reset
	I2C1->CR2 = 0x0010; //set peripheral clock to 16Mhz
	I2C1->CCR = 80; //set to standard mode with 100KHz clk
	I2C1->TRISE = 17; //set max rise time
	I2C1->CR1 |= 0x0001; //enable to I2C1 module
	
}


void I2C1_byteWrite(char saddr,char data)
{
	volatile int tmp;
	
	I2C1->CR1 &=~ 0x8000;//Takes out of Reset
	while(I2C1->SR2 & 2); //for for busy flag to clear
	
	I2C1->CR1 |= 0x100; //generate start and wait for start flag set
	while(!(I2C1->SR1 & 1));
	
	I2C1->DR = saddr << 1; //transmit slave address
	while(!(I2C1->SR1 & 2)); //wait until addr flag is set
	tmp = I2C1->SR2; //clear addr flag
	
	while (!(I2C1->SR1 & 0x80)); //wait until data register is empty
	
	I2C1->DR = data; //transmit the data
	
	while (!(I2C1->SR1 & 4)); //wait until end of transfer
	I2C1->CR1 |= 0x200; //generate stop bit
}



//void I2C_init_slave(void){
//// setup PB8 and PB9 pins for I2C1 
//	RCC->AHB1ENR  |=  0x00000007; //turns on the GPIO port
//	RCC->APB1ENR  |=  1<<21;			//starts i2C1 clk
//	
//	GPIOA->MODER |= 1<<(2*5);
//	//set PB8 and PB9 to AF4
//	GPIOB->MODER	&= ~(0x3<<(2*9));		
//	GPIOB->MODER	&= ~(0x3<<(2*8));
//	GPIOB->MODER	|= 0x2<<(2*9);
//	GPIOB->MODER	|= 0x2<<(2*8);
//	GPIOB->OTYPER |= 0x00300;    //set as open-drain
//	GPIOB->OSPEEDR |= 0x3<<(2*8);	//SET the speed as hgih speed
//	GPIOB->OSPEEDR |= 0x3<<(2*9);
//	GPIOB->PUPDR |= 0x1<<(2*8);
//	GPIOB->PUPDR |= 0x1<<(2*9);
//	GPIOB->AFR[1] &= ~0x0FF;  //setup PB8 for SCL and PB9 for SDA 
//	GPIOB->AFR[1] |= 0x044;
//	
//	
//	I2C1->CR1 = 0x8000;   //do software reset for I2C1
//	I2C1->CR1 &= ~0x8000; //end reset 
//	I2C1->CR1 |= 0x0001;  //enable I2C1
//	I2C1->CR1 |= 1<<10;
//	I2C1->OAR1 &= ~(1<<15);	//establish 7 -bit mode
//	I2C1->OAR1 |= 0x0F<<1; //sets memory addres
//}



//first bit in the memory addres is has a 1 like the rtc

//int	listen(char* data){
//	volatile int tmp;

//	//EV1
//	while (!(I2C1->SR1 & 1<<1));	//wait for address match
//	  tmp = I2C1->SR1;  	//clears the ADDR flag
//		tmp = I2C1->SR2;  	//clears the ADDR flag
//	
//	
//	//EV2
//	while(!(I2C1->SR1 & 1<<6));
//		*data = I2C1->DR;
//		
//	//EV4
//	while(!(I2C1->SR1 & 1<<4));
//		tmp = I2C1->SR1;  	//clears the ADDR flag
//		I2C1->CR1 |= 0x200;   /* generate stop */

//	return 0;
//}

	

	
//int I2C1_byteRead(char saddr, char maddr, char* data){
//    volatile int tmp;
//    while (I2C1->SR2 & 2);                /* wait until bus not busy */
//    I2C1->CR1 |= 0x100;                   /* generate start */
//		printf("Start bit generated - \n");
//    while (!(I2C1->SR1 & 1));             /* wait until start flag is set */
//    I2C1->DR = saddr << 1;                /* transmit slave address + Write */
//		printf("Transmit slave address - \n");
//    while (!(I2C1->SR1 & 2));             /* wait until addr flag is set */
//    tmp = I2C1->SR2;                      /* clear addr flag */
//		printf("ADDR flag cleared - \n");
//    while (!(I2C1->SR1 & 0x80));          /* wait until data register empty */	
//    I2C1->DR = maddr;                     /* send memory address */
//		printf("Transmit memory address - \n");
//    while (!(I2C1->SR1 & 0x80));          /* wait until data register empty */
//    I2C1->CR1 |= 0x100;                   /* generate restart */
//		printf("Generate a restart - \n");
//    while (!(I2C1->SR1 & 1));             /* wait until start flag is set */
//    I2C1->DR = saddr << 1 | 1;            /* transmit slave address + Read */
//		printf("Transmit slave addres - \n");
//    while (!(I2C1->SR1 & 2));             /* wait until addr flag is set */
//    I2C1->CR1 &= ~0x400;                  /* Disable Acknowledge */
//    tmp = I2C1->SR2;                      /* clear addr flag */
//    I2C1->CR1 |= 0x200;                   /* generate stop after data received */
//		printf("Generate Stop bit - \n");
//    while (!(I2C1->SR1 & 0x40));          /* Wait until RXNE flag is set */
//    *data = I2C1->DR;                   /* Read data from DR */
//		printf("Read data - \n");
//    return 0;
//}	

