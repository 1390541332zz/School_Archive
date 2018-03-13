#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <LED_HAL.h>
#include <Buttons_HAL.h>
#include <Timer_HAL.h>

// The below are toggling periods assigned to each of the LEDs
// These times are in microseconds, us
#define BOOSTER_LED_TIMING          50000       // 0.05 seconds
#define LAUNCHPAD_RIGHT_LED_TIMING  500000      // 0.5 seconds
#define LAUNCHPAD_LEFT_LED_TIMING   5000000     // 5 seconds

#define FAST 100000
#define SLOW 1000000



/* This main shows a demo where each LED blinks at different speeds.
 * Different LEDs blink at once every 0.05, 0.5 or 5 seconds
 */
// Comment out this main and uncomment the other main below to see the other demo
int main(void)
{
    WDT_A_hold(WDT_A_BASE);
    InitButtons();
    InitLEDs();
    InitHWTimers();



    OneShotSWTimer_t OST1, OST2, OST3;
    uint64_t waitCycles;

    waitCycles = WaitCycles(TIMER32_1_BASE, LAUNCHPAD_LEFT_LED_TIMING);
    InitOneShotSWTimer(&OST1,
                       TIMER32_1_BASE,
                       waitCycles);

    waitCycles = WaitCycles(TIMER32_1_BASE, LAUNCHPAD_RIGHT_LED_TIMING);
    InitOneShotSWTimer(&OST2,
                       TIMER32_1_BASE,
                       waitCycles);

    waitCycles = WaitCycles(TIMER32_1_BASE, BOOSTER_LED_TIMING);
    InitOneShotSWTimer(&OST3,
                       TIMER32_1_BASE,
                       waitCycles);

    StartOneShotSWTimer(&OST1);
    StartOneShotSWTimer(&OST2);
    StartOneShotSWTimer(&OST3);



     while (1)
     {
       if (OneShotSWTimerExpired(&OST1))
       {
            Toggle_Launchpad_Left_LED();
            StartOneShotSWTimer(&OST1);
       }

       if (OneShotSWTimerExpired(&OST2))
       {
           Toggle_Launchpad_Right_Green_LED();
           StartOneShotSWTimer(&OST2);
       }

       if (OneShotSWTimerExpired(&OST3))
       {
           Toggle_Booster_LED();
           StartOneShotSWTimer(&OST3);
       }

     }
 }




/* This main shows a demo where the beginning status is as follows
 * 1) The red LED on the booster is dark.
 * 2) The left LED on the launchpad blinks once per second
 * The application responds to two stimuli:
 * 1) Pushing the top button of the booster toggles the booster red LED
 * 2) Pushing the bottom button of the booster toggles the blinking speed of the left Launchpad LED between fast and slow.
 */

// In order to check the other demo on top, uncomment the below function and comment the above main

/*
int main(void) {
    WDT_A_hold(WDT_A_BASE);
    InitButtons();
    InitLEDs();
    InitHWTimers();


    int speed = 0;
    OneShotSWTimer_t OST;
    uint64_t fastCycles;
    uint64_t slowCycles;

    fastCycles = WaitCycles(TIMER32_1_BASE, FAST);
    slowCycles = WaitCycles(TIMER32_1_BASE, SLOW);

    InitOneShotSWTimer(&OST, TIMER32_1_BASE, slowCycles);

    while (1) {

        if (Booster_Top_Button_Pushed())
            Toggle_Booster_LED();

        if (Booster_Bottom_Button_Pushed())
        {
            if (!speed)
            {
                InitOneShotSWTimer(&OST, TIMER32_1_BASE, slowCycles);
                speed = 1;
            }
            else
            {
                InitOneShotSWTimer(&OST, TIMER32_1_BASE, fastCycles);
                speed = 0;
            }

        }

        if (OneShotSWTimerExpired(&OST))
        {
            Toggle_Launchpad_Left_LED();
            StartOneShotSWTimer(&OST);
        }
    }
}
*/
