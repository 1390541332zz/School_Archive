#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <LED_HAL.h>
#define OneSecInms   1000000 // One seconds is 1000000 ms
#define HalfSecInms   500000  // Half a second
#define QuartSecInms  250000  // A quarter of second

int counterWhenTimeHasPassed(int time_in_microseconds)
{
    int ticks_needed = time_in_microseconds * 3 / 256;

    if (ticks_needed > UINT16_MAX)
        return -1;

    int curCounter = Timer32_getValue(TIMER32_0_BASE);


    int nextCounter = curCounter - ticks_needed;

    if (nextCounter < 0)
        nextCounter += (UINT16_MAX + 1);

    return nextCounter;
}



int main(void) {
    WDT_A_hold(WDT_A_BASE);
    InitLEDs();

    // 16-bit timer.
    // System clock frequency is 3,000,000 Hz
    // The prescalar is 256. Therefore, the clock for the timer is 3MHz/256
    // Free running (periodic mode) with N equal to 2^16 -1
    Timer32_initModule(TIMER32_0_BASE,
    TIMER32_PRESCALER_256,
        TIMER32_16BIT,
        TIMER32_FREE_RUN_MODE);
    Timer32_setCount  (TIMER32_0_BASE, UINT16_MAX);
    Timer32_startTimer(TIMER32_0_BASE, false);

    int nextCounterForOneSecWait = counterWhenTimeHasPassed(OneSecInms);
    int nextCounterForHalfSecWait = counterWhenTimeHasPassed(HalfSecInms);
    int nextCounterForQuartSecWait = counterWhenTimeHasPassed(QuartSecInms);

    int curCounter;
    while (1) {

        curCounter = Timer32_getValue(TIMER32_0_BASE);
        if (curCounter <= nextCounterForOneSecWait)
        {
            Toggle_Booster_LED();
            nextCounterForOneSecWait = counterWhenTimeHasPassed(OneSecInms);
        }

        if (curCounter <= nextCounterForHalfSecWait)
        {
            Toggle_Launchpad_Left_LED();
            nextCounterForHalfSecWait = counterWhenTimeHasPassed(HalfSecInms);
        }

        if (curCounter <= nextCounterForQuartSecWait)
        {
            Toggle_Launchpad_Right_Green_LED();
            nextCounterForQuartSecWait = counterWhenTimeHasPassed(QuartSecInms);
        }

    }
}
