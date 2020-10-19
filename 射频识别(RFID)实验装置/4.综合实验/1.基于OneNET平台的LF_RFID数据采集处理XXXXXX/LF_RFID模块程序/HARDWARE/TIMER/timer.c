#include "timer.h"
#include "led.h"
#include "stm32f1xx.h"
#include "delay.h"

unsigned char  led_flag = 0;  //LED��״̬��־
uint8_t TIM2_IntFlag=0;
TIM_HandleTypeDef TIM2_Handler;      //��ʱ����� 

//==========================================================
//	�������ƣ�	TIM2_Init
//
//	�������ܣ�	ͨ�ö�ʱ��3�жϳ�ʼ��
//
//	��ڲ�����	arr���Զ���װֵ��
//              psc��ʱ��Ԥ��Ƶ��
//
//	���ز�����	��
//
//	˵����		��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.   Ft=��ʱ������Ƶ��,��λ:Mhz
//==========================================================
void TIM2_Init(unsigned int arr,unsigned int psc)
{
    TIM2_Handler.Instance           = TIM2;                   //ͨ�ö�ʱ��2
    TIM2_Handler.Init.Prescaler     = psc;                   //��Ƶϵ��
    TIM2_Handler.Init.CounterMode   = TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM2_Handler.Init.Period        = arr;                   //�Զ�װ��ֵ
    TIM2_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM2_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM2_Handler); //ʹ�ܶ�ʱ��2�Ͷ�ʱ��2�����жϣ�TIM_IT_UPDATE   
    delay_us(100);
    __HAL_TIM_DISABLE(&TIM2_Handler);
    __HAL_TIM_SET_COUNTER(&TIM2_Handler,0);       //�����������ֵ
    TIM2_IntFlag = 0;
}

//==========================================================
//	�������ƣ�	HAL_TIM_Base_MspInit
//
//	�������ܣ�	ʹ�ܶ�ʱ��
//
//	��ڲ�����	
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM2)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();            //ʹ��TIM3ʱ��
		HAL_NVIC_SetPriority(TIM2_IRQn,1,3);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM2_IRQn);          //����ITM3�ж�   
	}
}

//==========================================================
//	�������ƣ�	void TIM2_Delay(uint16_t nus)
//
//	�������ܣ�	���ڶ�ʱ��2����ʱ����,����΢�����ʱ
//
//	��ڲ�����	uint16_t nus�������ʱΪ50ms
//
//	���ز�����	uint8_t ��ʱ������� 1
//
//	˵����		
//==========================================================
uint8_t TIM2_Delay(uint16_t nus)
{
    __HAL_TIM_SET_COUNTER(&TIM2_Handler,0); 
    __HAL_TIM_SET_AUTORELOAD(&TIM2_Handler,50000);
    __HAL_TIM_ENABLE(&TIM2_Handler);
    while(__HAL_TIM_GET_COUNTER(&TIM2_Handler) < nus);
    __HAL_TIM_DISABLE(&TIM2_Handler);    
    
    return 1;
}

//==========================================================
//	�������ƣ�	TIM2_IRQHandler
//
//	�������ܣ�	��ʱ��2�жϷ�����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void TIM2_IRQHandler(void)
{
    TIM2_IntFlag = 1;
    HAL_TIM_IRQHandler(&TIM2_Handler);
}




