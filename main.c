#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"

// Global parameters with current application settings

typedef enum {black, red, green, yellow, blue, magenta, cyan, white} color_t;
typedef enum {baud9600, baud19200, baud38400, baud57600} UARTBaudRate_t;

//-----------------------------------------------------------------------
// Character Graphics API
//
// The 128*128 pixel screen is partitioned in a grid of 8 rows of 16 characters
// Each character is a plotted in a rectangle of 8 pixels (wide) by 16 pixels (high)
//
// The lower-level graphics functions are taken from the Texas Instruments Graphics Library
//
//            C Application        (this file)
//                   |
//                 GRLIB           (graphics library)
//                   |
//             CrystalFontz Driver (this project, LcdDriver directory)
//                   |
//                font data        (this project, fonts directory)

Graphics_Context g_sContext;

void InitGraphics() {
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    Graphics_initContext(&g_sContext,
                         &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
    GrContextFontSet(&g_sContext, &g_sFontCmtt16);
    Graphics_clearDisplay(&g_sContext);
}

void LCDClearDisplay() {
    Graphics_clearDisplay(&g_sContext);
}

void LCDDrawChar(unsigned row, unsigned col, int8_t c) {
    Graphics_drawString(&g_sContext,
                        &c,
                        1,
                        8 * (col % 16),
                        16 * (row % 8),
                        OPAQUE_TEXT);
}

//------------------------------------------
// UART API
//
// We are using EUSCI_A0, which is a user UART in MSP432 that is accessible
// on your laptop as 'XDS 110 Class Application/User UART'. It usually shows up as COM3.
//
// The low-level UART functions are taken from the MSP432 Driverlib, Chapter 24.
//
// The Baud Rate Computation Procedure is taken from the
// User Guide MSP432P4 Microcontroller, Chapter 24, page 915
//
//  Baud rate computation:
//  - System Clock SMCLK in MSP432P4 is 3MHz (Default)
//  - Baud Rate Division Factor N = 3MHz / Baudrate
//      Eg. N9600 = 30000000 / 9600 = 312.5
//  - If N>16 -> oversampling mode
//      Baud Rate Divider              UCBF  = FLOOR(N/16)     = INT(312.5/16)     = 19
//      First modulation stage select  UCBRF = FRAC(N/16) * 16 = FRAC(312.5/16)*16 = 8
//      Second modulation state select UCBRS = (table 24-4 based on FRAC(312.5))   = 0xAA

eUSCI_UART_Config uartConfig = {
     EUSCI_A_UART_CLOCKSOURCE_SMCLK,               // SMCLK Clock Source = 3MHz
     19,                                           // UCBR   = 19
     8,                                            // UCBRF  = 8
     0xAA,                                         // UCBRS  = 0xAA
     EUSCI_A_UART_NO_PARITY,                       // No Parity
     EUSCI_A_UART_LSB_FIRST,                       // LSB First
     EUSCI_A_UART_ONE_STOP_BIT,                    // One stop bit
     EUSCI_A_UART_MODE,                            // UART mode
     EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION // Oversampling
};

void InitUART() {
    UART_initModule(EUSCI_A0_BASE, &uartConfig);
    UART_enableModule(EUSCI_A0_BASE);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
        GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
}

bool UARTHasChar() {
    return (UART_getInterruptStatus (EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
                == EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);
}

uint8_t UARTGetChar() {
    if (UARTHasChar())
        return UART_receiveData(EUSCI_A0_BASE);
    else
        return 0;
}

bool UARTCanSend() {
    return (UART_getInterruptStatus (EUSCI_A0_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG)
                == EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG);
}

void UARTPutChar(uint8_t t) {
    while (!UARTCanSend()) ;
    UART_transmitData(EUSCI_A0_BASE,t);
}

//------------------------------------------
// Red LED API

void InitRedLED() {
    GPIO_setAsOutputPin    (GPIO_PORT_P1,    GPIO_PIN0);   // red LED on Launchpad
    GPIO_setOutputLowOnPin (GPIO_PORT_P1,    GPIO_PIN0);
}

void RedLEDToggle() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

//-----------------------------------------------------------------------

int main(void) {
    uint8_t c;

    WDT_A_hold(WDT_A_BASE);

    InitGraphics();
    InitUART();
    InitRedLED();

    LCDDrawChar(7,  0, 'R');
    LCDDrawChar(7,  1, '2');
    LCDDrawChar(7,  2, '!');
    LCDDrawChar(7,  3, ' ');
    LCDDrawChar(7,  4, 'W');
    LCDDrawChar(7,  5, 'H');
    LCDDrawChar(7,  6, 'E');
    LCDDrawChar(7,  7, 'R');
    LCDDrawChar(7,  8, 'E');
    LCDDrawChar(7,  9, ' ');
    LCDDrawChar(7, 10, 'A');
    LCDDrawChar(7, 11, 'R');
    LCDDrawChar(7, 12, 'E');
    LCDDrawChar(7, 13, ' ');
    LCDDrawChar(7, 14, 'U');
    LCDDrawChar(7, 15, '?');

    while (1) {
        if (UARTHasChar()) {
            c = UARTGetChar();
            RedLEDToggle();
            UARTPutChar(c);
        }
    }
}
