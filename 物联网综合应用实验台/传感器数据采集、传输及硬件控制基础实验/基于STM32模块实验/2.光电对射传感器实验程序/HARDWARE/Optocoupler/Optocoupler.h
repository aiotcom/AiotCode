#ifndef _Optocoupler_H
#define _Optocoupler_H

#include "stm32f7xx_hal.h"
#include "stm32f7xx.h"

#define 	Op_Switch_PORT 			GPIOG
#define 	Op_State_PORT 			GPIOA

#define 	Optocoupler_Switch 	GPIO_PIN_12
#define 	Optocoupler_State 	GPIO_PIN_6

#define 	Optocoupler_State_Read()   	HAL_GPIO_ReadPin(Op_State_PORT,Optocoupler_State)  //��ȡ��紫����״̬

#define 	Optocoupler_Switch_ON()			HAL_GPIO_WritePin(Op_Switch_PORT,Optocoupler_Switch,GPIO_PIN_RESET)	//������紫����
#define 	Optocoupler_Switch_OFF()		HAL_GPIO_WritePin(Op_Switch_PORT,Optocoupler_Switch,GPIO_PIN_SET)		//�رչ�紫����

extern void Optocoupler_Init(void);//��紫������ʼ��

#endif


