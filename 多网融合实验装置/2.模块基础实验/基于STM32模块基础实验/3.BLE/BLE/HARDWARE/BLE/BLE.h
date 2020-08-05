#ifndef __BLE_H__
#define __BLE_H__

#include "stm32f1xx_hal.h"

#define	AT					"AT\r\n"
#define	TXPW				"AT+TXPW0\r\n"						//�����ź�ǿ��
#define	ROLE				"AT+ROLE1\r\n"						//��������1�����豸   0�����豸
#define	NAME 				"AT+NAMEBaCheng\r\n"			//�޸���������
#define	ADDR 				"AT+ADDR?\r\n"						//��ѯ����MAC��ַ
#define	CON 				"AT+CON987BF362C25D\r\n"	//���Ӹ�MAC��ַ�Ĵӻ�

extern uint8_t BLE_AT_STA;    /*ATָ�����ɱ�־λ*/
extern void BLE_Init(uint8_t MS);//������ʼ��

#endif


