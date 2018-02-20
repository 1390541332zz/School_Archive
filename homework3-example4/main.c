#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

// Global parameters with current application settings

typedef enum {black, red, green, yellow, blue, magenta, cyan, white} color_t;

//------------------------------------------
// BUTTON API
//

void InitButtonS2() {
    GPIO_setAsInputPin (GPIO_PORT_P3, GPIO_PIN5); // upper switch S1 on BoostXL
}

int ButtonS2Pressed() {
    return (GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN5) == 0);
}

//------------------------------------------
// LED API
//

void InitLEDS() {
    GPIO_setAsOutputPin    (GPIO_PORT_P1,    GPIO_PIN0);   // red LED on Launchpad
    GPIO_setOutputLowOnPin (GPIO_PORT_P1,    GPIO_PIN0);

}

void RedLEDToggle() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
}


//------------------------------------------
// TIMER API
//

void InitTimer() {
    MAP_Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1,
            TIMER32_32BIT, TIMER32_FREE_RUN_MODE);
    MAP_Timer32_initModule(TIMER32_1_BASE, TIMER32_PRESCALER_1,
            TIMER32_32BIT, TIMER32_FREE_RUN_MODE);
}

void Timer200msStartOneShot() {
    Timer32_startTimer(TIMER32_0_BASE, true);
    Timer32_setCount(TIMER32_0_BASE, 600000);
}

int Timer200msExpiredOneShot() {
    return Timer32_getValue(TIMER32_0_BASE) == 0;
}

void TimerDebounceStartOneShot() {
    Timer32_startTimer(TIMER32_1_BASE, true);
    Timer32_setCount(TIMER32_1_BASE, 300000);
}

int TimerDebounceExpiredOneShot() {
    return Timer32_getValue(TIMER32_1_BASE) == 0;
}

//------------------------------------------
// Debounce FSM for S2
//

bool BounceFSM(bool b) {
    typedef enum {OFF, RUNNING} state_t;
    static state_t state = OFF;

    if (b && state == OFF) {
        Timer200msStartOneShot();
        state = RUNNING;
    } else if (b && Timer200msExpiredOneShot()) {
        Timer200msStartOneShot();
        return true;
    }
    return false;
}


#define UPEDGE(A, B) (A && !(B))

int main(void) {
    bool S2d = false, prev_S2d;

    WDT_A_hold(WDT_A_BASE);

    InitTimer();
    InitButtonS2();
    InitLEDS();

    while (1) {
        prev_S2d = S2d;
        S2d      = BounceFSM(ButtonS2Pressed());

        if (UPEDGE(S2d, prev_S2d)) {
            RedLEDToggle();
        }

    }
}
