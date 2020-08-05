#include "Stepper_Motor.h"
#include "delay.h"

//==========================================================
//	�������ƣ�	Stepper_Motor_Init()
//
//	�������ܣ�	���������ʼ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void Stepper_Motor_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  GPIO_InitStruct.Pin = A0_PIN|A1_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = B0_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	 GPIO_InitStruct.Pin = B1_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	
	A1LOW();A0LOW();B1LOW();B0LOW();		//��ʼ������
}

//==========================================================
//	�������ƣ�	Stepper_Motor_Set()
//
//	�������ܣ�	���ò������ת������
//
//	��ڲ�����	A1:	A+
//							A0:	A-
//							B1:	B+
//							B0:	B-
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Stepper_Motor_Set(uint8_t A1,uint8_t A0,uint8_t B1,uint8_t B0)
{
	A1==1?A1HIGH():A1LOW();
	A0==1?A0HIGH():A0LOW();	
	B1==1?B1HIGH():B1LOW();
	B0==1?B0HIGH():B0LOW();
}

//==========================================================
//	�������ƣ�	Stepper_Motor_Turn()
//
//	�������ܣ�	���ò������ת��
//
//	��ڲ�����	Direction:		��ת���� 1��˳ʱ��  0����ʱ��
//							Cycle_Number��ת��Ȧ��
//							Delay: 				תһȦ��ʱ(ms)
//
//	���ز�����	��
//
//	˵����			angle
//==========================================================
void Stepper_Motor_Turn(uint8_t Direction,uint16_t Cycle_Number,uint16_t Delay)
{
	static uint32_t i = 0;
	static uint16_t Time = 0;
	
	if(Delay>=40)
		Time = Delay/20;
	else
		Time = 2;
	
	if(Direction)
	{
		for(i=0;i<(Cycle_Number*5);i++)
		{
			Stepper_Motor_Set(1,0,0,0);		//��һ��
			delay_ms(Time);

			Stepper_Motor_Set(0,0,1,0);		//�ڶ���
			delay_ms(Time);

			Stepper_Motor_Set(0,1,0,0);		//������
			delay_ms(Time);

			Stepper_Motor_Set(0,0,0,1);		//������
			delay_ms(Time);
		}
	}
	else
	{
		for(i=0;i<(Cycle_Number*5);i++)
		{
			Stepper_Motor_Set(0,0,0,1);		//��һ��
			delay_ms(Time);

			Stepper_Motor_Set(0,1,0,0);		//�ڶ���
			delay_ms(Time);

			Stepper_Motor_Set(0,0,1,0);		//������
			delay_ms(Time);

			Stepper_Motor_Set(1,0,0,0);		//������
			delay_ms(Time);
		}
	}
	A1LOW();A0LOW();B1LOW();B0LOW();	//��ʼ������
}


