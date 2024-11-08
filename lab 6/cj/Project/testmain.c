/*
 * Author: Jacob Clarey
 * Date: 9/21/2024
 * Description: This main file incorporates a ClockConfig setup for the STM32F446RE IC with a SPI ILI9341 Driver code.
 * It shows off a the font and image functions as well as a rectangle screensaver loop.
 * Notes: The included headers and
 * sources are used to drive the LCD, provide images/fonts, and modify the system clock frequency.
 *
 * The wiring used for the ILI9341 module was as follows in the format MCU Pin->Display Pin, GPIOXX->SCK, GPIOXX->MOSI,
 * GPIOXX->CS, GPIOXX->RST, GPIOXX->DCX, 5V->VCC, GND->GND, 3.3V->LED
 *
 * In the ILI9341.h header file, CS, RST, and DCX are modifiable through simply changing the #define values.
 */

#include "ILI9341.h"
#include "RccConfig.h"
#include "font_ubuntu_mono_24.h"
#include "font_freemono_mono_bold_24.h"
#include "font_ubuntu_48.h"
#include "font_microsoft_16.h"
#include "font_firacode_regular_14.h"
#include "my_photos.h"
#include "spi.h"
#include <stdlib.h>
#include <stm32f446xx.h>
#include <string.h>


int main(void)
{

		char choice1[] = "BLUE";
		char choice2[] = "YELLOW";
		char choice3[] = "GREEN";
		char choice4[] = "RED";
		
		uint16_t choice1_width = ((strlen(choice1))*9);
		uint16_t choice2_width = ((strlen(choice2))*8);
		uint16_t choice3_width = ((strlen(choice3))*12);
		uint16_t choice4_width = ((strlen(choice4))*20);
		

    // SysClockConfig(); // This line enables the clock config function to max out SPI1 clock to 45 MHZ

    Display_Init(); // Initializes the LCD

    Fill_Screen(BLACK);
    Draw_Bitmap((TFT_WIDTH - testImage->width) / 2, (TFT_HEIGHT - testImage->height) / 2,
                testImage); // Displays a scaled image of an apple. (Small to maintain 32kB flash limit on Keil)
		
		delayMS(3000);
		Fill_Screen(BLACK);
    Draw_String_NoBG((TFT_WIDTH-choice1_width)/2-10, (TFT_HEIGHT/2)-(25/2)-25, choice1, BLUE, &font_firacode_regular_14);
		Draw_String_NoBG((TFT_WIDTH-choice2_width)/2-10, (TFT_HEIGHT/2)-25/2, choice2, YELLOW, &font_microsoft_16);
		Draw_String_NoBG((TFT_WIDTH-choice3_width)/2, (TFT_HEIGHT/2)+25/2, choice3, GREEN, &font_ubuntu_mono_24);
		Draw_String_NoBG((TFT_WIDTH-choice4_width)/2, (TFT_HEIGHT/2)+(25/2)+25, choice4,RED, &font_ubuntu_48);
		
		

      while (1)
    {

    }
}

// EOF
