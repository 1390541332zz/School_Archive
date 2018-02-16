#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

//-- UART API

eUSCI_UART_Config uartConfig = {
     ,                								// SMCLK Clock Source = 3MHz
     ,                                             	// UCBR
     ,                                            	// UCBRF
     ,                                             	// UCBRS
     ,                      						// Even Parity
     ,                        						// LSB First
     ,                     							// One stop bit
     ,                             					// UART mode
													// Oversampling
};

void InitUART() {





}

bool UARTHasChar() {
    return (UART_getInterruptStatus (EUSCI_A0_BASE,
                                     EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
                == EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);
}

uint8_t UARTGetChar() {
    if (UARTHasChar())
        return UART_receiveData(EUSCI_A0_BASE);
    else
        return 0;
}

bool UARTCanSend() {
    return (UART_getInterruptStatus (EUSCI_A0_BASE,
                                     EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG)
                == EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG);
}

void UARTPutChar(uint8_t t) {
    while (!UARTCanSend()) ;
    UART_transmitData(EUSCI_A0_BASE,t);
}

//-- ColorLED API

void InitColorLED() {
    GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN6);   // color LED red on sensor board
    GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN4);   // color LED green on sensor board
    GPIO_setAsOutputPin    (GPIO_PORT_P5,    GPIO_PIN6);   // color LED blue on sensor board
    GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN6);
    GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN4);
    GPIO_setOutputLowOnPin (GPIO_PORT_P5,    GPIO_PIN6);
}

void ToggleColorLED() {
    GPIO_toggleOutputOnPin (GPIO_PORT_P2,    GPIO_PIN6);
    GPIO_toggleOutputOnPin (GPIO_PORT_P2,    GPIO_PIN4);
    GPIO_toggleOutputOnPin (GPIO_PORT_P5,    GPIO_PIN6);
}

//-- FilterFSM

void FilterFSM(char c) {






}

int main(void) {
    char c;
    WDT_A_hold(WDT_A_BASE);

    InitUART();
    InitColorLED();

    while (1) {
        if (UARTHasChar()) {
            c = UARTGetChar();
            FilterFSM(c);
        }
    }

}
