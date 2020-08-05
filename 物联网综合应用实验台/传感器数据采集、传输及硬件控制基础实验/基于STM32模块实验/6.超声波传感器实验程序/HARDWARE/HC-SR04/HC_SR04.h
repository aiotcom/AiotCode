#ifndef __HC_SR04_H
#define __HC_SR04_H 			   

#include "stm32f7xx_hal.h"
#include "stm32f7xx.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#define  	HCSR04_GPIO_PORT1  	GPIOA
#define  	HCSR04_GPIO_PORT2  	GPIOA
#define  	HCSR04_GPIO_PORT3  	GPIOA

#define  	HCSR04_GPIOT_PORT4  GPIOG
#define  	HCSR04_GPIOE_PORT4  GPIOA

#define		Trigl1							GPIO_PIN_0
#define		Trigl2							GPIO_PIN_8		
#define		Trigl3							GPIO_PIN_15		
#define		Trigl4							GPIO_PIN_2		

#define		Echo1								GPIO_PIN_3		
#define		Echo2								GPIO_PIN_4
#define		Echo3								GPIO_PIN_5
#define		Echo4								GPIO_PIN_6	

#define 	Trigl1_HIGH()				HAL_GPIO_WritePin(HCSR04_GPIO_PORT1,Trigl1,GPIO_PIN_SET);
#define 	Trigl1_LOW()				HAL_GPIO_WritePin(HCSR04_GPIO_PORT1,Trigl1,GPIO_PIN_RESET);

#define 	Trigl2_HIGH()				HAL_GPIO_WritePin(HCSR04_GPIO_PORT2,Trigl2,GPIO_PIN_SET);
#define 	Trigl2_LOW()				HAL_GPIO_WritePin(HCSR04_GPIO_PORT2,Trigl2,GPIO_PIN_RESET);

#define 	Trigl3_HIGH()				HAL_GPIO_WritePin(HCSR04_GPIO_PORT3,Trigl3,GPIO_PIN_SET);
#define 	Trigl3_LOW()				HAL_GPIO_WritePin(HCSR04_GPIO_PORT3,Trigl3,GPIO_PIN_RESET);

#define 	Trigl4_HIGH()				HAL_GPIO_WritePin(HCSR04_GPIOT_PORT4,Trigl4,GPIO_PIN_SET);
#define 	Trigl4_LOW()				HAL_GPIO_WritePin(HCSR04_GPIOT_PORT4,Trigl4,GPIO_PIN_RESET);

#define 	Echo1_STATE()    		HAL_GPIO_ReadPin(HCSR04_GPIO_PORT1,Echo1)	//��ȡ���ص�ƽ
#define 	Echo2_STATE()    		HAL_GPIO_ReadPin(HCSR04_GPIO_PORT2,Echo2)	//��ȡ���ص�ƽ
#define 	Echo3_STATE()    		HAL_GPIO_ReadPin(HCSR04_GPIO_PORT3,Echo3)	//��ȡ���ص�ƽ
#define 	Echo4_STATE()    		HAL_GPIO_ReadPin(HCSR04_GPIOE_PORT4,Echo4)//��ȡ���ص�ƽ

extern void HCSR04_Init(void); 											//��ʼ��������ģ��
extern void HCSR04_StartMeasure(uint8_t Num);				//������ģ����

#endif

