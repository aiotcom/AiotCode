#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "timer.h"
#include "WiFi.h"
#include "WS2812B.h"
/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-04-22
*
*	�汾�� 		V1.0
*
*	˵���� 		WiFi����
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
void RS485_HandlerCb(void);
uint8_t RxBuffer[4];
uint8_t SendToOneNET[20];
uint32_t SendTicks;
int main(void)
{
    HAL_Init();             					//��ʼ��HAL��  
	Rs485_Init();								//��ʼ��485
	UART1_Init(115200);						    //��ʼ������1
	UART2_Init(115200);						    //��ʼ������2
	UART3_Init(115200);						    //��ʼ������3    
    WS2812B_Init();                             //��ʼ��ȫ�ʵ�WS2812B
	    
    WiFi_Init();							    //��ʼ��WiFi
	TIM2_Init(1000-1,64-1);						//��ʼ����ʱ��2(1ms)
    SendTicks = HAL_GetTick()+2000;
    TIM3_Init(10000-1,640-1,RS485_HandlerCb);//�ж�Ƶ��64M/640/10000=10HZ���ж�Ƶ��10HZ    
	while(1)
	{
        if(HAL_GetTick() >= SendTicks)
        {
            SendTicks = HAL_GetTick() + 2000;            
            sprintf((char *)SendToOneNET,"%d%d%d",RxBuffer[0],RxBuffer[1],((RxBuffer[3]<<8)|(RxBuffer[2])));
            printf("=%s\r\n",SendToOneNET);
            HAL_UART_Transmit(&UART2_Handler,SendToOneNET,8,1000);	//�������ݵ�OneNET  
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
            Rs485_Send(Addr_WiFi,Addr_2_4G,SHT20_Get_All,  0,(void*)0); 
            state = 1;
        }
    }
    else if(state == 1)
    {
        if(!DataHandling_485(Addr_WiFi))
        {           
            memcpy((void*)RxBuffer,Rx_Stack.Data,4);
        }
        state = 0;    
    }
}





