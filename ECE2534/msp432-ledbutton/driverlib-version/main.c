#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

int main(void) {
    volatile uint32_t i;

    // Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);

    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN1);

    while (1) {
        if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_HIGH)
            GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
        else
            GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
    }
}
