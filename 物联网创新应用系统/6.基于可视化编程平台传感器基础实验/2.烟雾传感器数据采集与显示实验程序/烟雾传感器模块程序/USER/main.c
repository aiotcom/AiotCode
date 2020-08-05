#include "stm32f1xx_hal.h"
#include "Smoke_Sensor.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "ADC.h"

/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2020-03-09
*
*	�汾�� 		V1.0
*
*	˵���� 		��������
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/

int main(void)
{
  HAL_Init();             		//��ʼ��HAL��  
	ADC_Init();									//��ʼ��ADC
	Rs485_Init();								//��ʼ��485
	UART1_Init(115200);					//��ʼ������1
	Smoke_Sensor_Init();				//��ʼ����������

	while(1)
	{
		Data_Conversion();				//�������Ũ��ת���ٷְ�
		
		if(!DataHandling_485(Addr_Smoke))		//����485����
		{
			Rs485_Send(Addr_Smoke,Rx_Stack.Src_Adr,Smoke_State,1,Data_Smoke_WiFi);	//�������ݵ�WiFiģ��
		}
		
		if(Smoke_Read())
		{
			 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 ,GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 ,GPIO_PIN_RESET);
			 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);
		}
		else
		{
			 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 ,GPIO_PIN_RESET);
			 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 ,GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);
		}
	}
}


