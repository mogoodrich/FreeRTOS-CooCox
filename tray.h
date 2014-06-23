
/* task that controls opening and closing the tray */
static void vTrayController(void *pvParameters);

/* Priorities at which the tasks are created. */
#define mainTRAY_CONTROLLER_TASK_PRIORITY		( tskIDLE_PRIORITY + 2 )
