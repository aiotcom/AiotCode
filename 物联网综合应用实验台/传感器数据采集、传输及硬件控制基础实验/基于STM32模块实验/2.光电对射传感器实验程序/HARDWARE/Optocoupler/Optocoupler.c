#include "Optocoupler.h"
#include "delay.h"

//==========================================================
//	�������ƣ�	Optocoupler_Init()
//
//	�������ܣ�	��紫������ʼ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Optocoupler_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();           //����GPIOAʱ��
		__HAL_RCC_GPIOG_CLK_ENABLE();           //����GPIOGʱ��
    
    GPIO_Initure.Pin=Optocoupler_State;    	//Optocoupler_State
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLDOWN;        //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(Op_State_PORT,&GPIO_Initure);

	  GPIO_Initure.Pin=Optocoupler_Switch; 		//Optocoupler_Switch
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;    	//����
    HAL_GPIO_Init(Op_Switch_PORT,&GPIO_Initure);
	
		Optocoupler_Switch_ON();//��ʼ��������紫����
}





