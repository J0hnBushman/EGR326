#ifndef __HEALTH_BAR_H__
#define __HEALTH_BAR_H__

#include "stm32f446xx.h"

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



#define DATA_PIN         		 (0)
#define DATA_PORT      		   (GPIOC)
#define DATA_OUT(X)     		   ( (X)? (DATA_PORT->ODR |= (1UL << DATA_PIN)) : (DATA_PORT->ODR &= ~(1UL << DATA_PIN)) )
#define IS_HIGH_DATA				   (DATA_PORT->ODR & (1UL << DATA_PIN))?1:0
#define DATA_TOGGLE     		   (DATA_PORT->ODR ^= (1UL << DATA_PIN))
#define DATA_MODER(X)         (DATA_PORT->MODER &= ~ (0x03UL<<(2*DATA_PIN))); (DATA_PORT->MODER |= (X<<(2*DATA_PIN)))
#define DATA_IN               (DATA_PORT->IDR& 1UL << DATA_PIN)
#define DATA_PUPDR(X)         (DATA_PORT->PUPDR &= ~(0x03UL<<(2*DATA_PIN))); (DATA_PORT->PUPDR |= X<<(2*DATA_PIN))

#define LATCH_PIN              (1)
#define LATCH_PORT             (GPIOC)
#define LATCH_OUT(X)           ( (X)? (LATCH_PORT->ODR |= (1UL << LATCH_PIN)) : (LATCH_PORT->ODR &= ~(1UL << LATCH_PIN)) )
#define IS_HIGH_LATCH				   (LATCH_PORT->ODR & (1UL << LATCH_PIN))?1:0
#define LATCH_MODER(X)         (LATCH_PORT->MODER &= ~ (0x03UL<<(2*LATCH_PIN))); (LATCH_PORT->MODER |= (X<<(2*LATCH_PIN)))
#define LATCH_IN               (LATCH_PORT->IDR & 1UL << LATCH_PIN)
#define LATCH_PUPDR(X)         (LATCH_PORT->PUPDR &= ~(0x03UL<<(2*LATCH_PIN))); (LATCH_PORT->PUPDR |= X<<(2*LATCH_PIN))

#define CLOCK_PIN            (2)
#define CLOCK_PORT           (GPIOC)
#define CLOCK_OUT(X)         ( (X)? (CLOCK_PORT->ODR |= (1UL << CLOCK_PIN)) : (CLOCK_PORT->ODR &= ~(1UL << CLOCK_PIN)) )
#define IS_HIGH_CLOCK				 (CLOCK_PORT->ODR & (1UL << CLOCK_PIN))?1:0
#define CLOCK_TOGGLE         (CLOCK_PORT->ODR ^= (1UL << CLOCK_PIN))
#define CLOCK_MODER(X)       (CLOCK_PORT->MODER &= ~ (0x03UL<<(2*CLOCK_PIN))); (CLOCK_PORT->MODER |= (X<<(2*CLOCK_PIN)))
#define CLOCK_IN             (CLOCK_PORT->IDR & 1UL << CLOCK_PIN)
#define CLOCK_PUPDR(X)       (CLOCK_PORT->PUPDR &= ~(0x03UL<<(2*CLOCK_PIN))); (CLOCK_PORT->PUPDR |= X<<(2*CLOCK_PIN))


void init_ShiftRegister(void);
void init_Health_Timer(void);
uint8_t HealthMinusMinus(void);
uint8_t HealthPlusPlus(void);
void HealthClear(void);

void PulseClock(void);

void HealthMax(void);

void SysTick_Init(void);
void delayMS(uint16_t n);
void delayMicroS(uint16_t n);



#endif