#ifndef __WiFi_H__
#define __WiFi_H__

#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

#define	CLOSE_TCP		 "+++"																						//�ر�TCP���ӣ��˳�͸��ģʽ
#define AT         	 "AT\r\n"
#define CWMODE     	 "AT+CWMODE=3\r\n"																//����ģʽΪAP+STA
#define RST        	 "AT+RST\r\n"																			//������ģ��
#define CIFSR        "AT+CIFSR\r\n"																		//��ѯIP��ַ
#define CWJAP        "AT+CWJAP=\"bacheng\",\"f0f0f0f0f0\"\r\n"				//����SID��PWD��������
#define TCP_CIPSTART "AT+CIPSTART=\"TCP\",\"183.230.40.40\",1811\r\n"	//����ΪTCPЭ�鴫�䲢ָ��IP�Ͷ˿ں�
#define CIPMODE      "AT+CIPMODE=1\r\n"																//͸��
#define CIPSEND      "AT+CIPSEND\r\n"																	//��ʼ����
#define CIPSTATUS    "*238724#0001#sample*"														//ONE.NETƽ̨�����˺�ʶ����
#define 	WiFi_LED_GPIO_RCC_EN() 	__HAL_RCC_GPIOA_CLK_ENABLE()
#define 	WiFi_LED_PORT 					GPIOA
#define 	WiFi_LED_PIN 						GPIO_PIN_0

#define 	WiFi_KEY_GPIO_RCC_EN() 	__HAL_RCC_GPIOA_CLK_ENABLE()
#define 	WiFi_KEY_PORT 					GPIOA
#define 	WiFi_KEY_PIN						GPIO_PIN_3

#define 	WiFi_RST_GPIO_RCC_EN() 	__HAL_RCC_GPIOA_CLK_ENABLE()
#define 	WiFi_RST_PORT 					GPIOA
#define 	WiFi_RST_PIN 						GPIO_PIN_8

#define 	WiFi_LED_High() 				HAL_GPIO_WritePin(WiFi_LED_PORT,WiFi_LED_PIN,GPIO_PIN_SET)
#define 	WiFi_LED_Low() 					HAL_GPIO_WritePin(WiFi_LED_PORT,WiFi_LED_PIN,GPIO_PIN_RESET)

#define 	WiFi_RST_High() 				HAL_GPIO_WritePin(WiFi_RST_PORT,WiFi_RST_PIN,GPIO_PIN_SET)
#define 	WiFi_RST_Low() 					HAL_GPIO_WritePin(WiFi_RST_PORT,WiFi_RST_PIN,GPIO_PIN_RESET)

#define 	WiFi_KEY_Read()   			HAL_GPIO_ReadPin(WiFi_KEY_PORT,WiFi_KEY_PIN)  //����

#define RED 		0xFF00  			//���
#define GREEN 	0xFF0000  		//�̹�
#define BLUE 		0xFF  				//����
#define WHITE 	0xFFFFFF  		//�׹�
#define CUTDOWN 0		  				//�ر���ʾ

extern uint8_t WiFi_AT_STA;    /*ATָ�����ɱ�־λ*/

extern void WiFi_Init(void);
extern void WiFi_LED_Init(void);					//��ʼ��LED
extern void WiFi_RST_Init(void);					//��ʼ��RST
extern void WiFi_KEY_Init(void);					//��ʼ������
extern void WiFi_RGB_Set_UP(void);				//1��  850ns�ߵ�ƽ  400ns�͵�ƽ
extern void WiFi_RGB_Set_Down(void);			//0��  400ns�ߵ�ƽ  850ns�͵�ƽ
extern void WiFi_RGB_SET(uint32_t G8R8B8);//������ɫ
extern void WiFi_RGB_REST(void);					//���͵�ƽ�ȴ���һ������ 
extern void WiFi_RGB_User(uint8_t Num_Lig,uint32_t DELAY);

#endif


