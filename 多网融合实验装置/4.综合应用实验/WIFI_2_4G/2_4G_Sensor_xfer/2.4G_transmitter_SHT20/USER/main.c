#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "string.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "timer.h"
#include "main.h"
#include "24l01.h"

/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-03-18
*
*	�汾�� 		V1.2
*
*	˵���� 		2.4Gģ�����
*
*	�޸ļ�¼��
************************************************************
************************************************************
************************************************************
**/
void RS485_HandlerCb(void);
#define RF_CHANNEL  0x40

uint8_t NRF_TxBuffer[32] = {"on"},NRF_RxBuffer[32];//NRF24L01 ÿ�η�������ֽ��� ��32���ֽ�
uint8_t UpdataFlg=0;
void Platform_RGB_LED_Init(void);
uint32_t GetSensorCount = 0; 
int main(void)
{
    uint8_t state = 0;
    HAL_Init();             	    //��ʼ��HAL��  
	Rs485_Init();				    //��ʼ��485
    TIM3_Init(10000-1,640-1,RS485_HandlerCb);//�ж�Ƶ��64M/640/10000=10HZ���ж�Ƶ��10HZ
	UART1_Init(115200);				//��ʼ������1
    USART3_Init(115200);            //printf ��ӡ��Ϣ��PB10->TX,PB11->RX,ͨ��ֻʹ�ã�TX����
    NRF24L01_Init();                //��ʼ��NRF24L01����оƬ
    
    while(NRF24L01_Check()&&1)
    {//nrf24l01Ӳ��������ʾ����
        printf("nrf24l01 check  error\r\n");
        HAL_Delay(1000);
    }
    printf("nrf24l01 check  OK\r\n");
    NRF24L01_TX_Mode(RF_CHANNEL);    
    while(1)
    {
        if(UpdataFlg)
        {
            printf("send\r\n");
            UpdataFlg = 0;
            NRF24L01_TxPacket(NRF_TxBuffer);
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
        if((++PollCounter) >= 5)
        {//500ms����һ����ѯָ��
            PollCounter = 0;
            Rs485_Send(Addr_2_4G,Addr_SHT20,SHT20_Get_All,  0,(void*)0); 
            state = 1;
        }
    }
    else if(state == 1)
    {
        if(!DataHandling_485(Addr_2_4G))
        {
            //printf("=%d,%d\r\n",Rx_Stack.Data[0],Rx_Stack.Data[1]);
            memcpy((void*)NRF_TxBuffer,Rx_Stack.Data,4);
            UpdataFlg = 1;
        }
        state = 0;    
    }
}

