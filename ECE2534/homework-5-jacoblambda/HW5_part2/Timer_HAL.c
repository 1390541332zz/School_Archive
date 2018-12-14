//------------------------------------------
// Timer API (Application Programming Interface)
// Also known as BUTTON HAL (Hardware Abstraction Layer)
// HAL is a specific form of API that designs the interface with a certain hardware

#include <TIMER_HAL.h>

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

// Initializes the 32-bit timer, named Timer 1
void InitHWTimer1() {
    Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    Timer32_setCount(TIMER32_0_BASE, UINT32_MAX);  // 100ms second period on 3MHz clock
    Timer32_startTimer(TIMER32_0_BASE, false);
}


// Starts the 32-bit timer for 100ms in one-shot mode
void Timer2StartOneShot100ms() {
    Timer32_setCount(TIMER32_1_BASE, 300000);  // 100ms second period on 3MHz clock
    Timer32_startTimer(TIMER32_1_BASE, true);
}

// Checks to see the 32-bit timer is expired (finished counting) or not.
int Timer2Expired() {
    return (Timer32_getValue(TIMER32_1_BASE) == 0);
}

// Timer1 HW functions
void Init1sTimer() {
    Timer32_initModule(TIMER32_0_BASE,
                       TIMER32_PRESCALER_1,
                       TIMER32_32BIT,
                       TIMER32_PERIODIC_MODE);
}


void StartOneShot1sTimer() {
    Timer32_setCount(TIMER32_0_BASE, 3000000);   //  1 s period
    Timer32_startTimer(TIMER32_0_BASE, true);
}

int OneShot1sTimerExpired() {
    return (Timer32_getValue(TIMER32_0_BASE) == 0);
}




// Software timer functions

void InitOneShotSWTimer(
        OneShotSWTimer_t* OST,
        uint32_t  hwtimer,
        uint32_t  waitCycles)
{
    OST->hwtimer = hwtimer;
    OST->waitCycles  = waitCycles;
}

void StartOneShotSWTimer(OneShotSWTimer_t* OST)
{
    OST->startCounter = Timer32_getValue(OST->hwtimer);
}

bool OneShotSWTimerExpired(OneShotSWTimer_t* OST)
{
    bool expired = false;
    uint32_t currentCounter = Timer32_getValue(OST->hwtimer);
    int64_t ticksPassed =  OST->startCounter - currentCounter;
    if (ticksPassed < 0)
        ticksPassed += (UINT32_MAX+ 1); //This is our max hardware counter

    if (ticksPassed >= OST->waitCycles)
        expired = true;
    else
        expired = false;

    return expired;
}



