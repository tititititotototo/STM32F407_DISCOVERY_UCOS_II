/*
 * app_user.c
 *
 *  Created on: 2017. 1. 30.
 *      Author: grooves
 */

/*
*********************************************************************************************************
*                                            EXAMPLE CODE
*
*               This file is provided as an example on how to use Micrium products.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only. This file can be modified as
*               required to meet the end-product requirements.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can find our product's user manual, API reference, release notes and
*               more information at https://doc.micrium.com.
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                           STM3240G-EVAL
*                                         Evaluation Board
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <stdarg.h>
#include  <stdio.h>
#include  <math.h>
#include  <stdlib.h>
#include  <time.h>
#include  <stm32f4xx_hal.h>

#include  <cpu.h>
#include  <lib_math.h>
#include  <lib_mem.h>
#include  <os.h>

#include  <app_cfg.h>
#include  <bsp.h>
#include  <bsp_user.h>

#if (APP_CFG_SERIAL_EN == DEF_ENABLED)
#include  <app_serial.h>
#endif


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  APP_TASK_EQ_0_ITERATION_NBR              16u
#define  APP_TASK_EQ_1_ITERATION_NBR              18u

#define  ALL_TASK_N 10

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

                                                                /* --------------- APPLICATION GLOBALS ---------------- */
static  OS_STK       AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE];

                                                                /* ------------- PROBE EXAMPLE VARIABLES -------------- */
        CPU_INT32U   AppProbe_CtrVal;
        CPU_INT32U   AppProbe_Slider;

                                                                /* --------------- SEMAPHORE TASK TEST ---------------- */

static  OS_STK       AppTaskAnsiStk[ALL_TASK_N][APP_CFG_TASK_EQ_STK_SIZE];


//#if (OS_SEM_EN > 0u)
//static  OS_EVENT    *AppTraceSem;
//#endif
//
//#if (OS_SEM_EN > 0u)
//static  OS_EVENT    *AppTaskObjSem;
//#endif
//
//#if (OS_MUTEX_EN > 0u)
//static  OS_EVENT    *AppTaskObjMutex;
//#endif
//
//#if (OS_Q_EN > 0u)
//static  OS_EVENT    *AppTaskObjQ;
//#endif
//
//#if (OS_FLAG_EN > 0u)
//static  OS_FLAG_GRP *AppTaskObjFlag;
//#endif
#if (OS_SEM_EN > 0u)
static OS_EVENT *RandomSem;
#endif

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskCreate  (void);
static  void  AppTaskStart   (void  *p_arg);
static  void  AppTaskAnsi   (void  *p_arg);

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*
* Notes       : 1) STM32F4xx HAL library initialization:
*                      a) Configures the Flash prefetch, intruction and data caches.
*                      b) Configures the Systick to generate an interrupt. However, the function ,
*                         HAL_InitTick(), that initializes the Systick has been overwritten since Micrium's
*                         RTOS has its own Systick initialization and it is recommended to initialize the
*                         Systick after multitasking has started.
*
*********************************************************************************************************
*/

