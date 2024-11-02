/*******************************************************************************
* Name:             Gabe Gipe and Mitch Hundal
* Course:           EGR 326 - Embedded Systems Lab
* Date:             10/28/24
* Lab:              Lab 9 
* File:             Lab9P2.c
* Description:      Master Program
********************************************************************************/

#include "stm32f4xx.h"
#include "keypadUSART.h"


extern void TIM3_IRQHandler(void);

//Declare Functions
void I2CInit(void);
int I2C1_byteWrite(char saddr, char data);
int I2C1_ByteRead(char saddr, char* data);
void button_init(void);
int speedkeypad(int keypress);
int speedkeypad2(int keypress);
void motorPosition(void);

//Globals
char slaveAdd = 0x69;
int BTN1Stop = 0;
int BTN2Stop = 0;
int BTN3Stop = 0;
int keysentF = 0;
int keysentR = 0;
int totalmove = 0;
int abstotal = 0;

int main(void){
	uint16_t  key; 
  char carray[17];
	char keypadIntString[10];
	button_init();
	I2CInit();
  keypadInit(); 

	
	//Initialization
	while(1){	
		if((key = readKeypad())){  /*Get which keys pressed*/ 
		decodeKeypad(key, carray);  /*What are those keys*/ 
		while(readKeypad() == key);  /*Wait for the keypad to change*/ 
		if(carray[0] != 0 && carray[0] != 11 && carray[0] != 12){
			printf("You Entered %d Speed\n", carray[0]);
			keysentF = speedkeypad(carray[0]);
		}
	}
		//LED 
		if(BTN3Stop){
			//Transmit data to signify btn press
			I2C1_byteWrite(slaveAdd, 0x22);
			BTN3Stop = 0;
		}
		
		//Forward Motor
		if(BTN1Stop){
			totalmove = totalmove + carray[0];
			I2C1_byteWrite(slaveAdd, keysentF);
			motorPosition();
			BTN1Stop = 0;
		}
		
		//Reverse Motor
		if(BTN2Stop){
			//Transmit data to signify btn press
			totalmove = totalmove - carray[0];
			keysentR = speedkeypad2(keysentF);
			I2C1_byteWrite(slaveAdd, keysentR);
			motorPosition();
			BTN2Stop = 0;
		}
	}	
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
	//Setup I2C
	RCC->APB1ENR |= 1<<21;//Enable I2C clk
	I2C1->CR1 = 0x8000; //Software Reset for I2C1
	I2C1->CR1 &=~ 0x8000;//Takes out of Reset
	I2C1->CR2 = 0x0010;//Set peripheral Clk to 16Mhz
	I2C1->CCR = 80; //Standard mode 100kHz clk
	I2C1->TRISE = 17; //Max rise time
	I2C1-> CR1 |= 0x0001; //Enable I2C1 
	
}

/***************************************************************
* Brief: Function to read I2C bus
* param:   Slave and master address and data string  
* return:    Transmit data in 8 bits     
****************************************************************/
int I2C1_byteWrite(char saddr, char data){
    volatile int tmp;
	
		I2C1->CR1 &=~ 0x8000;//Takes out of Reset
    while (I2C1->SR2 & 2);              /* wait until bus not busy */

    I2C1->CR1 |= 0x100;                 /* generate start */
    while (!(I2C1->SR1 & 1));           /* wait until start flag is set */

    I2C1->DR = saddr << 1;              /* transmit slave address */
    while (!(I2C1->SR1 & 2));           /* wait until addr flag is set */
    tmp = I2C1->SR2;                    /* clear addr flag */
        
	
    while (!(I2C1->SR1 & 0x80));        /* wait until data register empty */
    I2C1->DR = data;                    /* transmit data */

    while (!(I2C1->SR1 & 4));           /* wait until transfer finished */
    I2C1->CR1 |= 0x200;                 /* generate stop */

    return 0;
}


/***************************************************************
* Brief: Function to read I2C bus
* param:   Slave and master address and data string  
* return:    Received data in 8 bits     
****************************************************************/
int I2C1_ByteRead(char saddr, char* data){
	volatile int tmp;
		while(I2C1->SR2 & 2);//Wait until bus is not busy

		I2C1->CR1 |= 0x100;                 /* generate start */
    while (!(I2C1->SR1 & 1));           /* wait until start flag is set */

    I2C1->DR = saddr << 1;              /* transmit slave address + Write */
    while (!(I2C1->SR1 & 2));           /* wait until addr flag is set */
    tmp = I2C1->SR2;                    /* clear addr flag */

    while (!(I2C1->SR1 & 0x80));        /* wait until data register empty */

    I2C1->CR1 |= 0x100;                 /* generate restart */
    while (!(I2C1->SR1 & 1));           /* wait until start flag is set */
    I2C1->DR = saddr << 1 | 1;          /* transmit slave address + Read */

    while (!(I2C1->SR1 & 2));           /* wait until addr flag is set */
    I2C1->CR1 &= ~0x0400;                /* Disable Acknowledge */
    tmp = I2C1->SR2;                    /* clear addr flag */

    I2C1->CR1 |= 0x200;                 /* generate stop after data received */

    while (!(I2C1->SR1 & 0x40));        /* Wait until RXNE flag is set */
    *data++ = I2C1->DR;                 /* Read data from DR */

    return 0;
}


