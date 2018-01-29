#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

int main(void) {
    volatile uint32_t i;

    // Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);

    P1DIR = BIT0;  // P1.0 as output

    P1REN = BIT1;  // P1.1 as input with pullup/pulldown resistor
    P1OUT = BIT1;  // select pull-up

    while (1) {
        if (P1IN & 2)
            P1OUT = P1OUT & ~BIT0;
        else
            P1OUT = P1OUT |  BIT0;
    }
}
