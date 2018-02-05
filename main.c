#include <ti/devices/msp432p4xx/driverlib/driverlib.h>


//------------------------------------------
// BUTTON API

void InitButtonS1() {
    GPIO_setAsInputPin (GPIO_PORT_P5, GPIO_PIN1); // upper switch S1 on BoostXL
}

bool ButtonS1Pressed() {
    return (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == 0);
}

//------------------------------------------
// LED API

void InitLEDs() {
    GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN6);   // color LED red on booster board
    GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN6);

    GPIO_setAsOutputPin    (GPIO_PORT_P2,  GPIO_PIN0);    // color LED red on launchpad
    GPIO_setOutputLowOnPin (GPIO_PORT_P2,  GPIO_PIN0);
}

void Toggle_Booster_LED(){
    GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN6);
}

void Toggle_Launchpad_LED() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0);
}

//------------------------------------------
// TIMER API

void InitTimer() {
    Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
}

void TimerStartOneShot() {
    Timer32_setCount(TIMER32_0_BASE, 300000);  // 100ms second period on 3MHz clock
    Timer32_startTimer(TIMER32_0_BASE, true);
}

int TimerExpiredOneShot() {
    return (Timer32_getValue(TIMER32_0_BASE) == 0);
}

//------------------------------------------
// Debounce FSM
// This FSM has two inputs the raw button status (rawBtn), which is an input to this funciton
// The other input is the status of the timer that can be directly checked here.
// The FSM also has two outputs. One is the debounced button status (debouncedBtn), which is also the output of this function
// The other output is a boolean that decides whether to start a new timer or not

bool Debounce(bool rawBtn) {
    typedef enum {stable0, trans0To1, stable1, trans1To0} state_t;
    static state_t S = stable0;

    // The second input of the FSM
    bool timerExpired = TimerExpiredOneShot();

    // Default outputs of the FSM
    bool debouncedBtn = false;
    bool startTimer = false;

    switch (S)
    {
    case stable0:
        if (rawBtn == 1)
        {
            // Change state
            S = trans0To1;

            // Update outputs, if different from default
            startTimer = 1;

         }
        break;

    case trans0To1:

        if (!rawBtn)
            S = stable0;
        else
            if (timerExpired)
                //Change state
                S = stable1;

        break;

    case stable1:
        debouncedBtn = 1;
        if (rawBtn == 0) {
            // Change state
            S = trans1To0;

            // Update outputs, if different from default
            startTimer = 1;
        }


     case trans1To0:
         debouncedBtn = 1;
         if (rawBtn)
             S = stable1;
         else
             if (timerExpired)
                 S = stable0;
        break;
    }

    if (startTimer)
        TimerStartOneShot();

    return debouncedBtn;
}



int main(void) {
    bool b  = false,  prev_b;
    bool bd = false, prev_bd;

    WDT_A_hold(WDT_A_BASE);
    InitButtonS1();
    InitLEDs();

    while (1) {

        // Update history. Notice it makes little difference to update history at the end of last cycle or beginning of the new cycle.
        prev_b  = b;
        prev_bd = bd;

        // Read the new button status
        b       = ButtonS1Pressed();

        // Debounce it
        bd      = Debounce(b);

        // The non-debounced button toggles the Launchpad LED. This is to give us an idea of how the not debounced button would have behaved.
        if (b & !prev_b)
            Toggle_Launchpad_LED();

        // The debounced button toggles the Booster board LED.
        if (bd & !prev_bd)
            Toggle_Booster_LED();
    }
}
