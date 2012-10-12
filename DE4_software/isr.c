#include <stdio.h>
#include <sys/alt_irq.h>
//#include <sys/alt_alarm.h>
#include <fcntl.h>
#include <altera_avalon_pio_regs.h>
#include <altera_avalon_jtag_uart_regs.h>
//#include "altera_avalon_dma.h"
#include <altera_avalon_dma_regs.h>
#include "includes.h"
#include "system.h"
#include "alt_ucosii_simple_error_check.h"
#include "alt_types.h"

#include "isr.h"


/*	semaphore declaration	*/
extern	OS_EVENT *SEM_REPORT;
extern	OS_EVENT *SEM_DMA0;
//extern	OS_EVENT *SEM_JTAG_UART;
//extern	OS_EVENT *SEM_UART;

/* initialization & interrupt registration fuction declaration */
static void init_button_pio();
static void init_dma0();
//static void init_jtag_uart();

/* interrupt handler declaration */
static void	handle_dma0_interrupt(void* context);
static void handle_button_interrupt(void* context);
//static void handle_uart_interrupt(void *context);
//static void handle_jtag_uart_interrupt(void* context);

/* peripheral control function declaration */
void dma_done_func(void* handle, void* data);
//static int jtag_uart_init(alt_avn_jtag_uart_state* sp, int flags);
//static int jtag_uart_close(alt_avn_jtag_uart_state* sp, int flags);
//static alt_u32 jtag_uart_timeout(void* context);


void init_interrupts()
{

	init_button_pio();
	init_dma0();

	//init_jtag_uart();
}

void dma_done_func(void* handle, void* data)
{
	dma_context->dma_done = 1;
	//OSSemPost(SEM_DMA0);
}

static void init_dma0()
{
	/* initialize interrupt context	*/
	if ((dma_context->txchan = alt_dma_txchan_open("/dev/dma_0")) == NULL)
	{
		printf ("Failed to open transmit channel\n");
		exit (1);
	}

	if ((dma_context->rxchan = alt_dma_rxchan_open("/dev/dma_0")) == NULL)
	{
		printf ("Failed to open receive channel\n");
		exit (1);
	}

	dma_context->src = DMA_0_READ_MASTER_SRC_ON_CHIP_BASE;
	dma_context->dst = DMA_0_WRITE_MASTER_DST_ON_CHIP_BASE;
	//dma_context->len = (1 << (DMA_0_LENGTHWIDTH - 1)) - 1; // 32KB
	dma_context->len = 32; // 32KB
	dma_context->dma_done = 0;
	dma_context->done_callback = dma_done_func;

	/* Halt any current transactions (reset the device) */
	//IOWR_ALTERA_AVALON_DMA_CONTROL (DMA_0_BASE, ALTERA_AVALON_DMA_CONTROL_SOFTWARERESET_MSK);
	IOWR_ALTERA_AVALON_DMA_CONTROL (DMA_0_BASE, ALTERA_AVALON_DMA_CONTROL_SOFTWARERESET_MSK);

	/* Set the default mode of the device (32 bit block reads and writes from/to memory). */
	IOWR_ALTERA_AVALON_DMA_CONTROL (DMA_0_BASE,
			ALTERA_AVALON_DMA_CONTROL_WORD_MSK      |
			ALTERA_AVALON_DMA_CONTROL_GO_MSK        |
			ALTERA_AVALON_DMA_CONTROL_I_EN_MSK      |
			ALTERA_AVALON_DMA_CONTROL_REEN_MSK      |
			ALTERA_AVALON_DMA_CONTROL_WEEN_MSK      |
			ALTERA_AVALON_DMA_CONTROL_LEEN_MSK);

	/* Clear any pending interrupts and the DONE flag */
	IOWR_ALTERA_AVALON_DMA_STATUS (DMA_0_BASE, 0);

	/* kick off the transfer */
	if(alt_dma_txchan_send(dma_context->txchan, 
			(void *)dma_context->src, 
			dma_context->len, 
			NULL, 
			NULL) < 0)
		printf("dma tx channel open error\n");

	if(alt_dma_rxchan_prepare(dma_context->rxchan, 
						   (void *)dma_context->dst, 
						   dma_context->len, 
						   dma_context->done_callback, 
						   NULL) < 0)
		printf("dma rx channel open error\n");


	/* Register the ISR. */
	alt_ic_isr_register(DMA_0_IRQ_INTERRUPT_CONTROLLER_ID,
			DMA_0_IRQ,
			handle_dma0_interrupt,
			(void*)dma_context, 0x0);
}

