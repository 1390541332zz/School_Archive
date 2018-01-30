#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void InitButtonS1() {
    GPIO_setAsInputPin (GPIO_PORT_P5, GPIO_PIN1); // upper switch S1 on BoostXL
}

int ButtonS1Pressed() {
    return (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == 0);
}

void InitLEDS() {
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0); // red LED
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0); // color LED red
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1); // color LED green
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2); // color LED blue
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
}

void ColorLEDToggle() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN2);
}

void RedLEDOn() {
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void RedLEDOff() {
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

int TimerExpired() {
    static unsigned int previousSnap;
    unsigned int currentSnap, ret;
    currentSnap = Timer32_getValue(TIMER32_0_BASE);
    ret = (currentSnap > previousSnap);
    previousSnap = currentSnap;
    return ret;
}

void InitTimer() {
    Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    Timer32_setCount(TIMER32_0_BASE, 3000000);  // 1 second period on 3MHz clock
    Timer32_startTimer(TIMER32_0_BASE, false);
}

int main(void) {
    volatile uint32_t i;

    // Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);

    InitTimer();
    InitButtonS1();
    InitLEDS();

    while (1) {
        if (ButtonS1Pressed())
            RedLEDOn();
        else
            RedLEDOff();

        if (TimerExpired())
            ColorLEDToggle();
    }
}
