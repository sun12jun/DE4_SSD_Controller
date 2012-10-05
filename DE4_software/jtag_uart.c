
/********************************************************************************
 *		jtag_uart.c	Ver	0.1															*
 ********************************************************************************/
#include "includes.h"
#include "jtag_uart.h"
#include "isr.h"
#include <altera_avalon_jtag_uart_regs.h>
#include <fcntl.h>
#include <string.h>


//-------------------------------------------------------------------------------
void jtag_uart_tx_byte(INT8U chr)
{
	INT8U err;

	char c = (char)(chr & 0xFF);
	alt_avn_jtag_uart_write(jtag_uart_context, &c, 1, 0);
}

//-------------------------------------------------------------------------------
void jtag_uart_tx_byte_checkcr(INT8U chr)
{
	jtag_uart_tx_byte(chr);
	if(chr=='\n')
		jtag_uart_tx_byte('\r');
}

//-------------------------------------------------------------------------------
void jtag_uart_tx_str(char *str)
{
	INT8U *ustr	= (INT8U*)str;

	while(*ustr != '\0')
		jtag_uart_tx_byte_checkcr(*(ustr++));
}

//-------------------------------------------------------------------------------
INT8U jtag_uart_rx_byte()
{
	char c;


	if(alt_avn_jtag_uart_read(jtag_uart_context, &c, 1, 0) <= 0)
		return -1;
	else
		return (INT8U)c;
}


//-------------------------------------------------------------------------------
int alt_avn_jtag_uart_read(alt_avn_jtag_uart_state* sp, 
		char * buffer, int space, int flags)
{
	char * ptr = buffer;

	alt_irq_context context;
	unsigned int n;

	/*
	 * When running in a multi threaded environment, obtain the "read_lock"
	 * semaphore. This ensures that reading from the device is thread-safe.
	 */
	ALT_SEM_PEND (sp->read_lock, 0);

	while (space > 0)
	{
		unsigned int in, out;

		/* Read as much data as possible */
		do
		{
			in  = sp->rx_in;
			out = sp->rx_out;

			if (in >= out)
				n = in - out;
			else
				n = ALTERA_AVALON_JTAG_UART_BUF_LEN - out;

			if (n == 0)
				break; /* No more data available */

			if (n > space)
				n = space;

			memcpy(ptr, sp->rx_buf + out, n);
			ptr   += n;
			space -= n;

			sp->rx_out = (out + n) % ALTERA_AVALON_JTAG_UART_BUF_LEN;
		}
		while (space > 0);

		/* If we read any data then return it */
		if (ptr != buffer)
			break;

		/* If in non-blocking mode then return error */
		if (flags & O_NONBLOCK)
			break;

		/* OS Present: Pend on a flag if the OS is running, otherwise spin */
		if(OSRunning == OS_TRUE) {
			/*
			 * When running in a multi-threaded mode, we pend on the read event
			 * flag set and timeout event flag set in the isr. This avoids wasting CPU
			 * cycles waiting in this thread, when we could be doing something more
			 * profitable elsewhere.
			 */
			ALT_FLAG_PEND (sp->events,
					ALT_JTAG_UART_READ_RDY | ALT_JTAG_UART_TIMEOUT,
					OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME,
					0);
		}
		else {
			/* Spin until more data arrives or until host disconnects */
			while (in == sp->rx_in && sp->host_inactive < sp->timeout)
				;
		}


		if (in == sp->rx_in)
			break;
	}

	/*
	 * Now that access to the circular buffer is complete, release the read
	 * semaphore so that other threads can access the buffer.
	 */

	ALT_SEM_POST (sp->read_lock);

	if (ptr != buffer)
	{
		/* If we read any data then there is space in the buffer so enable interrupts */
		context = alt_irq_disable_all();
		sp->irq_enable |= ALTERA_AVALON_JTAG_UART_CONTROL_RE_MSK;
		IOWR_ALTERA_AVALON_JTAG_UART_CONTROL(sp->base, sp->irq_enable);
		alt_irq_enable_all(context);
	}

	if (ptr != buffer)
		return ptr - buffer;
	else if (flags & O_NONBLOCK)
		return -EWOULDBLOCK;
	else
		return -EIO;
}


int alt_avn_jtag_uart_write(alt_avn_jtag_uart_state* sp, 
		const char * ptr, int count, int flags)
{
	/* Remove warning at optimisation level 03 by seting out to 0 */
	unsigned int in, out=0;
	unsigned int n;
	alt_irq_context context;

	const char * start = ptr;

	/*
	 * When running in a multi threaded environment, obtain the "write_lock"
	 * semaphore. This ensures that writing to the device is thread-safe.
	 */
	ALT_SEM_PEND (sp->write_lock, 0);

	do
	{
		/* Copy as much as we can into the transmit buffer */
		while (count > 0)
		{
			/* We need a stable value of the out pointer to calculate the space available */
			in  = sp->tx_in;
			out = sp->tx_out;

			if (in < out)
				n = out - 1 - in;
			else if (out > 0)
				n = ALTERA_AVALON_JTAG_UART_BUF_LEN - in;
			else
				n = ALTERA_AVALON_JTAG_UART_BUF_LEN - 1 - in;

			if (n == 0)
				break;

			if (n > count)
				n = count;

			memcpy(sp->tx_buf + in, ptr, n);
			ptr   += n;
			count -= n;

			sp->tx_in = (in + n) % ALTERA_AVALON_JTAG_UART_BUF_LEN;
		}

		/*
		 * If interrupts are disabled then we could transmit here, we only need 
		 * to enable interrupts if there is no space left in the FIFO
		 *
		 * For now kick the interrupt routine every time to make it transmit 
		 * the data 
		 */
		context = alt_irq_disable_all();
		sp->irq_enable |= ALTERA_AVALON_JTAG_UART_CONTROL_WE_MSK;
		IOWR_ALTERA_AVALON_JTAG_UART_CONTROL(sp->base, sp->irq_enable);
		alt_irq_enable_all(context);

		/* 
		 * If there is any data left then either return now or block until 
		 * some has been sent 
		 */
		/* consider: test whether there is anything there while doing this and delay for at most 2s. */
		if (count > 0)
		{
			if (flags & O_NONBLOCK)
				break;

			/* OS Present: Pend on a flag if the OS is running, otherwise spin */
			if(OSRunning == OS_TRUE) {
				/*
				 * When running in a multi-threaded mode, we pend on the write event
				 * flag set or the timeout flag in the isr. This avoids wasting CPU
				 * cycles waiting in this thread, when we could be doing something
				 * more profitable elsewhere.
				 */
				ALT_FLAG_PEND (sp->events,
						ALT_JTAG_UART_WRITE_RDY | ALT_JTAG_UART_TIMEOUT,
						OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME,
						0);
			}
			else {
				/*
				 * OS not running: Wait for data to be removed from buffer.
				 * Once the interrupt routine has removed some data then we
				 * will be able to insert some more.
				 */
				while (out == sp->tx_out && sp->host_inactive < sp->timeout)
					;
			}

			if (out == sp->tx_out)
				break;
		}
	}
	while (count > 0);

	/*
	 * Now that access to the circular buffer is complete, release the write
	 * semaphore so that other threads can access the buffer.
	 */
	ALT_SEM_POST (sp->write_lock);

	if (ptr != start)
		return ptr - start;
	else if (flags & O_NONBLOCK)
		return -EWOULDBLOCK;
	else
		return -EIO; /* Host not connected */
}

