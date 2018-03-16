#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>

eUSCI_UART_Config uartConfig = {
     EUSCI_A_UART_CLOCKSOURCE_SMCLK,                // SMCLK Clock Source = 3MHz
     19,                                            // UCBR
     8,                                             // UCBRF
     0x55,                                          // UCBRS
     EUSCI_A_UART_NO_PARITY,                        // No Parity
     EUSCI_A_UART_LSB_FIRST,                        // LSB First
     EUSCI_A_UART_ONE_STOP_BIT,                     // One stop bit
     EUSCI_A_UART_MODE,                             // UART mode
     EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};

int main(void) {

  unsigned pressed;

  // Stop WDT
  WDT_A_holdTimer();

  // Initialize UART
  UART_initModule(EUSCI_A0_BASE, &uartConfig);

  UART_enableModule(EUSCI_A0_BASE);
  GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
                                             GPIO_PIN2,
                                             GPIO_PRIMARY_MODULE_FUNCTION);
  GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1,
                                              GPIO_PIN3,
                                              GPIO_PRIMARY_MODULE_FUNCTION);

  UART_enableInterrupt(EUSCI_A0_BASE,EUSCI_A_UART_RECEIVE_INTERRUPT);
  Interrupt_enableInterrupt(INT_EUSCIA0);

  // Enabling MASTER interrupts
  Interrupt_enableMaster();

  // RED LED BOOSTER
  GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN6);
  GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN6);

  // and done
  while (1) ;

}

void EUSCIA0_IRQHandler() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN6);
    uint8_t c = UART_receiveData(EUSCI_A0_BASE);
    UART_transmitData(EUSCI_A0_BASE,c);
    UART_clearInterruptFlag(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
}
