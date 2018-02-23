#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "leds.h"
#include "swtimer.h"

int main(void) {
    WDT_A_hold(WDT_A_BASE);

    tSWTimer timer1;
    tSWTimer timer2;
    tSWTimer timer3;
    tSWTimer timer4;

    InitLEDs();
    InitTimer();

    InitSWTimer(&timer1, TIMER32_1_BASE, (uint16_t)  5000);
    InitSWTimer(&timer2, TIMER32_1_BASE, (uint16_t) 15000);
    InitSWTimer(&timer3,TIMER32_1_BASE,  (uint16_t)  1000);
    InitSWTimer(&timer4,TIMER32_1_BASE,  (uint16_t)  1000);

    StartSWTimer(&timer1);
    StartSWTimer(&timer2);

    while (1) {
        if (SWTimerExpired(&timer1)) {
            SensorColorLEDSet(red);
            StartSWTimer(&timer3);
        }
        if (SWTimerExpired(&timer2)) {
            MainColorLEDSet(blue);
            StartSWTimer(&timer4);
        }
        if (SWTimerOneShotExpired(&timer3))
            SensorColorLEDSet(black);
        if (SWTimerOneShotExpired(&timer4))
            MainColorLEDSet(black);
    }
}
