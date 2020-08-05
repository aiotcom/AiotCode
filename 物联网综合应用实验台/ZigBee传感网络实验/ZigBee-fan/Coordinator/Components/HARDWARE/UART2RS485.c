#include "UART2RS485.h"
#include "MT_UART.h"
#include "HAL_DEFS.h"
#include "string.h"
#include "stdio.h"
/*
��ʼ��UARTת485оƬ�շ���������
*/
void UART2RS485_Init(void)
{  
    halUARTCfg_t uartConfig;
    
    P1SEL &= ~BV(3);     //����P1.3Ϊ��ͨIO��  
    P1DIR |= BV(3);      //P1.3����Ϊ��� 
	P1_3 = 1;
    UartInit(HAL_UART_PORT_1,HAL_UART_BR_115200);
    printf("this is uart1 print\r\n");
}
/*
ͨ��RS485���߷�������
*/
void RS485Bus_Send(void)
{
  
}