#ifndef STEPPER_H
#define STEPPER_H

#include "stm32f446xx.h"

#define STEPS_PER_REVOLUTION 32             
#define PI                   3.1415

/* Used for MODER */
#define INPUT  (0x00)
#define OUTPUT (0x01)
#define ALT_F  (0x02)
#define ANALOG (0x03)

/* Used for PUPDR */
#define PULLUP   (0x01)
#define PULLDOWN (0x02)
#define NUNYA  (0x00)

/* Used for ODR */
#define ON   1
#define OFF  0

#define HIGH 1
#define LOW  0


/*DEFINITIONS FOR BIPOLAR STEPPER MOTOR*/


#define BLUE_COIL_4_PIN         		 (0)
#define BLUE_COIL_4_PORT      		   (GPIOB)
#define BLUE_COIL_4_OUT(X)     		   ( (X)? (BLUE_COIL_4_PORT->ODR |= (1UL << BLUE_COIL_4_PIN)) : (BLUE_COIL_4_PORT->ODR &= ~(1UL << BLUE_COIL_4_PIN)) )
#define IS_HIGH_BLUE_COIL_4				   (BLUE_COIL_4_PORT->ODR & (1UL << BLUE_COIL_4_PIN))?1:0
#define BLUE_COIL_4_TOGGLE     		   (BLUE_COIL_4_PORT->ODR ^= (1UL << BLUE_COIL_4_PIN))
#define BLUE_COIL_4_MODER(X)         (BLUE_COIL_4_PORT->MODER &= ~ (0x03UL<<(2*BLUE_COIL_4_PIN))); (BLUE_COIL_4_PORT->MODER |= (X<<(2*BLUE_COIL_4_PIN)))
#define BLUE_COIL_4_IN               (BLUE_COIL_4_PORT->IDR& 1UL << BLUE_COIL_4_PIN)
#define BLUE_COIL_4_PUPDR(X)         (BLUE_COIL_4_PORT->PUPDR &= ~(0x03UL<<(2*BLUE_COIL_4_PIN))); (BLUE_COIL_4_PORT->PUPDR |= X<<(2*BLUE_COIL_4_PIN))

#define PINK_COIL_2_PIN              (1)
#define PINK_COIL_2_PORT             (GPIOB)
#define PINK_COIL_2_OUT(X)           ( (X)? (PINK_COIL_2_PORT->ODR |= (1UL << PINK_COIL_2_PIN)) : (PINK_COIL_2_PORT->ODR &= ~(1UL << PINK_COIL_2_PIN)) )
#define IS_HIGH_PINK_COIL_2				   (PINK_COIL_2_PORT->ODR & (1UL << PINK_COIL_2_PIN))?1:0
#define PINK_COIL_2_MODER(X)         (PINK_COIL_2_PORT->MODER &= ~ (0x03UL<<(2*PINK_COIL_2_PIN))); (PINK_COIL_2_PORT->MODER |= (X<<(2*PINK_COIL_2_PIN)))
#define PINK_COIL_2_IN               (PINK_COIL_2_PORT->IDR & 1UL << PINK_COIL_2_PIN)
#define PINK_COIL_2_PUPDR(X)         (PINK_COIL_2_PORT->PUPDR &= ~(0x03UL<<(2*PINK_COIL_2_PIN))); (PINK_COIL_2_PORT->PUPDR |= X<<(2*PINK_COIL_2_PIN))

#define YELLOW_COIL_3_PIN            (2)
#define YELLOW_COIL_3_PORT           (GPIOB)
#define YELLOW_COIL_3_OUT(X)         ( (X)? (YELLOW_COIL_3_PORT->ODR |= (1UL << YELLOW_COIL_3_PIN)) : (YELLOW_COIL_3_PORT->ODR &= ~(1UL << YELLOW_COIL_3_PIN)) )
#define IS_HIGH_YELLOW_COIL_3				 (YELLOW_COIL_3_PORT->ODR & (1UL << YELLOW_COIL_3_PIN))?1:0
#define YELLOW_COIL_3_TOGGLE         (YELLOW_COIL_3_PORT->ODR ^= (1UL << YELLOW_COIL_3_PIN))
#define YELLOW_COIL_3_MODER(X)       (YELLOW_COIL_3_PORT->MODER &= ~ (0x03UL<<(2*YELLOW_COIL_3_PIN))); (YELLOW_COIL_3_PORT->MODER |= (X<<(2*YELLOW_COIL_3_PIN)))
#define YELLOW_COIL_3_IN             (YELLOW_COIL_3_PORT->IDR & 1UL << YELLOW_COIL_3_PIN)
#define YELLOW_COIL_3_PUPDR(X)       (YELLOW_COIL_3_PORT->PUPDR &= ~(0x03UL<<(2*YELLOW_COIL_3_PIN))); (YELLOW_COIL_3_PORT->PUPDR |= X<<(2*YELLOW_COIL_3_PIN))

