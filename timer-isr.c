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

  // RED LED
  GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
  GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);

  // BUTTON S1
  GPIO_setAsInputPin (GPIO_PORT_P5, GPIO_PIN1);

  // Enable interrupts from Timer32 INT1 and start the timer
  Interrupt_enableInterrupt(INT_T32_INT1);
  Timer32_startTimer(TIMER32_0_BASE, false);


  // Enabling MASTER interrupts
  Interrupt_enableMaster();

  // and done
  while (1) ;
}

void T32_INT1_IRQHandler() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0);
    if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) != 0)
        // clear interrupt only when button is not pressed
        Timer32_clearInterruptFlag(TIMER32_0_BASE);
}
