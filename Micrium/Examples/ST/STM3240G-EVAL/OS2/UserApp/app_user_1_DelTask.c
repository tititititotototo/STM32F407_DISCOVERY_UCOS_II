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
#define FLOAT_TASK_PRIO 	6

#define START_TASK_STACK_SIZE 512u
#define LED_TASK_STACK_SIZE   256
#define FLOAT_TASK_STACK_SIZE 256u

static  OS_STK       StartTaskStk[START_TASK_STACK_SIZE];
static  OS_STK       LedTaskStk[LED_TASK_STACK_SIZE];
static  OS_STK       FloatTaskStk[FLOAT_TASK_STACK_SIZE];

static void StartTask(void *p_arg);
static void LedTask(void *p_arg);
static void FloatTask(void *p_arg);

extern UART_HandleTypeDef UartHandle;

int Usart2RxEnable = 0;

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


static void LedTask(void *p_arg)
{
	int count = 0;
	p_arg =p_arg;

	while(DEF_TRUE)
	{
		 BSP_LED_Toggle(count++);

		 if (count > 4)
			 count = 0;

		 OSTimeDlyHMSM(0u, 0u, 0u,200);
	}
}

static void FloatTask(void *p_arg)
{
	static float fnum = 0.01;
	OS_CPU_SR  cpu_sr = 0u;

	while(DEF_TRUE)
	{
		fnum += 0.01f;

		OS_ENTER_CRITICAL();
		UserPrint("floatNum %.4f\n",fnum);
		OS_EXIT_CRITICAL();

		if (fnum > 0.901f && fnum < 0.919f)
		{
			OSTaskDel(LED_TASK_PRIO);
		}
		if (fnum >1.991f && fnum < 2.001f)
		{
			OS_ENTER_CRITICAL();
			OSTaskCreateExt( LedTask,                              /* Create the start task                                */
							0,
						   &LedTaskStk[LED_TASK_STACK_SIZE - 1],
						   LED_TASK_PRIO,
						   LED_TASK_PRIO,
						   &LedTaskStk[0],
						   LED_TASK_STACK_SIZE,
							0,
						   (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
			OS_EXIT_CRITICAL();
			fnum = 0.0f;
		}

		OSTimeDlyHMSM(0u, 0u, 0u,300);
	}
}

void IntHandlerUSART2(void)
{
	HAL_UART_IRQHandler(&UartHandle);
}

