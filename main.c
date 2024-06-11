#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "FreeRTOS.h"
#include "task.h"

static void setup_hardware(void);
void simple_task(void* pvParameters);
void init_USART1(void);
void USART_SendString(USART_TypeDef* USARTx, const char* str);

int main(void) 
{
	setup_hardware();
	init_USART1();  	
	xTaskCreate(simple_task, "Simple Task", 128, NULL, 2, NULL);
  	vTaskStartScheduler();
  	for (;;);
}
void vApplicationIdleHook(void) 
{
	//Idle Task
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char* pcTaskName) 
{
  	for (;;);
}

void vApplicationMallocFailedHook(void) 
{
  	for (;;);
}

static void setup_hardware(void) 
{
	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
}

void vApplicationGetIdleTaskMemory(StaticTask_t** ppxIdleTaskTCBBuffer, StackType_t** ppxIdleTaskStackBuffer, uint32_t* pulIdleTaskStackSize) 
{
	static StaticTask_t xIdleTaskTCB;
	static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];
  
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
	*ppxIdleTaskStackBuffer = uxIdleTaskStack;
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
static StaticTask_t xTimerTaskTCB;
static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory(StaticTask_t** ppxTimerTaskTCBBuffer, StackType_t** ppxTimerTaskStackBuffer, uint32_t* pulTimerTaskStackSize) 
{
	*ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
	*ppxTimerTaskStackBuffer = uxTimerTaskStack;
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

void simple_task(void* pvParameters) 
{
	USART_SendString(USART1, "Start simple task  ");
	for (;;) 
	{
		USART_SendString(USART1, "Hello from simple task  ");
		vTaskDelay(2000);
  	}

	vTaskDelete(NULL);
}

void init_USART1(void) 
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	USART_InitStruct.USART_BaudRate = 1200;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStruct);
	USART_Cmd(USART1, ENABLE);
}

void USART_SendString(USART_TypeDef* USARTx, const char* str) 
{
	while (*str) {
		USART_SendData(USARTx, (uint16_t) *str++);
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
  }
}

