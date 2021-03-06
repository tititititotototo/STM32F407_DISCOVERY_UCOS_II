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
#define PROTOCOL_TASK_PRIO 	4
#define FLOAT_TASK_PRIO 	5
#define LED_TASK_PRIO   	8

#define START_TASK_STACK_SIZE 512u
#define LED_TASK_STACK_SIZE   256
#define FLOAT_TASK_STACK_SIZE 256u
#define PROTOCOL_TASK_STACK_SIZE 256u

#define BLK_NUM  10
#define BLK_SIZE 100

static  OS_STK       StartTaskStk[START_TASK_STACK_SIZE];
static  OS_STK       LedTaskStk[LED_TASK_STACK_SIZE];
static  OS_STK       FloatTaskStk[FLOAT_TASK_STACK_SIZE];
//static  OS_STK       ProtocolTaskStk[PROTOCOL_TASK_STACK_SIZE];

static unsigned char MemoryPool[BLK_NUM][BLK_SIZE] __attribute__((aligned(4)));

static void StartTask(void *p_arg);
static void LedTask(void *p_arg);
static void FloatTask(void *p_arg);
//static void ProtocolTask(void *p_arg);

extern UART_HandleTypeDef UartHandle;
int Usart2RxEnable = 0;
static int UartReady = 0; // Uart RX IT End Flag

static OS_MEM 	   *MemoryStruct;

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
	OS_ERR err;
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

    MemoryStruct = OSMemCreate(MemoryPool,BLK_NUM,BLK_SIZE,&err);

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

	OSTaskSuspend(START_TASK_PRIO);

	OS_EXIT_CRITICAL();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	UartReady = SET;
	BSP_LED_Toggle(2);
}

static void LedTask(void *p_arg)
{
	int i;
	OS_ERR err;
	unsigned char *buf[5];

	p_arg =p_arg;

	while(DEF_TRUE)
	{
		for(i=0;i<5;i++)
		{
			buf[i] = OSMemGet(MemoryStruct,&err);

			if (err == OS_ERR_NONE)
				UserPrint("Led Task Get Memory(%d) (Prio : %d)\n",i,LED_TASK_PRIO);

			if (err == OS_ERR_MEM_NO_FREE_BLKS)
				UserPrint("No Free Memory(%d)\n",i);

			OSTimeDlyHMSM(0u, 0u, 0u,500u);
		}

		for(i=0;i<5;i++)
		{
			OSMemPut(MemoryStruct,(void *)buf[i]);
			UserPrint("Memory Put(%d) !!\n",i);
			UserPrint("Buf Addr %x\n",buf[i]);

			OSTimeDlyHMSM(0u, 0u, 0u,500u);
		}
		UserPrint("\n");
	}
}

static void FloatTask(void *p_arg)
{
	p_arg = p_arg;

	while(DEF_TRUE)
	{
		UserPrint("Float Task : Mem Free Block %d (Prio : %d)\n",MemoryStruct->OSMemNFree,FLOAT_TASK_PRIO);
		OSTimeDlyHMSM(0u, 0u, 0u,500u);
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
