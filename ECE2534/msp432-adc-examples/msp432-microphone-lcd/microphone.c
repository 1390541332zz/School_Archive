#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"

void InitTimer() {
    Timer32_initModule(TIMER32_0_BASE,
                       TIMER32_PRESCALER_1,
                       TIMER32_32BIT,
                       TIMER32_PERIODIC_MODE);
}

void Timer1msStartOneShot() {
    Timer32_setCount(TIMER32_0_BASE, 300);   // 10 KHz (100 microsecond period)
    Timer32_startTimer(TIMER32_0_BASE, true);
}

int Timer1msExpiredOneShot() {
    return (Timer32_getValue(TIMER32_0_BASE) == 0);
}

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

void initADC() {
    ADC14_enableModule();

    // This sets the conversion clock to 3MHz
    ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC,
                     ADC_PREDIVIDER_1,
                     ADC_DIVIDER_1,
                      0
                     );

    ADC14_setResolution(ADC_14BIT);

    // This configures the ADC to store output results
    // in ADC_MEM0 (single-channel conversion, repeat mode)
    ADC14_configureSingleSampleMode(ADC_MEM0, true);

    // This configures the ADC in automatic conversion mode
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
}

void startADC() {
    // The ADC is in continuous sampling mode, so after calling this once
    // the ADC will continuously update
    ADC14_enableConversion();
    ADC14_toggleConversionTrigger();
}

void initMicrophone() {
    // This configures ADC_MEM0 to store the result from
    // input channel A10 (Microphone), in non-differential input mode
    // (non-differential means: only a single input pin)
    // The reference for Vref- and Vref+ are VSS and VCC respectively
    ADC14_configureConversionMemory(ADC_MEM0,
                                    ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                    ADC_INPUT_A10,
                                    ADC_NONDIFFERENTIAL_INPUTS);

    // This selects the GPIO as analog input
    // A9 is multiplexed on GPIO port P4 pin PIN4
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,
                                               GPIO_PIN3,
                                               GPIO_TERTIARY_MODULE_FUNCTION);
}

unsigned getSampleMicrophone() {
    return ADC14_getResult(ADC_MEM0);
}


unsigned sampleconv(unsigned v) {
    // This function maps on ADC sample (range 0 to 3FFF, midpoint 1FFF)
    // to the display Y coordinates (range 0 to 127, midpoint 64)
    // It also adds a digital gain factor
    int s0127 = (0x3FFF - v) / 128; // scaled 0 to 127, midpoint 64
    int gain = 4;
    return (unsigned) (s0127 - 64) * gain + 64;
}

void addSample(unsigned vx) {
    // This function queues up 128 samples
    // When 128 samples are received, it draws the buffer on the display
    // while removing the previous trace
    unsigned i;
    static unsigned count = 0;
    static unsigned oldsamplebuf[128];
    static unsigned newsamplebuf[128];

    newsamplebuf[count++] = vx;

    if (count == 128) {
        count  = 0;

        // buffer filled with 128 samples, dump to the display
        for (i=1; i<128; i++) {
            // remove the previous trace
            Graphics_setForegroundColor(&g_sContext,GRAPHICS_COLOR_BLUE);
            Graphics_drawLine(&g_sContext,
                              i-1, sampleconv(oldsamplebuf[i-1]),
                              i,   sampleconv(oldsamplebuf[  i]));
           // put the new trace
           Graphics_setForegroundColor(&g_sContext,GRAPHICS_COLOR_YELLOW);
           Graphics_drawLine(&g_sContext,
                             i-1, sampleconv(newsamplebuf[i-1]),
                            i,   sampleconv(newsamplebuf[  i]));
        }
        // update the buffer
        for (i=0; i<128; i++)
          oldsamplebuf[i] = newsamplebuf[i];
    }
}

int main(void) {
    WDT_A_hold(WDT_A_BASE);
    unsigned vx;

    initADC();
    initMicrophone();
    InitGraphics();
    InitTimer();

    Timer1msStartOneShot();
    startADC();

    while (1) {
      if (Timer1msExpiredOneShot()) {
          vx = getSampleMicrophone();
          addSample(vx);
          Timer1msStartOneShot();
      }
    }

}
