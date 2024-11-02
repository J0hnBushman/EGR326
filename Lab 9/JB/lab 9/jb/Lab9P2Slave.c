/*******************************************************************************
* Name:             Gabe Gipe and Mitch Hundal
* Course:           EGR 326 - Embedded Systems Lab
* Date:             10/28/24
* Lab:              Lab 9 
* File:             Lab9P2.c
* Description:      Slave Program
********************************************************************************/


#include "stm32f4xx.h"


//Macro Functions
#define BIT(x) (uint32_t) (1<<x)
#define SHIFT(x,y) (uint32_t) (y<<x)

#define PC 2

#define MIn1 0
#define MIn2 2
#define MIn3 4
#define MIn4 6

//Declare Functions
void I2CInit(void);
int I2C1_ByteRead(char saddr, char* data);
void motorSetup(void);
void LEDinit(void);
void RunMotorFRWD(void);
void RunMotorRVRSE(void);
void SysTick_DelayMS(unsigned int delayTime);
void Motorcycles(void);

//Globals
char slaveAdd = 0x69;
int number = 0;
int LEDstate = 0;
int countF = 0;
int countR = 0;
int BTN2Stop = 2; 
int pressed = 0;
int cycle = 0;

int main(void){
	//Initialization
	LEDinit();
	I2CInit();
	motorSetup();
	
	while(1){
		
		I2C1_ByteRead(slaveAdd, &number);
		
		//LED BTN 
		if(number == 0x22){
			if(LEDstate == 0){
				GPIOA->ODR |= 0x0001;//Set one LED
				GPIOA->ODR &=~ 0x0002;//clear other LED
				number = 0;
				LEDstate++;
			}
			
			else if(LEDstate == 1){
				GPIOA->ODR |= 0x0002;//Set one LED
				GPIOA->ODR &=~ 0x0001;//clear other LED
				number = 0;
				LEDstate = 0;
			}
		}
		
		else if (number != 0x00 && number < 0x11){
			Motorcycles();
			RunMotorFRWD();
			number = 0x00;
		}
		
		else if (number != 0x00 && number > 0x10){
			Motorcycles();
			RunMotorRVRSE();
			number = 0x00;
		}	
	}	
}


void Motorcycles(void){
	if(number == 0x02) cycle = 1;
	if(number == 0x03) cycle = 2;
	if(number == 0x04) cycle = 3;
	if(number == 0x05) cycle = 4;
	if(number == 0x06) cycle = 5;
	if(number == 0x07) cycle = 6;
	if(number == 0x08) cycle = 7;
	if(number == 0x09) cycle = 8;
	if(number == 0x10) cycle = 9;
	if(number == 0x11) cycle = 1;
	if(number == 0x12) cycle = 2;
	if(number == 0x13) cycle = 3;
	if(number == 0x14) cycle = 4;
	if(number == 0x15) cycle = 5;
	if(number == 0x16) cycle = 6;
	if(number == 0x17) cycle = 7;
	if(number == 0x18) cycle = 8;
	if(number == 0x19) cycle = 9;
}

/***************************************************************
* Brief: Setups up PA9 and PA8 for I2C TIM3 CH1 to capture echo signal
* param:     void
* return:    void     
****************************************************************/
void I2CInit(void){
	//Configures PB 8 as SCL and PB9 as SDA
	RCC->AHB1ENR |= 0x0002;//Enable GPIOB clk
	GPIOB->MODER &=~ 0x000F0000;
	GPIOB->MODER |= 0x000A0000;
	GPIOB->AFR[1] &=~ 0x000000FF;
	GPIOB->AFR[1] |= 0x00000044;//AF 4 for PB8 and 9
	GPIOB->OTYPER |= 0x00000300;//open drain 
	GPIOB->OSPEEDR |= 0x000F0000;// Sets speed
	GPIOB->PUPDR |= 0x00050000;//Pull up on PB8 and 9
	
	//Setup I2C for Slave Address Polling
	RCC->APB1ENR |= 1<<21;//Enable I2C clk
	I2C1->CR1 = 0x8000; //Software Reset for I2C1
	I2C1->CR1 &=~ 0x8000;//Takes out of Reset
	I2C1->CR2 = 0x0010;//Set peripheral Clk to 16Mhz
	I2C1->CCR = 80; //Standard mode 100kHz clk
	I2C1->TRISE = 17; //Max rise time
	
	I2C1->OAR1 |= (0x69 << 1);//Sets 0x69 as address of this slave
	I2C1->OAR1 |= (1 << 15);//Enables this as address mode
	I2C1->CR1 |= I2C_CR1_ACK;//Sets ack bit
	

	I2C1-> CR1 |= 0x0001; //Enable I2C1 
	
}


