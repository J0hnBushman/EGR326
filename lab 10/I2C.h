#include "stm32f4xx.h"

#ifndef I2C_H_
#define I2C_H_

void I2C_init(void);
int I2C1_byteWrite(char saddr, char maddr, char data);
int I2C1_byteRead(char saddr, char maddr, char* data);

#endif