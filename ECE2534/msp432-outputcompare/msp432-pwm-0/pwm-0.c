#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>

unsigned glbTicks;

Timer_A_PWMConfig pwmConfig = {
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_1,    // 3 MHz
        (int) (3000000 / 1000),           // divider for 1KHz period
        TIMER_A_CAPTURECOMPARE_REGISTER_3,
        TIMER_A_OUTPUTMODE_SET_RESET,
        (int) (3000000 / 3000)            // 33% duty cucle
};

Timer_A_PWMConfig pwmConfig_2 = {
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_1,    // 3 MHz
        (int) (3000000 / 1000),           // divider for 1KHz period
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        TIMER_A_OUTPUTMODE_SET_RESET,
        (int) (3000000 /10000)            // 10% duty cucle
};

int main(void) {

  // Stop WDT
  WDT_A_holdTimer();

  // RED LED
  GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN6);
  GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN6);

  // GREEN LED
  GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN4);
  GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN4);

  GPIO_setAsPeripheralModuleFunctionOutputPin(
          GPIO_PORT_P2,
          GPIO_PIN6,
          GPIO_PRIMARY_MODULE_FUNCTION);

  GPIO_setAsPeripheralModuleFunctionOutputPin(
          GPIO_PORT_P2,
          GPIO_PIN4,
          GPIO_PRIMARY_MODULE_FUNCTION);

  Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
  Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig_2);

  while (1) ;

}
