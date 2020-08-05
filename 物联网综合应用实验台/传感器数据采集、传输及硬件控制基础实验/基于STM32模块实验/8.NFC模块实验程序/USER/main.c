#include "Rs485.h"
#include "usart.h"
#include "delay.h"
#include "PN532.h"
#include "NFC.h"

/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2020-02-20
*
*	�汾�� 		V1.0
*
*	˵���� 		STM32F767-NFCģ��ʵ��
*
*	�޸ļ�¼��
************************************************************
************************************************************
************************************************************
**/

uint32_t NFC_CardID2 = 0;
uint8_t Secret_Key2[6] = {0xff,0xff,0xff,0xff,0xff,0xff};//��Կ����
uint8_t NFC_Data[20];

int main(void)
{
	HAL_Init();       		//��ʼ��HAL��   
	PN532_Init();    			//��ʼ��PN532
	Rs485_Init();					//��ʼ��485
	UART7_Init(115200);		//��ʼ��������
	PN532_CSn_L;					//����PN532
	delay_ms(10);
	PN532_CSn_H;
	SAMConfig();					//��ʼ��оƬ����
	delay_ms(500);				//��ʱ�ȴ�

	while(1)
	{
		NFC_CardID2 = readPassiveTargetID(0x00);//0x00 s50�� 106kbps Ѱ��

		if(NFC_CardID2)
		{		
			if(authenticateBlock(1,NFC_CardID2,0x05,KEY_A,Secret_Key2))			//��֤��ԿA
			{
				if(readMemoryBlock(1,0x05,NFC_Data))//��ȡ����
				{

				}
			}
		}
	}
}



