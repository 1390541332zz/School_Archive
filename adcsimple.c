#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>

void initADC() {
    ADC14_enableModule();

    // This sets the conversion clock to 3MHz
    ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC,
                     ADC_PREDIVIDER_1,
                     ADC_DIVIDER_1,
                     0
                     );

    // This configures the ADC to store output results
    // in only one single output register, ADC_MEM0.
    // This is useful when we convert only one single input channel
    ADC14_configureSingleSampleMode(ADC_MEM0, true);

    // This configures the ADC in manual conversion mode
    // Software will start each conversion.
    ADC14_enableSampleTimer(ADC_MANUAL_ITERATION);
}

void initJoyStickX() {

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
}

unsigned getSampleJoyStickX() {
    // This starts the conversion process
    // The S/H will be followed by SAR conversion
    ADC14_enableConversion();
    ADC14_toggleConversionTrigger();

    // We wait for the ADC to complete
    while (ADC14_isBusy()) ;

    // and we read the output result from buffer ADC_MEM0
    return ADC14_getResult(ADC_MEM0);
}


int main(void) {
    WDT_A_hold(WDT_A_BASE);
    unsigned v;

    initADC();
    initJoyStickX();

    while (1) {
        v = getSampleJoyStickX();
        printf("%x\n", v);
    }
}
