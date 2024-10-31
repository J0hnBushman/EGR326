#include "stm32f446xx.h"
#include "main.h"

int main(void)
{
	int i = 0;
	BI_stepper_init();
	SysTick_Init();
	while(1)
	{
		for(i=0;i<50;i++)
		{
			BI_stepper_forward_step();
			delayMS(30);
		}
		
		for(i=0;i<50;i++)
		{
			BI_stepper_reverse_step();
			delayMS(30);
		}
	}
	return 0;
}