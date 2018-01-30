#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define LEFT_BUTTON    BIT1

#define LED1           BIT0


#define PRESSED 0


typedef enum  {WAITING_FOR_THE_FIRST_PUSH, WAITING_FOR_THE_SECOND_PUSH} STATES;

void main(void) {

  WDT_A_hold(WDT_A_BASE);

  // Configure the pin connected to LED1 as output
  GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

  // Configure the pin connected to left button an input with pull-up resistor
  GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN1);

  unsigned char left_button_prev, left_button_cur, left_button_pushed;
  STATES curState = WAITING_FOR_THE_FIRST_PUSH;

  while(1)
  {
      // Read the input from left button and mask it
      left_button_cur = (P1IN & LEFT_BUTTON);

      // Based on history, check to see if the button has been pushed
      // This happens only if the button is currently released, but it was pressed before
      left_button_pushed = (left_button_prev == PRESSED) && (left_button_cur  != PRESSED);

      // We need to take action only if left button is pushed
      if (left_button_pushed)
      {
          switch(curState)
                {
                    case WAITING_FOR_THE_FIRST_PUSH:
                        // update the state
                        curState = WAITING_FOR_THE_SECOND_PUSH;

                        // show reaction
                        // In this state, the application has no reaction

                        break;
                    case WAITING_FOR_THE_SECOND_PUSH:
                        // update the state
                        curState = WAITING_FOR_THE_FIRST_PUSH;

                        // show reaction
                        P1OUT ^= LED1; //toggle the LED
                        break;
                }
      }

      // Keep the history of this button
      left_button_prev = left_button_cur;
  }
  
}
