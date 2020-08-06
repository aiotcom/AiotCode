#include "led.h"
#include "delay.h"
#include "stm32f1xx.h"

//==========================================================
//	�������ƣ�	LED_Init
//
//	�������ܣ�	LED�Ƴ�ʼ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOA_CLK_ENABLE();           	//����GPIOAʱ��
	
    GPIO_Initure.Pin=LED1_PIN|LED2_PIN|LED3_PIN|LED4_PIN;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Initure.Pull=GPIO_PULLUP;          	//����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;    	 	//����
    HAL_GPIO_Init(LED_PORT,&GPIO_Initure);
	
    LED_OFF();
}

//==========================================================
//	�������ƣ�	Water_Lamp
//
//	�������ܣ�	LED��ˮ��
//
//	��ڲ�����	time:������ˮ��ʱ����
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Water_Lamp(uint16_t time)
{
	LED1_ON();delay_ms(time);LED1_OFF();
	
	LED2_ON();delay_ms(time);LED2_OFF();
	
	LED3_ON();delay_ms(time);LED3_OFF();
	
	LED4_ON();delay_ms(time);LED4_OFF();
}


