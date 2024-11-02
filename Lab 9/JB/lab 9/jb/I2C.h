#include "stm32f4xx.h"

#ifndef I2C_H_
#define I2C_H_

void I2C_init(void);
void I2C_init_slave(void);
int	listen(char* data);
void I2C1_byteWrite(char saddr, char data);
int I2C1_byteRead(char saddr, char maddr, char* data);

#endif