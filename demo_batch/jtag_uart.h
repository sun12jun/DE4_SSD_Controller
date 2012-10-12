#ifndef _JTAG_UART_H_
#define	_JTAG_UART_H_

#include "isr.h"
#include "includes.h"

int alt_avn_jtag_uart_read(alt_avn_jtag_uart_state* sp, char * buffer, int space, int flags);
int alt_avn_jtag_uart_write(alt_avn_jtag_uart_state* sp, const char * ptr, int count, int flags);

void jtag_uart_tx_byte(INT8U chr);
void jtag_uart_tx_byte_checkcr(INT8U chr);
void jtag_uart_tx_str(char *str);
INT8U jtag_uart_rx_byte();

#endif

