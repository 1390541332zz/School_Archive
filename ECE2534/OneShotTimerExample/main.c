// This application uses the following:
//      1) Buttons on launchpad (and corresponding GPIOs)
//      2) LEDs on launchpad (and corresponding GPIOs)
//      3) Timer module inside MCU

// This application implements the following functionality
//      1) Pushing the left button toggles the status of the left LED
//      2) LED2 periodically changes color between green and red


#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define LEFT_BUTTON     BIT1
#define LED1            BIT0
#define RIGHT_BUTTON    BIT4
#define LED2_RED        BIT0
#define LED2_GREEN      BIT1
#define LED2_BLUE       BIT2

#define PRESSED         0
enum LED2_STATES {RED, BLUE, GREEN, OFF} LED2_status = RED;

void InitTimer() {
    Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    Timer32_setCount(TIMER32_0_BASE, 3000000);  // 1 second period on 3MHz clock

}

void InitButtons() {
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN4);

}

void InitLEDs() {

    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2);


    P2OUT &= ~LED2_RED;
    P2OUT &= ~LED2_GREEN;
    P2OUT &= ~LED2_BLUE;
    P1OUT &= ~LED1;
}

void main(void) {

  WDT_A_hold(WDT_A_BASE);

  InitLEDs();
  InitButtons();
  InitTimer();

  unsigned char left_button_prev, left_button_cur, left_button_pushed;
  //unsigned char left_button_prev, left_button_cur, left_button_pushed;

  Timer32_startTimer(TIMER32_0_BASE, true);

  while(1)
  {
      // Respond to the left button push by toggling LED1
      left_button_cur = (P1IN & LEFT_BUTTON);
      left_button_pushed = (left_button_prev == PRESSED) && (left_button_cur  != PRESSED);

      if (left_button_pushed)
          P1OUT ^= LED1; //toggle the LED

      // Keep the history of this button
      left_button_prev = left_button_cur;
      // End of processing the left button


      if (Timer32_getValue(TIMER32_0_BASE) == 0) {

          switch (LED2_status) {
              case RED:
                  // Implement the actions for this transition
                  P2OUT |= LED2_GREEN;
                  P2OUT &= ~LED2_RED;
                  Timer32_setCount(TIMER32_0_BASE, 3000000);  // 1 second period on 3MHz clock
                  Timer32_startTimer(TIMER32_0_BASE, true);

                  // Change the state and make sure you stop here using "break"
                  LED2_status = GREEN;
                  break;

              case GREEN:
                  // Implement the actions for this transition
                  P2OUT &= ~LED2_GREEN;
                  P2OUT |= LED2_RED;
                  Timer32_setCount(TIMER32_0_BASE, 3000000);  // 1 second period on 3MHz clock
                  Timer32_startTimer(TIMER32_0_BASE, true);

                  // Change the state and make sure you stop here using "break"
                  LED2_status = RED;
                  break;
          }
      }

  }

}

/*#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void InitButtonS1() {
    GPIO_setAsInputPin (GPIO_PORT_P5, GPIO_PIN1); // upper switch S1 on BoostXL
}




int TimerExpired() {
    static unsigned int previousSnap;
    unsigned int currentSnap, ret;
    currentSnap = Timer32_getValue(TIMER32_0_BASE);
    ret = (currentSnap > previousSnap);
    previousSnap = currentSnap;
    return ret;
}

void InitTimer() {
    Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    Timer32_setCount(TIMER32_0_BASE, 3000000);  // 1 second period on 3MHz clock
    Timer32_startTimer(TIMER32_0_BASE, false);
}

int main(void) {
    WDT_A_hold(WDT_A_BASE);

    InitTimer();
    InitButtonS1();
    InitLEDS();

    while (1) {
        if (ButtonS1Pressed())
            RedLEDOn();
        else
            RedLEDOff();

        if (TimerExpired())
            ColorLEDToggle();
    }
}
*/
