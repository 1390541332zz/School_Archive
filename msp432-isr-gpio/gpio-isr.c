#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>

unsigned glbTicks;

int main(void) {

  unsigned pressed;

  // Stop WDT
  WDT_A_holdTimer();

  // BUTTON 1 from Launchpad
  GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN1);

  // Enable interrupts from GPIO port P1
  GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
  Interrupt_enableInterrupt(INT_PORT1);

  // Enabling MASTER interrupts
  Interrupt_enableMaster();

  // RED LED BOOSTER
  GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN6);
  GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN6);

  // and done
  while (1) ;

}

void PORT1_IRQHandler() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN6);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
}
