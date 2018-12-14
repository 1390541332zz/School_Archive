#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>

#define LEVEL(A) ((A & 7) << 5)

int main(void) {
  // Stop WDT
  WDT_A_holdTimer();

  // Timer Initialization
  Timer32_initModule(TIMER32_0_BASE,
                     TIMER32_PRESCALER_1,
                     TIMER32_32BIT,
                     TIMER32_PERIODIC_MODE);
  Timer32_setCount(TIMER32_0_BASE, 1500000);   // 2 Hz

  Timer32_initModule(TIMER32_1_BASE,
                     TIMER32_PRESCALER_1,
                     TIMER32_32BIT,
                     TIMER32_PERIODIC_MODE);
  Timer32_setCount(TIMER32_1_BASE, 500000);   // 3 Hz

  // RED LED BOOSTER
  GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN6);
  GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN6);

  // RED LED LAUNCHPAD
  GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN0);
  GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN0);

  // BUTTON S1
  GPIO_setAsInputPin (GPIO_PORT_P5, GPIO_PIN1);

  // Enable interrupts from Timer32 INT1 and start the timer
  Interrupt_enableInterrupt(INT_T32_INT1);
  Timer32_startTimer(TIMER32_0_BASE, false);

  Interrupt_enableInterrupt(INT_T32_INT2);
  Timer32_startTimer(TIMER32_1_BASE, false);

//  Interrupt_setPriority(INT_T32_INT1,LEVEL(0x1));
//  Interrupt_setPriority(INT_T32_INT2,LEVEL(0x2));

  // Enabling MASTER interrupts
  Interrupt_enableMaster();

  // and done
  while (1) ;
}

void T32_INT1_IRQHandler() {
    volatile int i;
    GPIO_setOutputHighOnPin (GPIO_PORT_P2,    GPIO_PIN6);
    for (i=0; i<50000; i++) ;
    GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN6);
    Timer32_clearInterruptFlag(TIMER32_0_BASE);
}

void T32_INT2_IRQHandler() {
    volatile int i;
    GPIO_setOutputHighOnPin (GPIO_PORT_P2,    GPIO_PIN0);
    for (i=0; i<10000; i++) ;
    GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN0);
    Timer32_clearInterruptFlag(TIMER32_1_BASE);
}
