/*
 * app_user_1.c
 *
 *  Created on: 2017. 2. 7.
 *      Author: grooves
 */

#include <stm32f4xx_hal.h>

#include <os.h>
#include <os_cpu.h>

#include <lib_def.h>

#include <bsp.h>
#include <bsp_user.h>

#define START_TASK_PRIO	 	3
#define LED_TASK_PRIO   	4
#define FLOAT_TASK_PRIO 	5
#define PROTOCOL_TASK_PRIO 	4

#define START_TASK_STACK_SIZE 512u
#define LED_TASK_STACK_SIZE   256
#define FLOAT_TASK_STACK_SIZE 256u
#define PROTOCOL_TASK_STACK_SIZE 256u

static  OS_STK       StartTaskStk[START_TASK_STACK_SIZE];
static  OS_STK       LedTaskStk[LED_TASK_STACK_SIZE];
static  OS_STK       FloatTaskStk[FLOAT_TASK_STACK_SIZE];
static  OS_STK       ProtocolTaskStk[PROTOCOL_TASK_STACK_SIZE];

static void StartTask(void *p_arg);
static void LedTask(void *p_arg);
static void FloatTask(void *p_arg);
static void ProtocolTask(void *p_arg);

extern UART_HandleTypeDef UartHandle;
int Usart2RxEnable = 0;
static int UartReady = 0; // Uart RX IT End Flag

#if (OS_SEM_EN > 0u)
static OS_EVENT *ShareDataSem;
#endif

int main(void)
{
#if (OS_TASK_NAME_EN > 0)
    CPU_INT08U  err;
#endif

    HAL_Init();                                                 /* See Note 1.                                          */
    Mem_Init();                                                 /* Initialize Memory Managment Module                   */

    BSP_IntDisAll();                                            /* Disable all Interrupts.                              */

    OSInit();                                                   /* Init uC/OS-II.                                       */

    OSTaskCreateExt( StartTask,                              /* Create the start task                                */
                     0,
                    &StartTaskStk[START_TASK_STACK_SIZE - 1],
					START_TASK_PRIO,
					START_TASK_PRIO,
                    &StartTaskStk[0],
					START_TASK_STACK_SIZE,
                     0,
                    (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

#if (OS_TASK_NAME_EN > 0)
    OSTaskNameSet(         APP_CFG_TASK_START_PRIO,
                  (INT8U *)"Start Task",
                           &err);
#endif

    OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II).  */

    while (DEF_ON) {                                            /* Should Never Get Here.                               */
        ;
    }
}

static void StartTask(void *p_arg)
{
	BSP_Init();
	CPU_Init();
	OS_CPU_SR  cpu_sr = 0u;
	p_arg = p_arg;

#if (OS_TASK_STAT_EN > 0)
    OSStatInit();                                               /* Determine CPU capacity                               */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif
    UartInit();
    BSP_LED_Off(0u);

    OS_ENTER_CRITICAL();

    ShareDataSem = OSSemCreate(1);

    OSTaskCreateExt( LedTask,                              /* Create the start task                                */
                        0,
                       &LedTaskStk[LED_TASK_STACK_SIZE - 1],
					   LED_TASK_PRIO,
					   LED_TASK_PRIO,
                       &LedTaskStk[0],
					   LED_TASK_STACK_SIZE,
                        0,
                       (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

    OSTaskCreateExt( FloatTask,                              /* Create the start task                                */
						0,
					   &FloatTaskStk[FLOAT_TASK_STACK_SIZE - 1],
					   FLOAT_TASK_PRIO,
					   FLOAT_TASK_PRIO,
					   &FloatTaskStk[0],
					   FLOAT_TASK_STACK_SIZE,
						0,
					   (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

    OSTaskCreateExt( ProtocolTask,                              /* Create the start task                                */
     				   0,
					   &ProtocolTaskStk[PROTOCOL_TASK_STACK_SIZE - 1],
   					   PROTOCOL_TASK_PRIO,
   					   PROTOCOL_TASK_PRIO,
					   &ProtocolTaskStk[0],
   					   PROTOCOL_TASK_STACK_SIZE,
					   0,
					   (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

	OSTaskSuspend(START_TASK_PRIO);

	OS_EXIT_CRITICAL();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	UartReady = SET;
	BSP_LED_Toggle(2);
}

static void ProtocolTask(void *p_arg)
{
	char aRxBuffer[10];
	int rxStartFlag = 0;
	UartReady = RESET;

	while(DEF_TRUE)
	{
		if ((UartReady == RESET) && (rxStartFlag == 0))
		{
			if(HAL_UART_Receive_IT(&UartHandle, (uint8_t *)aRxBuffer, 1) != HAL_OK)
			{
				UserPrint("USART2 Error\n");
			}
			rxStartFlag = 1;
		}
		else if ((UartReady == SET) && (rxStartFlag == 1))
		{
			UserPrint("Get:%c\n",aRxBuffer[0]);

			switch(aRxBuffer[0])
			{
				case '0':
					OSTaskSuspend(LED_TASK_PRIO);
					break;

				case '1':
					OSTaskResume(LED_TASK_PRIO);
					break;

				case '2':
					OSTaskDel(FLOAT_TASK_PRIO);
					break;

				case '3':
				    OSTaskCreateExt( FloatTask,                              /* Create the start task                                */
									0,
									&FloatTaskStk[FLOAT_TASK_STACK_SIZE - 1],
									FLOAT_TASK_PRIO,
									FLOAT_TASK_PRIO,
									&FloatTaskStk[0],
									FLOAT_TASK_STACK_SIZE,
									0,
									(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
					break;

				default:
					break;

			}

			rxStartFlag = 0;
			UartReady = RESET;
		}

		OSTimeDlyHMSM(0u, 0u, 0u,10);
	}
}

static void LedTask(void *p_arg)
{
	unsigned char err;
	p_arg =p_arg;

	while(DEF_TRUE)
	{
		UserPrint("Led Task Send Sem (Prio:%d)\n",LED_TASK_PRIO);
		if ((err = OSSemPost(ShareDataSem)) > OS_ERR_NONE)
			UserPrint("SPost Err %d\n",err);

		OSTimeDlyHMSM(0u, 0u, 2u,0u);
		UserPrint("Led Task WakeUp\n");
	}
}

static void FloatTask(void *p_arg)
{
	unsigned char err;
	p_arg = p_arg;

	while(DEF_TRUE)
	{
		UserPrint("Float Task Wait Sem (Prio:%d)\n",FLOAT_TASK_PRIO);
		OSSemPend(ShareDataSem,0,&err);

		OSTimeDlyHMSM(0u, 0u, 1u,0u);
		UserPrint("Float Task get Sem\n\n");
	}
}

// Direct Call
// UART2 Int ---> IntHandlerUSART2 --> HAL_UART_IRQHandler

void IntHandlerUSART2(void)
{
	if (OSRunning == 0)
		return;

	OSIntEnter();
	HAL_UART_IRQHandler(&UartHandle);
	OSIntExit();
}
