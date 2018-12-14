#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include <LED_HAL.h>
#include <Buttons_HAL.h>
#include <Timer_HAL.h>
#include <ADC_HAL.h>
#include <stdio.h>

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


void DrawMenu() {
    Graphics_clearDisplay(&g_sContext);
    char text[10] = "MENU";
    sprintf(text, "Red");
    Graphics_drawString(&g_sContext, (int8_t *) text, -1, 40, 20, true);

    sprintf(text, "Green");
    Graphics_drawString(&g_sContext, (int8_t *) text, -1, 40, 40, true);

    sprintf(text, "->");
    Graphics_drawString(&g_sContext, (int8_t *) text, -1, 20, 20, true);

}


int main(void) {
    WDT_A_hold(WDT_A_BASE);
    unsigned vx, vy;
    char buf[10];

    initADC_Multi();
    initJoyStick();
    InitGraphics();
    InitTimer2();
    Init1sTimer();
    InitButtons();
    InitLEDs();

    StartOneShot1sTimer();
    startADC();


    DrawMenu();

    while (1) {
        if (Booster_Top_Button_Pushed())
            Toggle_Launchpad_Left_LED();

        getSampleJoyStick(&vx, &vy);



    }

}
