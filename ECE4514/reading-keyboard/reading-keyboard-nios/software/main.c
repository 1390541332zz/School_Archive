#include <system.h>
#include <stdio.h>
#include "altera_avalon_jtag_uart_regs.h"

#define JTAG_UART_DATA ((volatile int*) JTAG_UART_0_BASE)

int main() {
  volatile unsigned *led_pio = (unsigned *) PIO_0_BASE;

  unsigned c;
  while (1) {
    c = *JTAG_UART_DATA;
    if (c & ALTERA_AVALON_JTAG_UART_DATA_RVALID_MSK) {
       *led_pio = (c & ALTERA_AVALON_JTAG_UART_DATA_DATA_MSK);
       if ((c & ALTERA_AVALON_JTAG_UART_DATA_DATA_MSK) == 'X')
          break;

       printf("char read: %c (hex %x)\n", c & ALTERA_AVALON_JTAG_UART_DATA_DATA_MSK, 
                                          c & ALTERA_AVALON_JTAG_UART_DATA_DATA_MSK);
      }
  }
  printf("Program complete\n");
  *led_pio = 0x0; // all off

  return 0;
}
