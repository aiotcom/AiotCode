#include "SW420.h"
#include "delay.h"

uint8_t SW420_fig = 0;
uint8_t Shock_Fre[10];			//��Ƶ��

//==========================================================
//	�������ƣ�	SW420_Init()
//
//	�������ܣ�	��ʼ���𶯴�����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			��⵽�͵�ƽ��
//==========================================================
void SW420_Init(void)
{
	  GPIO_InitTypeDef GPIO_Initure;

		__HAL_RCC_GPIOA_CLK_ENABLE();						//����GPIOAʱ��

		GPIO_Initure.Pin = SW420_OUT0|SW420_OUT1;
		GPIO_Initure.Mode = GPIO_MODE_INPUT;   	//��������
		GPIO_Initure.Pull = GPIO_NOPULL;				//����
		HAL_GPIO_Init(SW420_GPIO_PORT, &GPIO_Initure);
}

//==========================================================
//	�������ƣ�	SW420_Fig()
//
//	�������ܣ�	�����
//
//	��ڲ�����	��
//
//	���ز�����	SW420_fig = 1:��ʾ����
//							SW420_fig = 0:��ʾ����
//
//	˵����			��⵽�͵�ƽ��
//==========================================================
void SW420_Fig(void)
{
	if(!SW420_OUT0_STATE() || !SW420_OUT1_STATE())
	{
		if(!SW420_OUT0_STATE() && !SW420_OUT1_STATE())
		{
			SW420_fig = 1;
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 ,GPIO_PIN_RESET);
		}
	}
	else
	{
		SW420_fig = 0;
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 ,GPIO_PIN_SET);
	}
}











