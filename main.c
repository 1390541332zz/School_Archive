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

  unsigned char left_button_prev, left_button_cur;
  STATES curState = WAITING_FOR_THE_FIRST_PUSH;

  while(1)
  {

      left_button_cur = (P1IN & LEFT_BUTTON);

      // We need to take some action only if left button is pushed
      if ((left_button_prev == PRESSED) &&
                (left_button_cur  != PRESSED))
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
