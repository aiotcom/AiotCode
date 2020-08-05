#include "Relay.h"

//==========================================================
//	�������ƣ�	Relay_Init
//
//	�������ܣ�	��ʼ��485
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Relay_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOA_CLK_ENABLE();           				//����GPIOAʱ��
	
		GPIO_Initure.Pin = RELAY1_PIN | RELAY2_PIN;			//PA3 PA2
		GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;				//�������
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW; 			//����
		HAL_GPIO_Init(RELAY1_PORT, &GPIO_Initure);
	
		RELAY1_CLOSE();RELAY2_CLOSE(); //��ʼ���رռ̵���
}


//==========================================================
//	�������ƣ�	Relay_Config
//
//	�������ܣ�	���ؼ̵���
//
//	��ڲ�����	1(��)  0(��)
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Relay_Config(uint8_t fag0)
{
	HAL_Delay(10);
	if(fag0){
			RELAY1_OPEN();	 //�򿪼̵���1
			RELAY2_OPEN();	 //�򿪼̵���2
	}
	else{
			RELAY1_CLOSE();  //�رռ̵���1
			RELAY2_CLOSE();  //�رռ̵���2
	}
}



