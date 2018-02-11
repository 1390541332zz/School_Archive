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

    //--- COPY THIS FUNCTION FROM EXAMPLE 3



    //----------

}

void Timer200msStartOneShot() {

    //--- COPY THIS FUNCTION FROM EXAMPLE 3



    //----------

}

int Timer200msExpiredOneShot() {

    //--- COPY THIS FUNCTION FROM EXAMPLE 3



    //----------

}

void TimerDebounceStartOneShot() {

    //--- COPY THIS FUNCTION FROM EXAMPLE 3



    //----------

}

int TimerDebounceExpiredOneShot() {

    //--- COPY THIS FUNCTION FROM EXAMPLE 3



    //----------

}

//------------------------------------------
// Debounce FSM for S2
//

bool BounceFSM(bool b) {

    // --- YOU HAVE TO WRITE THIS FUNCTION BODY

    // ---

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
