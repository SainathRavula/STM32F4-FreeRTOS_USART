#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"
/*=====================================================*/
#define CCM_RAM __attribute__((section(".ccmram")))
#define FPU_TASK_STACK_SIZE 256
/*=====================================================*/

void GPIO_Config(void);
void vTask1_Red(void *pvParameters);
void vTask2_Green(void *pvParameters);
void vApplicationIdleHook(void) 
{
	//Idle task
}

int main(void) 
{
	SystemInit();
       // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
        
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
	NVIC_SetPriority(SysTick_IRQn,1);
	GPIO_Config();
	xTaskCreate(vTask1_Red,"Task_1",100,NULL,2,NULL);
	xTaskCreate(vTask2_Green,"Task_2",100,NULL,2,NULL);
	vTaskStartScheduler();
	while(1) 
	{
		//infinite loop
	}
}
/*==================================================================================================================================*/
//Including from Draft/main.c

void vApplicationMallocFailedHook(void) {
  taskDISABLE_INTERRUPTS();
  for(;;);
}

void vApplicationTickHook(void) {
}

void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char *pcTaskName) {
  (void) pcTaskName;
  (void) pxTask;
  /* Run time stack overflow checking is performed if
     configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
     function is called if a stack overflow is detected. */
     
 taskDISABLE_INTERRUPTS();
  for(;;);
}

StaticTask_t xIdleTaskTCB CCM_RAM;
StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE] CCM_RAM;

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
  /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
  state will be stored. */
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

  /* Pass out the array that will be used as the Idle task's stack. */
  *ppxIdleTaskStackBuffer = uxIdleTaskStack;

  /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
  Note that, as the array is necessarily of type StackType_t,
  configMINIMAL_STACK_SIZE is specified in words, not bytes. */
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

static StaticTask_t xTimerTaskTCB CCM_RAM;
static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH] CCM_RAM;

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize) {
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
  *ppxTimerTaskStackBuffer = uxTimerTaskStack;
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

/*==================================================================================================================================*/


void GPIO_Config(void) 
{
	RCC->AHB1ENR |= 0x00000008;
	GPIOD->MODER = 0x55000000;
	GPIOD->OSPEEDR |= 0xFF000000;
}

void vTask1_Red(void *pvParameters) 
{
	for(;;)
	{
		printf("Red LED\n");
		GPIOD->ODR = 0x00002000;
		vTaskDelay(2000);
	}
}
void vTask2_Green(void *pvParameters) 
{
	for(;;)
	{
		printf("Green LED\n");
		GPIOD->ODR = 0x00001000;
		vTaskDelay(5000);
	}
}

