#ifndef __Rs485_H
#define __Rs485_H
#include "stm32f1xx_hal.h"
#include "stdio.h"
#define Rs485_Printf(fmt,...)      Rs485_Config(1); HAL_Delay(10); printf(fmt,__VA_ARGS__); HAL_Delay(20); Rs485_Config(0);
//ģʽ����
#define RS485_TX_EN		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_SET);	//485ģʽ���Ʒ���.
#define RS485_RX_EN		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_RESET);	//485ģʽ���ƽ���;

void Rs485_Config(uint8_t fag); //����485����

void Rs485_Init(void);  //��ʼ��485

#endif

