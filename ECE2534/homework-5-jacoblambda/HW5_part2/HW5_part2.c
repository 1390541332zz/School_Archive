#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include <LED_HAL.h>
#include <Buttons_HAL.h>
#include <Timer_HAL.h>
#include <ADC_HAL.h>

#define ENTR_DELAY 6

Graphics_Context g_sContext;

void InitGraphics() {
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    Graphics_initContext(&g_sContext,
                         &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_YELLOW);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
    Graphics_setFont(&g_sContext, &g_sFontCmtt16);
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

void draw_rand_circle() {
    static uint_fast8_t i = 0;
    static uint_fast8_t j = 0;
    static uint_fast8_t x = 0;
    static uint_fast8_t y = 63;
    static uint_fast8_t randval = 0;
    unsigned vx, vy;
    getSampleJoyStick(&vx, &vy);

    if (OneShot1sTimerExpired()) {
        ++j;
        StartOneShot1sTimer();
    }
    if (i == 0 && j == 3) {
        i = ENTR_DELAY;
        j = 0;
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
        Graphics_fillCircle(&g_sContext, x, y, 5);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_YELLOW);
        x = randval;
        if (x > 127) x = 127;
        randval = 63;
        Graphics_fillCircle(&g_sContext, x, y, 5);
    } else if (i == 0) {
    } else if ((vx%2) ^ (vy%2)) {
        randval += 1 << i;
        --i;
    } else {
        randval -= 1 << i;
        --i;
    }
}

int main(void) {
    WDT_A_hold(WDT_A_BASE);

    initADC_Multi();
    initJoyStick();
    InitGraphics();
    InitHWTimer1();
    Init1sTimer();
    InitButtons();
    InitLEDs();

    StartOneShot1sTimer();
    startADC();

    while (1) {
        if (Booster_Top_Button_Pushed())
            Toggle_Launchpad_Left_LED();
        draw_rand_circle();
    }
}
