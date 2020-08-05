#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "usart.h"
#include "Rs485.h"
#include "TFT.h"
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
*	˵���� 		TFT����ʵ��-HAL��汾
*
*	�޸ļ�¼��	
************************************************************

************************************************************
************************************************************
**/
void RS485_HandlerCb(void);
uint8_t ucArray_ID[10];
uint8_t SendData[40];
uint8_t GetId = 0;
int main(void)
{
    uint8_t i = 0;
    HAL_Init();             //��ʼ��HAL��
    TFT_Init();             //��ʼ��TFT��ʾ���˿�
    Rs485_Init();			//��ʼ��485
    UART1_Init(115200);		//��ʼ������
    Lcd_Init();				//��ʼ��LCD
    LCD_UI();				//����UI
	TIM3_Init(10000-1,3200-1,RS485_HandlerCb);	//��ʼ����ʱ���ж�����64M/32/10000/ = 2HZ
    while(1)
    {
        if(GetId)
        {
            GetId = 0;
            for(i = 0;i < 8;i ++)
            {//ת����ASCII
                if(i%2==0)
                {
                    DataRep((ucArray_ID[(i/2)]>>4),i,1,1);
                }
                else
                {
                    DataRep((ucArray_ID[(i/2)]&0x0f),i,0,1);
                }
            }

            if(!(!ucArray_ID[0] && !ucArray_ID[1] && !ucArray_ID[2] && !ucArray_ID[3]))
            {
                LCD_ShowString(60,80,SendData,0);			
            } 
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
	static uint16_t i = 0,state = 0;

    if(state == 0)
    {
        Rs485_Send(Addr_LCD,Addr_HF_RFID,NFC_Get_ID,0,(void*)0);
        state = 1;   
    }   
    else if(state == 1)
    {
        if(!DataHandling_485(Addr_LCD))		//��������
        {
            if(Rx_Stack.Src_Adr == Addr_HF_RFID)	//����LF-RFID������
            {
                for(i=0;i<4;i++)
                {
                    ucArray_ID[i] = Rx_Stack.Data[i];
                }
                GetId = 1;    
            }
        }
        state = 0;
    }
}




