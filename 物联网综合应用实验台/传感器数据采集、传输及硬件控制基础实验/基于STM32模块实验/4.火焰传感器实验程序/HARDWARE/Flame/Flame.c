#include "Flame.h"
#include "delay.h"

//==========================================================
//	�������ƣ�	Flame_Init()
//
//	�������ܣ�	������ʼ������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Flame_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOA_CLK_ENABLE();           //����GPIOAʱ��
    
    GPIO_Initure.Pin=Flame1_PIN|Flame2_PIN;
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Speed=GPIO_SPEED_LOW;     	//����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
}




