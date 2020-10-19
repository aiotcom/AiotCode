#include "Platform_RGB_LED.h"
//==========================================================
//	�������ƣ�	Platform_RGB_LED_Init(void)
//
//	�������ܣ�	��ʼ��������RGB LED�ƵĿ���IO,PB3��PB4��PB15�����������ƽռ�ձ�Ϊ50%������Ϊ1s��
//              �ú�����systick�жϴ������е��á�
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Platform_RGB_LED_Init(void)
{    
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_AFIO_CLK_ENABLE();	
    __HAL_AFIO_REMAP_SWJ_NOJTAG(); 

    __HAL_RCC_GPIOB_CLK_ENABLE();           	                //����GPIOBʱ��
    __HAL_RCC_GPIOA_CLK_ENABLE();           	                //����GPIOBʱ��

    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;  	                //�������
    GPIO_Initure.Pull  = GPIO_PULLUP;          	                //����
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;    	 	            //����

    GPIO_Initure.Pin   = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_15; 	//PB3,PB4
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);

    GPIO_Initure.Pin   = GPIO_PIN_15; 	                        //PA15 	 	            
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);

    ////PB3,PB4,PA15 ��1��Ĭ�ϳ�ʼ������� 
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_15,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15                      ,GPIO_PIN_SET);        
}
//==========================================================
//	�������ƣ�	Platform_RGB_LED_Red(void)
//
//	�������ܣ�	�������� ��Ϊ��ɫ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Platform_RGB_LED_Green(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 ,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);
}
//==========================================================
//	�������ƣ�	Platform_RGB_LED_Red(void)
//
//	�������ܣ�	�������� ��Ϊ��ɫ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Platform_RGB_LED_Red(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3            ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4|GPIO_PIN_15,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15           ,GPIO_PIN_SET);    
}
//==========================================================
//	�������ƣ�	Platform_RGB_LED_Red(void)
//
//	�������ܣ�	�������� ��Ϊ��ɫ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Platform_RGB_LED_Blue(void)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15          ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3|GPIO_PIN_4,GPIO_PIN_SET);    
}
//==========================================================
//	�������ƣ�	void Platform_RGB_LED_Blackout(void)
//
//	�������ܣ�	�������� ��Ϊ��ɫ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Platform_RGB_LED_Blackout(void)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15          ,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3|GPIO_PIN_4,GPIO_PIN_SET);    
}
