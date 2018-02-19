#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"

Graphics_Context g_sContext;

void InitGraphics() {
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    Graphics_initContext(&g_sContext,
                         &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_YELLOW);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
    GrContextFontSet(&g_sContext, &g_sFontCmtt16);
    Graphics_clearDisplay(&g_sContext);
}

void LCDClearDisplay() {
    Graphics_clearDisplay(&g_sContext);
}

int main(void) {
    unsigned i;

    WDT_A_hold(WDT_A_BASE);

    InitGraphics();
    LCDClearDisplay();

    Graphics_Rectangle R;
    R.xMin = 0;
    R.xMax = 63;
    R.yMin = 0;
    R.yMax = 127;
    Graphics_setClipRegion(&g_sContext, &R);

    Graphics_fillCircle(&g_sContext, 63, 63, 30);

    while (1) ;
}
