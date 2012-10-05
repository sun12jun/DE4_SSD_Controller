#include <io.h>
#include "includes.h"
#include "tasks.h"

char led_table[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
//char led_table[8] = {0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00};

/* task using GPIO */
void task_gpio(void* pdata)
{
	int led_idx = 0;

	while (1)
	{
		IOWR(LED_BASE, 0, led_table[led_idx]);

		if(led_idx >= 7)
			led_idx = 0;
		else
			led_idx++;

		OSTimeDlyHMSM(0, 0, 0, 500);
	}
}