#define ORANGE_COIL_1_PIN             (3)
#define ORANGE_COIL_1_PORT            (GPIOB)
#define ORANGE_COIL_1_OUT(X)          ( (X)? (ORANGE_COIL_1_PORT->ODR |= (1UL << ORANGE_COIL_1_PIN)) : (ORANGE_COIL_1_PORT->ODR &= ~(1UL << ORANGE_COIL_1_PIN)) )
#define IS_HIGH_ORANGE_COIL_1				  (ORANGE_COIL_1_PORT->ODR & (1UL << ORANGE_COIL_1_PIN))?1:0
#define ORANGE_COIL_1_MODER(X)        (ORANGE_COIL_1_PORT->MODER &= ~ (0x03UL<<(2*ORANGE_COIL_1_PIN))); (ORANGE_COIL_1_PORT->MODER |= (X<<(2*ORANGE_COIL_1_PIN)))
#define ORANGE_COIL_1_IN              (ORANGE_COIL_1_PORT->IDR & 1UL << ORANGE_COIL_1_PIN)     
#define ORANGE_COIL_1_PUPDR(X)        (ORANGE_COIL_1_PORT->PUPDR &= ~(0x03UL<<(2*ORANGE_COIL_1_PIN))); (ORANGE_COIL_1_PORT->PUPDR |= X<<(2*ORANGE_COIL_1_PIN))


/* DEFINITIONS FOR BIPOLOR STEPPER MOTOR */
#define A0_PIN         		 (4)
#define A0_PORT      		   (GPIOB)
#define A0_OUT(X)     		 ( (X)? (A0_PORT->ODR |= (1UL << A0_PIN)) : (A0_PORT->ODR &= ~(1UL << A0_PIN)) )
#define IS_HIGH_A0				 (A0_PORT->ODR & (1UL << A0_PIN))?1:0
#define A0_TOGGLE     		 (A0_PORT->ODR ^= (1UL << A0_PIN))
#define A0_MODER(X)        (A0_PORT->MODER &= ~ (0x03UL<<(2*A0_PIN))); (A0_PORT->MODER |= (X<<(2*A0_PIN)))
#define A0_IN              (A0_PORT->IDR& 1UL << A0_PIN)
#define A0_PUPDR(X)        (A0_PORT->PUPDR &= ~(0x03UL<<(2*A0_PIN))); (A0_PORT->PUPDR |= X<<(2*A0_PIN))

#define A1_PIN             (0)
#define A1_PORT            (GPIOB)
#define A1_OUT(X)          ( (X)? (A1_PORT->ODR |= (1UL << A1_PIN)) : (A1_PORT->ODR &= ~(1UL << A1_PIN)) )
#define IS_HIGH_A1			   (A1_PORT->ODR & (1UL << A1_PIN))?1:0
#define A1_MODER(X)        (A1_PORT->MODER &= ~ (0x03UL<<(2*A1_PIN))); (A1_PORT->MODER |= (X<<(2*A1_PIN)))
#define A1_IN              (A1_PORT->IDR & 1UL << A1_PIN)
#define A1_PUPDR(X)        (A1_PORT->PUPDR &= ~(0x03UL<<(2*A1_PIN))); (A1_PORT->PUPDR |= X<<(2*A1_PIN))

#define B0_PIN             (2)
#define B0_PORT            (GPIOB)
#define B0_OUT(X)          ( (X)? (B0_PORT->ODR |= (1UL << B0_PIN)) : (B0_PORT->ODR &= ~(1UL << B0_PIN)) )
#define IS_HIGH_B0     	 	(B0_PORT->ODR & (1UL << B0_PIN))?1:0
#define B0_TOGGLE         (B0_PORT->ODR ^= (1UL << B0_PIN))
#define B0_MODER(X)       (B0_PORT->MODER &= ~ (0x03UL<<(2*B0_PIN))); (B0_PORT->MODER |= (X<<(2*B0_PIN)))
#define B0_IN             (B0_PORT->IDR & 1UL << B0_PIN)
#define B0_PUPDR(X)       (B0_PORT->PUPDR &= ~(0x03UL<<(2*B0_PIN))); (B0_PORT->PUPDR |= X<<(2*B0_PIN))

#define B1_PIN             (6)
#define B1_PORT            (GPIOB)
#define B1_OUT(X)          ( (X)? (B1_PORT->ODR |= (1UL << B1_PIN)) : (B1_PORT->ODR &= ~(1UL << B1_PIN)) )
#define IS_HIGH_B1				 (B1_PORT->ODR & (1UL << B1_PIN))?1:0
#define B1_MODER(X)        (B1_PORT->MODER &= ~ (0x03UL<<(2*B1_PIN))); (B1_PORT->MODER |= (X<<(2*B1_PIN)))
#define B1_IN              (B1_PORT->IDR & 1UL << B1_PIN)     
#define B1_PUPDR(X)        (B1_PORT->PUPDR &= ~(0x03UL<<(2*B1_PIN))); (B1_PORT->PUPDR |= X<<(2*B1_PIN))

void stepper_init(void);
void BI_stepper_init(void);

uint8_t get_step(void);
uint8_t BI_get_step(void);

void set_step(uint8_t step);
void BI_set_step(uint8_t step);

void stepper_full_step(void);

void BI_stepper_forward_step(void);
void BI_stepper_reverse_step(void);

void stepper_half_step(void);

void stepper_wave_step(void);


#endif