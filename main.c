#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define LEFT_BUTTON    BIT1

// THIS MACRO HAS TO BE DEFINED BY YOU
#define RIGHT_BUTTON   

#define LED1           BIT0

// THIS MACRO HAS TO BE DEFINED BY YOU
#define LED2_RED       

// THIS MACRO HAS TO BE DEFINED BY YOU
#define LED2_GREEN     

// THIS MACRO HAS TO BE DEFINED BY YOU
#define LED2_BLUE      

#define PRESSED 0

enum {RED, BLUE, GREEN, PURPLE} color = RED;

void main(void) {

  WDT_A_hold(WDT_A_BASE);

  // Configure the pin connected to LED1 as output
  GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

  // Configure the pin connected to left button an input with pull-up resistor
  GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN1);

  unsigned char left_button_prev, left_button_cur;


  while(1) {


      // P1IN contains all the pins on port1
      // When we mask it with LEFT_BUTTON, all the port bits become 0 except for the one representing left button
      // When this masked value becomes 0, it means this button is pressed (grouneded).
      left_button_cur = (P1IN & LEFT_BUTTON);

      // We recall that "pushing a button" consists of pressing and then releasing it.
      // If the button "was" pressed, but now it "is not" pressed, it means the user has finished "pushing the button"
      if ((left_button_prev == PRESSED) &&
          (left_button_cur  != PRESSED)) {
          P1OUT ^= LED1; //toggle the LED
      }

      // Keep the history of this button
      left_button_prev = left_button_cur;
  }
  
}
