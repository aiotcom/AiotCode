#include "stm32f1xx_hal.h"
#include "Smoke_Sensor.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"

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
uint8_t Data_Smoke[2];

int main(void)
{
  HAL_Init();             		//��ʼ��HAL��  
	Rs485_Init();								//��ʼ��485
	UART1_Init(115200);					//��ʼ������1
	Smoke_Sensor_Init();				//��ʼ����������

	while(1)
	{
		if(!DataHandling_485(Addr_Smoke))		//����485����
		{
			Rs485_Send(Addr_Smoke,Rx_Stack.Src_Adr,Smoke_State,1,Data_Smoke);	//�������ݵ�WiFiģ��
		}
		
		if(Smoke_Read())
		{
			 Data_Smoke[0] = 1;
			 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 ,GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 ,GPIO_PIN_RESET);
			 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);
		}
		else
		{
			 Data_Smoke[0] = 0;
			 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 ,GPIO_PIN_RESET);
			 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 ,GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);
		}
	}
}

