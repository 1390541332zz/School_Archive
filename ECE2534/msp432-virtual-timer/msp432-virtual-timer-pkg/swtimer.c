#include "swtimer.h"

void InitTimer() {

    // 16-bit timer at 3,000,000 Hz
    Timer32_initModule(TIMER32_0_BASE,
                       TIMER32_PRESCALER_1,
                       TIMER32_16BIT,
                       TIMER32_FREE_RUN_MODE);
    Timer32_setCount  (TIMER32_0_BASE, UINT16_MAX);
    Timer32_startTimer(TIMER32_0_BASE, false);

    // 16-bit timer at    11,718.75 Hz
    Timer32_initModule(TIMER32_1_BASE,
                       TIMER32_PRESCALER_256,
                       TIMER32_16BIT,
                       TIMER32_FREE_RUN_MODE);
    Timer32_setCount  (TIMER32_1_BASE, UINT16_MAX);
    Timer32_startTimer(TIMER32_1_BASE, false);
}

void InitSWTimer(tSWTimer *T,
                 uint32_t  hwtimer,
                 uint16_t  period) {
    T->hwtimer = hwtimer;
    T->period  = period;
    T->bound   = Timer32_getValue(hwtimer) - period;
    T->expired = false;
}

void StartSWTimer(tSWTimer *T) {
    T->bound   = Timer32_getValue(T->hwtimer) - T->period;
    T->expired = false;
}

bool SWTimerExpired(tSWTimer *T) {
    bool expired;
    uint16_t delta = Timer32_getValue(T->hwtimer) - T->bound;
    expired = (delta > T->period);
    if (expired)
        T->bound = T->bound - T->period;
    return expired;
}

bool SWTimerOneShotExpired(tSWTimer *T) {
    bool expired;
    uint16_t delta = Timer32_getValue(T->hwtimer) - T->bound;
    expired = (delta > T->period);
    if (expired)
        T->expired = true;
    return T->expired;
}
