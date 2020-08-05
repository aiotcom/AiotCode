#ifndef __Ble_H
#define __Ble_H

#include <ioCC2530.h>
#include "delay.h"

#define	AT		"AT\r\n"
#define	TXPW		"AT+TXPW0\r\n"		//�����ź�ǿ��
#define	ROLE		"AT+ROLE0\r\n"		//��������1�����豸   0�����豸
#define	NAME 		"AT+NAMEBaCheng\r\n"	//�޸���������
#define	ADDR 		"AT+ADDR?\r\n"		//��ѯ����MAC��ַ
#define	CON 		"AT+CON987BF362C25D\r\n"//���Ӹ�MAC��ַ�Ĵӻ�

extern uint8_t BLE_AT_STA;    /*ATָ�����ɱ�־λ*/
extern void BLE_Init(uint8_t MS);//������ʼ��

#endif

