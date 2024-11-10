/*  Author: John Bushman
 *  Date: 10/9/23
 *  Description: BTN stuff i guess
 *  Notes:
 */

#ifndef __BTN_H__
#define __BTN_H__

#include "stm32f446xx.h"

/* Used for MODER */
#define INPUT  (0x00)
#define OUTPUT (0x01)
#define ALT_F  (0x02)
#define ANALOG (0x03)

/* Used for PUPDR */
#define PULLUP   (0x01)
#define PULLDOWN (0x02)

/*BTN PIN AND PORT*/
#define BTN1_PIN       		 (11)
#define BTN1_PORT   	   (GPIOC)

void BTN_init(void);

#endif