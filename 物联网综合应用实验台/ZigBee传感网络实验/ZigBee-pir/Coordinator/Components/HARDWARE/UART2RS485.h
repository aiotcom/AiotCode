#ifndef __UART2RS485_H
#define __UART2RS485_H

#include "hal_types.h"
#define			Addr_Light						0x1001		//���մ�������ַ
#define			Addr_WS							0x1101		//��ʪ�ȴ�������ַ
#define			Addr_Motor						0x1201		//ֱ�������ַ
#define			Addr_Lock						0x1301		//�������ַ
#define			Addr_Siren						0x1401		//��������ַ
#define			Addr_Fan						0x1501		//���ȵ�ַ
#define         Addr_LED                        0x1601      //LED  
#define			Addr_PIR						0x1701		//�������
#define			Addr_NULL						0xFFFF		//�յ�ַ-�޶����ַʱ���ݴ���õ�ַ

void UART2RS485_Init(void);
#endif