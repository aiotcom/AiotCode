#include "stm32f1xx.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "timer.h"
#include "EM4095.h"
#include "usart.h"
#include "Rs485.h"
/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-12-17
*
*	�汾�� 		V2.0
*
*	˵���� 		LF-RFIDģ��
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
enum{CARD_ON,CARD_OFF};
void RS485_HandlerCb(void);
uint8_t GetId = 0;
uint8_t CardID[5]={0,0,0,0,0};
uint16_t count = 0,cardstate = CARD_OFF;
int main(void)
{
	HAL_Init();              //��ʼ��HAL��  
	Rs485_Init();    		 //��ʼ��485
	EM4095_Init();			 //��ʼ��EM4095
	UART1_Init(115200);		 //��ʼ������1
	TIM2_Init(2000-1,64-1);	 //��ʼ����ʱ��2(2ms�ж�)
    UART2_Init(115200);		 //��ʼ������1
    USART3_Init(115200);
    printf("usart3 print\r\n");
    TIM3_Init(10000-1,64-1,RS485_HandlerCb);	//��ʼ����ʱ���ж�����64M/64/10000/ = 100HZ
	while(1)
	{
        HAL_Delay(1);
        if(EM4095_SearchHdr(CardID)){
            count     = 0;
            cardstate = CARD_ON;
        }
        else{
            if((++count) >= 1000){
                count     = 0;
                cardstate = CARD_OFF;
                CardID[0] = 0;
                CardID[1] = 0;
                CardID[2] = 0;
                CardID[3] = 0;
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
    static uint8_t mark = 0;
    if(!DataHandling_485(Addr_LF_RFID))		//��������
    {
        if(Rx_Stack.Src_Adr == Addr_LCD)	//����LF-RFID������
        {
            printf("mark=%d\r\n",mark++);
            Rs485_Send(Addr_LF_RFID,Addr_LCD,LF_RFID_ID,4,CardID);			//����ID����
        }
    }
}