/***************************************************************
* Brief: Configures On board push button
* param:   None
* return:   None   
****************************************************************/
void button_init(void){
    __disable_irq(); /* global disable IRQs */
		RCC->AHB1ENR |= 0x0004; /* enable GPIOC clock */
		RCC->APB2ENR |= 0x4000; /* enable SYSCFG clock */
		//Configure PC6 ,PC7, and PC8 for external button interrupts
		GPIOC->MODER &=~ 0xFFFF;//Sets PC0 6, 7, 8 to inputs
		GPIOC->PUPDR &=~ 0xFFFF;//Clears the GPIOC PUPD register
	
		GPIOC->PUPDR |= 0x00010000;//Puts a pull up resistor on PC8
		GPIOC->PUPDR |= 0x00004000;//Puts a pull up resistor on PC7
		GPIOC->PUPDR |= 0x00001000;//Puts a pull up resistor on PC6

		//Configures push button interrupts
		 SYSCFG->EXTICR[1] &=~ 0xFFFF;//Clears port selection for EXTI6 and EXTI7
		 SYSCFG->EXTICR[2] &=~ 0xFFFF;//Clears port selection for EXTI8
		 
		 SYSCFG->EXTICR[1] |= 0x0200;//Selects port C for EXTI6
		 SYSCFG->EXTICR[1] |= 0x2000;//Selects port C for EXTI6
		 SYSCFG->EXTICR[2] |= 0x0002;//Selects port C for EXTI8
		 
		 EXTI->IMR |= 0x0040; //Unmask bit corresponding to PC6
		 EXTI->IMR |= 0x0080; //Unmask bit corresponding to PC7
		 EXTI->IMR |= 0x0100; //Unmask bit corresponding to PC8

		 EXTI->FTSR |= 0x0040; /* select falling edge trigger on PC6 */
		 EXTI->FTSR |= 0x0080; /* select falling edge trigger on PC7 */
		 EXTI->FTSR |= 0x0100; /* select falling edge trigger on PC8 */
		
		 NVIC_EnableIRQ(EXTI9_5_IRQn);//Enables IQR 6, 7, and 8
		 
		 __enable_irq(); /* global enable IRQs */
}

/***************************************************************
* Brief: determines motor step from keypad
* param:   None
* return:   None   
****************************************************************/
int speedkeypad(int keypress){
	if(keypress == 1) return 0x02;
	else if(keypress == 2) return 0x03;
	else if(keypress == 3) return 0x04;
	else if(keypress == 4) return 0x05;
	else if(keypress == 5) return 0x06;
	else if(keypress == 6) return 0x07;
	else if(keypress == 7) return 0x08;
	else if(keypress == 8) return 0x09;
	else if(keypress == 9) return 0x10;
}

/***************************************************************
* Brief: determines motor step from keypad
* param:   None
* return:   None   
****************************************************************/
int speedkeypad2(int keypress){
	if(keypress == 1) return 0x11;
	else if(keypress == 2) return 0x12;
	else if(keypress == 3) return 0x13;
	else if(keypress == 4) return 0x14;
	else if(keypress == 5) return 0x15;
	else if(keypress == 6) return 0x16;
	else if(keypress == 7) return 0x17;
	else if(keypress == 8) return 0x18;
	else if(keypress == 9) return 0x19;
}


void motorPosition(void){
	if (totalmove == 0){
		printf("Motor  at start\n");
	}
	
	else if (totalmove > 0){
		printf("Motor is %d cycles forward\n", totalmove);
	}
	
	else{
		abstotal = abs(totalmove);
		printf("Motor is %d cycles reversed\n", abstotal);
	}
}


//Interrupt Handler for button  on PC8 pin
void EXTI9_5_IRQHandler(void){
	//Debounces button if it was really pressed it will decrement count
	//PC6 INTRPT
	if(EXTI->PR & 0x0040){
			BTN1Stop = 1;
			EXTI->PR |= 0x0040; /* clear interrupt pending flag */
	}
	
	//PC7 INTRPT
	else if(EXTI->PR & 0x0080){
			BTN2Stop = 1;
			EXTI->PR |= 0x0080; /* clear interrupt pending flag */
	}
	
	//PC8 INTRPT
	else if(EXTI->PR & 0x0100){
			BTN3Stop = 1;
			EXTI->PR |= 0x0100; /* clear interrupt pending flag */
	}
}
