#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <LED_HAL.h>
#define OneSecInUs     1000000  // One seconds in microseconds
#define HalfSecInUs    500000   // Half a second in microseconds
#define TenthSecInUs   100000   // A tenth of second in microseconds
#define SysClockFInMHz 3        // The system clock frequency in MHz
#define Prescaler      256      // The prescaler

int counterWhenTimeHasPassed(unsigned int time_in_microseconds)
{
    // Time = Number of cycles * counter clock period
    // Number of cycles = Time * counter clock frequency
    // Number of cycles = Time (in seconds) * system clock frequency (in Hz) / prescaler
    // Number of cycles = Time (in microseconds) * system clock frequency (in MHz) / prescaler


    // The terminology used in this code matches the "Timer" document on google drive below:
    // https://docs.google.com/document/d/1UFbGhTpn-Iyz5sPtgmW1KIIvyrPsUKP-urtBeuwFOSE/edit?usp=sharing
    // To recap: There are two points on the counter_versus_time graph: (T1, C1) and (T2, C2)
    // We call number of cycles between T1 and T2, T2_T1
    // We calculate T2_T1 using the below formula:
    // Number of cycles = Time (in microseconds) * system clock frequency (in MHz) / prescaler

    unsigned int T2_T1 = time_in_microseconds * SysClockFInMHz / Prescaler;

    if (T2_T1 > UINT16_MAX)
        return -1;

    unsigned int C1 = Timer32_getValue(TIMER32_0_BASE);

    int C2 = C1 - T2_T1;

    if (C2 < 0)
        C2 += (UINT16_MAX + 1);

    return C2;
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

    int C2ForOneSecWait = counterWhenTimeHasPassed(OneSecInUs);
    int C2ForHalfSecWait = counterWhenTimeHasPassed(HalfSecInUs);
    int C2ForTenthSecWait = counterWhenTimeHasPassed(TenthSecInUs);

    int C1;
    while (1) {

        C1 = Timer32_getValue(TIMER32_0_BASE);

        // Booster LED blinks once per second
        if (C1 <= C2ForOneSecWait)
        {
            Toggle_Booster_LED();
            C2ForOneSecWait = counterWhenTimeHasPassed(OneSecInUs);
        }

        // The Left Launchpad LED blinks once every half a second (twice per second)
        if (C1 <= C2ForHalfSecWait)
        {
            Toggle_Launchpad_Left_LED();
            C2ForHalfSecWait = counterWhenTimeHasPassed(HalfSecInUs);
        }

        // The green Launchpad LED blinks once every quarter of a second (four times per second)
        if (C1 <= C2ForTenthSecWait)
        {
            Toggle_Launchpad_Right_Green_LED();
            C2ForTenthSecWait = counterWhenTimeHasPassed(TenthSecInUs);
        }

    }
}
