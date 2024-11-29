#ifndef __FLASH_ACCESS_H__
#define __FLASH_ACCESS_H__

#include "stm32f446xx.h"

#define FLASH_USER_START_ADDR   0x080E0000   // Flash address where we store data (choose an address in unused flash region)
#define FLASH_KEY1   (0x45670123)
#define FLASH_KEY2   (0xCDEF89AB)
#define FLASH_CR_PER (1<<0)  


void write_to_flash(uint32_t data);
uint32_t read_from_flash(void);

#endif