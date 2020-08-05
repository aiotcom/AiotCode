#include "timer.h"
#include "Usart.h"
#include "Rs485.h"

TIM_HandleTypeDef TIM3_Handler;   	//��ʱ����� 
static void (*TIMCb)(void);            //�ص�������ָ��

//==========================================================
//	�������ƣ�	TIM3_Init
//
//	�������ܣ�	ͨ�ö�ʱ��3�жϳ�ʼ��
//
//	��ڲ�����	
//							arr���Զ���װֵ��
//							psc��ʱ��Ԥ��Ƶ��
//							��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//							Ft=��ʱ������Ƶ��,��λ:Mhz
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void TIM3_Init(uint16_t arr,uint16_t psc,void (*cb)(void))
{  
    TIM3_Handler.Instance        = TIM3;                          //ͨ�ö�ʱ��3
    TIM3_Handler.Init.Prescaler  = psc;                     //��Ƶϵ��
    TIM3_Handler.Init.CounterMode= TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM3_Handler.Init.Period     = arr;                        //�Զ�װ��ֵ
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM3_Handler);
    
    TIMCb = cb;
    HAL_TIM_Base_Start_IT(&TIM3_Handler); //ʹ�ܶ�ʱ��3�Ͷ�ʱ��3�����жϣ�TIM_IT_UPDATE   
}

//==========================================================
//	�������ƣ�	HAL_TIM_Base_MspInit
//
//	�������ܣ�	��ʱ���ײ�����������ʱ�ӣ������ж����ȼ�
//
//	��ڲ�����	
//
//	���ز�����	��
//
//	˵����			�˺����ᱻHAL_TIM_Base_Init()��������
//==========================================================
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  if(htim->Instance==TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();            //ʹ��TIM3ʱ��
		HAL_NVIC_SetPriority(TIM3_IRQn,1,3);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM3_IRQn);          //����ITM3�ж�   
	}
}

//==========================================================
//	�������ƣ�	TIM3_IRQHandler
//
//	�������ܣ�	��ʱ��3�жϷ�����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM3_Handler);
    TIMCb();
}









