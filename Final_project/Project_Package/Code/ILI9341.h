/*  Author: Jacob Clarey
 *  Date: 9/21/2024
 *  Description: This is a header file for the 4-wire SPI ILI9341 driver.
 *  Notes:
 */

#ifndef _ILI9341_H_
#define _ILI9341_H_

#include "bitmap_typedefs.h"
#include "spi.h"
#include <stm32f446xx.h>

/*****************************************************************************/
//                               USER DEFINES
/*****************************************************************************/

/***************************** COLOR DEFINITIONS *****************************/

#define BLACK       0x0000
#define WHITE       0xFFFF
#define RED         0xF800
#define GREEN       0x07E0
#define BLUE        0x001F
#define VIOLET      RED | BLUE
#define YELLOW      RED | GREEN
#define TEAL        BLUE | GREEN
#define PURPLE      0x9191
#define BRIGHT_TEAL 0x0D0D
#define SKY_BLUE    0x7575
#define GRAY        0x6B6B
#define NAVY        0x0808
#define MAROON      0x4040
#define ORANGE      0xE1E1
#define OLIVE       0x2121
#define CYAN        0x0C0C
#define MAGENTA     0xF1F1
#define BROWN       0x6a46
#define PINK        0xF3F3
#define JADE        0x0202

/*****************************************************************************/

/***************************** PINOUT DEFINITION *****************************/

#define LCD_RST_PORT GPIOC
#define LCD_RST      12U

#define LCD_CS_PORT GPIOA
#define LCD_CS      4U

#define LCD_DCX_PORT GPIOC
#define LCD_DCX      10U

#define SD_CS_PORT GPIOA
#define SD_CS      4U

#define SD_DI_PORT GPIOA //mosi
#define SD_DI      7U

#define SD_DO_PORT GPIOA //miso
#define SD_DO      6U

#define SD_SCK_PORT GPIOA
#define SD_SCK      5U

/*****************************************************************************/

/**************************** DIMENSION DEFINITION ***************************/

#define TFT_HEIGHT 320
#define TFT_WIDTH  240

/*****************************************************************************/

/***************************** COMMAND DEFINITION ****************************/

#define ILI_NOP     0x00
#define ILI_SWRESET 0x01
#define ILI_RDDID   0xD3
#define ILI_RDDST   0x09

#define ILI_SLPIN  0x10
#define ILI_SLPOUT 0x11
#define ILI_PTLON  0x12
#define ILI_NORON  0x13

#define ILI_RDMODE     0x0A
#define ILI_RDMADCTL   0x0B
#define ILI_RDPIXFMT   0x0C
#define ILI_RDIMGFMT   0x0D
#define ILI_RDSELFDIAG 0x0F

#define ILI_INVOFF   0x20
#define ILI_INVON    0x21
#define ILI_GAMMASET 0x26
#define ILI_DISPOFF  0x28
#define ILI_DISPON   0x29

#define ILI_CASET 0x2A
#define ILI_PASET 0x2B
#define ILI_RAMWR 0x2C
#define ILI_RAMRD 0x2E

#define ILI_PTLAR  0x30
#define ILI_MADCTL 0x36
#define ILI_PIXFMT 0x3A

#define ILI_FRMCTR1 0xB1
#define ILI_FRMCTR2 0xB2
#define ILI_FRMCTR3 0xB3
#define ILI_INVCTR  0xB4
#define ILI_DFUNCTR 0xB6

#define ILI_PWCTR1 0xC0
#define ILI_PWCTR2 0xC1
#define ILI_PWCTR3 0xC2
#define ILI_PWCTR4 0xC3
#define ILI_PWCTR5 0xC4
#define ILI_VMCTR1 0xC5
#define ILI_VMCTR2 0xC7

#define ILI_RDID1 0xDA
#define ILI_RDID2 0xDB
#define ILI_RDID3 0xDC
#define ILI_RDID4 0xDD

#define ILI_GMCTRP1 0xE0
#define ILI_GMCTRN1 0xE1


/*****************************************************************************/
//                                 USER MACROS
/*****************************************************************************/

/****************************** SET/RESET MACROS *****************************/

#define SET_LCD_RST LCD_RST_PORT->BSRR |= 1U << LCD_RST
#define SET_LCD_CS  LCD_CS_PORT->BSRR |= 1U << LCD_CS
#define SET_LCD_DCX LCD_DCX_PORT->BSRR |= 1U << LCD_DCX

#define RESET_LCD_RST LCD_RST_PORT->BSRR |= 1U << (LCD_RST + 16)
#define RESET_LCD_CS  LCD_CS_PORT->BSRR |= 1U << (LCD_CS + 16)
#define RESET_LCD_DCX LCD_DCX_PORT->BSRR |= 1U << (LCD_DCX + 16)

/*****************************************************************************/

/*****************************************************************************/
/*****************************************************************************/

/*****************************************************************************/
//                           USER FUNCTION PROTOTYPE
/*****************************************************************************/
#ifndef __SYSTICK__
#define __SYSTICK__
/// @brief Initializes SysTick timer for delays.
void SysTick_Init(void);

/// @brief Delays a given number of milliseconds.
/// @param n is number of milliseconds to delay.
void delayMS(uint16_t n);

