#include <stm32f446xx.h>
#include "spi.h"

int16_t x,y,z;

uint8_t RxData[6];

void adxl_read (uint8_t address);


//*********************************************************************************
//************************************MAIN*****************************************
//*********************************************************************************
int main(void)
{
	__disable_irq();
		SPI_Init();
		SPI_Enable();
		adxl_init();
	
	__enable_irq();
	

	
      while (1)
    {
			
    }
}

//NOTE THE ADXL IS A DIFFERENT PART I INCLUDED IN THE SPI, BUT IT IS NOT NESSISARY

//reading function
void adxl_read (uint8_t address)
{
	address |= 0x80;  // read operation
	address |= 0x40;  // multibyte read
	uint8_t rec;
	SS_High();  // pull the pin low ?????DOUBLE CHECK THIS TOMMOROW
	SPI_Transmit (&address, 1);  // send address
	SPI_recive(RxData, 6);  // receive 6 bytes data
	SS_Low();  // pull the pin high
}