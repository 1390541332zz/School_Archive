#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
#include <stdbool.h>
// Global parameters with current application settings

#define CLKSPD 3000000
#define X_SIZE 16
#define Y_SIZE 16

typedef enum {
    black = 0, 
    red = 1, 
    green = 2, 
    yellow = 3, 
    blue = 4, 
    magenta = 5, 
    cyan = 6, 
    white = 7
} color_t;

typedef enum {
    baud9600 = 0,
    baud19200 = 1,
    baud38400 = 2,
    baud57600 = 3
} UARTBaudRate_t;

struct lcd_state {
    uint8_t x;
    uint8_t y;
    color_t fg;
    color_t bg;
    uint16_t n;
    UARTBaudRate_t bd;
};

struct lcd_state lcd_s = {
    0,
    0,
    white,
    blue,
    0,
    baud9600
};

int8_t bd_txt[4][5] = { " 9600", "19200", "38400", "57600" };


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

// set_uart_bd(): Sets the new baud rate.
void set_uart_bd(UARTBaudRate_t t) {
    uint_fast16_t baud = 0;
    switch(t) {
    case baud9600:
        baud = 9600;
        uartConfig.secondModReg = 0xAA;
        break;
    case baud19200:
        baud = 19200;
        uartConfig.secondModReg = 0xDD;
        break;
    case baud38400:
        baud = 38400;
        uartConfig.secondModReg = 0xF7;
        break;
    case baud57600:
        baud = 57600;
        uartConfig.secondModReg = 0x44;
        break;
    }
    uartConfig.clockPrescalar = (CLKSPD / baud) / 16;
    uartConfig.firstModReg  = (CLKSPD / baud) % 16;
    UART_initModule(EUSCI_A0_BASE, &uartConfig);
    UART_enableModule(EUSCI_A0_BASE);
    lcd_s.bd = t;
}

// cycle_uart_bd(): Cycles the Baud Rate. 9600->19200->38400->57600->9600->...
void cycle_uart_bd() {
    ++(lcd_s.bd);
    if (lcd_s.bd > baud57600) lcd_s.bd = baud9600;
    set_uart_bd(lcd_s.bd);
}


//------------------------------------------
// TIMER API
//

void InitTimer() {
    MAP_Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1,
            TIMER32_32BIT, TIMER32_FREE_RUN_MODE);
    MAP_Timer32_initModule(TIMER32_1_BASE, TIMER32_PRESCALER_1,
            TIMER32_32BIT, TIMER32_FREE_RUN_MODE);
}

void Timer222msStartOneShot() {
    Timer32_startTimer(TIMER32_0_BASE, true);
    Timer32_setCount(TIMER32_0_BASE, 666000);
}

int Timer222msExpiredOneShot() {
    return Timer32_getValue(TIMER32_0_BASE) == 0;
}

void TimerDebounceStartOneShot() {
    Timer32_startTimer(TIMER32_1_BASE, true);
    Timer32_setCount(TIMER32_1_BASE, 600000);
}

int TimerDebounceExpiredOneShot() {
    return Timer32_getValue(TIMER32_1_BASE) == 0;
}

//------------------------------------------
// Debounce FSM for S2
//

bool BounceFSM(bool b) {
    static bool started = false;
    static bool lastb = false;

    if (b && !started) {
        TimerDebounceStartOneShot();
        started = true;
    } else if (!b && lastb && TimerDebounceExpiredOneShot()) {
        TimerDebounceStartOneShot();
        lastb = b;
        return true;
    }
    lastb = b;
    return false;
}

//------------------------------------------
// BUTTON API
//

void InitButtonS2() {
    GPIO_setAsInputPin (GPIO_PORT_P5, GPIO_PIN1); // upper switch S2 on BoostXL
}

void InitButtonS1() {
    GPIO_setAsInputPin (GPIO_PORT_P3, GPIO_PIN5); // upper switch S1 on BoostXL
}

int ButtonS2Pressed() {
    return (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == 0);
}

int ButtonS1Pressed() {
    return (GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN5) == 0);
}

//------------------------------------------
// LED API

// init_led(): Configures the LED
void init_led() {
    GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN6);
    GPIO_setAsOutputPin    (GPIO_PORT_P2,    GPIO_PIN4);
    GPIO_setAsOutputPin    (GPIO_PORT_P5,    GPIO_PIN6);
    GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN6);
    GPIO_setOutputLowOnPin (GPIO_PORT_P2,    GPIO_PIN4);
    GPIO_setOutputLowOnPin (GPIO_PORT_P5,    GPIO_PIN6);
}

// set_led(): Sets the LED with the color c (black is off)
void set_led(color_t c) {
    switch(c) {
        case black:
            GPIO_setOutputLowOnPin (GPIO_PORT_P2, GPIO_PIN6);
            GPIO_setOutputLowOnPin (GPIO_PORT_P2, GPIO_PIN4);
            GPIO_setOutputLowOnPin (GPIO_PORT_P5, GPIO_PIN6);
            break;
        case white:
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN6);
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);
            GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN6);
            break;
        case red:
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN6);
            GPIO_setOutputLowOnPin (GPIO_PORT_P2, GPIO_PIN4);
            GPIO_setOutputLowOnPin (GPIO_PORT_P5, GPIO_PIN6);
            break;
        case blue:
            GPIO_setOutputLowOnPin (GPIO_PORT_P2, GPIO_PIN6);
            GPIO_setOutputLowOnPin (GPIO_PORT_P2, GPIO_PIN4);
            GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN6);
            break;
        case green:
            GPIO_setOutputLowOnPin (GPIO_PORT_P2, GPIO_PIN6);
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);
            GPIO_setOutputLowOnPin (GPIO_PORT_P5, GPIO_PIN6);
            break;
    }
}

