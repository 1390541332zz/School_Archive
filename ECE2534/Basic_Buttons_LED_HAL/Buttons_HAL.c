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

