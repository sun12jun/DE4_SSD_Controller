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
#include <stdlib.h>
#include "sys/alt_dma.h"
#include "system.h"

/*	semaphore declaration	*/
OS_EVENT *SEM_DMA0;

/* external fuction */
extern void get_info();
extern void mem_display();
void get_info_dma();

/*-----------------------------------------------------------*/
void task_dma(void *parg)
{
	INT8U err;
	INT32U i;

	i = 0;
	for(;;)
	{
		OSSemPend(SEM_DMA0, 0, &err);

		if(i > 10000)
		{
			printf("DMA transfer is done\n");
//			get_info_dma();
//			mem_display((INT32U)DMA_0_WRITE_MASTER_DST_ON_CHIP_BASE);
			i = 0;
		}
		else
			i++;
	}
}

void get_info_dma()
{
	printf("transfer from src_on_chip to dst_on_chip is completed\n");
	printf("src : 64KB size on-chip memory attached by SOPC\n");
	printf("dst : 64KB size on-chip memory attached by SOPC\n");
}
