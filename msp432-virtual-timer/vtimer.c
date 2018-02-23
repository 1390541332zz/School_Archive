#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void InitLEDs() {
    GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN6);   // color LED red on sensor board
    GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN4);   // color LED green on sensor board
    GPIO_setAsOutputPin    (GPIO_PORT_P5,    GPIO_PIN6);   // color LED blue on sensor board
    GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN6);
    GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN4);
    GPIO_setOutputLowOnPin (GPIO_PORT_P5,    GPIO_PIN6);

    GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN0);   // color LED red on main board
    GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN1);   // color LED green on main board
    GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN2);   // color LED blue on main board
    GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN0);
    GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN1);
    GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN2);
}

enum {black, red, green, yellow, blue, purple, cyan, white};

void SensorColorLEDSet(uint8_t c) {
    if (c & 1)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN6);
    else
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN6);
    if (c & 2)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);
    else
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN4);
    if (c & 4)
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN6);
    else
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN6);
}

void MainColorLEDSet(uint8_t c) {
    if (c & 1)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
    else
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
    if (c & 2)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
    else
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
    if (c & 4)
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
    else
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
}

//-----------------------------------------------------------------------
// We use two 16-bit hardware timers
// - The first is a fast one that runs at the system clock
// - The second is a slow one that runs at 1/256 of the system clock
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
                 uint16_t  period) {
    T->hwtimer = hwtimer;
    T->period  = period;
    T->bound   = Timer32_getValue(hwtimer) - period;
    T->expired = false;
}

//------------------------------------------------------------------------
// Start a software timer
//     T          pointer to software timer structure
void StartSWTimer(tSWTimer *T) {
    T->bound   = Timer32_getValue(T->hwtimer) - T->period;
    T->expired = false;
}

//------------------------------------------------------------------------
// Test when a periodic software timer expires
//     T          pointer to software timer structure
bool SWTimerExpired(tSWTimer *T) {
    bool expired;
    uint16_t delta = Timer32_getValue(T->hwtimer) - T->bound;
    expired = (delta > T->period);
    if (expired)
        T->bound = T->bound - T->period;
    return expired;
}

//------------------------------------------------------------------------
// Test when a one-shot software timer expires
//     T          pointer to software timer structure
bool SWTimerOneShotExpired(tSWTimer *T) {
    bool expired;
    uint16_t delta = Timer32_getValue(T->hwtimer) - T->bound;
    expired = (delta > T->period);
    if (expired)
        T->expired = true;
    return T->expired;
}

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
