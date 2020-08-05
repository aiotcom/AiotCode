#include "stm32f1xx_hal.h"
#include "MsgHandler.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "timer.h"
#include "M5310.h"
#include "nbiot.h"
#include "utils.h"
#include "coap.h"

/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-04-18
*
*	�汾�� 		V1.0
*
*	˵���� 		����NB-IoT������ʪ�ȴ�����ʵ��
*
*	�޸ļ�¼��
************************************************************
************************************************************
************************************************************
**/

int main(void)
{
  HAL_Init();             					//��ʼ��HAL��  
	Rs485_Init();											//��ʼ��485
	M5310_Power_Init(); 							//M5310�ĸ�λ����IO��ʼ��
	UART1_Init(115200);								//��ʼ������1
	UART2_Init(9600);									//��ʼ������2
	netdev_init();      							//��ʼ��M5310
  init_miplconf(86400,coap_uri,endpoint_name);//�ϱ�ע����
	Subscription_esources();					//���� Object ������
	m5310_register_request();         //������½����
	delay_ms(1000);
	TIM2_Init(1000-1,64-1);						//��ʼ����ʱ��2(1ms)

	while(1)
	{
		msgcode = Msg_Handler();				//�������ݽ���
		USART_Data_Send();							//�������ݷ���
		USART1_IRQHand();								//����1���ݴ���(485���ݴ���)
	}
}






