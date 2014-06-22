
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include <stdio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>



/* task that controls opening and closing the feeder */
static void vFeederController(void *pvParameters);

/* Priorities at which the tasks are created. */
#define mainFEEDER_CONTROLLER_TASK_PRIORITY		( tskIDLE_PRIORITY + 2 )

int main(void)
{

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Create the feeder task */
	xTaskCreate(vFeederController, (signed char *) "Feeder", 240, NULL, mainFEEDER_CONTROLLER_TASK_PRIORITY, NULL);

	printf("hello world!");

	/* Start up the tasks */
	vTaskStartScheduler();

	while(1) {
		printf("bye bye");

	//	static int count=0;
	//	static int i;
		//static int led_state=0;

		//for (i=0; i<1000000; ++i);
		//GPIO_WriteBit(GPIOD, GPIO_Pin_12, led_state ? Bit_SET : Bit_RESET);
		//led_state = !led_state;
		//GPIO_WriteBit(GPIOD, GPIO_Pin_15, led_state ? Bit_SET : Bit_RESET);

		//printf("%d\r\n", ++count);
	}
}


static void vFeederController(void *pvParameters) {

	// configure the feeder switch
	GPIO_InitTypeDef gpio;

	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_12; // Green LED  (feeder closed)
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_15; // Blue LED  (feeder open)
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

