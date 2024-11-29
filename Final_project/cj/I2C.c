#include "stm32f4xx.h"
#include "I2C.h"

void I2C_init(void){
	// setup PB8 and PB9 pins for I2C1 
	RCC->AHB1ENR  |=  0x00000007;
	RCC->APB1ENR  |=  1<<21;
	GPIOB->AFR[1] &= ~0x000000FF;  //setup PB8 for SCL and PB9 for SDA 
	GPIOB->AFR[1] |= 0x00000044;
	GPIOB->MODER  &= ~0x000F0000;   //setup PB8 and PB9 for alternate function
	GPIOB->MODER  |= 0x000A0000; 
	GPIOB->OTYPER |= 0x00000300;    //set as open-drain

	I2C1->CR1 = 0x8000;   //do software reset for I2C1
	I2C1->CR1 &= ~0x8000; //end reset 
	I2C1->CR2 = 0x0010;   //setup peripheral clock as 16MHz
	I2C1->CCR =  80;      //sets up as standard mode and 100kHz clock
	I2C1->TRISE =  17;    //set max rise time 
	I2C1->CR1 |= 0x0001;  //enable I2C1
}

	int I2C1_byteWrite(char saddr, char maddr, char data) {
    volatile int tmp;
    while (I2C1->SR2 & 2);                /* wait until bus not busy */
    I2C1->CR1 |= 0x100;                   /* generate start */
    while (!(I2C1->SR1 & 1));             /* wait until start flag is set */
    I2C1->DR = saddr << 1;                /* transmit slave address */
    while (!(I2C1->SR1 & 2));             /* wait until addr flag is set */
    tmp = I2C1->SR2;                      /* clear addr flag */
    while (!(I2C1->SR1 & 0x80));          /* wait until data register empty */
    I2C1->DR = maddr;                     /* send memory address */
    while (!(I2C1->SR1 & 0x80));          /* wait until data register empty */
    I2C1->DR = data;                      /* transmit data */
    while (!(I2C1->SR1 & 4));             /* wait until transfer finished */
    I2C1->CR1 |= 0x200;                   /* generate stop */
    return 0;
} 
	
int I2C1_byteRead(char saddr, char maddr, char* data) {
    volatile int tmp;
    while (I2C1->SR2 & 2);                /* wait until bus not busy */
    I2C1->CR1 |= 0x100;                   /* generate start */
    while (!(I2C1->SR1 & 1));             /* wait until start flag is set */
    I2C1->DR = saddr << 1;                /* transmit slave address + Write */
    while (!(I2C1->SR1 & 2));             /* wait until addr flag is set */
    tmp = I2C1->SR2;                      /* clear addr flag */
    while (!(I2C1->SR1 & 0x80));          /* wait until data register empty */
    I2C1->DR = maddr;                     /* send memory address */
    while (!(I2C1->SR1 & 0x80));          /* wait until data register empty */
    I2C1->CR1 |= 0x100;                   /* generate restart */
    while (!(I2C1->SR1 & 1));             /* wait until start flag is set */
    I2C1->DR = saddr << 1 | 1;            /* transmit slave address + Read */
    while (!(I2C1->SR1 & 2));             /* wait until addr flag is set */
    I2C1->CR1 &= ~0x400;                  /* Disable Acknowledge */
    tmp = I2C1->SR2;                      /* clear addr flag */
    I2C1->CR1 |= 0x200;                   /* generate stop after data received */
    while (!(I2C1->SR1 & 0x40));          /* Wait until RXNE flag is set */
    *data = I2C1->DR;                   /* Read data from DR */
    return 0;
}	