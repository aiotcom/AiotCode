#ifndef __USART_H
#define __USART_H
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

#define UART1  	1
#define USART7  1

#if UART1

#define EN_USART1_RX   1
#define USART1_RECV_BUFFER_LENGTH 100	  	
extern uint8_t USART1_RecvBuffer[ ];
extern uint16_t USART1_RecvIndex;

extern UART_HandleTypeDef UART1_Handler; 	//UART���

//����봮���жϽ��գ��벻Ҫע�����º궨��
extern void UART1_Init(int bound);

#endif

#if USART7

#define USART7_REC_LEN  	200  			//�����������ֽ��� 200
#define EN_USART7_RX 			1					//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern unsigned char  USART7_RX_BUF[USART7_REC_LEN]; 	//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern unsigned int USART7_RX_STA;        //����״̬���	
extern UART_HandleTypeDef UART7_Handler; 	//UART���

#define UART7_RXBUFFERSIZE   1 						//�����С
extern unsigned char UART7_RxBuffer[UART7_RXBUFFERSIZE];			//HAL��USART����Buffer

//����봮���жϽ��գ��벻Ҫע�����º궨��
extern void USART7_IRQHand(void);
extern void UART7_Init(int bound);
extern void USART7_Data_Send(void);

#endif


#endif

