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

#define USART1_REC_LEN  			200  											//定义最大接收字节数 200
#define EN_USART1_RX 					1													//使能（1）/禁止（0）串口1接收
	  	
extern uint16_t Command_LED,Command_Relay,Command;			//控制LED、继电器命令码
extern unsigned char  USART1_RX_BUF[USART1_REC_LEN]; 		//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern unsigned int USART1_RX_STA;         							//接收状态标记	
extern UART_HandleTypeDef UART1_Handler; 								//UART句柄

#define UART1_RXBUFFERSIZE   1 													//缓存大小
extern unsigned char UART1_RxBuffer[UART1_RXBUFFERSIZE];//HAL库USART接收Buffer

extern void USART1_IRQHand(void); 	//串口1服务函数
extern void UART1_Init(int bound);	//串口1初始化
extern void USART_Data_Send(void);	//串口数据发送函数

#endif


#if UART2

//#define USART2_REC_LEN  	200  												//定义最大接收字节数 200
//#define EN_USART2_RX 			1														//使能（1）/禁止（0）串口1接收

//extern unsigned char  USART2_RX_BUF[USART2_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
//extern unsigned int 	USART2_RX_STA;         					//接收状态标记	
//extern UART_HandleTypeDef UART2_Handler; 							//UART句柄

//#define UART2_RXBUFFERSIZE   1 												//缓存大小
//extern unsigned char UART2_RxBuffer[UART2_RXBUFFERSIZE];//HAL库USART接收Buffer


//uint8_t* WiFi_Send_Cmd(uint8_t *cmd,uint8_t *ack,uint16_t waittime);	//向WiFi发送命令
////如果想串口中断接收，请不要注释以下宏定义
//extern void USART2_IRQHand(void);											//串口二中断处理函数
//extern void UART2_Init(int bound);					//串口2初始化
//extern void USART2_Receive(uint8_t data);		//串口二数据接收
#define EN_USART2_RX   1
#define USART2_RECV_BUFFER_LENGTH 200	  	
extern uint8_t USART2_RecvBuffer[ ];
extern uint16_t USART2_RecvIndex;
extern unsigned int 	USART2_RX_STA;         	//接收状态标记	

extern UART_HandleTypeDef UART2_Handler; 			//UART句柄

//如果想串口中断接收，请不要注释以下宏定义
void UART2_Init(int bound);
extern void USART2_IRQHand(void);
void USART2_SendBytes(char *pdata,uint16_t lenght);

#endif

#endif

