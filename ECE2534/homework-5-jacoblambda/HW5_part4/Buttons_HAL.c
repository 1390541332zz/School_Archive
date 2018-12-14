//------------------------------------------
// BUTTON API (Application Programming Interface)
// Also known as BUTTON HAL (Hardware Abstraction Layer)
// HAL is a specific form of API that designs the interface with a certain hardware

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#define STABLE_0 0X0
#define STABLE_1 0xffffffffffffffff


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


bool Booster_Top_Button_Debounce(bool rawBtn) {
    typedef enum {stable0, stable1} state_t;
    static state_t S = stable0;
    static int history = STABLE_0;
    bool debouncedBtn;

    history = (history << 1) | rawBtn;

    switch (S)
    {
    case stable0:
        debouncedBtn = false;
        if (history == STABLE_1)
            S = stable1;
        break;

     case stable1:
        debouncedBtn = true;
        if (history == STABLE_0)
            S = stable0;
    }
    return debouncedBtn;
}




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

bool Booster_Bottom_Button_Pushed() {

    bool rw_bttm_bttn;

    static bool dbncd_bttm_bttn = false;
    bool prvs_dbncd_bttm_bttn;


    prvs_dbncd_bttm_bttn = dbncd_bttm_bttn;

    // Read the new button status
    rw_bttm_bttn = Booster_Bottom_Button_Pressed();

    // Debounce it
    dbncd_bttm_bttn = Booster_Bottom_Button_Debounce(rw_bttm_bttn);

    if (!dbncd_bttm_bttn & prvs_dbncd_bttm_bttn)
        return true;
    else
        return false;
}