/// @brief Delays a given number of microseconds.
/// @param n is number of microseconds to delay.
void delayMicroS(uint16_t n);
#endif

/// @brief Set an area for drawing on the display.
/// @param x1 is start column address.
/// @param y1 is start row address.
/// @param x2 is end column address.
/// @param y2 is end row address.
void Set_Address_Window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

/// @brief Fills number of pixels with a color.
/// @brief Note: Call Set_Address_Window() before calling this function.
/// @param color is 16-bit RGB565 color value.
/// @param len is 32-bit number of pixels.
void Fill_Color(uint16_t color, uint32_t len);

/// @brief Draw a line from (x0,y0) to (x1,y1).
/// @param x0 is start column address.
/// @param y0 is start row address.
/// @param x1 is end column address.
/// @param y1 is end row address.
/// @param width is thickness of the line.
/// @param color is 16-bit RGB565 color of the line.
void Draw_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color);

/// @brief Draw a vertical line starting top to bottom.
/// @param x0 is start column address.
/// @param length is length of line.
/// @param row is start row address.
/// @param width is width of line.
/// @param color is color of line.
void Draw_VLine(uint16_t x0, uint16_t length, uint16_t row, uint8_t width, uint16_t color);

/// @brief Draw a horizontal line starting left to right.
/// @param y0 is start row address
/// @param length is length of line.
/// @param col is start column address.
/// @param width is width of line.
/// @param color is color of line.
void Draw_HLine(uint16_t y0, uint16_t length, uint16_t col, uint8_t width, uint16_t color);

/// @brief Draw a rectangle without filling it.
/// @param x is start column address.
/// @param y is start row address.
/// @param w is width of rectangle.
/// @param h is height of rectangle.
/// @param color is color of box.
void Draw_Box(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

/// @brief Inverts the colors on the display.
void Invert_Display(void);

/// @brief Rotate display to an orientation. 0: Portrait. 1: Landscape.
/// @brief 2: Portrait Inverted. 3: Landscape Inverted.
/// @param rotation Values 0, 1, 2, 3. Else, default to Portrait.
void Rotate_Display(uint8_t rotation);

/// @brief Initialize the display driver.
void Display_Init(void);

/// @brief Sets up the GPIO pin modes of the display pins.
void GPIO_PinMode_Setup(void);

/// @brief Sends an 8-bit parameter to the display.
/// @param parameter is the parameter to send.
void ILI_Push_16Bit(uint16_t parameter);

/// @brief Sends an 8-bit command to the display.
/// @param command is the command to send.
void ILI_8Bit_Command(uint8_t command);

/// @brief Sends an 8-bit data to the display.
/// @param data is the data to send.
void ILI_8Bit_Data(uint8_t data);

/// @brief Fills a rectangular area with color.
/// @param x is start col address.
/// @param y is start row address.
/// @param w is width of rectangle.
/// @param h is height of rectangle.
/// @param color is 16-bit RGB565 color.
void Fill_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

/// @brief Fills the entire display with color.
/// @param color is 16-bit RGB565 color.
void Fill_Screen(uint16_t color);

/// @brief Writes a string on the display. Select Background color.
/// @param x is top left col address.
/// @param y is top left row address.
/// @param str is pointer to the string to be drawn.
/// @param fore_color is 16-bit RGB565 foreground color.
/// @param back_color is 16-bit RGB565 background color.
/// @param font is pointer to the font of the string.
void Draw_String_BG(uint16_t x, uint16_t y, char *str, uint16_t fore_color, uint16_t back_color, const tFont *font);

/// @brief Writes a string on the display. No Background color.
/// @param x is top left col address.
/// @param y is top left row address.
/// @param str is pointer to the string to be drawn.
/// @param fore_color is 16-bit RGB565 foreground color.
/// @param font is pointer to the font of the string.
void Draw_String_NoBG(uint16_t x, uint16_t y, char *str, uint16_t fore_color, const tFont *font);

/// @brief Write a character at a given position. Select Background color.
/// @param x is top left col address.
/// @param y is top left row address.
/// @param character is the ASCII character to be drawn.
/// @param fore_color is foreground color.
/// @param back_color is background color.
/// @param font is pointer to the font of the character.
void Draw_Char_BG(uint16_t x, uint16_t y, char character, uint16_t fore_color, uint16_t back_color, const tFont *font);

/// @brief Write a character at a given position. No Background color.
/// @param x is top left col address.
/// @param y is top left row address.
/// @param character is the ASCII character to be drawn.
/// @param fore_color is foreground color.
/// @param font is pointer to the font of the character.
void Draw_Char_NoBG(uint16_t x, uint16_t y, char character, uint16_t fore_color, const tFont *font);

/// @brief Display a bitmap image on the screen.
/// @param x is top left col address.
/// @param y is top left row address.
/// @param bitmap is pointer to the image data to be drawn.
void Draw_Bitmap(uint16_t x, uint16_t y, const tImage16bit *bitmap);

/// @brief Draw a pixel at a coord x,y with color.
/// @param x is col address.
/// @param y is row address.
void Draw_Pixel(uint16_t x, uint16_t y, uint16_t color);

void doFontTest(const tFont *font);
/*****************************************************************************/
/*****************************************************************************/

#endif // _ILI9341_H_

/* EOF */
