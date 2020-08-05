#include "stm32f1xx.h"
#include "delay.h"
#include "led.h"
#include "Usart.h"
#include "string.h"
#include "NFC.h"
#include "PN532.h"
#include "timer.h"
#include "Rs485.h"
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
*	˵���� 		NFCģ��
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/

uint32_t NFC_CardID2 = 0;
uint8_t Secret_Key2[6] = {0xff,0xff,0xff,0xff,0xff,0xff};//��Կ����
uint8_t NFC_SendBuffer[32];
uint8_t Set_NFC_Memblock = 0;
uint8_t Buffer_WriteMemblock[32];
void RS485_HandlerCb(void);
int main(void)
{
    HAL_Init();  							//��ʼ��HAL��
    PN532_Init();    					//��ʼ��PN532    
    USART3_Init(115200);				//��ʼ������2
    PN532_CSn_L;							//����PN532
    delay_ms(10);
    PN532_CSn_H;
    SAMConfig();							//��ʼ��оƬ����
    delay_ms(500);						//��ʱ�ȴ�
    printf("usart3 print\r\n");
    
    UART1_Init(115200);
    Rs485_Init();
	TIM3_Init(1000-1,640-1,RS485_HandlerCb);					//��ʼ����ʱ���ж�����64M/640/1000/ = 100HZ    
    while(1)
    {
        NFC_CardID2 = readPassiveTargetID(0x00);//0x00 s50�� 106kbps Ѱ��

        if(NFC_CardID2)
        {		         
            if(authenticateBlock(1,NFC_CardID2,0x05,KEY_A,Secret_Key2))			//��֤��ԿA
            {
                if(Set_NFC_Memblock)
                {
                    Set_NFC_Memblock = 0;
                    printf("write nfc block\r\n");
                    printf("---%c%c%c\r\n",Buffer_WriteMemblock[0],Buffer_WriteMemblock[1],Buffer_WriteMemblock[2]);
                    if(writeMemoryBlock(1,05, Buffer_WriteMemblock) ) 
                    {
                        printf("write nfc block success\r\n");
                    }                        
                }
                else if(readMemoryBlock(1,0x05,&NFC_SendBuffer[4]))//��ȡ����
                {
                   memcpy(NFC_SendBuffer,(const void*)&NFC_CardID2,4);
                }
                

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
//	˵����		��ʱ��3�жϣ��ص�������ÿ100ms����һ��
//==========================================================
void RS485_HandlerCb(void)
{  
    if(!DataHandling_485(Addr_NFC))
    {
        if(Rx_Stack.Command == NFC_Get_All)
        {
            Rs485_Send(Addr_NFC,Addr_LCD,NFC_ID,20,NFC_SendBuffer);
        }
        else if(Rx_Stack.Command == NFC_Set_Memblock)
        {
            printf("write nfc block---\r\n");
            memcpy((void*)Buffer_WriteMemblock,(const void*)Rx_Stack.Data,16);
            Set_NFC_Memblock = 1;
        }            
    }        
}
