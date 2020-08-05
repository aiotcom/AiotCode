#ifndef __SW420_H
#define __SW420_H 			   

#include "stm32f1xx_hal.h" 
#include "stm32f1xx.h"

#define  	SW420_GPIO_PORT  		GPIOA

#define		SW420_OUT0					GPIO_PIN_0			//�����0
#define		SW420_OUT1					GPIO_PIN_1			//�����1

#define 	SW420_OUT0_STATE()  HAL_GPIO_ReadPin(SW420_GPIO_PORT,SW420_OUT0)	//��ȡ�����0
#define 	SW420_OUT1_STATE()  HAL_GPIO_ReadPin(SW420_GPIO_PORT,SW420_OUT1)	//��ȡ�����1

extern uint8_t SW420_fig;
extern uint8_t Shock_Fre[];			//��Ƶ��
extern void SW420_Init(void); 	//�𶯴�������ʼ��
extern void SW420_Fig(void);		//�𶯼��

#endif


