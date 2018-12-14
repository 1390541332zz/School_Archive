#include "leds.h"
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

void SensorColorLEDSet(color_t c) {
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

void MainColorLEDSet(color_t c) {
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
