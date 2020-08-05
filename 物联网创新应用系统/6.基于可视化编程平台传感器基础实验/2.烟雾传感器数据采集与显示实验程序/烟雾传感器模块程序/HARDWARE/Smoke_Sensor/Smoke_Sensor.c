#include "Smoke_Sensor.h"
#include "stm32f1xx.h"
#include "delay.h"

//==========================================================
//	�������ƣ�	Smoke_Sensor_Init()
//
//	�������ܣ�	����������ʼ������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void Smoke_Sensor_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();           //����GPIOAʱ��
    
    GPIO_Initure.Pin=Smoke_PIN;    					//PA2
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLDOWN;        //����
    GPIO_Initure.Speed=GPIO_SPEED_LOW;     	//����
    HAL_GPIO_Init(Smoke_PORT,&GPIO_Initure);
}



