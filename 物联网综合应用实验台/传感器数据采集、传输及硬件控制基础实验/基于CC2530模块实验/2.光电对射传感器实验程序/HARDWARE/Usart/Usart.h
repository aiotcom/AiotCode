#ifndef __USART_H
#define __USART_H
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include <ioCC2530.h>
#include "delay.h"

#define UART0  0
#define UART1  1

#if UART0

#define USART0_REC_LEN          200  		        //�����������ֽ��� 200

extern unsigned char WiFi_AT_STA;                       //WiFi��ʼ����ɱ�־λ
extern unsigned char  USART0_RX_BUF[USART0_REC_LEN]; 	//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern unsigned int   USART0_RX_STA;         		//����״̬���	

extern void USRT0_Init(void);                           //����0��ʼ��
extern void USART0_IRQHand(void); 	                //����0������
extern void USART0_Receive(uint8_t data);               //����0���մ���
extern void USART0_SendByte(unsigned char dat);         //����0���͵��ֽ�
extern void USART0_SendString(unsigned char *str,uint16_t Len);            //����0�����ַ���
extern uint8_t* WiFi_Send_Cmd(uint8_t *cmd,uint8_t *ack,uint16_t waittime);//��WiFi��������
#endif


#if UART1

#define USART1_REC_LEN          200  		        //�����������ֽ��� 200

extern unsigned char  USART1_RX_BUF[USART1_REC_LEN]; 	//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern unsigned int   USART1_RX_STA;         		//����״̬���

extern void USRT1_Init(void);                           //����1��ʼ��
extern void USART1_IRQHand(void); 	                //����1������
extern void USART_Data_Send(void);                      //�������ݷ��ͺ���
extern void USART1_SendByte(unsigned char dat);         //����1���͵��ֽ�
extern void USART1_SendString(unsigned char *str,uint16_t Len);             //����1�����ַ���

#endif

#endif



