#ifndef _TIMER_H
#define _TIMER_H
#include "stm32f1xx.h"

extern uint8_t RFID_Data[];
extern uint16_t Command_Relay,Command_KEY,Command;	//���Ƽ̵��������롢���հ���ֵ�����롢����RFID����������
extern uint32_t Task_Count;								//��ʱ�������ֵ
extern TIM_HandleTypeDef TIM2_Handler;  	//��ʱ����� 
void TIM2_Init(unsigned int arr,unsigned int psc);

#endif

