#include <stdio.h>
#include <unistd.h>           // close
#include <fcntl.h>            // O_RDWR, O_SYNC
#include <sys/mman.h>         // PROT_READ, PROT_WRITE

#include "socal/socal.h"      // alt_write
#include "socal/hps.h"
#include "socal/alt_gpio.h"

#include "hps_0.h"            // definitions for LED_PIO and SWITCH_PIO

#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

#include <termios.h>

static struct termios oldt;
int atexit(void (*func)(void));

void restore_terminal_settings(void)
{
    tcsetattr(0, TCSANOW, &oldt);  /* Apply saved settings */
}

void disable_waiting_for_enter(void)
{
    struct termios newt;

    /* Make terminal read 1 char at a time */
    tcgetattr(0, &oldt);  /* Save terminal settings */
    newt = oldt;  /* Init new settings */
    newt.c_lflag &= ~(ICANON | ECHO);  /* Change settings */
    tcsetattr(0, TCSANOW, &newt);  /* Apply settings */
    atexit(restore_terminal_settings); /* Make sure settings will be restored when program ends  */
}


int main(int argc, char **argv) {
  void *virtual_base;
  volatile unsigned long *led_pio;
  int fd;

  if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
    printf( "ERROR: could not open \"/dev/mem\"...\n" );
    return( 1 );
  }
  virtual_base = mmap( NULL,
		       HW_REGS_SPAN,
		       ( PROT_READ | PROT_WRITE ),
		       MAP_SHARED,
		       fd,
		       HW_REGS_BASE );	
  if( virtual_base == MAP_FAILED ) {
    printf( "ERROR: mmap() failed...\n" );
    close( fd );
    return(1);
  }
  
  led_pio = virtual_base +
    ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + LED_PIO_0_BASE) & ( unsigned long)( HW_REGS_MASK ) );

  char c;
  disable_waiting_for_enter();
  while (1) {
    c = getchar();
    *led_pio = c;
    if (c == 'X')
      break;
    printf("char read: %c (hex %x)\n", c, c);
  }

  *led_pio = 0x0; // all off

  if( munmap( virtual_base, HW_REGS_SPAN ) != 0 ) {
    printf( "ERROR: munmap() failed...\n" );
    close( fd );
    return( 1 );
    
  }
  close( fd );
  return 0;
}
