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
//	�������ƣ�	LED_Twinkle
//
//	�������ܣ�	LED����˸
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void LED_Twinkle(void)
{
	LED_ON();delay_ms(200);LED_OFF();delay_ms(200);
	LED_ON();delay_ms(200);LED_OFF();delay_ms(200);
	LED_ON();delay_ms(200);LED_OFF();
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
	static uint8_t Time_Flag = 1;		//ִ�б�־λ
	static uint16_t Time_Count = 0;	//����ֵ
	
	switch(Time_Flag)
	{
		case 1://����LED1
			LED1_ON();
			delay_ms(1);
			Time_Count++;
		
			if(Time_Count>=time)
			{
				LED1_OFF();
				Time_Flag = 2;
				Time_Count = 0;
			}
			break;
		case 2://����LED2
			LED2_ON();
			delay_ms(1);
			Time_Count++;
		
			if(Time_Count>=time)
			{
				LED2_OFF();
				Time_Flag = 3;
				Time_Count = 0;
			}
			break;
		case 3://����LED3
			LED3_ON();
			delay_ms(1);
			Time_Count++;
		
			if(Time_Count>=time)
			{
				LED3_OFF();
				Time_Flag = 4;
				Time_Count = 0;
			}
			break;
		case 4://����LED4
			LED4_ON();
			delay_ms(1);
			Time_Count++;
		
			if(Time_Count>=time)
			{
				LED4_OFF();
				Time_Flag = 1;
				Time_Count = 0;
			}
			break;
		default: break;
	}
}

