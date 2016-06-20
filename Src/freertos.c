/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "gpio.h"
#include "usart.h"
#include "dma.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId Task1Handle;
osSemaphoreId myBinarySem01Handle;

/* USER CODE BEGIN Variables */
//xSemaphoreHandle xBinarySemaphore;

osSemaphoreId testBinarySemHandle;

osThreadId Task2Handle;
osThreadId Task3Handle;
osThreadId Task4Handle;
osThreadId taskLed7SegHandle;

uint8_t Rx_indx, Rx_data[2], Rx_Buffer[255], Transfer_cplt, idxTest, txDone = 0;

uint8_t buffer[10],len=2;

volatile uint32_t UartErrorCount;
volatile uint32_t astan;
volatile int licznikBussyRx=0;
volatile uint32_t statusTX;
volatile uint32_t statusRX;
volatile uint32_t licznikRXBussyState;
volatile uint8_t timeDelayRxFlag;
volatile uint8_t recivingRxFlag;


/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void task1(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

void task2(void const * argument);
void task3(void const * argument);
void task4(void const * argument);
void taskLed7Seg(void const * argument);


/* USER CODE END FunctionPrototypes */

/* Hook prototypes */
void vApplicationIdleHook(void);

/* USER CODE BEGIN 2 */
void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       

	HAL_UART_Receive_DMA(&huart1, Rx_data, 1);

	//statusRX = HAL_UART_Receive_IT(&huart2, Rx_data, 1);
	//statusRX = HAL_UART_Receive_DMA(&huart2, Rx_data, 1);

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of myBinarySem01 */
  osSemaphoreDef(myBinarySem01);
  myBinarySem01Handle = osSemaphoreCreate(osSemaphore(myBinarySem01), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */

  osSemaphoreDef(testBinarySemHandle);
  testBinarySemHandle = osSemaphoreCreate(osSemaphore(testBinarySemHandle), 1);


  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of Task1 */
  osThreadDef(Task1, task1, osPriorityNormal, 0, 128);
  Task1Handle = osThreadCreate(osThread(Task1), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */

  osThreadDef(Task2, task2, osPriorityNormal, 0, 128);
  Task2Handle = osThreadCreate(osThread(Task2), NULL);

  osThreadDef(Task3, task3, osPriorityNormal, 0, 128);
  Task3Handle = osThreadCreate(osThread(Task3), NULL);

  osThreadDef(Task4, task4, osPriorityNormal, 0, 128);
  Task4Handle = osThreadCreate(osThread(Task4), NULL);

  osThreadDef(TaskLed7Seg, taskLed7Seg, osPriorityNormal, 0, 128);
  taskLed7SegHandle = osThreadCreate(osThread(TaskLed7Seg), NULL);





  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* task1 function */
void task1(void const * argument)
{

  /* USER CODE BEGIN task1 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(100);
  }
  /* USER CODE END task1 */
}

/* USER CODE BEGIN Application */
void taskLed7Seg(void const * argument)
{
	uint32_t PreviousWakeTime = osKernelSysTick();
	for(;;)
	{

		//idle time uart 1
//		if (timeDelayRxFlag == 0) {
//			timeDelayRxFlag = 1;
//		}
//		else if (recivingRxFlag == 1)
//		{
//			recivingRxFlag = 0;
//			Transfer_cplt = 1;
//			Rx_indx = 0;
//		}
	 if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) == 1)
		{
		 __HAL_UART_CLEAR_IDLEFLAG(&huart1);
		 HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
			recivingRxFlag = 0;
			Transfer_cplt = 1;
			Rx_indx = 0;
		}


		//******************



		if( (Transfer_cplt == 1) && (txDone == 0))
		{
			txDone = 1;
			Transfer_cplt = 0;
			osSemaphoreRelease(testBinarySemHandle);
			HAL_GPIO_TogglePin(LD6_GPIO_Port, LD6_Pin);
		}



		astan = HAL_UART_GetState( &huart1 ) ;
		astan = HAL_UART_GetState( &huart2 ) ;

		if(  astan ==  34 )
		{
			licznikBussyRx++;
		} else
		{
			licznikBussyRx = 0;
		}



	    osDelayUntil(&PreviousWakeTime, 5);
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	if (Rx_indx==0)
	{
		for (uint8_t i=0;i<255;i++)
		{
			Rx_Buffer[i]=0;
		}
	}


	if (huart->Instance == USART1)
		{
		HAL_UART_DMAPause(huart);
		__HAL_UART_FLUSH_DRREGISTER(huart);

		Rx_Buffer[Rx_indx++] = Rx_data[0];

		if ( Rx_indx >= 255 )
		{
			Rx_indx = 0;
		}

		timeDelayRxFlag = 0;
		recivingRxFlag = 1;

		HAL_UART_DMAResume(huart);
		}


	if (huart->Instance == USART2)
	{
		__HAL_UART_FLUSH_DRREGISTER(huart);
		if( Rx_data[0]!=13 )
		{

			Rx_Buffer[Rx_indx++] = Rx_data[0];
			if ( Rx_indx >= 100 )
			{
				Rx_indx = 0;
			}
		}
		else
		{
			idxTest = Rx_indx;
			Rx_indx=0;
			Transfer_cplt = 1;
		}

		statusRX = HAL_UART_Receive_IT(&huart2, Rx_data, 1);
		//statusRX = HAL_UART_Receive_DMA(&huart2, Rx_data, 1);




		  if (statusRX == HAL_OK) {
			  licznikRXBussyState = 1;
		  }
		  else if (statusRX == HAL_ERROR)
		  {
			  licznikRXBussyState = 2;
		  }
		  else if (statusRX == HAL_BUSY)
		  {
			  licznikRXBussyState = 3;
		  }


	}


	//HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	txDone = 0;
	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);

}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	txDone = 0;

	UartErrorCount++;

	  __HAL_UART_CLEAR_OREFLAG(huart);
	  __HAL_UART_CLEAR_NEFLAG(huart);
	  __HAL_UART_CLEAR_FEFLAG(huart);
	  __HAL_UART_CLEAR_PEFLAG(huart);
//	  __HAL_UART_CLEAR_IDLEFLAG(huart);

	//  __HAL_UART_DISABLE_IT(huart, UART_IT_ERR );


	 if(huart->Instance == USART1)
	  {
		 __HAL_UART_FLUSH_DRREGISTER(&huart1);
		// HAL_UART_Receive_DMA(&huart1, Rx_data, 1);
		 HAL_UART_Receive_DMA(&huart1, Rx_data, 1);
	  }

	 if(huart->Instance == USART2)
	  {
		 __HAL_UART_FLUSH_DRREGISTER(&huart2);
		 statusRX = HAL_UART_Receive_IT(&huart2, Rx_data, 1);
		 //statusRX = HAL_UART_Receive_DMA(&huart2, Rx_data, 1);
	  }
}




