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

#define USART1_REC_LEN  	200  												//�����������ֽ��� 200
#define EN_USART1_RX 			1														//ʹ�ܣ�1��/��ֹ��0������1����

extern uint8_t Temp;																	//�¶�����
extern uint8_t Humi;																	//ʪ������

extern unsigned char  USART1_RX_BUF[USART1_REC_LEN]; 	//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern unsigned int 	USART1_RX_STA;         					//����״̬���	
extern UART_HandleTypeDef UART1_Handler; 							//UART���

#define UART1_RXBUFFERSIZE   1 												//�����С
extern unsigned char UART1_RxBuffer[UART1_RXBUFFERSIZE];//HAL��USART����Buffer

uint8_t* WiFi_Send_Cmd(uint8_t *cmd,uint8_t *ack,uint16_t waittime);	//��WiFi��������
//����봮���жϽ��գ��벻Ҫע�����º궨��
extern void UART1_Init(int bound);				//����1��ʼ��
extern void USART1_IRQHand(void);					//����1�жϴ�����
extern void USART_Data_Send(void);				//�������ݷ��ͺ���
extern void USART1_Receive(uint8_t data);	//����1���ݽ���


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

