#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

//-- ColorLED API

eUSCI_UART_Config uartConfig = {
     EUSCI_A_UART_CLOCKSOURCE_SMCLK,                // SMCLK Clock Source = 3MHz
     1,                                             // UCBR
     10,                                            // UCBRF
     0,                                             // UCBRS
     EUSCI_A_UART_EVEN_PARITY,                      // Even Parity
     EUSCI_A_UART_LSB_FIRST,                        // LSB First
     EUSCI_A_UART_ONE_STOP_BIT,                     // One stop bit
     EUSCI_A_UART_MODE,                             // UART mode
     EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};

void InitUART() {
    UART_initModule(EUSCI_A0_BASE, &uartConfig);
    UART_enableModule(EUSCI_A0_BASE);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
        GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1,
        GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
}

bool UARTHasChar() {
    return (UART_getInterruptStatus (EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
                == EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);
}

uint8_t UARTGetChar() {
    if (UARTHasChar())
        return UART_receiveData(EUSCI_A0_BASE);
    else
        return 0;
}

bool UARTCanSend() {
    return (UART_getInterruptStatus (EUSCI_A0_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG)
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
    typedef enum {idle, has_f, has_l, has_i} state_t;
    static state_t S = idle;

    switch (S) {
    case idle:
        if (c == 'f')
            S = has_f;
        else
            UARTPutChar(c);
        break;
    case has_f:
        if (c == 'l')
            S = has_l;
        else {
            UARTPutChar('f');
            UARTPutChar(c);
            S = idle;
        }
        break;
    case has_l:
        if (c == 'i')
            S = has_i;
        else {
            UARTPutChar('f');
            UARTPutChar('l');
            UARTPutChar(c);
            S = idle;
        }
        break;
    case has_i:
        if (c == 'p') {
            ToggleColorLED();
            S = idle;
        } else {
            UARTPutChar('f');
            UARTPutChar('l');
            UARTPutChar('i');
            UARTPutChar(c);
            S = idle;
        }
        break;
    }
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