void task2(void const * argument)
{
  /* Infinite loop */
  for(;;)
  {


	  buffer[0]=UartErrorCount;
	  buffer[1]= 66;
	  buffer[2]=67;
	  buffer[3]=13;
	  buffer[4]=10;

	  //HAL_UART_Transmit(&huart1, buffer, len, 1000);
	//statusTX =  HAL_UART_Transmit_IT(&huart2, buffer, 5);
	//UART_Transmit_IT

	  if (statusTX == HAL_OK) {
		  licznikRXBussyState = 1;
	  }
	  else if (statusTX == HAL_ERROR)
	  {
		  licznikRXBussyState = 2;

	  }
	  else if (statusTX == HAL_BUSY)
	  {
		  licznikRXBussyState = 3;
	  }

//	  HAL_UART_Transmit_DMA(&huart1, buffer, 5);
	//	 __HAL_UART_FLUSH_DRREGISTER(&huart2);
	//	 HAL_UART_Receive_IT(&huart2, Rx_data, 1);

	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
    osDelay(5000);
 //   osSemaphoreRelease(testBinarySemHandle);

  }
}
void task3(void const * argument)
{
  /* Infinite loop */
	static uint8_t data[255];
	static uint16_t size;

	static int licznikOK = 0;
	static int licznikAll = 0;

  for(;;)
  {
	  osSemaphoreWait(testBinarySemHandle, osWaitForever);

	  size = sprintf( (char *) data, "Semafor Task OK: %d, BUSSY: %d, ERROR: %d SIZE %d\r\n", (int) licznikOK , licznikAll++, (int)UartErrorCount, (int) size  );




	  if (size > 255)
		{
			size = 255;
		}

	  statusTX = HAL_UART_Transmit_IT(&huart2, Rx_Buffer , sizeof(Rx_Buffer));
	  statusTX = HAL_UART_Transmit_IT(&huart1, data , size);


	  if (statusTX == HAL_OK) {
		  licznikOK++;
	  }
	  else if (statusTX == HAL_ERROR)
	  {
			txDone = 0;
			Transfer_cplt = 1;

	  }
	  else if (statusTX == HAL_BUSY)
	  {
			txDone = 0;
			Transfer_cplt = 1;
	  }



	  data[0] = (uint8_t)UartErrorCount + 48;
	  data[1]=10;
	  data[2]=13;
	 // HAL_UART_Transmit_DMA(&huart1, data , 2);


//	  HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
//	  osDelay(100);
//	  HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);

  }
}

void task4(void const * argument)
{
  /* Infinite loop */
  for(;;)
  {
	 // xSemaphoreTake( xBinarySemaphore, portMAX_DELAY );
	  HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin);
	  osDelay(200);
  }
}

     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
