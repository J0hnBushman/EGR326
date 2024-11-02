#include "stepper.h"
#include "stm32f446xx.h"

/*
			Full Step
1100	0110	0011	1001
BPYO	BPYO	BPYO	BPYO

									Half Step
1000	1100	0100	0110	0010	0011	0001	1001
BPYO	BPYO	BPYO	BPYO	BPYO	BPYO	BPYO	BPYO
*/

void stepper_init(void)
{
	RCC->AHB1ENR |= (1<<0) | (1<<1) | (1<<2);
	
	ORANGE_COIL_1_MODER(OUTPUT);
	ORANGE_COIL_1_OUT(LOW);
	
	PINK_COIL_2_MODER(OUTPUT);
	PINK_COIL_2_OUT(LOW);
	
	YELLOW_COIL_3_MODER(OUTPUT);
	YELLOW_COIL_3_OUT(LOW);
	
	BLUE_COIL_4_MODER(OUTPUT);
	BLUE_COIL_4_OUT(LOW);
}

uint8_t get_step(void)
{
	uint8_t state = 0x00;
	state |= (IS_HIGH_BLUE_COIL_4)<<3;
	state |= (IS_HIGH_PINK_COIL_2)<<2;
	state |= (IS_HIGH_YELLOW_COIL_3)<<1;
	state |= (IS_HIGH_ORANGE_COIL_1)<<0;
	return state;
}

void set_step(uint8_t step)
{
	BLUE_COIL_4_OUT(step & 1<<3);
	PINK_COIL_2_OUT(step & 1<<2);
	YELLOW_COIL_3_OUT(step & 1<<1);
	ORANGE_COIL_1_OUT(step & 1<<0);
}

void stepper_half_step(void)
{
	uint8_t state = get_step();
	if(state==0x00) state = 0x08;
	
	switch(state)
	{
		case 0x08:
			set_step(0x0C);
			break;
		
		case 0x0C:
			set_step(0x04);
			break;
		
		case 0x04:
			set_step(0x06);
			break;
		
		case 0x06:
			set_step(0x02);
			break;
		
		case 0x02:
			set_step(0x03);
			break;
		
		case 0x03:
			set_step(0x01);
			break;
		
		case 0x01:
			set_step(0x09);
			break;
		
		case 0x09:
			set_step(0x08);
			break;
		
		default:
			set_step(0x08);
			break;
	}
	
	
}

void stepper_full_step(void)
{
	uint8_t state = get_step();
	if(state==0x00) state = 0x0C;
	
	switch(state)
	{
		
		case 0x0C:
			set_step(0x06);
			break;
		
		case 0x06:
			set_step(0x03);
			break;
		
		case 0x03:
			set_step(0x09);
			break;
		
		case 0x09:
			set_step(0x0C);
			break;
		
		default:
			set_step(0x0C);
			break;
	}
	
	
}