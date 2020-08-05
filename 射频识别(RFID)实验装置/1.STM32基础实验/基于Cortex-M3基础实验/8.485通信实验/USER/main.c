#include "stm32f1xx.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "key.h"
#include "led.h"

/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-12-31
*
*	�汾�� 		V1.0
*
*	˵���� 		485ͨ��ʵ��
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/

#define	Rs485_TX	1
#define	Rs485_RX	0

int main(void)
{
	HAL_Init();						//��ʼ��HAL��    
	LED_Init();						//��ʼ��LED	
	KEY_Init();						//��ʼ������
	Rs485_Init();					//��ʼ��485
	UART1_Init(115200);		//��ʼ������һ

	while(1)
	{

#if Rs485_TX	//����

		key_Operatio();	//�������Ϳ����������LED��

#endif

#if Rs485_RX	//����

		if(!DataHandling_485(Addr_LED))		//����485����
		{
			switch(Rx_Stack.Command)
			{
				case LED_ON1:
					LED1_ON();	//����LED1
					break;
				case LED_ON2:
					LED2_ON();	//����LED2
					break;
				case LED_ON3:
					LED3_ON();	//����LED3
					break;
				case LED_ON4:
					LED4_ON();	//����LED4
					break;
				case LED_OFF1:
					LED1_OFF();	//�ر�LED1
					break;
				case LED_OFF2:
					LED2_OFF();	//�ر�LED2
					break;
				case LED_OFF3:
					LED3_OFF();	//�ر�LED3
					break;
				case LED_OFF4:
					LED4_OFF();	//�ر�LED4
					break;
				case LED_Control://����4��LED��
					Rx_Stack.Data[0]==0?LED1_OFF():LED1_ON();
					Rx_Stack.Data[1]==0?LED2_OFF():LED2_ON();
					Rx_Stack.Data[2]==0?LED3_OFF():LED3_ON();
					Rx_Stack.Data[3]==0?LED4_OFF():LED4_ON();
					break;
				default: break;
			}
		}

#endif

	}
}




