#include "stm32f1xx_hal.h"
#include "Martix_Key.h"	
#include "stm32f1xx.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "Rs485.h"
/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-03-18
*
*	�汾�� 		V1.0
*
*	˵���� 		������̳���
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
void RS485_HandlerCb(void);
uint8_t TheKeyValue;
int main(void)
{
    HAL_Init();             					//��ʼ��HAL��  
	KEY_Init();												//��ʼ������
	UART1_Init(115200);								//��ʼ�����ڶ�
    Rs485_Init();
	TIM3_Init(10000-1,64-1,RS485_HandlerCb);					//��ʼ����ʱ���ж�����64M/64/10000/ = 100HZ
    
    USART3_Init(115200);
	while(1)
	{
        TheKeyValue = KEY_Process();  								//���հ�������
	}
}
//==========================================================
//	�������ƣ�	void RS485_HandlerCb(void)
//
//	�������ܣ�	ͨ��485���߻�ȡ���ݴ�����
//
//	��ڲ�����	void
//
//	���ز�����	��
//
//	˵����		��ʱ��3�жϣ��ص�������ÿ10ms����һ��
//==========================================================
void RS485_HandlerCb(void)
{  
    static uint16_t command;
    if((!DataHandling_485(Addr_Matrixkey))&&(Rx_Stack.Command == Matrixkey_Get_value))
    {
        //printf("get req\r\n");
        if(TheKeyValue != KEY_NULL)
        {
            command = FindKeyValue2Command(TheKeyValue);
            Rs485_Send(Addr_Matrixkey,Addr_Linux,command,1,&TheKeyValue);
            TheKeyValue = KEY_NULL;
        }
    }        
}


