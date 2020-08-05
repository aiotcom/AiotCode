#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "Rs485.h"
#include "usart.h"

//==========================================================
//	�������ƣ�	Rs485_Init()
//
//	�������ܣ�	��ʼ��485
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			 
//==========================================================
void Rs485_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
	
    __HAL_RCC_GPIOF_CLK_ENABLE();           	//����GPIOFʱ��

		GPIO_Initure.Pin = GPIO_PIN_8;						//PF8
		GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;	//�������
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW; //����
		HAL_GPIO_Init(GPIOF, &GPIO_Initure);

		RS485_RX_EN();   													//��ʼ��Ϊ����ģʽ
}

//==========================================================
//	�������ƣ�	Rs485_Send()
//
//	�������ܣ�	�������ݵ�485������
//
//	��ڲ�����	*pData:����
//							Len		:���ݳ���
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Rs485_Send(uint8_t *pData,uint8_t Len)
{
	RS485_TX_EN();		//����485����
	Rs485_delay_ms(2);
	HAL_UART_Transmit(&UART7_Handler,pData,Len,1000);//485��������
	Rs485_delay_ms(1);
	RS485_RX_EN();		//����485����
}

//==========================================================
//	�������ƣ�	Rs485_delay_ms()
//
//	�������ܣ�	������ʱ����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Rs485_delay_ms(unsigned int nms)
{
	unsigned int i = 0,j = 0;
	
	for(i = 0;i<nms;i++)
	{
		for(j = 0;j<9600;j++)
		{;}
	}
}


