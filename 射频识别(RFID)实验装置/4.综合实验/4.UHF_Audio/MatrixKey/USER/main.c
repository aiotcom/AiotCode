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
uint8_t KeyValue;
int main(void)
{
    HAL_Init();             					//��ʼ��HAL��  
	KEY_Init();												//��ʼ������
	UART1_Init(115200);								//��ʼ�����ڶ�
    Rs485_Init();
    USART3_Init(115200);
    printf("usart3 printf\r\n");
    TIM3_Init(10000-1,64-1,RS485_HandlerCb);	//��ʼ����ʱ���ж�����64M/64/10000/ = 100HZ
	while(1)
	{
        KeyValue = KEY_Process();  								//���հ�������
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
//	˵����		����ͨ��485���߷��͹�������������
//==========================================================
void RS485_HandlerCb(void)
{
    uint16_t command;
    uint8_t item = 0xff;
    if(!DataHandling_485(Addr_Matrixkey))	
    {
        if(KeyValue != KEY_NULL)
        {
            printf("KeyValue=%d\r\n",KeyValue);
        }
        switch(KeyValue)
        {
            case KEY_LEFT:
                command = MP3_Last_Song;
                break;
            case KEY_RIGHT:
                command = MP3_Next_Song;
                break;
            case KEY_1:
            case KEY_2:
            case KEY_3:
                command = MP3_Target;
                item    = KeyValue;
                break;
            case KEY_CANNCEL:
                command = MP3_Start_Pause;
                break;
            default:
                command = 0;
                item = 0;
                break;
        }
        KeyValue = KEY_NULL;
        Rs485_Send(Addr_Matrixkey,Addr_UHF_RFID,command,1,&item);
    }    
}

