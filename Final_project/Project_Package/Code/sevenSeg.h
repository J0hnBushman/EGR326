/*  Author: Jacob Clarey
 *  Date: 10/9/23
 *  Description: This is the source file for spi transmission functions.
 *  Notes:
 */

#ifndef __sevenSeg_H__
#define __sevenSeg_H__

#include <stm32f446xx.h>


/*******************************************************************************/
//                          USER FUNCTION PROTOTYPE
/*******************************************************************************/
void sevenSeg_init(void);

void sevenSeg_write(uint8_t adder, uint8_t dater);

void Init_seq(void);

/*******************************************************************************/
/*******************************************************************************/

#endif

/* EOF */