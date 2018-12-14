//------------------------------------------
// TIMER API
// Also known as TIMER HAL (Hardware Abstraction Layer)
// HAL is a specific form of API that designs the interface with a certain hardware

#ifndef TIMERS_H_
#define TIMERS_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

// Functions related to 32-bit timer. Notice how we change the name to a generic name.
// Initializes the 32-bit timer, named Timer 1
void InitTimer1();
void InitTimer2();

// Starts the 32-bit timer for 100ms in one-shot mode
void Timer2StartOneShot100ms();

// Checks to see the 32-bit timer is expired (finished counting) or not.
int Timer2Expired();


void Init1sTimer();
void StartOneShot1sTimer();
int OneShot1sTimerExpired();


typedef struct {
    uint32_t    hwtimer;        // hardware timer used as basis for this software timer
    uint32_t    waitCycles;         // wait "cycles" for the software timer
    uint32_t    startCounter;   // last counter value when the SW timer started
} OneShotSWTimer_t;

void InitOneShotSWTimer(OneShotSWTimer_t* OST,
                        uint32_t  hwtimer,
                        uint32_t  waitCycles);

void StartOneShotSWTimer(OneShotSWTimer_t* OST);

bool OneShotSWTimerExpired(OneShotSWTimer_t* OST);

// Functions related to 32-bit timer. Notice how we change the name to a generic name.
// Initializes the 32-bit timer, named Timer 1
void InitHWTimer1();



#endif

