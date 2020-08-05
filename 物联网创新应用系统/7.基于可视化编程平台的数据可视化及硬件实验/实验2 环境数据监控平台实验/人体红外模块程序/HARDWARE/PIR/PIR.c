#include "PIR.h"
#include "delay.h"
#include "stm32f1xx.h"

uint8_t PIR_Sta[2];	//�������״̬

//==========================================================
//	�������ƣ�	PIR_Init()
//
//	�������ܣ�	��������ʼ������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void PIR_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOA_CLK_ENABLE();           //����GPIOAʱ��

    GPIO_Initure.Pin=PIR_PIN;	
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLUP;        	//����
    GPIO_Initure.Speed=GPIO_SPEED_LOW;     	//����
    HAL_GPIO_Init(PIR_PORT,&GPIO_Initure);
	
		GPIO_Initure.Pin=PIR_LED_PIN;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Initure.Pull=GPIO_PULLUP;          	//����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;    	 	//����
    HAL_GPIO_Init(PIR_LED_PORT,&GPIO_Initure);
}



