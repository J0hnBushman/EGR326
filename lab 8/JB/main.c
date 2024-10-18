#include <stm32f446xx.h>
#include "spi.h"


void SevenSeg_Push_16Bit(uint16_t parameter);
void SevenSeg_8Bit_DataSend(uint8_t DataSend);
	


//*********************************************************************************
//************************************MAIN*****************************************
//*********************************************************************************
int main(void)
{
	__disable_irq();
		SPI_Init();
	__enable_irq();
	
	SevenSeg_Push_16Bit(0x0A02);
	
      while (1)
    {
			
    }
}





void SevenSeg_Push_16Bit(uint16_t parameter)
{
    SevenSeg_8Bit_DataSend((uint8_t)(parameter >> 8));
    SevenSeg_8Bit_DataSend((uint8_t)parameter);
}


void SevenSeg_8Bit_DataSend(uint8_t DataSend)
{
    SPI_Transmit(&DataSend, 1);
}