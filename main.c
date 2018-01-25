#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

int main(void) {
    WDT_A_hold(WDT_A_BASE);

    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2);

    //--------------------------------------------------------------------------
    // Run the program. Extend the following comment before checking in the file
    // My name is ...............
    // The color I'm seeing on the tri-color LED is  CHECK ...............

    while (1) {
        GPIO_setOutputHighOnPin (GPIO_PORT_P2, GPIO_PIN0);
        GPIO_setOutputHighOnPin (GPIO_PORT_P2, GPIO_PIN1);
        GPIO_setOutputLowOnPin  (GPIO_PORT_P2, GPIO_PIN2);
        GPIO_setOutputLowOnPin  (GPIO_PORT_P2, GPIO_PIN0);
        GPIO_setOutputLowOnPin  (GPIO_PORT_P2, GPIO_PIN1);
        GPIO_setOutputLowOnPin  (GPIO_PORT_P2, GPIO_PIN2);
    }
}
