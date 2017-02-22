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
#define LED_TASK_PRIO   	6
#define FLOAT_TASK_PRIO 	5
#define PROTOCOL_TASK_PRIO 	4

#define START_TASK_STACK_SIZE 1024u
#define LED_TASK_STACK_SIZE   512u
#define FLOAT_TASK_STACK_SIZE 512u
#define PROTOCOL_TASK_STACK_SIZE 512u

static  OS_STK       StartTaskStk[START_TASK_STACK_SIZE];
static  OS_STK       LedTaskStk[LED_TASK_STACK_SIZE];
static  OS_STK       FloatTaskStk[FLOAT_TASK_STACK_SIZE];
static  OS_STK       ProtocolTaskStk[PROTOCOL_TASK_STACK_SIZE];

static void StartTask(void *p_arg);
static void LedTask(void *p_arg);
static void FloatTask(void *p_arg);
static void ProtocolTask(void *p_arg);

static void Tmr1CallBack(void* p_tmr,void* p_arg);
static void Tmr2CallBack(void* p_tmr,void* p_arg);

void IntHandlerUSART2(void);

extern UART_HandleTypeDef UartHandle;
int Usart2RxEnable = 1;
static int UartReady = 0; // Uart RX IT End Flag

static OS_TMR *TimerStruct1;
static OS_TMR *TimerStruct2;

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
	CPU_INT08U  err;
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

    UserPrint("Tmr1 Create\n");
    TimerStruct1 = OSTmrCreate(20,100,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)Tmr1CallBack,(void*)0,(INT8U*)0,&err);
    if(err > OS_ERR_NONE)
       	UserPrint("Tmr1 Create Error\n");

    UserPrint("Tmr2 Create\n");
    TimerStruct2 = OSTmrCreate(200,0,OS_TMR_OPT_ONE_SHOT,(OS_TMR_CALLBACK)Tmr2CallBack,(void*)0,(INT8U*)0,&err);
    if(err > OS_ERR_NONE)
       	UserPrint("Tmr2 Create Error\n");



    OSTaskCreateExt( ProtocolTask,                              /* Create the start task                                */
  						0,
  					   &ProtocolTaskStk[PROTOCOL_TASK_STACK_SIZE - 1],
					   PROTOCOL_TASK_PRIO,
					   PROTOCOL_TASK_PRIO,
  					   &ProtocolTaskStk[0],
					   PROTOCOL_TASK_STACK_SIZE,
  						0,
  					   (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

    OSTmrStart(TimerStruct1,&err);
    if(err > OS_ERR_NONE)
    	UserPrint("Tmr1 Start Error\n");

    OSTmrStart(TimerStruct2,&err);
    if(err > OS_ERR_NONE)
		UserPrint("Tmr2 Start Error\n");

    OS_EXIT_CRITICAL();

    //OSTaskSuspend(START_TASK_PRIO);

    while(1)
    {
    	OSTimeDlyHMSM(0u, 0u, 1u,0u);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  /* Set transmission flag: transfer complete */
  UartReady = SET;

  /* Turn LED4 on: Transfer in reception process is correct */
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
	//int count = 0;
	p_arg =p_arg;

	while(DEF_TRUE)
	{
		 BSP_LED_Toggle(1);
		 OSTimeDlyHMSM(0u, 0u, 0u,800u);
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
			OS_ENTER_CRITICAL();
			OSTaskSuspend(LED_TASK_PRIO);
			OS_EXIT_CRITICAL();
		}
		if (fnum >1.991f && fnum < 2.001f)
		{
			OS_ENTER_CRITICAL();
			OSTaskResume(LED_TASK_PRIO);
			OS_EXIT_CRITICAL();
			fnum = 0.0f;
		}

		OSTimeDlyHMSM(0u, 0u, 0u,300u);
	}
}


void Tmr1CallBack(void *p_tmr,void* p_arg)
{
	//CPU_INT08U  err;
	OS_CPU_SR  cpu_sr = 0u;
	static unsigned char flag = 0;

	p_arg = p_arg;

	flag++;

	if((flag%2) == 0)
	{
		UserPrint("TMR1 Del FloatTask\n");
		OSTaskDel(FLOAT_TASK_PRIO);
		return;
	}

	UserPrint("TMR1 Create FloatTask\n");

	OS_ENTER_CRITICAL();

	OSTaskCreateExt( FloatTask,                              /* Create the start task                                */
						0,
					   &FloatTaskStk[FLOAT_TASK_STACK_SIZE - 1],
					   FLOAT_TASK_PRIO,
					   FLOAT_TASK_PRIO,
					   &FloatTaskStk[0],
					   FLOAT_TASK_STACK_SIZE,
						0,
					   (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

	OS_EXIT_CRITICAL();
}

void Tmr2CallBack(void *p_tmr,void* p_arg)
{
	//CPU_INT08U  err;
	OS_CPU_SR  cpu_sr = 0u;

	p_arg = p_arg;

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

	UserPrint("TMR2 Create Led Task \n");
}

// Delayed Call
// UART2 Int ---> IntHandlerUSART2 --> (OSIntEnter) BSP_IntHandlerUSART2 (OSIntExit)
//           ---> WrapRXITHandler ---> HAL_UART_IRQHandler

void IntHandlerUSART2(void)
{
	if (OSRunning == 0)
		return;

	OSIntEnter();
	HAL_UART_IRQHandler(&UartHandle);
	OSIntExit();
}

