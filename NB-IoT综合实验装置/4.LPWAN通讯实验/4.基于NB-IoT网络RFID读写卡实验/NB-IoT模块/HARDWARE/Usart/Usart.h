#ifndef __USART_H
#define __USART_H
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"

#define UART1  1
#define UART2  1

#if UART1

#define USART1_REC_LEN  			200  											//�����������ֽ��� 200
#define EN_USART1_RX 					1													//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern unsigned char  USART1_RX_BUF[USART1_REC_LEN]; 		//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern unsigned int USART1_RX_STA;         							//����״̬���	
extern UART_HandleTypeDef UART1_Handler; 								//UART���

#define UART1_RXBUFFERSIZE   1 													//�����С
extern unsigned char UART1_RxBuffer[UART1_RXBUFFERSIZE];//HAL��USART����Buffer

extern void USART1_IRQHand(void); 	//����1������
extern void UART1_Init(int bound);	//����1��ʼ��
extern void USART_Data_Send(void);	//�������ݷ��ͺ���

#endif


#if UART2

#define EN_USART2_RX   1
#define USART2_RECV_BUFFER_LENGTH 100	  	
extern uint8_t USART2_RecvBuffer[ ];
extern uint16_t USART2_RecvIndex;

extern UART_HandleTypeDef UART2_Handler; 	//UART���

//����봮���жϽ��գ��벻Ҫע�����º궨��
void UART2_Init(int bound);
void USART2_SendBytes(char *pdata,uint16_t lenght);

#endif

#endif

