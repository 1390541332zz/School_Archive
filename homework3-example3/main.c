#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

typedef enum {black, red, green, yellow, blue, magenta, cyan, white} color_t;

//------------------------------------------
// LED API
//

void InitLEDS() {
    GPIO_setAsOutputPin    (GPIO_PORT_P1,    GPIO_PIN0);   // red LED on Launchpad
    GPIO_setOutputLowOnPin (GPIO_PORT_P1,    GPIO_PIN0);

    GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN6);   // color LED red on sensor board
    GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN4);   // color LED green on sensor board
    GPIO_setAsOutputPin    (GPIO_PORT_P5,    GPIO_PIN6);   // color LED blue on sensor board
    GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN6);
    GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN4);
    GPIO_setOutputLowOnPin (GPIO_PORT_P5,    GPIO_PIN6);
}

void ColorLEDSet(color_t t) {
    switch (t) {
    case black:
        GPIO_setOutputLowOnPin (GPIO_PORT_P2, GPIO_PIN6);
        GPIO_setOutputLowOnPin (GPIO_PORT_P2, GPIO_PIN4);
        GPIO_setOutputLowOnPin (GPIO_PORT_P5, GPIO_PIN6);
        break;
    case red:
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN6);
        GPIO_setOutputLowOnPin (GPIO_PORT_P2, GPIO_PIN4);
        GPIO_setOutputLowOnPin (GPIO_PORT_P5, GPIO_PIN6);
        break;
    case green:
        GPIO_setOutputLowOnPin (GPIO_PORT_P2, GPIO_PIN6);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);
        GPIO_setOutputLowOnPin (GPIO_PORT_P5, GPIO_PIN6);
        break;
    case yellow:
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN6);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);
        GPIO_setOutputLowOnPin (GPIO_PORT_P5, GPIO_PIN6);
        break;
    case blue:
        GPIO_setOutputLowOnPin (GPIO_PORT_P2, GPIO_PIN6);
        GPIO_setOutputLowOnPin (GPIO_PORT_P2, GPIO_PIN4);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN6);
        break;
    case magenta:
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN6);
        GPIO_setOutputLowOnPin (GPIO_PORT_P2, GPIO_PIN4);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN6);
        break;
    case cyan:
        GPIO_setOutputLowOnPin (GPIO_PORT_P2, GPIO_PIN6);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN6);
        break;
    case white:
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN6);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN6);
        break;
    }
}

void RedLEDToggle() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void RedLEDOn() {
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void RedLEDOff() {
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
}


//------------------------------------------
// TIMER API
//

void InitTimer() {

    // --- YOU HAVE TO WRITE THIS FUNCTION BODY

    // ---

}

void Timer200msStartOneShot() {

    // --- YOU HAVE TO WRITE THIS FUNCTION BODY

    // ---

}

int Timer200msExpiredOneShot() {

    // --- YOU HAVE TO WRITE THIS FUNCTION BODY

    // ---

}

void TimerDebounceStartOneShot() {

    // --- YOU HAVE TO WRITE THIS FUNCTION BODY

    // ---

}

int TimerDebounceExpiredOneShot() {

    // --- YOU HAVE TO WRITE THIS FUNCTION BODY

    // ---

}

int main(void) {
    WDT_A_hold(WDT_A_BASE);
    color_t c = black;

    InitTimer();
    InitLEDS();

    Timer200msStartOneShot();
    ColorLEDSet(c);
    c = (c == white) ? black : c+1;

    TimerDebounceStartOneShot();
    RedLEDOn();

    while (1) {

        if (Timer200msExpiredOneShot()) {
            ColorLEDSet(c);
            c = (c == white) ? black : c+1;
            Timer200msStartOneShot();
        }

        if (TimerDebounceExpiredOneShot()) {
            RedLEDToggle();
            TimerDebounceStartOneShot();
        }
    }
}
