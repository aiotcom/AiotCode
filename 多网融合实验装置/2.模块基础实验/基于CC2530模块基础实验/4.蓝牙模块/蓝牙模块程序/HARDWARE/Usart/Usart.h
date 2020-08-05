#ifndef __USART_H
#define __USART_H
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include <ioCC2530.h>
#include "delay.h"

extern uint8_t USART0_RX_STA;
extern uint8_t USART0_RX_BUF[200];

extern void Init_Uart0();                     //����0��ʼ��
extern void UR0SendByte(unsigned char dat);   //����0���͵��ֽ�
extern void UR0SendString(unsigned char *str);//����0�����ַ���
extern uint8_t* ble_send_cmd(uint8_t *cmd,uint8_t *ack,uint16_t waittime);

#endif



