/********************************************************************************
 *		Uart.c	Ver	0.1															*
 ********************************************************************************/

#include <includes.h>
#include "uart.h"
#include "isr.h"
#include <altera_avalon_jtag_uart_regs.h>

#define UartMem_Size	4096

#define TxQue0_Size	4096
#define RxQue0_Size	1024

//-------------------------------------------------------------------------------
//	Queue Structure Definition
//-------------------------------------------------------------------------------
OS_MEM *UartMemPart;
INT8U UartMem[UartMem_Size][4];

OS_EVENT *TxQue0;
void *TxQue0Tbl[TxQue0_Size];
OS_EVENT *RxQue0;
void *RxQue0Tbl[RxQue0_Size];

//-------------------------------------------------------------------------------
//	Semaphore Declaration
//-------------------------------------------------------------------------------
extern OS_EVENT *SEM_UART;          

//-------------------------------------------------------------------------------

void task_uart(void *parg)
{
	INT8U err;
	INT32U control;
	
	UartMemPart = OSMemCreate(&UartMem[0][0],UartMem_Size,4,&err);
	
	TxQue0 = OSQCreate(&TxQue0Tbl[0],TxQue0_Size);
	RxQue0 = OSQCreate(&RxQue0Tbl[0],RxQue0_Size);
	

	while(1){
		OSSemPend(SEM_UART,0,&err);

		control = IORD_ALTERA_AVALON_JTAG_UART_CONTROL(JTAG_UART_BASE) & (ALTERA_AVALON_JTAG_UART_CONTROL_RI_MSK | ALTERA_AVALON_JTAG_UART_CONTROL_WI_MSK);

		switch(control){
			//case 0x00000200:
			case ALTERA_AVALON_JTAG_UART_CONTROL_WI_MSK:
				UART_FIFO_Write();
				break;	
			//case 0x00000100:
			case ALTERA_AVALON_JTAG_UART_CONTROL_RI_MSK:
				UART_FIFO_Read();
				break;
			default :
				break;	
		}
	}
}
//-------------------------------------------------------------------------------

void UART_FIFO_Read()
{
	INT8U *msg, err;
	INT32U irq_state, i;
	
	i = 0;
	while( (IORD_ALTERA_AVALON_JTAG_UART_DATA(JTAG_UART_BASE) & ALTERA_AVALON_JTAG_UART_DATA_RVALID_MSK) & \
		   !(IORD_ALTERA_AVALON_JTAG_UART_DATA(JTAG_UART_BASE) & ALTERA_AVALON_JTAG_UART_DATA_RAVAIL_MSK) )
	{
		msg = (INT8U *)OSMemGet(UartMemPart, &err);
		*msg = (INT8U)(IORD_ALTERA_AVALON_JTAG_UART_DATA(JTAG_UART_BASE) & ALTERA_AVALON_JTAG_UART_DATA_DATA_MSK);
		OSQPost(RxQue0, msg);
		i++;
	}

	/* If we read any data then there is space in the buffer so enable interrupts */
	if(i != 0)
	{
		irq_state = IORD_ALTERA_AVALON_JTAG_UART_CONTROL(JTAG_UART_BASE) | ALTERA_AVALON_JTAG_UART_CONTROL_RE_MSK;
		IOWR_ALTERA_AVALON_JTAG_UART_CONTROL(JTAG_UART_BASE, irq_state);
		alt_irq_enable_all(jtag_uart_context);
	}

}
//-------------------------------------------------------------------------------

void UART_FIFO_Write()
{
	INT8U *msg, err;
	INT32U irq_state, i;

	i = 0;
    while(!(IORD_ALTERA_AVALON_JTAG_UART_CONTROL(JTAG_UART_BASE) & ALTERA_AVALON_JTAG_UART_CONTROL_WSPACE_MSK))
	{
		//msg = OSQAccept(TxQue0, &err);
		msg = OSQPend(TxQue0,5, &err);
		if(msg != (void *)0)
		{
			IOWR_ALTERA_AVALON_JTAG_UART_DATA(JTAG_UART_BASE, *msg);
			err = OSMemPut(UartMemPart, msg);
		}
		else
			break;

		i++;
	}

	if(i != 0)
	{
		irq_state = IORD_ALTERA_AVALON_JTAG_UART_CONTROL(JTAG_UART_BASE) | ALTERA_AVALON_JTAG_UART_CONTROL_WE_MSK;
		IOWR_ALTERA_AVALON_JTAG_UART_CONTROL(JTAG_UART_BASE, irq_state);
		alt_irq_enable_all(jtag_uart_context);
	}


}
//-------------------------------------------------------------------------------

void UART_Tx_Byte(INT8U chr)
{
	INT8U *msg, err;
	OS_Q_DATA pData;
	
	OSQQuery(TxQue0, &pData);
	
	if(!(IORD_ALTERA_AVALON_JTAG_UART_CONTROL(JTAG_UART_BASE) & ALTERA_AVALON_JTAG_UART_CONTROL_WSPACE_MSK) && pData.OSNMsgs == 0)
		IOWR_ALTERA_AVALON_JTAG_UART_DATA(JTAG_UART_BASE, chr);
	else
	{
		msg = (INT8U *)OSMemGet(UartMemPart, &err);
		*msg = chr;
		OSQPost(TxQue0, msg);
	}
}

//-------------------------------------------------------------------------------
void UART_Tx_Byte_CheckCR(INT8U chr)
{
	UART_Tx_Byte(chr);
	if(chr=='\n')
		UART_Tx_Byte('\r');
}

//-------------------------------------------------------------------------------

INT8U UART_Rx_Byte()
{
	INT8U *msg, err, RxData;
	
	msg = OSQPend(RxQue0,0,&err);
	RxData = *msg;
	err = OSMemPut(UartMemPart, msg);
	
	return RxData;
}
//-------------------------------------------------------------------------------

void UART_Tx_Str(char *str)
{
	INT8U *ustr	= (INT8U*)str;

	while(*ustr != '\0')
		//UART_Tx_Byte(*(ustr++));
		UART_Tx_Byte_CheckCR(*(ustr++));
}


