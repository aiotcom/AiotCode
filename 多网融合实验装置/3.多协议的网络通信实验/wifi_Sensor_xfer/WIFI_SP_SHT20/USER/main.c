#include "stm32f1xx.h"
#include "string.h"
#include "delay.h"
#include "Usart.h"
#include "Rs485.h"
#include "WiFi.h"
#include "TIMER.h"
#include "WS2812b.h"
/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-01-01
*
*	�汾�� 		V1.0
*
*	˵���� 		LORAģ��
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
uint8_t WiFiSendBuffer[32],UpdataFlg = 0;
uint8_t WiFiReceiveBuffer[32],lenght=0;
void RS485_HandlerCb(void);
int main(void)
{
	uint8_t LedState = 1;

	HAL_Init();                     //��ʼ��HAL��       
    USART3_Init(115200);            //printf ��ӡ��Ϣ��PB10->TX,PB11->RX,ͨ��ֻʹ�ã�TX���� 
    printf("WIFI:usart3 print\r\n");//���Դ�ӡ��Ϣ
    
    WS2812B_Init();
    UART2_Init(115200);
    WiFi_Init();                    //WIFIģ���ʼ��
	Rs485_Init();				    //��ʼ��485
    TIM3_Init(10000-1,640-1,RS485_HandlerCb);//�ж�Ƶ��64M/640/10000=10HZ���ж�Ƶ��10HZ
	UART1_Init(115200);				//��ʼ������1
	
	while(1)
	{
        if(UpdataFlg)
        {//�����ݸ��·������ݣ�RS485_HandlerCb()�����и���UpdataFlg
            UpdataFlg = 0;
            WiFi_Send(WiFiSendBuffer,4);
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
//	˵����		��ʱ��3�жϣ��ص�������ÿ100ms����һ��
//==========================================================
void RS485_HandlerCb(void)
{
    static uint32_t PollCounter=0;
    static uint8_t state = 0;
    
    if(state == 0)
    {
        if((++PollCounter) >= 20)
        {//2000ms����һ����ѯָ��
            PollCounter = 0;
            Rs485_Send(Addr_WiFi,Addr_SHT20,SHT20_Get_All,  0,(void*)0); 
            state = 1;
        }
    }
    else if(state == 1)
    {
        if(!DataHandling_485(Addr_WiFi))
        {
            //printf("=%d,%d\r\n",Rx_Stack.Data[0],Rx_Stack.Data[1]);
            memcpy((void*)WiFiSendBuffer,Rx_Stack.Data,4);
            UpdataFlg = 1;
        }
        state = 0;    
    }
}
