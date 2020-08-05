#include "MsgHandler.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
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
*	���ڣ� 		2020-03-19
*
*	�汾�� 		V1.0
*
*	˵���� 		STM32F767-NB-IoTģ��ʵ��
*
*	�޸ļ�¼��
************************************************************
************************************************************
************************************************************
**/

uint8_t uiuiui[10] = {1,2,3,4,5};

int main(void)
{
	HAL_Init();       		//��ʼ��HAL��
	Rs485_Init();					//��ʼ��485
	M5310_Power_Init(); 	//M5310�ĸ�λ����IO��ʼ��
	UART1_Init(9600);			//��ʼ������1
	UART7_Init(115200);		//��ʼ������7
	netdev_init();      	//��ʼ��M5310
  init_miplconf(86400,coap_uri,endpoint_name);//�ϱ�ע����
	Subscription_esources();					//���� Object ������
	m5310_register_request();         //������½����
	delay_ms(1000);

	while(1)
	{
//		HAL_UART_Transmit(&UART1_Handler,uiuiui,5,1000);
//		delay_ms(1000);
		msgcode = Msg_Handler();				//�������ݽ���
	}
}



