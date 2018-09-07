#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

int main(void) {
    volatile uint32_t i;

    // Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);
    //these are the changes I will push to master

    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    while (1) {

        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);

        // Delay through empty loop
        for (i = 50000; i > 0; i--)   ;
    }
}
