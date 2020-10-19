#ifndef __USART_H
#define __USART_H 			   

#include <ioCC2530.h>
#include "delay.h"

extern uint32_t USART0_RX_STA;       //���ڽ��ձ�־λ
extern uint8_t USART0_RX_BUF[200];   //���ڽ�������

extern void Init_Uart0();
extern void UR0SendByte(unsigned char dat);
extern void UR0SendString(unsigned char *str);

#endif