static void	handle_dma0_interrupt(void* context)
{
	alt_irq_context        cpu_sr;
	dma_context_state *dma_context_int = (dma_context_state *)context;

	dma_context_int->dma_done = 0;

	// relaunch dma transfer
	alt_dma_txchan_send(dma_context_int->txchan, 
						(void *)dma_context_int->src, 
						dma_context_int->len, 
						NULL, 
						NULL);

	alt_dma_rxchan_prepare(dma_context_int->rxchan, 
						   (void *)dma_context_int->dst, 
						   dma_context_int->len, 
						   dma_context_int->done_callback, 
						   NULL);

	cpu_sr = alt_irq_disable_all();
	alt_irq_enable_all(cpu_sr);

	OSSemPost(SEM_DMA0);
}

static void handle_button_interrupt(void* context)
{
	/* cast context to edge_capture's type. it is important that this
	   be declared volatile to avoid unwanted compiler optimization. */
	volatile int* edge_capture_ptr = (volatile int*) context;

	/*
	 * read the edge capture register on the button pio.
	 * store value.
	 */
	*edge_capture_ptr =	IORD_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_BASE);

	/* write to the edge capture register to reset it. */
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_BASE, 0);

	/* read the pio to delay isr exit. this is done to prevent a
	   spurious interrupt in systems with high processor -> pio
	   latency and fast interrupts. */
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_BASE);

	OSSemPost(SEM_REPORT);
}

/* Initialize the button_pio. */
static void init_button_pio()
{
	/* Recast the edge_capture pointer to match the
	   alt_irq_register() function prototype. */
	void* edge_capture_ptr = (void*) &edge_capture;
	/* Enable all 4 button interrupts. */
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTON_BASE, 0xf);
	/* Reset the edge capture register. */
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_BASE, 0x0);

	/* Register the ISR. */
	alt_ic_isr_register(BUTTON_IRQ_INTERRUPT_CONTROLLER_ID,
			BUTTON_IRQ,
			handle_button_interrupt,
			edge_capture_ptr, 0x0);
}

