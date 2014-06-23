
#include "FreeRTOS.h"
#include "queue.h"

#include <stm32f4xx_gpio.h>

void vTrayController(void *pvParameters) {

	/* Give tray controller access to the Open Tray Queue */
	xQueueHandle *xOpenTrayQueue = (xQueueHandle *) pvParameters;

	/* just a flashing gpio for now, need to add control based on queue */
	GPIO_InitTypeDef gpio;

	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_12; // Green LED  (tray closed)
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_15; // Blue LED  (tray open)
	GPIO_Init(GPIOD, &gpio);

	for(;;) {
		static int count=0;
		static int i;
		static int led_state=0;

		for (i=0; i<1000000; ++i);
		GPIO_WriteBit(GPIOD, GPIO_Pin_12, led_state ? Bit_SET : Bit_RESET);
		led_state = !led_state;
		GPIO_WriteBit(GPIOD, GPIO_Pin_15, led_state ? Bit_SET : Bit_RESET);
		printf("%d\r\n", ++count);
	}

}
