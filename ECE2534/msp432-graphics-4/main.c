#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include <string.h>

Graphics_Context g_sContext;

void InitGraphics() {
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    Graphics_initContext(&g_sContext,
                         &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    GrContextFontSet(&g_sContext, &g_sFontCmtt16);
    Graphics_clearDisplay(&g_sContext);
}

void LCDClearDisplay() {
    Graphics_clearDisplay(&g_sContext);
}

#define LSIZE 5

typedef struct {
    unsigned cx, cy;
    unsigned r;
    char label[LSIZE];
} tCircle;

void LCDPlotCircle(tCircle *C) {
    Graphics_drawCircle(&g_sContext,
                        C->cx,
                        C->cy,
                        C->r);
    Graphics_drawStringCentered(&g_sContext,
                        C->label,
                        LSIZE,
                        C->cx,
                        C->cy,
                        false);
}

int main(void) {
    WDT_A_hold(WDT_A_BASE);

    InitGraphics();
    LCDClearDisplay();

    tCircle C;
    C.cx = 40;
    C.cy = 50;
    C.r  = 25;
    strncpy(C.label, "Cir", 5);

    tCircle D = {75, 75, 25, "ABC"};

    LCDPlotCircle(&C);
    LCDPlotCircle(&D);

    while (1) ;
}
