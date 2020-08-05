#include "led.h"
#include "delay.h"
#include "timer.h"
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

//==========================================================
//	�������ƣ�	Water_Lamp_Time
//
//	�������ܣ�	LED��ˮ��
//
//	��ڲ�����	time:������ˮ��ʱ����
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void Water_Lamp_Time(uint16_t time)
{
	static uint8_t LED_Flag = 1;
	
	switch(LED_Flag)
	{
		case 1://����LED1
			LED1_ON();
			if(Time_Count>=time)
			{
				LED1_OFF();
				LED_Flag = 2;
				Time_Count = 0;
			}
			break;
		case 2://����LED2
			LED2_ON();
			if(Time_Count>=time)
			{
				LED2_OFF();
				LED_Flag = 3;
				Time_Count = 0;
			}
			break;
		case 3://����LED3
			LED3_ON();
			if(Time_Count>=time)
			{
				LED3_OFF();
				LED_Flag = 4;
				Time_Count = 0;
			}
			break;
		case 4://����LED4
			LED4_ON();
			if(Time_Count>=time)
			{
				LED4_OFF();
				LED_Flag = 1;
				Time_Count = 0;
			}
			break;
		default:break;
	}
}


