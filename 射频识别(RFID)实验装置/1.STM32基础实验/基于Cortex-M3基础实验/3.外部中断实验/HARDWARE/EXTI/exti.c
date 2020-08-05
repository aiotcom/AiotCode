#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "stm32f1xx.h"

unsigned char Key_flag = 0;  //������־

//==========================================================
//	�������ƣ�	EXTI_Init
//
//	�������ܣ�	�ⲿ�жϳ�ʼ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();               //����GPIOAʱ��

    GPIO_Initure.Pin=S1_PIN|S2_PIN; 						//����S1��S2
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //�½��ش���
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(KEY1_PORT,&GPIO_Initure);

		HAL_NVIC_SetPriority(EXTI4_IRQn,1,1);      	//��ռ���ȼ�Ϊ1�������ȼ�Ϊ1
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);            	//ʹ���ж���
	
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,1,1);    	//��ռ���ȼ�Ϊ1�������ȼ�Ϊ1
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);          	//ʹ���ж���
}

//==========================================================
//	�������ƣ�	EXTI4_IRQHandler()
//
//	�������ܣ�	�жϷ�����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(S2_PIN);		//�����жϴ����ú���
}

//==========================================================
//	�������ƣ�	EXTI9_5_IRQHandler()
//
//	�������ܣ�	�жϷ�����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(S1_PIN);		//�����жϴ����ú���
}

//==========================================================
//	�������ƣ�	HAL_GPIO_EXTI_Callback
//
//	�������ܣ�	�жϷ������
//
//	��ڲ�����	GPIO_Pin:�ж����ź�
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(!Key_flag)
	{
		switch(GPIO_Pin)
		{
			case S1_PIN:
				Key_flag = 1;
				break;
			case S2_PIN:
				Key_flag = 2;
				break;
			default:break;
		}
	}
}
