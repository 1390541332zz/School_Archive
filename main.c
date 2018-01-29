#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

// LR Buttons at Port 1 Pin 1(Left) & 4(Right)
#define LEFT_BUTTON    BIT1
#define RIGHT_BUTTON   BIT4

#define LED1           BIT0

// RGB LED at Port 2 Pins 0:2
#define LED2_RED       BIT0
#define LED2_GREEN     BIT1
#define LED2_BLUE      BIT2

#define PRESSED 0

enum color {RED, BLUE, GREEN, PURPLE};

void main(void) {

  WDT_A_hold(WDT_A_BASE);

  // Configure the pin connected to LED1 as output
  GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
  // Configure the pins connected to LED2 as output
  GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);

  // Configure the pin connected to left button an input with pull-up resistor
  GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN1);
  // Configure the pin connected to right button an input with pull-up resistor
  GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN4);

  unsigned char left_button_prev = 1;
  unsigned char left_button_cur = 1;
  unsigned char right_button_prev = 1;
  unsigned char right_button_cur = 1;
  enum color color = RED;

  while(1) {


      // P1IN contains all the pins on port1
      // When we mask it with LEFT_BUTTON, all the port bits become 0 except for the one representing left button
      // When this masked value becomes 0, it means this button is pressed (grounded).
      left_button_cur = (P1IN & LEFT_BUTTON);
      //The same applies but for RIGHT_BUTTON
      right_button_cur = (P1IN & RIGHT_BUTTON);

      // We recall that "pushing a button" consists of pressing and then releasing it.
      // If the button "was" pressed, but now it "is not" pressed, it means the user has finished "pushing the button"
      if ((left_button_prev == PRESSED) && (left_button_cur != PRESSED)) {
          P1OUT ^= LED1; //toggle the LED
      }

      // Every Right button toggle steps the led counter to the next state and configures the led pins for output.
      // If the button has not been pressed, the light should not be on.
      // Once it has been pressed, each press will step it through the steps below.
      // LED Colours: Red, Blue, Green, Purple
      if ((right_button_prev == PRESSED) && (right_button_cur != PRESSED)) {
          switch(color) {
            case RED:
                P2OUT &= ~LED2_BLUE;
                P2OUT &= ~LED2_GREEN;
                P2OUT |= LED2_RED;
                color = BLUE;
                break;
            case BLUE:
                P2OUT &= ~LED2_RED;
                P2OUT |= LED2_BLUE;
                color = GREEN;
                break;
            case GREEN:
                P2OUT &= ~LED2_BLUE;
                P2OUT |= LED2_GREEN;
                color = PURPLE;
                break;
            case PURPLE:
                P2OUT &= ~LED2_GREEN;
                P2OUT |= LED2_RED | LED2_BLUE;
                color = RED;
                break;
          }
      }


      // Keep the history of these button
      left_button_prev = left_button_cur;
      right_button_prev = right_button_cur;
  }
  
}