int main(void)
{
#if (OS_TASK_NAME_EN > 0)
    CPU_INT08U  err;
#endif

    HAL_Init();                                                 /* See Note 1.                                          */

    Mem_Init();                                                 /* Initialize Memory Managment Module                   */
    Math_Init();                                                /* Initialize Mathematical Module                       */

    BSP_IntDisAll();                                            /* Disable all Interrupts.                              */

    OSInit();                                                   /* Init uC/OS-II.                                       */

    OSTaskCreateExt( AppTaskStart,                              /* Create the start task                                */
                     0,
                    &AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE - 1],
                     APP_CFG_TASK_START_PRIO,
                     APP_CFG_TASK_START_PRIO,
                    &AppTaskStartStk[0],
                     APP_CFG_TASK_START_STK_SIZE,
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


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
    CPU_INT32U  r0;
    CPU_INT32U  r1;
    CPU_INT32U  r2;
    CPU_INT32U  r3;
    CPU_INT32U  r4;
    CPU_INT32U  r5;
    CPU_INT32U  r6;
    CPU_INT32U  r7;
    CPU_INT32U  r8;
    CPU_INT32U  r9;
    CPU_INT32U  r10;
    CPU_INT32U  r11;
    CPU_INT32U  r12;

    int endNum = 50;

   (void)p_arg;

    r0  =  0u;                                                  /* Initialize local variables.                          */
    r1  =  1u;
    r2  =  2u;
    r3  =  3u;
    r4  =  4u;
    r5  =  5u;
    r6  =  6u;
    r7  =  7u;
    r8  =  8u;
    r9  =  9u;
    r10 = 10u;
    r11 = 11u;
    r12 = 12u;

    BSP_Init();                                                 /* Initialize BSP functions                             */
    CPU_Init();                                                 /* Initialize the uC/CPU services                       */

#if (OS_TASK_STAT_EN > 0)
    OSStatInit();                                               /* Determine CPU capacity                               */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif

#if 0
//#if (APP_CFG_SERIAL_EN == DEF_ENABLED)
    if (App_SerialInit() == DEF_FAIL)                                           /* Initialize Serial Communication for Application ...  */
    {
        BSP_LED_On(1u);
         while(1);
    }
#endif

    //BspUart2GpioInit();
    UartInit();

    //UartSendChar('X');
    //AppEventCreate();                                           /* Create Applicaiton kernel objects                    */

    RandomSem = OSSemCreate(1);

    //UartSendChar('O');
    AppTaskCreate();                                            /* Create Application tasks                             */

    BSP_LED_Off(0u);
    AppProbe_CtrVal = 0u;
    AppProbe_Slider = 100u;

    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
        BSP_LED_Toggle(0u);
        OSTimeDlyHMSM(0u, 0u, 0u, (AppProbe_Slider));

        UserPrint("\x1B[40m");
        //UserPrintXY(0,AppProbe_CtrVal,0,"Task0");
        //UserPrint("Count %d\n",AppProbe_CtrVal);

        if ((r0  !=  0u) ||                                     /* Check task context.                                  */
            (r1  !=  1u) ||
            (r2  !=  2u) ||
            (r3  !=  3u) ||
            (r4  !=  4u) ||
            (r5  !=  5u) ||
            (r6  !=  6u) ||
            (r7  !=  7u) ||
            (r8  !=  8u) ||
            (r9  !=  9u) ||
            (r10 != 10u) ||
            (r11 != 11u) ||
            (r12 != 12u)) {
        	UserPrint(("Context Error\n"));
        }

        AppProbe_CtrVal++;

        if (AppProbe_CtrVal >= endNum) {
        //if (AppProbe_CtrVal >= DEF_INT_32_MASK) {
        	if (endNum > 0)
        		endNum--;

        	if (endNum == 0)
        		endNum = 50;

            AppProbe_CtrVal = 0u;
        }
    }
}

/*
*********************************************************************************************************
*                                          AppTaskCreate()
*
* Description : Create Application Tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     : none.
*********************************************************************************************************
*/

static char TaskArg[ALL_TASK_N];

static void AppTaskCreate(void)
{
#if (OS_TASK_NAME_EN > 0)
    CPU_INT08U  err;
#endif

    int i;

    for(i=0;i<ALL_TASK_N;i++)
    {
    	TaskArg[i] = '0'+i;

		OSTaskCreateExt( AppTaskAnsi, &TaskArg[i], &AppTaskAnsiStk[i][APP_CFG_TASK_EQ_STK_SIZE - 1],
						 APP_CFG_TASK_EQ0_PRIO+i,APP_CFG_TASK_EQ0_PRIO+i,&AppTaskAnsiStk[i][0],
						 APP_CFG_TASK_EQ_STK_SIZE,0,
						(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR | OS_TASK_OPT_SAVE_FP));
    }

#if (OS_TASK_NAME_EN > 0)
    OSTaskNameSet(         APP_CFG_TASK_EQ0_PRIO,
                  (INT8U *)"Task VT100 ANSI Demo",
                           &err);
#endif


}

/*
*********************************************************************************************************
*                                             AppTaskEq0Fp()
*
* Description : This task finds the root of the following equation.
*               f(x) =  e^-x(3.2 sin(x) - 0.5 cos(x)) using the bisection mehtod
*
* Argument(s) : p_arg   is the argument passed to 'AppTaskEq0Fp' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Note(s)     : 1) Atollic TrueSTUDIO needs special settings to output floating point format; however,
*                  IAR and KeilMDK should work properly.
*********************************************************************************************************
*/

void  AppTaskAnsi (void  *p_arg)
{
	int x,y,col;
	char ch;
	unsigned char err;
	char str[10];
	//int ranCount = 0;

	while (DEF_TRUE)
	{
		ch = (char)*((char*)p_arg);
		col = (40 + ch - '0');

		if (col > 47)
			col-=7;

		OSSemPend(RandomSem,0,&err);
		if (err > OS_ERR_NONE)
			UserPrint("SPend Err %d\n",err);

		x = rand() % 80;
		y = rand() % 16;

		if ((err = OSSemPost(RandomSem)) > OS_ERR_NONE)
			UserPrint("SPost Err %d\n",err);

		snprintf(str,10,"\x1B[%dm",col);
		UserPrint("%s",str);
		UserPrintXY(0,x,y,"%c",ch);

		//UserPrint("p_arg %d\n",x);

		OSTimeDlyHMSM(0u, 0u, 0u,200);
	}
}
