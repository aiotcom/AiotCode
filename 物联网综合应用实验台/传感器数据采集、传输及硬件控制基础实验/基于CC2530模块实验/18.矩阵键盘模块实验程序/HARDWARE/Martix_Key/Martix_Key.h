#ifndef __Martix_Key_H
#define __Martix_Key_H

#include <ioCC2530.h>
#include "delay.h"

/*
*	�������--1��
*	1��   ��Enter��1��4��7
*	2��   ��0��2��5��8
*	3��   ��Canel��3��6��9
*	Right��	��Right��Left��Down��UP
*/
#define	WKEY_1_PIN			P1_4
#define	WKEY_2_PIN			P1_5
#define	WKEY_3_PIN			P1_7
#define	WKEY_Right_PIN			P1_6

#define	WKEY_1_Hight()			WKEY_1_PIN = 1
#define	WKEY_1_Low()			WKEY_1_PIN = 0

#define	WKEY_2_Hight()			WKEY_2_PIN = 1
#define	WKEY_2_Low()			WKEY_2_PIN = 0

#define	WKEY_3_Hight()			WKEY_3_PIN = 1
#define	WKEY_3_Low()			WKEY_3_PIN = 0

#define	WKEY_Right_Hight()	        WKEY_Right_PIN = 1
#define	WKEY_Right_Low()		WKEY_Right_PIN = 0

#define WKEY_All_Hight()		WKEY_1_Hight();WKEY_2_Hight();WKEY_3_Hight();WKEY_Right_Hight() //ȫ������
#define WKEY_All_Low()			WKEY_1_Low();WKEY_2_Low();WKEY_3_Low();WKEY_Right_Low()	        //ȫ������

/*
*	������ȡ--1��
*	UP��	��UP��7��8��9
*	Down��	��Down��4��5��6
*	Left��	��Left��1��2��3
*	Right��	��Right��Enter��0��Canel
*/
#define	RKEY_Up_PIN			P0_0
#define	RKEY_Down_PIN			P1_2
#define	RKEY_Left_PIN			P0_2
#define	RKEY_Right_PIN			P0_3

#define	RKEY_Up_Read()			RKEY_Up_PIN
#define	RKEY_Down_Read()		RKEY_Down_PIN
#define	RKEY_Left_Read()		RKEY_Left_PIN
#define	RKEY_Right_Read()	        RKEY_Right_PIN

extern uint16_t Key_value;
extern void KEY_ConFig(void); //��ȡ����
extern void KEY_Init(void);  	//��ʼ����������

#endif




