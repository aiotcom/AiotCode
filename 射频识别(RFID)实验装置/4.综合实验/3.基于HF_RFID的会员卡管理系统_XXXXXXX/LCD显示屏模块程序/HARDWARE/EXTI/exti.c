#include "TFT.h"
#include "exti.h"
#include "delay.h"
#include "stm32f1xx.h"

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
    
    __HAL_RCC_GPIOB_CLK_ENABLE();               	//����GPIOBʱ��

    GPIO_Initure.Pin=GPIO_PIN_14;									//PB14
    GPIO_Initure.Mode=GPIO_MODE_IT_RISING;     		//�����ش���
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
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
	
   HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);		//�����жϴ����ú���
}


