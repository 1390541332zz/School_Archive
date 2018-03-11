#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>

int main(void) {
  // Stop WDT
  WDT_A_holdTimer();

  // Timer Initialization
  Timer32_initModule(TIMER32_0_BASE,
                     TIMER32_PRESCALER_1,
                     TIMER32_32BIT,
                     TIMER32_PERIODIC_MODE);
  Timer32_setCount(TIMER32_0_BASE, 1500000);   // 2 Hz

  // Configuring P1.0 as output
  GPIO_setAsOutputPin   (GPIO_PORT_P1, GPIO_PIN0);
  GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

  // Enabling interrupts and starting the timer
  Interrupt_enableInterrupt(INT_TA0_0);
  Timer32_startTimer(TIMER32_0_BASE, false);

  Interrupt_enableInterrupt(INT_T32_INT1);

  // Enabling MASTER interrupts
  Interrupt_enableMaster();

  // and done
  while (1) ;
}

void T32_INT1_IRQHandler() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
    Timer32_clearInterruptFlag(TIMER32_0_BASE);
}
