#include "stm32f1xx.h"
#include "string.h"
#include "delay.h"
#include "RC522.h"
#include "usart.h"	
#include "timer.h"
#include "rs485.h"	
/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-12-11
*
*	�汾�� 		V2.0
*
*	˵���� 		HF-RFID
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
void RS485_HandlerCb(void);
uint8_t SendBuffer[32];
uint8_t GetData = 0;
uint8_t CardId[5],BlockData[32];
int main(void)
{
	HAL_Init();           		//��ʼ��HAL��
    Rs485_Init();
	RC522_Init();     				//��ʼ��RC522ģ��
	UART2_Init(115200);				//��ʼ������2

    UART1_Init(115200);						    //��ʼ������1
    TIM3_Init(10000-1,64-1,RS485_HandlerCb);	//��ʼ����ʱ���ж�����64M/64/10000/ = 100HZ
	while(1)
	{
		GetData = IC_Card_Search(CardId,BlockData);				//��⿨-��⵽�����ݷ���
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
    if((!DataHandling_485(Addr_HF_RFID))&&(Rx_Stack.Command == HF_RFID_Get_ID))
    {
        printf("get cmd\r\n");
        if(GetData)
        {
            GetData = 0;
            memcpy((void*)SendBuffer,(const void*)CardId,4);
            Rs485_Send(Addr_HF_RFID,Addr_Linux,HF_RFID_ID,4,SendBuffer);
        }
    }        
}


