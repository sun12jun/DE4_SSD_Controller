/*
 * report.c
 *
 *  Created on: 2012. 10. 03.
 *      Author: ydj
 */

#include <stdio.h>
#include <string.h>
#include <io.h>
#include "includes.h"
#include "report.h"
#include "alt_ucosii_simple_error_check.h"

/*	semaphore declaration	*/
OS_EVENT *SEM_REPORT;

/*	Local function declaration	*/
extern void viewlogo();
extern void get_info();

/*-----------------------------------------------------------*/
void task_report(void *parg)
{
	INT8U err;

	viewlogo();

	for(;;)
	{
		OSSemPend(SEM_REPORT, 0, &err);

		printf("report is start..\n");
		get_info();
		printf("report is done\n");

//		OSTimeDlyHMSM(0, 0, 0, 0);
	}
}

