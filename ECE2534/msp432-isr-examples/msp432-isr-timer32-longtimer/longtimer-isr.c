#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>

unsigned glbTicks;

int main(void) {
  unsigned pressed;

  // Stop WDT
  WDT_A_holdTimer();

  // Timer Initialization
  Timer32_initModule(TIMER32_0_BASE,
                     TIMER32_PRESCALER_1,
                     TIMER32_16BIT,
                     TIMER32_PERIODIC_MODE);
  Timer32_setCount(TIMER32_0_BASE, 3000);   // 1000 Hz

  // BUTTON S1
  GPIO_setAsInputPin (GPIO_PORT_P5, GPIO_PIN1);

  // Enable interrupts from Timer32 INT1 and start the timer
  Interrupt_enableInterrupt(INT_T32_INT1);
  Timer32_startTimer(TIMER32_0_BASE, false);

  // Enabling MASTER interrupts
  Interrupt_enableMaster();

  // and done
  while (1) {

      if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == 0) {
          if (!pressed) {
              // presses the S1 button
              glbTicks = 0;
              pressed  = 1;
          }
      }

      if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) != 0) {
          if (pressed) {
              printf("Button S1 pressed %d ms\n", glbTicks);
              pressed = 0;
          }
      }

  }

}

void T32_INT1_IRQHandler() {
    glbTicks++;
    Timer32_clearInterruptFlag(TIMER32_0_BASE);
}
