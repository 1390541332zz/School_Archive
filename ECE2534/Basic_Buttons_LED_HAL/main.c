#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <LED_HAL.h>
#include <Buttons_HAL.h>


int main(void) {
    WDT_A_hold(WDT_A_BASE);
    InitButtons();
    InitLEDs();

    while (1) {
        if (Booster_Top_Button_Pressed())
            TurnON_Launchpad_Left_LED();
        else
            TurnOFF_Launchpad_Left_LED();

        if (Booster_Bottom_Button_Pressed())
            TurnON_Launchpad_Right_Red_LED();
        else
            TurnOFF_Launchpad_Right_Red_LED();

    }
}
