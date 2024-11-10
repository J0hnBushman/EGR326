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
#include <string.h>

		typedef struct{
			uint16_t x;
			uint16_t y;
		}point;
point TopLeft = {12,0};
point TopRight = {TFT_WIDTH-12,0};
point BottomRight = {TFT_WIDTH-12,TFT_HEIGHT-25};
point BottomLeft = {12,TFT_HEIGHT-25};
point Center = {(TFT_WIDTH/2),(TFT_HEIGHT/2)-25};
void countup(point coord);
int main(void)
{

		

		
		

    // SysClockConfig(); // This line enables the clock config function to max out SPI1 clock to 45 MHZ

    Display_Init(); // Initializes the LCD

		Fill_Screen(BLACK);

		//Draw_Char_NoBG(TopLeft.x,TopLeft.y,'0',WHITE,&font_ubuntu_mono_24);
		//Draw_Char_NoBG(TopRight.x,TopRight.y,'1',WHITE,&font_ubuntu_mono_24);
		//Draw_Char_NoBG(BottomRight.x,BottomRight.y,'2',WHITE,&font_ubuntu_mono_24);
		//Draw_Char_NoBG(BottomLeft.x,BottomLeft.y,'3',WHITE,&font_ubuntu_mono_24);
		



      while (1)
    {
			countup(TopLeft);
			countup(TopRight);
			countup(BottomRight);
			countup(BottomLeft);
			countup(Center);
			delayMS(3000);
			Draw_Char_BG(TopLeft.x,TopLeft.y,' ',WHITE,BLACK,&font_ubuntu_mono_24);
			Draw_Char_BG(TopRight.x,TopRight.y,' ',WHITE,BLACK,&font_ubuntu_mono_24);
			Draw_Char_BG(Center.x,Center.y,' ',WHITE,BLACK,&font_ubuntu_mono_24);
			Draw_Char_BG(BottomRight.x,BottomRight.y,' ',WHITE,BLACK,&font_ubuntu_mono_24);
			Draw_Char_BG(BottomLeft.x,BottomLeft.y,' ',WHITE,BLACK,&font_ubuntu_mono_24);
    }
}





void countup(point coord)
{

    for(uint8_t i = 0; i < 10; i++)
    {

        Draw_Char_BG(coord.x,coord.y,'0'+i,WHITE,BLACK,&font_ubuntu_mono_24);
        delayMS(500);
				//Draw_Char_BG(coord.x,coord.y,' ',WHITE,BLACK,&font_ubuntu_mono_24);
    }
    
       // Draw_Char_NoBG(coord.x,coord.y,'\0',WHITE,&font_ubuntu_mono_24);
       // delayMS(500);
	}
