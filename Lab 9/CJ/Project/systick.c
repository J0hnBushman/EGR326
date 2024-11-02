#include "stm32f446xx.h"
#include "systick.h"
void SysTick_Init(void)
{
    SysTick->CTRL = 0;
    SysTick->LOAD = 0x00FFFFFF;
    SysTick->VAL = 0;
    SysTick->CTRL |= 5;
}

void delayMS(uint16_t n)
{
    SysTick->LOAD = ((n * 16000) - 1);
    SysTick->VAL = 0;
    while ((SysTick->CTRL & 0x00010000) == 0)
    {
    }
}

void delayMicroS(uint16_t n)
{
    SysTick->LOAD = ((n * 16) - 1);
    SysTick->VAL = 0;
    while ((SysTick->CTRL & 0x00010000) == 0)
    {
    }
}