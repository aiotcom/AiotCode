#include "TFT.h"
#include "exti.h"
#include "delay.h"

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
    
    __HAL_RCC_GPIOA_CLK_ENABLE();               	//����GPIOAʱ��

    GPIO_Initure.Pin=GPIO_PIN_12;									//PA12
    GPIO_Initure.Mode=GPIO_MODE_IT_RISING;     		//�����ش���
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
	  HAL_NVIC_SetPriority(EXTI15_10_IRQn,1,1);   	//��ռ���ȼ�Ϊ1�������ȼ�Ϊ1
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);         	//ʹ���ж���
}

//==========================================================
//	�������ƣ�	EXTI15_10_IRQnHandler
//
//	�������ܣ�	�жϷ�����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void EXTI15_10_IRQHandler(void)
{
		if(!touch_fig)			//����������
		{
			touch_fig = 1;	//һ�νӴ����
		}
	
   HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);		//�����жϴ����ú���
}


