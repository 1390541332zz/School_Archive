#include <ti/devices/msp432p4xx/driverlib/driverlib.h>


//------------------------------------------
// BUTTON API

void InitButtonS1() {
    GPIO_setAsInputPin (GPIO_PORT_P5, GPIO_PIN1); // upper switch S1 on BoostXL
}

bool ButtonS1Pressed() {
    return (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == 0);
}

//------------------------------------------
// LED API

void InitLEDs() {
    GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN6);   // color LED red on sensor board
    GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN6);

    GPIO_setAsOutputPin    (GPIO_PORT_P2,  GPIO_PIN0);    // color LED red on launchpad
    GPIO_setOutputLowOnPin (GPIO_PORT_P2,  GPIO_PIN0);
}

void SensorColorLEDToggle() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN6);
}

void SensorColorLEDOn() {
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN6);
}

void SensorColorLEDOff() {
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN6);
}

void MainColorLEDToggle() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0);
}

//------------------------------------------
// TIMER API

void InitTimer() {
    Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
}

void TimerStartOneShot() {
    Timer32_setCount(TIMER32_0_BASE, 300000);  // 100ms second period on 3MHz clock
    Timer32_startTimer(TIMER32_0_BASE, true);
}

int TimerExpiredOneShot() {
    return (Timer32_getValue(TIMER32_0_BASE) == 0);
}

//------------------------------------------
// Debounce FSM
//

bool BounceFSM(bool b) {
    typedef enum {stable0, trans0, stable1, trans1} state_t;
    static state_t S = stable0;
    bool rval;

    switch (S) {
    case stable0:
        rval = false;
        if (b) {
            TimerStartOneShot();
            S = trans0;
        }
        break;
    case trans0:
        rval = false;
        if (b && TimerExpiredOneShot())
            S = stable1;
        if (!b)
            S = stable0;
        break;
    case stable1:
        if (!b) {
            TimerStartOneShot();
            S = trans1;
        }
        rval = true;
        break;
    case trans1:
        if (!b && TimerExpiredOneShot())
            S = stable0;
        if (b)
            S = stable1;
        rval = true;
        break;
    }

    return rval;
}

#define UPEDGE(A, B) (A && !(B))

int main(void) {
    bool b  = false,  prev_b;
    bool bd = false, prev_bd;

    WDT_A_hold(WDT_A_BASE);
    InitButtonS1();
    InitLEDs();

    while (1) {
        prev_b  = b;
        prev_bd = bd;
        b       = ButtonS1Pressed();
        bd      = BounceFSM(b);

        if (bd & !prev_b)
            MainColorLEDToggle();

        if (bd & !prev_bd)
            SensorColorLEDToggle();
    }
}
