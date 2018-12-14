//------------------------------------------
// Timer API (Application Programming Interface)
// Also known as BUTTON HAL (Hardware Abstraction Layer)
// HAL is a specific form of API that designs the interface with a certain hardware



#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

// Initializes the 32-bit timer, named Timer 1
void InitTimer2() {
    Timer32_initModule(TIMER32_1_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
}

// Starts the 32-bit timer for 100ms in one-shot mode
void Timer2StartOneShot100ms() {
    Timer32_setCount(TIMER32_1_BASE, 300000);  // 100ms second period on 3MHz clock
    Timer32_startTimer(TIMER32_1_BASE, true);
}

// Checks to see the 32-bit timer is expired (finished counting) or not.
bool Timer2Expired() {
    return (Timer32_getValue(TIMER32_1_BASE) == 0);
}

void Init10mTimer() {
    Timer32_initModule(TIMER32_0_BASE,
                       TIMER32_PRESCALER_1,
                       TIMER32_32BIT,
                       TIMER32_PERIODIC_MODE);
}


void StartOneShot10mTimer() {
    Timer32_setCount(TIMER32_0_BASE, 30000);   //  10 ms period
    Timer32_startTimer(TIMER32_0_BASE, true);
}

int OneShot10mTimerExpired() {
    return (Timer32_getValue(TIMER32_0_BASE) == 0);
}

