
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "tray.h"

#include <stdio.h>
#include <stm32f4xx_rcc.h>

xQueueHandle xOpenTrayQueue;

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Create the queue by which the tray controller is alerted to open the tray */
	xOpenTrayQueue = xQueueCreate(1, sizeof(char));

	/* Create the tray task (defined in tray.c) */
	xTaskCreate(vTrayController, (signed char *) "Tray",  configMINIMAL_STACK_SIZE, &xOpenTrayQueue, mainTRAY_CONTROLLER_TASK_PRIORITY, NULL);

	/* Start up the tasks */
	vTaskStartScheduler();

	while(1) {

	}
}


