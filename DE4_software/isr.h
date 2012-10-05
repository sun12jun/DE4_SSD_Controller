#ifndef _ISR_H_
#define	_ISR_H_

#include <stddef.h>

#include "sys/alt_alarm.h"
#include "sys/alt_warning.h"

#include "os/alt_sem.h"
#include "os/alt_flag.h"


#define ALTERA_AVALON_JTAG_UART_DEFAULT_TIMEOUT 10
#define ALTERA_AVALON_JTAG_UART_BUF_LEN 2048
/*
 * ALT_JTAG_UART_READ_RDY and ALT_JTAG_UART_WRITE_RDY are the bitmasks 
 * that define uC/OS-II event flags that are releated to this device.
 *
 * ALT_JTAG_UART_READ_RDY indicates that there is read data in the buffer 
 * ready to be processed. ALT_JTAG_UART_WRITE_RDY indicates that the transmitter is
 * ready for more data.
 */
#define ALT_JTAG_UART_READ_RDY  0x1
#define ALT_JTAG_UART_WRITE_RDY 0x2
#define ALT_JTAG_UART_TIMEOUT   0x4


typedef struct alt_avn_jtag_uart_state_s
{
  unsigned int base;

 
  unsigned int  timeout; /* Timeout until host is assumed inactive */
  alt_alarm     alarm;
  unsigned int  irq_enable;
  unsigned int  host_inactive;

  ALT_SEM      (read_lock)
  ALT_SEM      (write_lock)
  ALT_FLAG_GRP (events)
  
  /* The variables below are volatile because they are modified by the
   * interrupt routine.  Making them volatile and reading them atomically
   * means that we don't need any large critical sections.
   */
  volatile unsigned int rx_in;
  unsigned int  rx_out;
  unsigned int  tx_in;
  volatile unsigned int tx_out;
  char          rx_buf[ALTERA_AVALON_JTAG_UART_BUF_LEN];
  char          tx_buf[ALTERA_AVALON_JTAG_UART_BUF_LEN];

} alt_avn_jtag_uart_state;



volatile int edge_capture;
alt_avn_jtag_uart_state *jtag_uart_context;


void alt_avn_jtag_uart_init(alt_avn_jtag_uart_state* sp, int irq_controller_id, int irq);
void init_interrupts();


#endif