// trigger_222led(): Starts a 222ms timer and the LED with color c
void trigger_222led(color_t c) {
    Timer222msStartOneShot();
    set_led(c);
}

// disable_222led(): Disables the LED.
void disable_222led() {
    set_led(black);
}

//-----------------------------------------------------------------------
// lcd_clear(): Resets the text stream for the display.
void lcd_clear() {
    lcd_s.x = 0;
    lcd_s.y = 0;
    Graphics_clearDisplay(&g_sContext);
}

// conv_color(): Converts a color_t into a GraphicsLib Color
int32_t conv_color(color_t c) {
    switch (c) {
        case black:   return GRAPHICS_COLOR_BLACK;
        case red:     return GRAPHICS_COLOR_RED;
        case green:   return GRAPHICS_COLOR_GREEN;
        case yellow:  return GRAPHICS_COLOR_YELLOW;
        case blue:    return GRAPHICS_COLOR_BLUE;
        case magenta: return GRAPHICS_COLOR_MAGENTA;
        case cyan:    return GRAPHICS_COLOR_CYAN;
        case white:   return GRAPHICS_COLOR_WHITE;
        default:      return 0;
    }
}

// lcd_set_fg(): Sets the foreground color
void lcd_set_fg(color_t c) {
    Graphics_setForegroundColor(&g_sContext, conv_color(c));
    lcd_s.fg = c;
}

// lcd_set_bg(): Sets the foreground color
void lcd_set_bg(color_t c) {
    Graphics_setBackgroundColor(&g_sContext, conv_color(c));
    lcd_s.bg = c;
}

// lcd_out(): A basic text stream for the display.
void lcd_out(int8_t c) {
    LCDDrawChar(lcd_s.y, lcd_s.x, c);
    UARTPutChar(c);
    ++(lcd_s.x);
    if (lcd_s.x >= X_SIZE) {
        lcd_s.x = 0;
        ++(lcd_s.y);
    }
    if (lcd_s.y >= Y_SIZE) {
        lcd_s.y = 0;
    }
}

// status(): Prints the status text
void status() {
    uint16_t n = lcd_s.n;
    lcd_clear();
    Graphics_setForegroundColor(&g_sContext, conv_color(white));
    Graphics_setBackgroundColor(&g_sContext, conv_color(black));
    lcd_out('b');
    lcd_out('d');
    int i = 0;
    while (i < 5) lcd_out(bd_txt[lcd_s.bd][i++]);
    lcd_out(' '); lcd_out(' ');
    lcd_out('f');
    lcd_out('g');
    lcd_out(lcd_s.fg + 0x30);
    lcd_out(' ');
    lcd_out('b');
    lcd_out('g');
    lcd_out(lcd_s.bg + 0x30);
    lcd_out('n');
    lcd_out(' ');
    lcd_out((n / 1000) + 0x30);
    n = n % 1000;
    lcd_out((n / 100) + 0x30);
    n = n % 100;
    lcd_out((n / 10) + 0x30);
    n = n % 10;
    lcd_out(n + 0x30);
    while (lcd_s.y != 2) lcd_out(' ');

    Graphics_setForegroundColor(&g_sContext, conv_color(lcd_s.fg));
    Graphics_setBackgroundColor(&g_sContext, conv_color(lcd_s.bg));
}

// parse_chars(): Parses the input text for commands and led side effects
void parse_chars(int8_t c) {
    static uint8_t stage = 0;
    static bool is_fg = false;
    static color_t option = black;
    ++(lcd_s.n);
    if (lcd_s.n > 9999) lcd_s.n = 0;

    //Tracks incoming commands
    if (c == '#' && stage == 0) {
        ++stage;
    } else if (c == 'f' && stage == 1) {
        ++stage;
        is_fg = true;
    } else if (c == 'b' && stage == 1) {
        ++stage;
        is_fg = false;
    } else if (c >= '0' && c <= '7' && stage == 2) {
        ++stage;
        option = c - 0x30;
    } else {
        if (stage == 2) {
            lcd_out('#');
            lcd_out(is_fg ? 'f' : 'b');
        } else if (stage == 1) {
            lcd_out('#');
        }
        stage = 0;
        lcd_out(c);
    }
    //Trigger Command
    if (stage == 3 && is_fg) {
        stage = 0;
        lcd_set_fg(option);
    } else if (stage == 2 && !is_fg) {
        stage = 0;
        lcd_set_bg(option);
    }

    //Flash LED
    if (c == '#') {
        trigger_222led(white);
    } else if (c >= '0' && c <= '9') {
        trigger_222led(red);
    } else if (  (c >= 'A' && c <= 'Z')
              || (c >= 'a' && c <= 'z')) {
        trigger_222led(blue);
    } else {
        trigger_222led(green);
    }
}

int main(void) {
    uint8_t c;

    WDT_A_hold(WDT_A_BASE);

    InitGraphics();
    InitButtonS2();
    InitButtonS1();
    InitUART();
    InitTimer();
    init_led();

    while (1) {
        if (ButtonS2Pressed()) status();
        if (BounceFSM(ButtonS1Pressed())) cycle_uart_bd();
        if (Timer222msExpiredOneShot()) disable_222led();
        if (UARTHasChar()) {
            c = UARTGetChar();
            parse_chars(c);
        }
    }
}
