//------------------------------------------
// BUTTON API (Application Programming Interface)
// Also known as BUTTON HAL (Hardware Abstraction Layer)
// HAL is a specific form of API that designs the interface with a certain hardware

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void InitButtons() {
    GPIO_setAsInputPin (GPIO_PORT_P5, GPIO_PIN1); // upper switch S1 on BoostXL

    GPIO_setAsInputPin (GPIO_PORT_P3, GPIO_PIN5); // lower switch S2 on BoostXL

    GPIO_setAsInputPin (GPIO_PORT_P1, GPIO_PIN1); // left button on Launchpad
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN1);

    GPIO_setAsInputPin (GPIO_PORT_P1, GPIO_PIN4); // right button on Launchpad
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN4);
}

bool Booster_Top_Button_Pressed() {
    return (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == 0);
}

bool Booster_Bottom_Button_Pressed() {
    return (GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN5) == 0);
}

bool Launchpad_Left_Button_Pressed() {
    return (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == 0);
}

bool Launchpad_Right_Button_Pressed() {
    return (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4) == 0);
}

bool Booster_Top_Button_Debounce(bool rawBtn);

bool Booster_Top_Button_Pushed() {

    bool rw_tp_bttn;

    static bool dbncd_tp_bttn = false;
    bool prvs_dbncd_tp_bttn;


    prvs_dbncd_tp_bttn = dbncd_tp_bttn;

    // Read the new button status
    rw_tp_bttn = Booster_Top_Button_Pressed();

    // Debounce it
    dbncd_tp_bttn = Booster_Top_Button_Debounce(rw_tp_bttn);

    if (!dbncd_tp_bttn & prvs_dbncd_tp_bttn)
        return true;
    else
        return false;
}


//------------------------------------------
// Debounce FSM
// This FSM has two inputs the raw button status (rawBtn), which is an input to this funciton
// The other input is the status of the timer that can be directly checked here.
// The FSM also has two outputs. One is the debounced button status (debouncedBtn), which is also the output of this function
// The other output is a boolean that decides whether to start a new timer or not

bool Booster_Top_Button_Debounce(bool rawBtn) {
    typedef enum {stable0, trans0To1, stable1, trans1To0} state_t;
    static state_t S = stable0;

    // The second input of the FSM
    bool timerExpired = Timer2Expired();

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
        break;

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
        Timer2StartOneShot();

    return debouncedBtn;
}


