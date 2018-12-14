/*
 * This application reacts the position of the joystick to change the color of the right LED on the launchpad.
 * It has no states (No FSM). This means the color of the LED only depends on the current position of the joystick and has no memory of the past.
 * Neutral position: gree, Up position: Red, Down position: Blue
 */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include "LED_HAL.h"

#define UP_THRESHOLD  0x3000
#define DOWN_THRESHOLD 0x1000


void initADC() {
    ADC14_enableModule();

    // This sets the conversion clock to 3MHz
    ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC,
                     ADC_PREDIVIDER_1,
                     ADC_DIVIDER_1,
                      0
                     );

    // This configures the ADC to store output results
    // in ADC_MEM0 up to ADC_MEM1. Each conversion will
    // thus use two channels.
    ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM1, true);

    // This configures the ADC in manual conversion mode
    // Software will start each conversion.
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
}

void startADC() {
   // Starts the ADC with the first conversion
   // in repeat-mode, subsequent conversions run automatically
   ADC14_enableConversion();
   ADC14_toggleConversionTrigger();
}

void initJoyStick() {

    // This configures ADC_MEM0 to store the result from
    // input channel A15 (Joystick X), in non-differential input mode
    // (non-differential means: only a single input pin)
    // The reference for Vref- and Vref+ are VSS and VCC respectively
    ADC14_configureConversionMemory(ADC_MEM0,
                                  ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                  ADC_INPUT_A15,                 // joystick X
                                  ADC_NONDIFFERENTIAL_INPUTS);

    // This selects the GPIO as analog input
    // A15 is multiplexed on GPIO port P6 pin PIN0
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,
                                               GPIO_PIN0,
                                               GPIO_PRIMARY_MODULE_FUNCTION);

    // This configures ADC_MEM0 to store the result from
    // input channel A15 (Joystick X), in non-differential input mode
    // (non-differential means: only a single input pin)
    // The reference for Vref- and Vref+ are VSS and VCC respectively
    ADC14_configureConversionMemory(ADC_MEM1,
                                    ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                    ADC_INPUT_A9,                 // joystick Y
                                    ADC_NONDIFFERENTIAL_INPUTS);

    // This selects the GPIO as analog input
    // A9 is multiplexed on GPIO port P4 pin PIN4
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,
                                               GPIO_PIN4,
                                               GPIO_TERTIARY_MODULE_FUNCTION);
}

void getSampleJoyStick(unsigned *X, unsigned *Y) {
    // ADC runs in continuous mode, we just read the conversion buffers
    *X = ADC14_getResult(ADC_MEM0);
    *Y = ADC14_getResult(ADC_MEM1);
}

int main(void) {
    WDT_A_hold(WDT_A_BASE);
    unsigned vx, vy;

    initADC();
    initJoyStick();
    InitLEDs();

    startADC();

    while (1)
    {
        getSampleJoyStick(&vx, &vy);

        if (vy > UP_THRESHOLD)
        {
            TurnON_Launchpad_Right_Red_LED();
            TurnOFF_Launchpad_Right_Blue_LED();
            TurnOFF_Launchpad_Right_Green_LED();
        }
        else if (vy < DOWN_THRESHOLD)
        {
            TurnOFF_Launchpad_Right_Red_LED();
            TurnON_Launchpad_Right_Blue_LED();
            TurnOFF_Launchpad_Right_Green_LED();
        }
        else
        {
            TurnON_Launchpad_Right_Green_LED();
            TurnOFF_Launchpad_Right_Red_LED();
            TurnOFF_Launchpad_Right_Blue_LED();
        }
    }
}

