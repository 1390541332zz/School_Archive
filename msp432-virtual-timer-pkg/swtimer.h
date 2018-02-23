#ifndef SWTIMER_H
#define SWTIMER_H

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

//-----------------------------------------------------------------------
// Initializes TIMER32_0_BASE and TIMER32_1_BASE in free running mode
// - The first is a fast one that runs at the system clock
// - The second is a slow one that runs at 1/256 of the system clock
void InitTimer();

//-----------------------------------------------------------------------
// This struct defines a periodic software timer
typedef struct {
    uint32_t hwtimer;  // hardware timer used as basis for this software timer
    uint16_t period;   // period of the software timer
    uint16_t bound;    // next expiration time for software timer
    bool     expired;
} tSWTimer;

//------------------------------------------------------------------------
// Initialize a software timer
//     T          pointer to software timer structure
//     hwtimer    id of the hardware timer that drives this software timer
//     period     period of this software timer
void InitSWTimer(tSWTimer *T,
                 uint32_t  hwtimer,
                 uint16_t  period);

//------------------------------------------------------------------------
// Start a software timer
//     T          pointer to software timer structure
void StartSWTimer(tSWTimer *T);

//------------------------------------------------------------------------
// Test when a periodic software timer expires
//     T          pointer to software timer structure
bool SWTimerExpired(tSWTimer *T);

//------------------------------------------------------------------------
// Test when a one-shot software timer expires
//     T          pointer to software timer structure
bool SWTimerOneShotExpired(tSWTimer *T);

#endif /* SWTIMER_H */
