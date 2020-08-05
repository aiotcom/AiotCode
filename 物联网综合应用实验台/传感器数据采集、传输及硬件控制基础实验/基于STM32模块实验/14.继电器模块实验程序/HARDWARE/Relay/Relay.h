#ifndef __Relay_H
#define __Relay_H

#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

#define 	RELAY1_PORT 		GPIOA
#define 	RELAY2_PORT 		GPIOA

#define 	RELAY1_PIN 			GPIO_PIN_10
#define 	RELAY2_PIN 			GPIO_PIN_9

#define  RELAY1_OPEN()  	HAL_GPIO_WritePin(RELAY1_PORT, RELAY1_PIN, GPIO_PIN_SET); 		//RL1����
#define  RELAY1_CLOSE()   HAL_GPIO_WritePin(RELAY1_PORT, RELAY1_PIN, GPIO_PIN_RESET);	  //RL1�ر�

#define  RELAY2_OPEN()  	HAL_GPIO_WritePin(RELAY2_PORT, RELAY2_PIN, GPIO_PIN_SET);  		//RL2����
#define  RELAY2_CLOSE()   HAL_GPIO_WritePin(RELAY2_PORT, RELAY2_PIN, GPIO_PIN_RESET);  	//RL2�ر�

void Relay_Config(uint8_t fag0);  //���Ƽ̵�������

void Relay_Init(void);  //�̵�����ʼ��

#endif /*__Bsp_Relay_H */


