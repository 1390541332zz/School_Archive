#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define LEFT_BUTTON    BIT1
#define RIGHT_BUTTON   BIT4

#define LED1           BIT0
#define LED2_RED       BIT0
#define LED2_GREEN     BIT1
#define LED2_BLUE      BIT2

#define PUSHED 0

enum {RED, BLUE, GREEN, PURPLE} color = RED;

void main(void) {

  WDT_A_hold(WDT_A_BASE);

  // your solution goes here


}
