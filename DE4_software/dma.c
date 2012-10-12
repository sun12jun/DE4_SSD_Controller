/*
 * dma.c
 *
 *  Created on: 2012. 10. 12
 *      Author: ydj
 */

#include <stdio.h>
#include "includes.h"
#include "dma.h"
#include "alt_ucosii_simple_error_check.h"
#include <altera_avalon_jtag_uart_regs.h>

/*	semaphore declaration	*/
OS_EVENT *SEM_DMA0;

/*-----------------------------------------------------------*/
void task_dma(void *parg)
{
	INT8U err;
	INT8U i;

	i = 0;
	for(;;)
	{
		OSSemPend(SEM_DMA0, 0, &err);

		// DMA body
		//if(i > 30)
		//{
			printf("DMA is completed at least 1 times\n");
			//i = 0;
		//}
		//else
			//i++;
		
		//OSTimeDlyHMSM(0, 0, 0, 5);
	}
}
