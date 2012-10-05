#ifndef _UART_H_
#define _UART_H_

void task_uart(void *parg);
void UART_FIFO_Read();
void UART_FIFO_Write();
void UART_Tx_Byte(INT8U chr);
void UART_Tx_Byte_CheckCR(INT8U chr);
INT8U UART_Rx_Byte();
void UART_Tx_Str(char *str);

#endif /* _UART_H_ */
