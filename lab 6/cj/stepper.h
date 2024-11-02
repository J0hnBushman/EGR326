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


void stepper_init(void);

uint8_t get_step(void);

void set_step(uint8_t step);

void stepper_full_step(void);

void stepper_half_step(void);


#endif