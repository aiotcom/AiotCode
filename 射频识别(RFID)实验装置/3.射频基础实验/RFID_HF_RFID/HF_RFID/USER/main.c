#include "stm32f1xx.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "usart.h"	
#include "RC522.h"
#include "Rs485.h"	
#include "string.h"
#include "timer.h"
/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2018-01-01
*
*	�汾�� 		V1.0
*
*	˵���� 		������������ʵ��-HAL��汾
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
void RS485_HandlerCb(void);
uint8_t DataToIC_Card[16]={1,2,3,5,6,7,8,9,0,1,2,3,4,5,6};//����д��IC������Ϣ
uint8_t kv;
uint8_t count = 0;
uint8_t SendBuf[16];
int main(void)
{
    uint8_t index;  
    uint8_t i;
    HAL_Init();             //��ʼ��HAL��

    USART3_Init(115200);		//��ʼ������    
    printf("usart3 print\r\n");
    RC522_Init ();     //RC522ģ���ʼ��    
    delay_ms(200);	

    Rs485_Init();
    UART1_Init(115200);		//��ʼ������
    
    TIM3_Init(10000-1,640-1,RS485_HandlerCb);	//��ʼ����ʱ���ж�����64M/64/10000/ = 10HZ
	while(1)
	{
        if(IC_Card_Search(SendBuf))//IC�����  
        {
            //printf("%d,%d,%d,%d\r\n",SendBuf[0],SendBuf[1],SendBuf[2],SendBuf[3]);
        }    
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
    if(!DataHandling_485(Addr_HF_RFID))		//��������
    {
        if(Rx_Stack.Src_Adr == Addr_LCD)	//����LF-RFID������
        {
            Rs485_Send(Addr_HF_RFID,Addr_LCD,HF_RFID_ID,4,SendBuf);
        }
    }
}
