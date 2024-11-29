#include "stm32f446xx.h"
#include "Flash_Access.h"

/*
The Flash memory programming sequence is as follows:

1. Check that no main Flash memory operation is ongoing by checking the BSY bit in the
FLASH_SR register.

2. Set the PG bit in the FLASH_CR register

3. Perform the data write operation(s) to the desired memory address (inside main
memory block or OTP area):
   Byte access in case of x8 parallelism
   Half-word access in case of x16 parallelism
   Word access in case of x32 parallelism
   Double word access in case of x64 parallelism

4. Wait for the BSY bit to be cleared.

Note: Successive write operations are possible without the need of an erase operation when
changing bits from '1' to '0'. Writing '1' requires a Flash memory erase operation.
If an erase and a program operation are requested simultaneously, the erase operation is
performed first. 
*/

/*
To erase a sector, follow the procedure below:
1. Check that no Flash memory operation is ongoing by checking the BSY bit in the
FLASH_SR register

2. Set the SER bit and select the sector out of the 7 sectors in the main memory block you
wish to erase (SNB) in the FLASH_CR register

3. Set the STRT bit in the FLASH_CR register

4. Wait for the BSY bit to be cleared.
*/

void write_to_flash(uint32_t data) {
    // Wait for any previous operations to complete
    while (FLASH->SR & FLASH_SR_BSY);

    // Unlock Flash memory for writing
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;

    // Wait for Flash to be ready
    while (FLASH->SR & FLASH_SR_BSY);

    // Erase the page before writing new data
    FLASH->CR |= FLASH_CR_PER;              // Page erase enabled
    //FLASH->AR = FLASH_USER_START_ADDR;      // Set the address of the page to be erased
    FLASH->CR |= FLASH_CR_STRT;             // Start the erase operation
    while (FLASH->SR & FLASH_SR_BSY);       // Wait for the operation to complete
    FLASH->CR &= ~FLASH_CR_PER;             // Disable page erase

    // Wait for Flash to be ready
    while (FLASH->SR & FLASH_SR_BSY);

    // Write the data to Flash memory
    *((volatile uint32_t*)FLASH_USER_START_ADDR) = data;

    // Wait for the write operation to complete
    while (FLASH->SR & FLASH_SR_BSY);

    // Lock Flash memory after the operation
    FLASH->CR |= FLASH_CR_LOCK;
}

uint32_t read_from_flash(void) {
    // Read the data from the specified Flash memory address
    return *((volatile uint32_t*)FLASH_USER_START_ADDR);
}