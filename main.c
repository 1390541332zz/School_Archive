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

#define PUSHED 0

enum {RED, BLUE, GREEN, PURPLE} color = RED;

void main(void) {

  WDT_A_hold(WDT_A_BASE);

  // Set the LED pins as output
  // The dafault is input. In order to turn into output, 
  // we need to set the corresponding bit to 1
  P1DIR = LED1;

  // Set the button pins as input
  // The default for PxDIR is input, so we do not need to 
  // change that. We need to specify if the input needs a 
  // pull (up or down) resistor. Based on figure 29 of 
  // board document, buttons will need pull up resistors
  // Based on Table 12-1 of microcontroller document, 
  // both REN and OUT bits should be set to 1 to achieve this
  P1REN = LEFT_BUTTON;
  P1OUT = LEFT_BUTTON;

  unsigned char left_button_prev, left_button_cur;

  while(1) {

      left_button_cur = (P1IN & LEFT_BUTTON);

      if((left_button_cur  == PUSHED) && 
	     (left_button_prev != PUSHED)) {
          P1OUT ^= LED1; //toggle the LED
      }

      left_button_prev = left_button_cur;
  }
  
}
