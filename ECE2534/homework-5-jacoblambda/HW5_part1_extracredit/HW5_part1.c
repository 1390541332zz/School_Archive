#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include <LED_HAL.h>
#include <Buttons_HAL.h>
#include <Timer_HAL.h>
#include "lambda.h"


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


void moveCircle() {
    static unsigned x = 0, y = 63;
    Graphics_drawImage(&g_sContext, &neglambda, x, y);
    if (x >= 127+5) {
        x = 0;
    } else {
        ++x;
    }
    Graphics_drawImage(&g_sContext, &lambda, x, y);
}

int main(void) {
    WDT_A_hold(WDT_A_BASE);

    Init10mTimer();
    StartOneShot10mTimer();
    InitButtons();
    InitLEDs();
    InitTimer2();
    InitGraphics();

    while (1) {
        if (Booster_Top_Button_Pushed())
            Toggle_Launchpad_Left_LED();

        if (OneShot10mTimerExpired()) {
            moveCircle();
            StartOneShot10mTimer();
      }
    }

}
