#include "stm32f1xx_hal.h"
//==========================================================
//	�������ƣ�	static void delay(uint32_t n) 
//
//	�������ܣ�	WS2812B ���ƹ����е���ʱ����
//
//	��ڲ�����	n,��ʱ��λʱ��
//              
//	���ز�����	��
//
//	˵����	��	
//==========================================================
static void delay(uint32_t delay)   
{
    int i=0;
    for(i = 0;i<delay;i++)
    {;}
}

//==========================================================
//	�������ƣ�	void RGB_Set_UP(void) 
//
//	�������ܣ�	���WS2812B �����źŸߵ�ƽ��1���ĵ��ź�
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����	/*  1��  850ns�ߵ�ƽ  400ns�͵�ƽ*/	
//==========================================================
void RGB_Set_UP(void)
{ 
	/*
			д�ߵ�ƽ
	*/
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
	/*
			д�͵�ƽ
	*/
		GPIOA->BRR = 0x80;
		GPIOA->BRR = 0x80;
		GPIOA->BRR = 0x80;
}
//==========================================================
//	�������ƣ�	void RGB_Set_UP(void) 
//
//	�������ܣ�	���WS2812B �����źŸߵ�ƽ��1���ĵ��ź�
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����	    /*  0��  400ns�ߵ�ƽ  850ns�͵�ƽ*/
//==========================================================
void RGB_Set_Down()
{
	/*
			д�ߵ�ƽ
	*/
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
		GPIOA->BSRR = 0x80;
	/*
			д�͵�ƽ
	*/
		GPIOA->BRR = 0x80;
		GPIOA->BRR = 0x80;
		GPIOA->BRR = 0x80;
		GPIOA->BRR = 0x80;
		GPIOA->BRR = 0x80;
		GPIOA->BRR = 0x80;
		GPIOA->BRR = 0x80;
		GPIOA->BRR = 0x80;
		GPIOA->BRR = 0x80;
		GPIOA->BRR = 0x80;
		GPIOA->BRR = 0x80;
		GPIOA->BRR = 0x80;
		GPIOA->BRR = 0x80;
		GPIOA->BRR = 0x80;
		GPIOA->BRR = 0x80;
		GPIOA->BRR = 0x80;
		GPIOA->BRR = 0x80;
}
//==========================================================
//	�������ƣ�	void RGB_REST(void)
//
//	�������ܣ�	WS2812B ��ʼ���ź�
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����	   
//==========================================================
void RGB_REST(void)
{
	GPIOA->BSRR = GPIO_PIN_7;
	delay(8000);  //��ʱ58us
}
//==========================================================
//	�������ƣ�	void WS2812B_SetColour(uint32_t G8R8B8)
//
//	�������ܣ�	����WS2812Bɫ��
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����	    /*  0��  400ns�ߵ�ƽ  850ns�͵�ƽ*/
//==========================================================
void WS2812B_SetColour(uint32_t G8R8B8)
{
	int byte = 0;
	int i = 0;
	for(i = 23;i>=0;i--)
	{
		byte = ((G8R8B8 >> i) & 0x01);
		if(byte == 1)
		{
			RGB_Set_UP();//1
		}
		else
		{
			RGB_Set_Down(); //0
		}
	}
}
//==========================================================
//	�������ƣ�	WS2812B_Init()
//
//	�������ܣ�	��ʼ��WS2812B�ϵĲʵƿ��ƹܽţ�����Ϊ�������
//
//	��ڲ�����	void
//              
//	���ز�����	��
//
//	˵����	��WS2812B �� λWIFIģ����	
//==========================================================
void WS2812B_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOA_CLK_ENABLE();              //����GPIOAʱ��

    GPIO_Initure.Pin   = GPIO_PIN_7;           //GPIO_PIN_6:WS2812B�ʵƿ��ƹܽš�
    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW;  //����
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);
    
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);//��ʼ��ƽ��Ϊ��
}


