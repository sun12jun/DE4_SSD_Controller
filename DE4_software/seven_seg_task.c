#include <io.h>
#include "includes.h"
#include "tasks.h"

/* task using 7 segments */
void task_7seg(void* pdata)
{
	//int seg_idx = 0;

	while (1)
	{
		//if(seg_idx >= 7)
		//seg_idx = 0;
		//else
		//seg_idx++;

		OSTimeDlyHMSM(0, 0, 3, 0);
	}
}

