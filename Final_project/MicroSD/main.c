#include <stm32f446xx.h>
#include "spi.h"

int16_t x,y,z;

uint16_t TxData[2] = {0x0100C}; //light intensty

void delayMs(int n);

//*********************************************************************************
//************************************MAIN*****************************************
//*********************************************************************************
int main(void)
{
		SPI_Init();
		SPI_Enable();
		

      while (1)
    {
			SS_Low();
			SPI_Transmit(TxData, 1); //light initensity address
			SS_High();
			delayMs(10);
    }
}

//NOTE THE ADXL IS A DIFFERENT PART I INCLUDED IN THE SPI, BUT IT IS NOT NESSISARY


void delayMs(int n){
	int i;
	for(; n > 0 ; n --)
		for(i = 0; i < 3195; i ++);
}