#ifndef __WiFi_H__
#define __WiFi_H__

#include "stm32f1xx_hal.h"

#define	CLOSE_TCP		 "+++"																						//�ر�TCP���ӣ��˳�͸��ģʽ
#define AT         	 "AT\r\n"
#define CWMODE     	 "AT+CWMODE=3\r\n"																//����ģʽΪAP+STA
#define RST        	 "AT+RST\r\n"																			//������ģ��
#define CIFSR        "AT+CIFSR\r\n"																		//��ѯIP��ַ
#define CWJAP        "AT+CWJAP=\"bacheng\",\"f0f0f0f0f0\"\r\n"				//����SID��PWD��������
#define TCP_CIPSTART "AT+CIPSTART=\"TCP\",\"103.46.128.41\",50196\r\n"	//����ΪTCPЭ�鴫�䲢ָ��IP�Ͷ˿ں�
#define CIPMODE      "AT+CIPMODE=1\r\n"																//͸��
#define CIPSEND      "AT+CIPSEND\r\n"																	//��ʼ����

extern uint8_t WiFi_AT_STA;    /*ATָ�����ɱ�־λ*/
void WiFi_Init(void);

#endif


