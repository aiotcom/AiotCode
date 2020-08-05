#include "stm32f1xx.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "led.h"

/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-03-18
*
*	�汾�� 		V1.0
*
*	˵���� 		LED����
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/

int main(void)
{
	HAL_Init();						//��ʼ��HAL��    
	LED_Init();						//��ʼ��LED	
	Rs485_Init();					//��ʼ��485
	UART1_Init(115200);		//��ʼ������һ

	while(1)
	{
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
				default: break;
			}
		}
	}
}