///* Initialize the jtag_uart */
//static void init_jtag_uart()
//{
//	jtag_uart_init(jtag_uart_context,
//			JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID,
//			JTAG_UART_IRQ);
//}
//
//// uart interrupt service routine
//static void handle_uart_interrupt(void *context)
//{
//	INT8U err;
//	INT32U control;
//
//	control = IORD_ALTERA_AVALON_JTAG_UART_CONTROL(JTAG_UART_BASE) & (ALTERA_AVALON_JTAG_UART_CONTROL_RI_MSK | ALTERA_AVALON_JTAG_UART_CONTROL_WI_MSK) ;
//
//	if ( control  )
//	{
//		volatile unsigned int *jtag_uart_context_ptr = (volatile unsigned int*) context;
//
//		*jtag_uart_context_ptr =  *jtag_uart_context_ptr & ~(ALTERA_AVALON_JTAG_UART_CONTROL_RE_MSK | ALTERA_AVALON_JTAG_UART_CONTROL_WE_MSK);
//
//		IOWR_ALTERA_AVALON_JTAG_UART_CONTROL(JTAG_UART_BASE, *jtag_uart_context_ptr);
//
//		err = OSSemPost(SEM_UART);
//		//alt_ucosii_check_return_code(err);
//	}
//
//}
//
//// jtag_uart interrupt service routine
//static void handle_jtag_uart_interrupt(void* context)
//{
//	alt_avn_jtag_uart_state* sp = (alt_avn_jtag_uart_state*) context;
//	unsigned int base = sp->base;
//
//
//	for ( ; ; )
//	{
//		unsigned int control = IORD_ALTERA_AVALON_JTAG_UART_CONTROL(base);
//
//		/* Return once nothing more to do */
//		if ((control & (ALTERA_AVALON_JTAG_UART_CONTROL_RI_MSK | ALTERA_AVALON_JTAG_UART_CONTROL_WI_MSK)) == 0)
//			break;
//
//		if (control & ALTERA_AVALON_JTAG_UART_CONTROL_RI_MSK)
//		{
//			/* process a read irq.  Start by assuming that there is data in the
//			 * receive FIFO (otherwise why would we have been interrupted?)
//			 */
//			unsigned int data = 1 << ALTERA_AVALON_JTAG_UART_DATA_RAVAIL_OFST;
//
//			for ( ; ; )
//			{
//				/* Check whether there is space in the buffer.  If not then we must not
//				 * read any characters from the buffer as they will be lost.
//				 */
//				unsigned int next = (sp->rx_in + 1) % ALTERA_AVALON_JTAG_UART_BUF_LEN;
//				if (next == sp->rx_out)
//					break;
//
//				/* Try to remove a character from the FIFO and find out whether there
//				 * are any more characters remaining.
//				 */
//				data = IORD_ALTERA_AVALON_JTAG_UART_DATA(base);
//
//				if ((data & ALTERA_AVALON_JTAG_UART_DATA_RVALID_MSK) == 0)
//					break;
//
//				sp->rx_buf[sp->rx_in] = (data & ALTERA_AVALON_JTAG_UART_DATA_DATA_MSK) >> ALTERA_AVALON_JTAG_UART_DATA_DATA_OFST;
//				sp->rx_in = (sp->rx_in + 1) % ALTERA_AVALON_JTAG_UART_BUF_LEN;
//
//				/* Post an event to notify jtag_uart_read that a character has been read */
//				ALT_FLAG_POST (sp->events, ALT_JTAG_UART_READ_RDY, OS_FLAG_SET);
//			}
//
//			if (data & ALTERA_AVALON_JTAG_UART_DATA_RAVAIL_MSK)
//			{
//				/* If there is still data available here then the buffer is full
//				 * so turn off receive interrupts until some space becomes available.
//				 */
//				sp->irq_enable &= ~ALTERA_AVALON_JTAG_UART_CONTROL_RE_MSK;
//				IOWR_ALTERA_AVALON_JTAG_UART_CONTROL(base, sp->irq_enable);
//
//				/* Dummy read to ensure IRQ is cleared prior to ISR completion */
//				IORD_ALTERA_AVALON_JTAG_UART_CONTROL(base);
//			}
//		}
//
//		if (control & ALTERA_AVALON_JTAG_UART_CONTROL_WI_MSK)
//		{
//			/* process a write irq */
//			unsigned int space = (control & ALTERA_AVALON_JTAG_UART_CONTROL_WSPACE_MSK) >> ALTERA_AVALON_JTAG_UART_CONTROL_WSPACE_OFST;
//
//			while (space > 0 && sp->tx_out != sp->tx_in)
//			{
//				IOWR_ALTERA_AVALON_JTAG_UART_DATA(base, sp->tx_buf[sp->tx_out]);
//
//				sp->tx_out = (sp->tx_out + 1) % ALTERA_AVALON_JTAG_UART_BUF_LEN;
//
//				/* Post an event to notify jtag_uart_write that a character has been written */
//				ALT_FLAG_POST (sp->events, ALT_JTAG_UART_WRITE_RDY, OS_FLAG_SET);
//				//ALT_SEM_POST (SEM_JTAG_UART_WRITE);
//
//				space--;
//			}
//
//			if (space > 0)
//			{
//				/* If we don't have any more data available then turn off the TX interrupt */
//				sp->irq_enable &= ~ALTERA_AVALON_JTAG_UART_CONTROL_WE_MSK;
//				IOWR_ALTERA_AVALON_JTAG_UART_CONTROL(sp->base, sp->irq_enable);
//
//				/* Dummy read to ensure IRQ is cleared prior to ISR completion */
//				IORD_ALTERA_AVALON_JTAG_UART_CONTROL(base);
//			}
//		}
//	}
//}
//
//void jtag_uart_init(alt_avn_jtag_uart_state* sp, int irq_controller_id, int irq)
//{
//
//	sp->base = JTAG_UART_BASE;
//	sp->timeout = ALTERA_AVALON_JTAG_UART_DEFAULT_TIMEOUT;
//	//sp->tx_in = 1;
//	//sp->tx_out = 0;
//
//	/////////////////////////////////////
//
//	ALT_FLAG_CREATE(&sp->events, 0);
//	ALT_SEM_CREATE(&sp->read_lock, 1);
//	ALT_SEM_CREATE(&sp->write_lock, 1);
//
//
//	/* enable read interrupts at the device */
//	sp->irq_enable = ALTERA_AVALON_JTAG_UART_CONTROL_RE_MSK;
//
//	IOWR_ALTERA_AVALON_JTAG_UART_CONTROL(sp->base, sp->irq_enable);
//
//	/* register the interrupt handler */
//	alt_ic_isr_register(irq_controller_id, irq, handle_jtag_uart_interrupt,
//			sp, NULL);
//
//	/* Register an alarm to go off every second to check for presence of host */
//	sp->host_inactive = 0;
//
//	if (alt_alarm_start(&sp->alarm, alt_ticks_per_second(),
//				&jtag_uart_timeout, sp) < 0)
//	{
//		/* If we can't set the alarm then record "don't know if host present"
//		 * and behave as though the host is present.
//		 */
//		sp->timeout = INT_MAX;
//	}
//}
//
//
//
///*
// * Timeout routine is called every second
// */
//
//static alt_u32 jtag_uart_timeout(void* context)
//{
//  alt_avn_jtag_uart_state* sp = (alt_avn_jtag_uart_state *) context;
//
//  unsigned int control = IORD_ALTERA_AVALON_JTAG_UART_CONTROL(sp->base);
//
//  if (control & ALTERA_AVALON_JTAG_UART_CONTROL_AC_MSK)
//  {
//    IOWR_ALTERA_AVALON_JTAG_UART_CONTROL(sp->base, sp->irq_enable | ALTERA_AVALON_JTAG_UART_CONTROL_AC_MSK);
//    sp->host_inactive = 0;
//  }
//  else if (sp->host_inactive < INT_MAX - 2) {
//    sp->host_inactive++;
//
//    if (sp->host_inactive >= sp->timeout) {
//      /* Post an event to indicate host is inactive (for jtag_uart_read */
//      ALT_FLAG_POST (sp->events, ALT_JTAG_UART_TIMEOUT, OS_FLAG_SET);
//    }
//  }
//
//  return alt_ticks_per_second();
//}
//
///*
// * The close() routine is implemented to drain the JTAG UART transmit buffer
// * when not in "small" mode. This routine will wait for transimt data to be
// * emptied unless a timeout from host-activity occurs. If the driver flags
// * have been set to non-blocking mode, this routine will exit immediately if
// * any data remains. This routine should be called indirectly (i.e. though
// * the C library close() routine) so that the file descriptor associated
// * with the relevant stream (i.e. stdout) can be closed as well. This routine
// * does not manage file descriptors.
// *
// * The close routine is not implemented for the small driver; instead it will
// * map to null. This is because the small driver simply waits while characters
// * are transmitted; there is no interrupt-serviced buffer to empty
// */
//static int jtag_uart_close(alt_avn_jtag_uart_state* sp, int flags)
//{
//  /*
//   * Wait for all transmit data to be emptied by the JTAG UART ISR, or
//   * for a host-inactivity timeout, in which case transmit data will be lost
//   */
//  while ( (sp->tx_out != sp->tx_in) && (sp->host_inactive < sp->timeout) ) {
//    if (flags & O_NONBLOCK) {
//      return -EWOULDBLOCK;
//    }
//  }
//
//  return 0;
//}
