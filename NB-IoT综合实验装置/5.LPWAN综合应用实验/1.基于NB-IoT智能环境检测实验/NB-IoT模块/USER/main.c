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
*	˵���� 		����NB-IoT���ܻ������ʵ��
*
*	�޸ļ�¼��
*
************************************************************
************************************************************
************************************************************
**/

uint8_t SendOneNET[10];
uint16_t Light_Intensity;
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
		msgcode = Msg_Handler();							//�������ݽ���
		
		if(!DataHandling_485(Addr_NB))				//����485�д����NBģ�������
		{
			if(Rx_Stack.Src_Adr == Addr_SHT20)	//������ʪ�ȹ�ǿ����
			{
				memset((void*)SendOneNET,0,10);
				sprintf((char *)SendOneNET,"%0.2f",(float)Rx_Stack.Data[0]);
				m5310_notify_upload(&temp_uri,NBIOT_FLOAT,(char*)&SendOneNET[0],1,0);	//�ϴ��¶�����
				
				memset((void*)SendOneNET,0,10);
				sprintf((char *)SendOneNET,"%0.2f",(float)Rx_Stack.Data[1]);
				m5310_notify_upload(&humi_uri,NBIOT_FLOAT,(char*)&SendOneNET[0],1,0);	//�ϴ�ʪ������
				
				memset((void*)SendOneNET,0,10);
				Light_Intensity = Rx_Stack.Data[2]*256+Rx_Stack.Data[3];
				sprintf((char *)SendOneNET,"%0.0f",(float)Light_Intensity);
				m5310_notify_upload(&illum_uri,NBIOT_FLOAT,(char*)&SendOneNET[0],1,0);	//�ϴ���ǿ����
			}
		}
	}
}






