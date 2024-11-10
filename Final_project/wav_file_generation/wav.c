#include "stm32f446xx.h"
#include <stdio.h>


//oof.wav
//Audio Format: 4194305
//Number Of Channels: 2
//Sample Rate: 24000
//Byte Rate: 96000
//Block Align: 4
//Bits Per Sample: 16
//Size: 26

/*
DMA Stream configuration procedure (Page 222 in Reference Manual)
The following sequence must be followed to configure a DMA stream x (where x is the
stream number):
1. If the stream is enabled, disable it by resetting the EN bit in the DMA_SxCR register,
then read this bit in order to confirm that there is no ongoing stream operation. Writing
this bit to 0 is not immediately effective since it is actually written to 0 once all the
current transfers are finished. When the EN bit is read as 0, this means that the stream
is ready to be configured. It is therefore necessary to wait for the EN bit to be cleared
before starting any stream configuration. All the stream dedicated bits set in the status
register (DMA_LISR and DMA_HISR) from the previous data block DMA transfer must
be cleared before the stream can be re-enabled.

2. Set the peripheral port register address in the DMA_SxPAR register. The data is moved
from/ to this address to/ from the peripheral port after the peripheral event.

3. Set the memory address in the DMA_SxMA0R register (and in the DMA_SxMA1R
register in the case of a double-buffer mode). The data is written to or read from this
memory after the peripheral event.

4. Configure the total number of data items to be transferred in the DMA_SxNDTR
register. After each peripheral event or each beat of the burst, this value is
decremented.

5. Select the DMA channel (request) using CHSEL[2:0] in the DMA_SxCR register.

6. If the peripheral is intended to be the flow controller and if it supports this feature, set
the PFCTRL bit in the DMA_SxCR register.

7. Configure the stream priority using the PL[1:0] bits in the DMA_SxCR register.

8. Configure the FIFO usage (enable or disable, threshold in transmission and reception)

9. Configure the data transfer direction, peripheral and memory incremented/fixed mode,
single or burst transactions, peripheral and memory data widths, circular mode,
double-buffer mode and interrupts after half and/or full transfer, and/or errors in the
DMA_SxCR register.

10. Activate the stream by setting the EN bit in the DMA_SxCR register.
As soon as the stream is enabled, it can serve any DMA request from the peripheral
connected to the stream.

Once half the data have been transferred on the AHB destination port, the half-transfer flag
(HTIF) is set and an interrupt is generated if the half-transfer interrupt enable bit (HTIE) is
set. At the end of the transfer, the transfer complete flag (TCIF) is set and an interrupt is
generated if the transfer complete interrupt enable bit (TCIE) is set.
*/

void GPIOinit(void);
void DACinit(void);
void DMAinit(void);
void TIMinit(void);

uint8_t dacValues[] = {73,78,70,79,73,83,70,84,13,0,0,0,76,97,118,102,54,49,46,49,
46,49,48,48,0,0};

int main(void) {
	
	
	GPIOinit();
	DACinit();
	DMAinit();
	TIMinit();
	
	while(1){
		
	}

}

void GPIOinit(void){
	RCC->AHB1ENR|=(1<<0);
}

void DACinit(void){
	
	RCC->APB1ENR|=(1<<29); //Enable DAC
	
	DAC1->CR|=(1<<0);  //Enabe Channel 1 in DAC
	DAC1->CR|=(1<<2);  //Enable DAC Channel 1 Trigger (There will be external event that triggers DAC)
	DAC1->CR|=(2<<3);  //Timer 7 will trigger DAC
	DAC1->CR|=(1<<12); //Enable DMA Mode
	
}

void DMAinit(void){
	// DMA1 Channel 7, Stream 5, for DAC1 (Pg. 207 in reference manual)
	
	RCC->AHB1ENR|=(1<<21);// Enable DMA1 Clock
	
	
	DMA1_Stream5->PAR = (uint32_t)(&(DAC1->DHR8R1)); //Set the peripheral register address for DAC_DHR8R1 in the DMA_PARx register THIS IS AN ADDRESS VALUE//Going to Try this later to see if it works
	//DMA1_Stream5->PAR |= (0x40007400+0x10); //Set the peripheral register address for DAC_DHR8R1 in the DMA_PARx register THIS IS AN ADDRESS VALUE
	
	DMA1_Stream5->M0AR = (uint32_t)dacValues; // This needs to be an address but it throws an error, so im typecasting the address as an integer
	
	DMA1_Stream5->NDTR = 26; //Total number of data items to be transferred
	
	DMA1_Stream5->CR|=(0x07<<25); // Select the DMA1 Stream Channel
	
	DMA1_Stream5->CR|=(0x03<<16); // Set the Priority level (0b11 is 'very high')
	
	DMA1_Stream5->FCR&=~(1<<7); // Disable FIFO error Interrupt
	
	DMA1_Stream5->CR|=(1<<6); // Direction of data transfer (memory-to-peripheral)
	
	DMA1_Stream5->CR&=~(1<<8); // Disable Circular Mode
	//DMA1_Stream5->CR&=~(1<<8); // Disable Circular Mode
	
	DMA1_Stream5->CR|=(1<<10);// Enable Memory Increment Mode Because data is being read from an array
	
	DMA1_Stream5->CR&=~(3<<13);// Set the Memory Data Size
	DMA1_Stream5->CR&=~(3<<11);// Set the Peripheral Data Size
	
	DMA1_Stream5->CR|=(1<<0);//Enable the Stream
	
}

void TIMinit(void){
	RCC->APB1ENR|=(1<<5);
	
	//Sample rate is 24000 so we have to trigger DAC 24000 times per second
	//Timer Freq = Clock Frequency / ((arr+1) * (prescalar +1))
	// Timer Frequency Equal to Sample Rate
	TIM7->PSC = 9; 
	TIM7->ARR = 67;
	
	TIM7->CR2 |= (2<<4); // Set Trigger Event
	TIM7->CR1 |= (1<<0); // Enable Counter
}