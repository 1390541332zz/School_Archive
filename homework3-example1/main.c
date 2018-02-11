#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"

// Global parameters with current application settings

typedef enum {black, red, green, yellow, blue, magenta, cyan, white} color_t;

//-----------------------------------------------------------------------
// Character Graphics API
//
// The 128*128 pixel screen is partitioned in a grid of 8 rows of 16 characters
// Each character is a plotted in a rectangle of 8 pixels (wide) by 16 pixels (high)
//
// The lower-level graphics functions are taken from the Texas Instruments Graphics Library
//
//            C Application        (this file)
//                   |
//                 GRLIB           (graphics library)
//                   |
//             CrystalFontz Driver (this project, LcdDriver directory)
//                   |
//                font data        (this project, fonts directory)

Graphics_Context g_sContext;

void InitGraphics() {
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    Graphics_initContext(&g_sContext,
                         &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
    GrContextFontSet(&g_sContext, &g_sFontCmtt16);
    Graphics_clearDisplay(&g_sContext);
}

void LCDClearDisplay() {
    Graphics_clearDisplay(&g_sContext);
}

void LCDDrawChar(unsigned row, unsigned col, int8_t c) {
    Graphics_drawString(&g_sContext,
                        &c,
                        1,
                        8 * (col % 16),
                        16 * (row % 8),
                        OPAQUE_TEXT);
}

void LCDSetFgColor(color_t c) {

    // --- YOU HAVE TO WRITE THIS FUNCTION BODY

    // ---

}

void LCDSetBgColor(color_t c) {

    // --- YOU HAVE TO WRITE THIS FUNCTION BODY

    // ---

}

//-----------------------------------------------------------------------

int main(void) {
    WDT_A_hold(WDT_A_BASE);

    InitGraphics();

    LCDSetFgColor(yellow);
    LCDSetBgColor(red);
    LCDClearDisplay();

    LCDDrawChar(0,  0, 'Y');
    LCDDrawChar(0,  1, 'E');
    LCDDrawChar(0,  2, 'L');
    LCDDrawChar(0,  3, 'L');
    LCDDrawChar(0,  4, 'O');
    LCDDrawChar(0,  5, 'W');
    LCDDrawChar(0,  6, ' ');
    LCDDrawChar(0,  7, 'O');
    LCDDrawChar(0,  8, 'N');
    LCDDrawChar(0,  9, ' ');
    LCDDrawChar(0,  10, 'R');
    LCDDrawChar(0,  11, 'E');
    LCDDrawChar(0,  12, 'D');

    while (1) { }

}
