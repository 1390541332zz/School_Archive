#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void InitButtons() {
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN4);
}

bool ButtonLeftPressed() {
    return (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == 0);
}

bool ButtonRightPressed() {
    return (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4) == 0);
}

void InitLEDs() {
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0); // red LED
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0); // color LED red
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1); // color LED green
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2); // color LED blue
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
}

void ColorLEDToggle() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN2);
}

void RedLEDToggle() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

bool ButtonFSM(bool B1) {
   typedef enum {ONE, ONEwait, TWO, TWOwait} tState;
   static tState state = ONE;
   bool retval = false;
   switch (state) {
      case ONE:
        if (B1)
            state = ONEwait;
        break;
      case ONEwait:
          if (!B1)
              state = TWO;
          break;
      case TWO:
        if (B1) {
            state = TWOwait;
            retval = true;
        }
        break;
      case TWOwait:
        if (!B1) {
            state = ONE;
        }
        break;
    }
    return retval;
}

int main(void) {
    bool bp;

    WDT_A_hold(WDT_A_BASE);
    InitButtons();
    InitLEDs();

    while (1) {
        bp = ButtonLeftPressed();
        if (ButtonFSM(bp))
           ColorLEDToggle();
    }
}
