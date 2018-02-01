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

void ColorLEDOn() {
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
}

void ColorLEDOff() {
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
}

void RedLEDToggle() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

bool TwoButtonFSMOn(bool BL, bool BR) {
   typedef enum {IDLE, FIRSTLEFT, THENRIGHT} tState;
   static tState state = IDLE;
   bool retval = false;
   switch (state) {
      case IDLE:
        if (BL & !BR)
            state = FIRSTLEFT;
        break;
      case FIRSTLEFT:
          if (BL & BR)
              state = THENRIGHT;
          else if (BL & !BR)
              state = FIRSTLEFT;
          else
              state = IDLE;
          break;
      case THENRIGHT:
        retval = true;
        state = IDLE;
        break;
    }
    return retval;
}

bool TwoButtonFSMOff(bool BL, bool BR) {
   typedef enum {IDLE, FIRSTRIGHT, THENLEFT} tState;
   static tState state = IDLE;
   bool retval = false;
   switch (state) {
      case IDLE:
        if (!BL & BR)
            state = FIRSTRIGHT;
        break;
      case FIRSTRIGHT:
          if (BL & BR)
              state = THENLEFT;
          else if (!BL & BR)
              state = FIRSTRIGHT;
          else
              state = IDLE;
          break;
      case THENLEFT:
        retval = true;
        state = IDLE;
        break;
    }
    return retval;
}

int main(void) {
    bool bpleft, bpright;

    WDT_A_hold(WDT_A_BASE);
    InitButtons();
    InitLEDs();

    while (1) {
        bpleft  = ButtonLeftPressed();
        bpright = ButtonRightPressed();

        if (TwoButtonFSMOn(bpleft, bpright))
            ColorLEDOn();

        if (TwoButtonFSMOff(bpleft, bpright))
            ColorLEDOff();
    }
}
