#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "Rs485.h"
#include "usart.h"
#include "delay.h"
#include "Relay.h"

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
*	˵���� 		�̵�������
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/

int main(void)
{
  HAL_Init();             		//��ʼ��HAL��  
	Relay_Init();   						//��ʼ���̵���
	Rs485_Init();								//��ʼ��485
	UART1_Init(115200);					//��ʼ������һ

	while(1)
	{
		if(!DataHandling_485(Addr_Relay))//���շ��͵��̵���������
		{
			if(Rx_Stack.Command == Relay1_ON)
			{
				RELAY1_OPEN();	 //�򿪼̵���1
				delay_ms(3000);
				RELAY1_CLOSE();  //�رռ̵���1
			}
			else if(Rx_Stack.Command == Relay1_OFF)
			{
				RELAY1_CLOSE();  //�رռ̵���1
			}
			else if(Rx_Stack.Command == Relay2_ON)
			{
				RELAY2_OPEN();	 //�򿪼̵���2
				delay_ms(3000);
				RELAY2_CLOSE();  //�رռ̵���2
			}
			else if(Rx_Stack.Command == Relay2_OFF)
			{
				RELAY2_CLOSE();  //�رռ̵���2
			}
		}
	}
}




