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
#include "my_photos.h"
#include "spi.h"
#include <stdlib.h>
#include <stm32f446xx.h>


int main(void)
{



    // SysClockConfig(); // This line enables the clock config function to max out SPI1 clock to 45 MHZ

    Display_Init(); // Initializes the LCD

    delayMS(1000);
    doFontTest(&font_ubuntu_mono_24); // Prints every character in the font_ubuntu_mono_24 font header.

    delayMS(1000);
    Draw_Bitmap((TFT_WIDTH - testImage->width) / 2, (TFT_HEIGHT - testImage->height) / 2,
                testImage); // Displays a scaled image of an apple. (Small to maintain 32kB flash limit on Keil)

    delayMS(1000);
    Fill_Screen(BLACK);
    Draw_String_NoBG(60, 240, "STM32F446", RED, &font_ubuntu_mono_24);



      while (1)
    {

    }
}

// EOF
