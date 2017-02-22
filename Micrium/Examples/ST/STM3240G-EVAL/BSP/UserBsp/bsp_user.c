// User Define BSP. 2017.1.30


/*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

//#define   BSP_MODULE
//#include  <bsp.h>
//#include  <bsp_os.h>

#include <stdarg.h>
#include <stdio.h>
#include <stm32f407xx.h>
#include <stm32f4xx_hal.h>
#include <bsp.h>
#include <bsp_user.h>

//extern int Usart2RxEnable;

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    BSP_PeriphEn(BSP_PERIPH_ID_GPIOA);                          /* Configure GPIOG for LED1 and LED2                    */
    BSP_PeriphEn(BSP_PERIPH_ID_USART2);

    GPIO_InitStructure.Pin       = GPIO_PIN_2;
	GPIO_InitStructure.Speed     = GPIO_SPEED_FAST;
	GPIO_InitStructure.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Pull      = GPIO_PULLUP;
	GPIO_InitStructure.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
															   /* Configure GPIOC.11 as input floating.                 */
	GPIO_InitStructure.Pin       = GPIO_PIN_3;
	GPIO_InitStructure.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

//	if (Usart2RxEnable == 1)
//	{
		HAL_NVIC_SetPriority(USART2_IRQn, 0, 1);
		HAL_NVIC_EnableIRQ(USART2_IRQn);
//	}
}

//static char printfBuff[128];

UART_HandleTypeDef UartHandle;

void UartInit(void)
{
	UartHandle.Instance          = USART2;
	UartHandle.Init.BaudRate     = 115200;
	UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits     = UART_STOPBITS_1;
	UartHandle.Init.Parity       = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode         = UART_MODE_TX_RX;
	//UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	HAL_UART_Init(&UartHandle);
}



void UartSendChar(char c)
{
	HAL_UART_Transmit(&UartHandle,(unsigned char*)&c,1,1000);
}

void UartSendString(char *s)
{
	while(*s != '\0')
	{
		if(*s == '\n')
			UartSendChar('\r');
		UartSendChar(*s++);
	}
}

void UserPrint(const char *format, ...)
{
    va_list     vArgs;
    //int         sz;
    char        printfBuff[128];

    va_start (vArgs, format);
    //sz = vsprintf (printfBuff, format, vArgs);
    vsprintf (printfBuff, format, vArgs);
    va_end (vArgs);

    UartSendString(printfBuff);
}

void UserPrintXY(int task, int x, int y, const char *format, ...)
{
    va_list     vArgs;
    int         sz;
    char        printfBuff[128];

    sz = sprintf (printfBuff, "\x1B[%d;%dH", y, x);
    va_start (vArgs, format);
    vsprintf (&printfBuff[sz], format, vArgs);
    va_end (vArgs);

    UartSendString(printfBuff);
}
