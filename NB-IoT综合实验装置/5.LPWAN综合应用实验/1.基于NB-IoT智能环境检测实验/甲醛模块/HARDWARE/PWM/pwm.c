#include "pwm.h"

TIM_HandleTypeDef 	TIM2_Handler;     //��ʱ����� 
TIM_OC_InitTypeDef 	TIM2_CH2Handler;	//��ʱ��2ͨ��2���

//==========================================================
//	�������ƣ�	TIM2_PWM_Init
//
//	�������ܣ�	TIM2 PWM���ֳ�ʼ�� 
//
//	��ڲ�����	arr���Զ���װֵ��
//							psc��ʱ��Ԥ��Ƶ��
//							��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft(��λS).
//							Ft=��ʱ������Ƶ��,��λ:Mhz
//							
//	���ز�����	��
//
//	˵����		
//==========================================================
void TIM2_PWM_Init(uint16_t psc,uint16_t arr)
{  
    TIM2_Handler.Instance=TIM2;         								//��ʱ��2
    TIM2_Handler.Init.Prescaler=psc;       							//��ʱ����Ƶ
    TIM2_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;		//���ϼ���ģʽ
    TIM2_Handler.Init.Period=arr;          							//�Զ���װ��ֵ
    TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM2_Handler);       							//��ʼ��PWM
    
    TIM2_CH2Handler.OCMode=TIM_OCMODE_PWM1; 						//ģʽѡ��PWM1
    TIM2_CH2Handler.Pulse=0;           	 								//���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
    TIM2_CH2Handler.OCPolarity=TIM_OCPOLARITY_LOW; 			//����Ƚϼ���Ϊ�� 
    HAL_TIM_PWM_ConfigChannel(&TIM2_Handler,&TIM2_CH2Handler,TIM_CHANNEL_2);//����TIM2ͨ��2 

		HAL_TIM_PWM_Start(&TIM2_Handler,TIM_CHANNEL_2);			//����PWMͨ��2 
		TIM2->CCR2=9680; 																		//��ʼ����PM2.5
}

//==========================================================
//	�������ƣ�	HAL_TIM_PWM_MspInit
//
//	�������ܣ�	��ʱ���ײ�������ʱ��ʹ�ܣ���������
//							�˺����ᱻHAL_TIM_PWM_Init()����
//
//	��ڲ�����	htim:��ʱ�����
//							
//	���ز�����	��
//
//	˵����		
//==========================================================
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef GPIO_Initure;
	
  if(htim->Instance==TIM2)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();						//ʹ�ܶ�ʱ��2
		__HAL_RCC_GPIOA_CLK_ENABLE();						//����GPIOAʱ��
		
		GPIO_Initure.Pin=GPIO_PIN_1;          	//PA1
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;  		//�����������
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_LOW; //����
		
		HAL_GPIO_Init(GPIOA,&GPIO_Initure); 
	}
}

//==========================================================
//	�������ƣ�	TIM_SetTIM4Compare2
//
//	�������ܣ�	����TIM2ͨ��2��ռ�ձ�
//
//	��ڲ�����	compare:�Ƚ�ֵ
//							
//	���ز�����	��
//
//	˵����		
//==========================================================
void TIM_SetTIM2Compare2(uint32_t compare)
{
	TIM2->CCR2=compare; 
}













































