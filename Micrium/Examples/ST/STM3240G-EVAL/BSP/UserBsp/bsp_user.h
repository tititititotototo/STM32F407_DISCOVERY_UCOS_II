#ifndef  BSP_USER_PRESENT
#define  BSP_USER_PRESENT

void BspUart2GpioInit(void);
void UartInit(void);
void UartSendChar(char c);
void UartSendString(char *s);
void UserPrint (const char *format, ...);
void UserPrintXY(int task, int x, int y, const char *format, ...);

//#define USART2_IRQn 38

#endif


