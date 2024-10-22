/*




*/

#include "stm32f446xx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "KP.h" 

#define  LSB(X) (X & 0x0F) + '0'
#define  MSB(X) ((X & 0x70)>>4) + '0'

//***RTC ADRESSES***
#define SecondsAddr 0x00
#define MinsAddr 0x01
#define HoursAddr 0x02
#define slaveAddr 0x68



/* NOTE:
RTC Slave Address:
The slave address byte contains the 7-bit DS3231
address, which is 1101000, followed by the direction
bit (R/W), which is 1 for a read.
so the address is 11101000
*/

int I2C1_byteWrite(char saddr, char maddr, char data);
int I2C1_byteRead(char saddr, char maddr, char* data);
void I2C_init(void);

void USART2_init(void);
void USART2_write(char c);
void delayMs(int n);
void read_time(char maddr);
void userPrompt(int num);

int i;

char RTC_data;
char *RTC_Data_ptr = &RTC_data;





//*************************MAIN***************************************
int main (void){
	I2C_init();
	USART2_init();
	uint16_t  key;
	char carray[13];
	uint16_t userInput = 0;
	uint16_t count = 0;
	keypadInit();
	
	userPrompt(0);
	
	while(1){
		//I2C1_byteWrite(slaveAddr, HoursAddr, 0x12);
		//I2C1_byteWrite(slaveAddr, MinsAddr, 0x42);
		//I2C1_byteWrite(slaveAddr, SecondsAddr, 0x18);
		
		
		while(!(key = readKeypad()));  /*Get which keys pressed*/
		decodeKeypad(key, carray);  /*What are those keys*/
		count ++;
		//printf("Count Value: %d\n",count);  /*Print those keys to screen*/
		
		USART2_write(carray[0]);
		
		
		if(carray[0]=='*'){
			read_time(0x05);
			USART2_write(':');
			read_time(0x04);
			USART2_write(':');
			read_time(0x03);
			USART2_write(':');
			read_time(0x02);
			USART2_write(':');
			read_time(0x01);
			USART2_write(':');
			read_time(0x00);
			count = 0;
		}else if(carray[0]=='#'){
			count = 0;
		}else{
			if(count%2 == 0){
				userInput |= (carray[0] & 0x0F);
				I2C1_byteWrite(slaveAddr, (count/2), userInput);
				printf("User Input Value: %x\n",userInput);
				userInput = 0;
			}else{
				userInput |= (carray[0] & 0x0F)<<4;
			}
		}
				
		while(readKeypad() == key); /*Wait for the keypad to change*/
		
		
		
		//read_time(HoursAddr);
		//USART2_write(':');
		//read_time(MinsAddr);
		//USART2_write(':');
		//read_time(SecondsAddr);
		//USART2_write(0x0D);
		//delayMs(1000);
	}
	
		return 0;
}





//**************************I2C_init**************************************
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





//**********************************USART2_init*********************************
void USART2_init(void){
RCC->AHB1ENR |= 1;
RCC->APB1ENR |= 0x20000;

GPIOA->AFR[0] &= ~ 0x0F00;
GPIOA->AFR[0] |=   0x0700;

GPIOA->MODER &= ~0x0030;
GPIOA->MODER |= 0x0020;

USART2->BRR = 0x0683;
USART2->CR1 = 0x0008;
USART2->CR2 = 0x0000;
USART2->CR3 = 0x0000;
USART2->CR1 |= 0x2000;
}






//*****************************USART2_write*****************************
void USART2_write(char c){
while(!(USART2->SR & 0x0080)){}
USART2->DR = (c);
}





//**************************READ_SECONDS***********************************
void read_time(char maddr){
	char sec_tens;
	char sec_ones;
	
	I2C1_byteRead(slaveAddr, maddr, RTC_Data_ptr);
	
	sec_ones = LSB(RTC_data);
	sec_tens = MSB(RTC_data);
	
	USART2_write(sec_tens);
	USART2_write(sec_ones);
}





//**************************I2C_WRITE******************************************
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




//*******************************I2C_READ****************************************
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



//*****************USER_PROMPTS***********************
void userPrompt(int num){
	char prompt[200];
	
	
	switch(num){
		case 0:
			strcpy(prompt, "Enter a date and time in the following format: Year(00) Month(00) Day(00) Hour(00) Minute(00) Second(00)");
			break;
		
		case 1:
			
			break;
		
		case 2:
			break;
	}
	//USART2_write(0x1b);
	for(unsigned int i =0; i < strlen(prompt); i++){
		USART2_write(prompt[i]);
	}

	
	
}


//*****************************DELAY********************************
void delayMs(int n){
int i;
for(; n > 0 ; n --)
for(i = 0; i < 2000; i++);
}
