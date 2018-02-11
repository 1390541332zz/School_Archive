#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

// Global parameters with current application settings

typedef enum {baud9600, baud19200, baud38400, baud57600} UARTBaudRate_t;


//------------------------------------------
// UART API
//
// We are using EUSCI_A0, which is a user UART in MSP432 that is accessible
// on your laptop as 'XDS 110 Class Application/User UART'. It usually shows up as COM3.
//
// The low-level UART functions are taken from the MSP432 Driverlib, Chapter 24.
//
// The Baud Rate Computation Procedure is taken from the
// User Guide MSP432P4 Microcontroller, Chapter 24, page 915
//
//  Baud rate computation:
//  - System Clock SMCLK in MSP432P4 is 3MHz (Default)
//  - Baud Rate Division Factor N = 3MHz / Baudrate
//      Eg. N9600 = 30000000 / 9600 = 312.5
//  - If N>16 -> oversampling mode
//      Baud Rate Divider              UCBF  = FLOOR(N/16)     = INT(312.5/16)     = 19
//      First modulation stage select  UCBRF = FRAC(N/16) * 16 = FRAC(312.5/16)*16 = 8
//      Second modulation state select UCBRS = (table 24-4 based on FRAC(312.5))   = 0xAA

eUSCI_UART_Config uartConfig = {
     EUSCI_A_UART_CLOCKSOURCE_SMCLK,               // SMCLK Clock Source = 3MHz
     19,                                           // UCBR   = 19
     8,                                            // UCBRF  = 8
     0xAA,                                         // UCBRS  = 0xAA
     EUSCI_A_UART_NO_PARITY,                       // No Parity
     EUSCI_A_UART_LSB_FIRST,                       // LSB First
     EUSCI_A_UART_ONE_STOP_BIT,                    // One stop bit
     EUSCI_A_UART_MODE,                            // UART mode
     EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION // Oversampling
};

void InitUART() {
    UART_initModule(EUSCI_A0_BASE, &uartConfig);
    UART_enableModule(EUSCI_A0_BASE);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
        GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
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

void UARTSetBaud(UARTBaudRate_t t) {

    // --- YOU HAVE TO WRITE THIS FUNCTION BODY

    // ---

}
//-----------------------------------------------------------------------

int main(void) {
    volatile int i;
    WDT_A_hold(WDT_A_BASE);

    InitUART();

    UARTSetBaud(baud9600);
    UARTPutChar('B');
    UARTPutChar('a');
    UARTPutChar('u');
    UARTPutChar('d');
    UARTPutChar(' ');
    UARTPutChar('i');
    UARTPutChar('s');
    UARTPutChar(' ');
    UARTPutChar('9');
    UARTPutChar('6');
    UARTPutChar('0');
    UARTPutChar('0');
    for (i=0; i<300000; i++) ; // short delay to finish transmission of last char

    UARTSetBaud(baud19200);
    UARTPutChar('B');
    UARTPutChar('a');
    UARTPutChar('u');
    UARTPutChar('d');
    UARTPutChar(' ');
    UARTPutChar('i');
    UARTPutChar('s');
    UARTPutChar(' ');
    UARTPutChar('1');
    UARTPutChar('9');
    UARTPutChar('2');
    UARTPutChar('0');
    UARTPutChar('0');
    for (i=0; i<300000; i++) ; // short delay to finish transmission of last char

    UARTSetBaud(baud38400);
    UARTPutChar('B');
    UARTPutChar('a');
    UARTPutChar('u');
    UARTPutChar('d');
    UARTPutChar(' ');
    UARTPutChar('i');
    UARTPutChar('s');
    UARTPutChar(' ');
    UARTPutChar('3');
    UARTPutChar('8');
    UARTPutChar('4');
    UARTPutChar('0');
    UARTPutChar('0');
    for (i=0; i<300000; i++) ; // short delay to finish transmission of last char

    UARTSetBaud(baud57600);
    UARTPutChar('B');
    UARTPutChar('a');
    UARTPutChar('u');
    UARTPutChar('d');
    UARTPutChar(' ');
    UARTPutChar('i');
    UARTPutChar('s');
    UARTPutChar(' ');
    UARTPutChar('5');
    UARTPutChar('7');
    UARTPutChar('6');
    UARTPutChar('0');
    UARTPutChar('0');

    while (1) { }

}
