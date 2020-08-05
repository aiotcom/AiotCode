#ifndef __Rs485_H
#define __Rs485_H
#include "stm32f1xx_hal.h"

//ģʽ����
#define RS485_TX_EN		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_SET);	//485ģʽ���Ʒ���.
#define RS485_RX_EN		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_RESET);	//485ģʽ���ƽ���;

void RS485_Init(void);  //��ʼ��485
void RS485_Send(uint8_t *pdata,uint8_t len);
void RS485_Printf(uint8_t *pdata,uint32_t Data);
#endif

