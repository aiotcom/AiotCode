#include "stm32f1xx.h"
#include "delay.h"
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
uint8_t LF_HRFID_CardID[5];
uint8_t GetId = 0;
void RS485_HandlerCb(void);
int main(void)
{
	HAL_Init();                                 //��ʼ��HAL��  
	Rs485_Init();    							//��ʼ��485
	EM4095_Init();								//��ʼ��EM4095
	UART1_Init(115200);						    //��ʼ������1
	UART2_Init(115200);						    //��ʼ������1    
	TIM2_Init(2000-1,64-1);				        //��ʼ����ʱ��2(2ms�ж�)
    TIM3_Init(10000-1,64-1,RS485_HandlerCb);	//��ʼ����ʱ���ж�����64M/64/10000/ = 100HZ
    printf("debug\r\n");
	while(1)
	{
		if(EM4095_SearchHdr(LF_HRFID_CardID) == GET_ID)
        {
            HAL_Delay(50);
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
    if((!DataHandling_485(Addr_LF_RFID))&&(LF_RFID_All == Rx_Stack.Command))
    {
        if(LF_HRFID_CardID[0]||LF_HRFID_CardID[1]||LF_HRFID_CardID[2]||LF_HRFID_CardID[3])
        {
            GetId = 0;
            Rs485_Send(Addr_LF_RFID,Addr_LinuxP,LF_RFID_ID,5,&LF_HRFID_CardID[0]);
            LF_HRFID_CardID[0] = 0;
            LF_HRFID_CardID[1] = 0;
            LF_HRFID_CardID[2] = 0;
            LF_HRFID_CardID[3] = 0;
            printf("requery\r\n");
        }
    }        
}