/***************************************************************
* Brief: Function to read I2C bus
* param:   Slave and master address and data string  
* return:    Received data in 8 bits     
****************************************************************/
int I2C1_ByteRead(char saddr, char* data){
	volatile int tmp;
		
    I2C1->CR1 |= 0x0400;                /* Enable Acknowledge */
	
    while (!(I2C1->SR1 & 2)); 
	
    tmp = I2C1->SR2;                    /* clear addr flag */

    while (!(I2C1->SR1 & 0x40));        /* Wait until RXNE flag is set */
			while (!(I2C1->SR1 & 0x10));  //wait until address flag set
	
			*data++ = I2C1->DR;                 /* Read data from DR */
    I2C1->CR1 &=~ 0x0400;                /* Disable Acknowledge */
	
	return 0;
}

/***************************************************************
* Brief: Initialize RBD LED
* param:   None 
* return:    None     
****************************************************************/
void LEDinit(void){
	RCC->AHB1ENR |= 0x0001;//Enable GPIOA clk
	//LED init on PA0 2
	GPIOA->MODER &=~ 0x000F;
	GPIOA->MODER |= 0x005;
}


/***************************************************************
* Brief: Initialize stepper Motor
* param:   None 
* return:    None     
****************************************************************/
void motorSetup(void){
	//Motor Setup
	RCC->AHB1ENR |= 0x0004; //Enable GPIOC clock
	GPIOC->MODER &=~0x3333;
	GPIOC->MODER |= 0x1111;//PC 0,2,4,6 for o/ps
	
}

void RunMotorFRWD(void){
	while(countF <= cycle){
		//setps through 4 steps (one cycle)
		GPIOC->ODR |= BIT(MIn1);
		GPIOC->ODR |= BIT(MIn3);
		GPIOC->ODR &=~ BIT(MIn2);
		GPIOC->ODR &=~ BIT(MIn4);
		SysTick_DelayMS(2);
		GPIOC->ODR &=~ BIT(MIn1);
		GPIOC->ODR |= BIT(MIn3);
		GPIOC->ODR |= BIT(MIn2);
		GPIOC->ODR &=~ BIT(MIn4);
		SysTick_DelayMS(2);
		GPIOC->ODR &=~ BIT(MIn1);
		GPIOC->ODR &=~ BIT(MIn3);
		GPIOC->ODR |= BIT(MIn2);
		GPIOC->ODR |= BIT(MIn4);
		SysTick_DelayMS(2);
		GPIOC->ODR |= BIT(MIn1);
		GPIOC->ODR &=~ BIT(MIn3);
		GPIOC->ODR &=~ BIT(MIn2);
		GPIOC->ODR |= BIT(MIn4);
		SysTick_DelayMS(2);	
		countF = countF + 1;
	}
	countF = 0;
}
	

void RunMotorRVRSE(void){
	while(countR <= cycle){
		//setps through 4 steps backwards (one cycle)
		GPIOC->ODR |= BIT(MIn1);
		GPIOC->ODR &=~ BIT(MIn3);
		GPIOC->ODR &=~ BIT(MIn2);
		GPIOC->ODR |= BIT(MIn4);
		SysTick_DelayMS(2);	
		GPIOC->ODR &=~ BIT(MIn1);
		GPIOC->ODR &=~ BIT(MIn3);
		GPIOC->ODR |= BIT(MIn2);
		GPIOC->ODR |= BIT(MIn4);
		SysTick_DelayMS(2);
		GPIOC->ODR &=~ BIT(MIn1);
		GPIOC->ODR |= BIT(MIn3);
		GPIOC->ODR |= BIT(MIn2);
		GPIOC->ODR &=~ BIT(MIn4);
		SysTick_DelayMS(2);		
		GPIOC->ODR |= BIT(MIn1);
		GPIOC->ODR |= BIT(MIn3);
		GPIOC->ODR &=~ BIT(MIn2);
		GPIOC->ODR &=~ BIT(MIn4);
		SysTick_DelayMS(2);
		countR = countR + 1;
	}
	countR = 0;
}

/**************************************************************** 
Brief: This function delays the code for a certain amount of time based from the input delayTime
param: delayTime (usigned int)
return: void
****************************************************************/
	
void SysTick_DelayMS(unsigned int delayTime){
// Systick delay function
	SysTick->CTRL = 0; // disable SysTick During CTRL
	SysTick->LOAD = ((delayTime * 16000) - 1); //delay for 1 msecond per delay value
	SysTick->VAL = (unsigned long)0x00000000; // any write to CVR clears it
	SysTick->CTRL = (unsigned long)0x00000005; // enable systic, 16MHz, No Interrupts
	
		while(((SysTick->CTRL) & 0x00010000) == 0); // wait for flag to be SET	
	}