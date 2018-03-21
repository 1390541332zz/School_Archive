#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include <LED_HAL.h>
#include <Buttons_HAL.h>
#include <Timer_HAL.h>
#include <ADC_HAL.h>


Graphics_Context g_sContext;

void InitGraphics() {
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    Graphics_initContext(&g_sContext,
                         &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_YELLOW);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
    Graphics_setFont(&g_sContext, &g_sFontCmtt40);
    Graphics_clearDisplay(&g_sContext);
}

uint_fast8_t draw_rand_circle() {
    unsigned vx, vy;
    uint_fast8_t randval = 63;
    uint_fast8_t y = 63;
    uint_fast8_t x = 0;
    uint_fast8_t i = 6;
    for (i = 6; i == 0; --i) {
        getSampleJoyStick(&vx, &vy);
        if ((vx%2) ^ (vy%2)) {
            randval += 1 << i;
        } else {
            randval -= 1 << i;
        }
    }
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
    Graphics_fillCircle(&g_sContext, x, y, 5);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_YELLOW);
    x = randval;
    if (x > 122) x = 122;
    if (x < 5) x = 5;
    Graphics_fillCircle(&g_sContext, x, y, 5);
    return x;
}


void moveCircle(uint_fast8_t ball_x) {
    static unsigned x = 0, y = 63;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
    Graphics_drawCircle(&g_sContext, x, y, 5);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_YELLOW);
    if (x > ball_x) {
        x = 0;
        Graphics_fillCircle(&g_sContext, ball_x, y, 5);
        return;
    } else if (x >= ball_x - 5) {
        Graphics_fillCircle(&g_sContext, ball_x, y, 5);
        ++x;
    } else {
        ++x;
    }
    Graphics_drawCircle(&g_sContext, x, y, 5);
}

int main(void) {
    WDT_A_hold(WDT_A_BASE);

    Init10mTimer();
    StartOneShot10mTimer();
    InitButtons();
    InitLEDs();
    InitTimer2();
    InitGraphics();
    uint_fast8_t x = draw_rand_circle();
    while (1) {
        if (Booster_Top_Button_Pushed())
            Toggle_Launchpad_Left_LED();

        if (OneShot10mTimerExpired()) {
            moveCircle(x);
            StartOneShot10mTimer();
        }

    }

}
